/*
 * @brief Common PHY functions
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

#ifndef __LPC_PHY_H_
#define __LPC_PHY_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(ETH_PHY_SMSC87X0) && !defined(ETH_PHY_DP83848)
#define ETH_PHY_SMSC87X0
#endif

typedef void (*p_msDelay_func_t)(uint32_t);

/** @defgroup BOARD_PHY BOARD: Board specific PHY drivers
 * @ingroup BOARD_Common
 * The simple PHY function API provides simple non-blocking PHY status
 * monitoring and initialization support for various Ethernet PHYs.
 * To initialize the PHY, call lpc_phy_init() once. lpc_phy_init() requires
 * several standard functions from the MAC driver for interfacing to the
 * PHY via a MII link (Chip_ENET_StartMIIWrite(), Chip_ENET_IsMIIBusy(),
 * Chip_ENET_StartMIIRead(), and Chip_ENET_ReadMIIData()).
 *
 * Once initialized, just preiodically call the lpcPHYStsPoll() function
 * from the background loop or a thread and monitor the returned status
 * to determine if the PHY state has changed and the current PHY state.
 * @{
 */
#define PHY_LINK_ERROR     (1 << 0)	/*!< PHY status bit for link error */
#define PHY_LINK_BUSY      (1 << 1)	/*!< PHY status bit for MII link busy */
#define PHY_LINK_CHANGED   (1 << 2)	/*!< PHY status bit for changed state (not persistent) */
#define PHY_LINK_CONNECTED (1 << 3)	/*!< PHY status bit for connected state */
#define PHY_LINK_SPEED100  (1 << 4)	/*!< PHY status bit for 100Mbps mode */
#define PHY_LINK_FULLDUPLX (1 << 5)	/*!< PHY status bit for full duplex mode */

/**
 * @brief	Phy status update state machine
 * @return	An Or'ed value of PHY_LINK_* statuses
 * @note	This function can be called at any rate and will poll the the PHY status. Multiple
 * calls may be needed to determine PHY status.
 */
uint32_t lpcPHYStsPoll(void);

/**
 * @brief	Initialize the PHY
 * @param	rmii			: Initializes PHY for RMII mode if true, MII if false
 * @param	pDelayMsFunc	: Delay function (in mS) used for this driver
 * @return	PHY_LINK_ERROR or 0 on success
 * @note	This function initializes the PHY. It will block until complete. It will not
 * wait for the PHY to detect a connected cable and remain busy. Use lpcPHYStsPoll to
 * detect cable insertion.
 */
uint32_t lpc_phy_init(bool rmii, p_msDelay_func_t pDelayMsFunc);

/* Read from the PHY. Will block for delays based on the pDelayMs function. Returns
   true on success, or false on failure */
Status lpc_mii_read(uint8_t reg, uint16_t *data);

/* Write to the PHY. Will block for delays based on the pDelayMs function. Returns
   true on success, or false on failure */
Status lpc_mii_write(uint8_t reg, uint16_t data);
/**
 * @}
 */

/* LAN8720 PHY register offsets */
#define LAN8_BCR_REG        0x0	/*!< Basic Control Register */
#define LAN8_BSR_REG        0x1	/*!< Basic Status Reg */
#define LAN8_PHYID1_REG     0x2	/*!< PHY ID 1 Reg  */
#define LAN8_PHYID2_REG     0x3	/*!< PHY ID 2 Reg */
#define LAN8_PHYSPLCTL_REG  0x1F/*!< PHY special control/status Reg */

/* LAN8720 BCR register definitions */
#define LAN8_RESET          (1 << 15)	/*!< 1= S/W Reset */
#define LAN8_LOOPBACK       (1 << 14)	/*!< 1=loopback Enabled */
#define LAN8_SPEED_SELECT   (1 << 13)	/*!< 1=Select 100MBps */
#define LAN8_AUTONEG        (1 << 12)	/*!< 1=Enable auto-negotiation */
#define LAN8_POWER_DOWN     (1 << 11)	/*!< 1=Power down PHY */
#define LAN8_ISOLATE        (1 << 10)	/*!< 1=Isolate PHY */
#define LAN8_RESTART_AUTONEG (1 << 9)	/*!< 1=Restart auto-negoatiation */
#define LAN8_DUPLEX_MODE    (1 << 8)	/*!< 1=Full duplex mode */

/* LAN8720 BSR register definitions */
#define LAN8_100BASE_T4     (1 << 15)	/*!< T4 mode */
#define LAN8_100BASE_TX_FD  (1 << 14)	/*!< 100MBps full duplex */
#define LAN8_100BASE_TX_HD  (1 << 13)	/*!< 100MBps half duplex */
#define LAN8_10BASE_T_FD    (1 << 12)	/*!< 100Bps full duplex */
#define LAN8_10BASE_T_HD    (1 << 11)	/*!< 10MBps half duplex */
#define LAN8_AUTONEG_COMP   (1 << 5)	/*!< Auto-negotation complete */
#define LAN8_RMT_FAULT      (1 << 4)	/*!< Fault */
#define LAN8_AUTONEG_ABILITY (1 << 3)	/*!< Auto-negotation supported */
#define LAN8_LINK_STATUS    (1 << 2)	/*!< 1=Link active */
#define LAN8_JABBER_DETECT  (1 << 1)	/*!< Jabber detect */
#define LAN8_EXTEND_CAPAB   (1 << 0)	/*!< Supports extended capabilities */

