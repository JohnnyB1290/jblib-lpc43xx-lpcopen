/*
 * @brief Mational DP83848 simple PHY driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"
#include "lpc_phy.h"

/** @defgroup DP83848_PHY	BOARD: PHY status and control driver for the DP83848
 * @ingroup BOARD_PHY
 * Various functions for controlling and monitoring the status of the
 * DP83848 PHY.
 * @{
 */

#ifdef ETH_PHY_DP83848

/* DP83848 PHY update flags */
static uint32_t physts, olddphysts;

/* PHY update counter for state machine */
static int32_t phyustate;

/* Pointer to delay function used for this driver */
static p_msDelay_func_t pDelayMs;

/* Write to the PHY. Will block for delays based on the pDelayMs function. Returns
   true on success, or false on failure */
Status lpc_mii_write(uint8_t reg, uint16_t data)
{
	Status sts = ERROR;
	int32_t mst = 250;

	/* Write value for register */
	Chip_ENET_StartMIIWrite(LPC_ETHERNET, reg, data);

	/* Wait for unbusy status */
	while (mst > 0) {
		if (Chip_ENET_IsMIIBusy(LPC_ETHERNET)) {
			mst--;
			pDelayMs(1);
		}
		else {
			mst = 0;
			sts = SUCCESS;
		}
	}

	return sts;
}

/* Read from the PHY. Will block for delays based on the pDelayMs function. Returns
   true on success, or false on failure */
Status lpc_mii_read(uint8_t reg, uint16_t *data)
{
	Status sts = ERROR;
	int32_t mst = 250;

	/* Start register read */
	Chip_ENET_StartMIIRead(LPC_ETHERNET, reg);

	/* Wait for unbusy status */
	while (mst > 0) {
		if (!Chip_ENET_IsMIIBusy(LPC_ETHERNET)) {
			mst = 0;
			*data = Chip_ENET_ReadMIIData(LPC_ETHERNET);
			sts = SUCCESS;
		}
		else {
			mst--;
			pDelayMs(1);
		}
	}

	return sts;
}

/* Update PHY status from passed value */
static void lpc_update_phy_sts(uint16_t linksts)
{
	/* Update link active status */
	if (linksts & DP8_VALID_LINK) {
		physts |= PHY_LINK_CONNECTED;
	}
	else {
		physts &= ~PHY_LINK_CONNECTED;
	}

	/* Full or half duplex */
	if (linksts & DP8_FULLDUPLEX) {
		physts |= PHY_LINK_FULLDUPLX;
	}
	else {
		physts &= ~PHY_LINK_FULLDUPLX;
	}

	/* Configure 100MBit/10MBit mode. */
	if (linksts & DP8_SPEED10MBPS) {
		physts &= ~PHY_LINK_SPEED100;
	}
	else {
		physts |= PHY_LINK_SPEED100;
	}

	/* If the status has changed, indicate via change flag */
	if ((physts & (PHY_LINK_SPEED100 | PHY_LINK_FULLDUPLX | PHY_LINK_CONNECTED)) !=
		(olddphysts & (PHY_LINK_SPEED100 | PHY_LINK_FULLDUPLX | PHY_LINK_CONNECTED))) {
		olddphysts = physts;
		physts |= PHY_LINK_CHANGED;
	}
}

/* Initialize the DP83848 PHY */
uint32_t lpc_phy_init(bool rmii, p_msDelay_func_t pDelayMsFunc)
{
	uint16_t tmp;
	int32_t i;

	pDelayMs = pDelayMsFunc;

	/* Initial states for PHY status and state machine */
	olddphysts = physts = phyustate = 0;

	/* Only first read and write are checked for failure */
	/* Put the DP83848C in reset mode and wait for completion */
	if (lpc_mii_write(DP8_BMCR_REG, DP8_RESET) != SUCCESS) {
		return ERROR;
	}
	i = 400;
	while (i > 0) {
		pDelayMs(1);
		if (lpc_mii_read(DP8_BMCR_REG, &tmp) != SUCCESS) {
			return ERROR;
		}

		if (!(tmp & (DP8_RESET | DP8_POWER_DOWN))) {
			i = -1;
		}
		else {
			i--;
		}
	}
	/* Timeout? */
	if (i == 0) {
		return ERROR;
	}

//#if 0
//	/* Setup link based on configuration options */
//#if PHY_USE_AUTONEG == 1
//	tmp = DP8_AUTONEG;
//#else
//	tmp = 0;
//#endif
//#if PHY_USE_100MBS == 1
//	tmp |= DP8_SPEED_SELECT;
//#endif
//#if PHY_USE_FULL_DUPLEX == 1
//	tmp |= DP8_DUPLEX_MODE;
//#endif

//#else
//	tmp = DP8_AUTONEG;
//#endif

//	lpc_mii_write(DP8_BMCR_REG, tmp);

//	/* Enable RMII mode for PHY */
//	if (rmii) {
//		lpc_mii_write(DP8_PHY_RBR_REG, DP8_RBR_RMII_MODE);
//	}

	/* The link is not set active at this point, but will be detected
	   later */

	return SUCCESS;
}

/* Phy status update state machine */
uint32_t lpcPHYStsPoll(void)
{
	switch (phyustate) {
	default:
	case 0:
		/* Read BMSR to clear faults */
		Chip_ENET_StartMIIRead(LPC_ETHERNET, DP8_PHY_STAT_REG);
		physts &= ~PHY_LINK_CHANGED;
		physts = physts | PHY_LINK_BUSY;
		phyustate = 1;
		break;

	case 1:
		/* Wait for read status state */
		if (!Chip_ENET_IsMIIBusy(LPC_ETHERNET)) {
			/* Update PHY status */
			physts &= ~PHY_LINK_BUSY;
			lpc_update_phy_sts(Chip_ENET_ReadMIIData(LPC_ETHERNET));
			phyustate = 0;
		}
		break;
	}

	return physts;
}

#endif

/**
 * @}
 */