/* LAN8720 PHYSPLCTL status definitions */
#define LAN8_SPEEDMASK      (7 << 2)	/*!< Speed and duplex mask */
#define LAN8_SPEED100F      (6 << 2)	/*!< 100BT full duplex */
#define LAN8_SPEED10F       (5 << 2)	/*!< 10BT full duplex */
#define LAN8_SPEED100H      (2 << 2)	/*!< 100BT half duplex */
#define LAN8_SPEED10H       (1 << 2)	/*!< 10BT half duplex */

/* LAN8720 PHY ID 1/2 register definitions */
#define LAN8_PHYID1_OUI     0x0007		/*!< Expected PHY ID1 */
#define LAN8_PHYID2_OUI     0xC0F0		/*!< Expected PHY ID2, except last 4 bits */


/** @brief  DP83848 PHY register offsets */
#define DP8_BMCR_REG        0x0	/*!< Basic Mode Control Register */
#define DP8_BMSR_REG        0x1	/*!< Basic Mode Status Reg */
#define DP8_ANADV_REG       0x4	/*!< Auto_Neg Advt Reg  */
#define DP8_ANLPA_REG       0x5	/*!< Auto_neg Link Partner Ability Reg */
#define DP8_ANEEXP_REG      0x6	/*!< Auto-neg Expansion Reg  */
#define DP8_PHY_STAT_REG    0x10/*!< PHY Status Register  */
#define DP8_PHY_INT_CTL_REG 0x11/*!< PHY Interrupt Control Register */
#define DP8_PHY_RBR_REG     0x17/*!< PHY RMII and Bypass Register  */
#define DP8_PHY_STS_REG     0x19/*!< PHY Status Register  */

/* DP83848 Control register definitions */
#define DP8_RESET          (1 << 15)	/*!< 1= S/W Reset */
#define DP8_LOOPBACK       (1 << 14)	/*!< 1=loopback Enabled */
#define DP8_SPEED_SELECT   (1 << 13)	/*!< 1=Select 100MBps */
#define DP8_AUTONEG        (1 << 12)	/*!< 1=Enable auto-negotiation */
#define DP8_POWER_DOWN     (1 << 11)	/*!< 1=Power down PHY */
#define DP8_ISOLATE        (1 << 10)	/*!< 1=Isolate PHY */
#define DP8_RESTART_AUTONEG (1 << 9)	/*!< 1=Restart auto-negoatiation */
#define DP8_DUPLEX_MODE    (1 << 8)		/*!< 1=Full duplex mode */
#define DP8_COLLISION_TEST (1 << 7)		/*!< 1=Perform collsion test */

/* DP83848 Status register definitions */
#define DP8_100BASE_T4     (1 << 15)	/*!< T4 mode */
#define DP8_100BASE_TX_FD  (1 << 14)	/*!< 100MBps full duplex */
#define DP8_100BASE_TX_HD  (1 << 13)	/*!< 100MBps half duplex */
#define DP8_10BASE_T_FD    (1 << 12)	/*!< 100Bps full duplex */
#define DP8_10BASE_T_HD    (1 << 11)	/*!< 10MBps half duplex */
#define DP8_MF_PREAMB_SUPPR (1 << 6)	/*!< Preamble suppress */
#define DP8_AUTONEG_COMP   (1 << 5)		/*!< Auto-negotation complete */
#define DP8_RMT_FAULT      (1 << 4)		/*!< Fault */
#define DP8_AUTONEG_ABILITY (1 << 3)	/*!< Auto-negotation supported */
#define DP8_LINK_STATUS    (1 << 2)		/*!< 1=Link active */
#define DP8_JABBER_DETECT  (1 << 1)		/*!< Jabber detect */
#define DP8_EXTEND_CAPAB   (1 << 0)		/*!< Supports extended capabilities */

/* DP83848 PHY RBR MII dode definitions */
#define DP8_RBR_RMII_MODE  (1 << 5)		/*!< Use RMII mode */

/* DP83848 PHY status definitions */
#define DP8_REMOTEFAULT    (1 << 6)		/*!< Remote fault */
#define DP8_FULLDUPLEX     (1 << 2)		/*!< 1=full duplex */
#define DP8_SPEED10MBPS    (1 << 1)		/*!< 1=10MBps speed */
#define DP8_VALID_LINK     (1 << 0)		/*!< 1=Link active */

/* DP83848 PHY ID register definitions */
#define DP8_PHYID1_OUI     0x2000		/*!< Expected PHY ID1 */
#define DP8_PHYID2_OUI     0x5c90		/*!< Expected PHY ID2 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC_PHY_H_ */
