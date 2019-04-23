/*
 * @brief LPC43xx Serial GPIO driver
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

#ifndef __SGPIO_43XX_H_
#define __SGPIO_43XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SGPIO_43XX CHIP: LPC43xx Serial GPIO driver
 * @ingroup LPC_CHIP_18XX_43XX_Drivers
 * This module is present in LPC43xx MCUs only.
 * @{
 */

#if defined(CHIP_LPC43XX)

/**
 * @brief Serial GPIO register block structure
 */
typedef struct {						/*!< SGPIO Structure        */
	__IO uint32_t  OUT_MUX_CFG[16];		/*!< Pin multiplexer configurationregisters. */
	__IO uint32_t  SGPIO_MUX_CFG[16];	/*!< SGPIO multiplexer configuration registers. */
	__IO uint32_t  SLICE_MUX_CFG[16];	/*!< Slice multiplexer configuration registers. */
	__IO uint32_t  REG[16];				/*!< Slice data registers. Eachtime COUNT0 reaches 0x0 the register shifts loading bit 31 withdata captured from DIN(n). DOUT(n) is set to REG(0) */
	__IO uint32_t  REG_SS[16];			/*!< Slice data shadow registers. Each time POSreaches 0x0 the contents of REG_SS is exchanged with the contentof REG */
	__IO uint32_t  PRESET[16];			/*!< Reload valueof COUNT0, loaded when COUNT0 reaches 0x0 */
	__IO uint32_t  COUNT[16];			/*!< Down counter, counts down each clock cycle. */
	__IO uint32_t  POS[16];				/*!< Each time COUNT0 reaches 0x0 */
	__IO uint32_t  MASK_A;				/*!< Mask for pattern match function of slice A */
	__IO uint32_t  MASK_H;				/*!< Mask for pattern match function of slice H */
	__IO uint32_t  MASK_I;				/*!< Mask for pattern match function of slice I */
	__IO uint32_t  MASK_P;				/*!< Mask for pattern match function of slice P */
	__I  uint32_t  GPIO_INREG;			/*!< GPIO input status register */
	__IO uint32_t  GPIO_OUTREG;			/*!< GPIO output control register */
	__IO uint32_t  GPIO_OENREG;			/*!< GPIO OE control register */
	__IO uint32_t  CTRL_ENABLED;		/*!< Enables the slice COUNT counter */
	__IO uint32_t  CTRL_DISABLED;		/*!< Disables the slice COUNT counter */
	__I  uint32_t  RESERVED0[823];
	__O  uint32_t  CLR_EN_0;			/*!< Shift clock interrupt clear mask */
	__O  uint32_t  SET_EN_0;			/*!< Shift clock interrupt set mask */
	__I  uint32_t  ENABLE_0;			/*!< Shift clock interrupt enable */
	__I  uint32_t  STATUS_0;			/*!< Shift clock interrupt status */
	__O  uint32_t  CTR_STATUS_0;		/*!< Shift clock interrupt clear status */
	__O  uint32_t  SET_STATUS_0;		/*!< Shift clock interrupt set status */
	__I  uint32_t  RESERVED1[2];
	__O  uint32_t  CLR_EN_1;			/*!< Capture clock interrupt clear mask */
	__O  uint32_t  SET_EN_1;			/*!< Capture clock interrupt set mask */
	__I  uint32_t  ENABLE_1;			/*!< Capture clock interrupt enable */
	__I  uint32_t  STATUS_1;			/*!< Capture clock interrupt status */
	__O  uint32_t  CTR_STATUS_1;		/*!< Capture clock interrupt clear status */
	__O  uint32_t  SET_STATUS_1;		/*!< Capture clock interrupt set status */
	__I  uint32_t  RESERVED2[2];
	__O  uint32_t  CLR_EN_2;			/*!< Pattern match interrupt clear mask */
	__O  uint32_t  SET_EN_2;			/*!< Pattern match interrupt set mask */
	__I  uint32_t  ENABLE_2;			/*!< Pattern match interrupt enable */
	__I  uint32_t  STATUS_2;			/*!< Pattern match interrupt status */
	__O  uint32_t  CTR_STATUS_2;		/*!< Pattern match interrupt clear status */
	__O  uint32_t  SET_STATUS_2;		/*!< Pattern match interrupt set status */
	__I  uint32_t  RESERVED3[2];
	__O  uint32_t  CLR_EN_3;			/*!< Input interrupt clear mask */
	__O  uint32_t  SET_EN_3;			/*!< Input bit match interrupt set mask */
	__I  uint32_t  ENABLE_3;			/*!< Input bit match interrupt enable */
	__I  uint32_t  STATUS_3;			/*!< Input bit match interrupt status */
	__O  uint32_t  CTR_STATUS_3;		/*!< Input bit match interrupt clear status */
	__O  uint32_t  SET_STATUS_3;		/*!< Shift clock interrupt set status */
} LPC_SGPIO_T;

/* SGPIO slice definitions */
typedef enum SGPIO_Slice {
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	NUM_SGPIO_SLICES
} SGPIO_Slice;

/* SGPIO pin definitions */
typedef enum SGPIO_Pin {
	SGPIO_0 = 0,
	SGPIO_1,
	SGPIO_2,
	SGPIO_3,
	SGPIO_4,
	SGPIO_5,
	SGPIO_6,
	SGPIO_7,
	SGPIO_8,
	SGPIO_9,
	SGPIO_10,
	SGPIO_11,
	SGPIO_12,
	SGPIO_13,
	SGPIO_14,
	SGPIO_15,
	NUM_SGPIO_PIN
} SGPIO_Pin;

/* types of signals defined for the pin */
typedef enum SGPIO_PinFunction {
	SGPIO_INPUT_PIN,
	SGPIO_OUTPUT_PIN,
	SGPIO_INTERNAL
} SGPIO_PinFunction;

/******************************************************************************
 * SLICE_MUX_CFG register definitions
 *****************************************************************************/
typedef enum SMC_MatchMode {

	SMC_DONT_MATCH 		= 0x0,
	SMC_MMODE_DEFAULT 	= SMC_DONT_MATCH,
	SMC_MMODE_DONTCARE 	= SMC_DONT_MATCH,
	SMC_MATCH_DATA 		= 0x1

} SMC_MatchMode;

typedef enum SMC_ClkCaptureMode {

	SMC_CLKCAP_RISING 	= 0x0,
	SMC_CLKCAP_DEFAULT 	= SMC_CLKCAP_RISING,
	SMC_CLKCAP_DONTCARE = SMC_CLKCAP_RISING,
	SMC_CLKCAP_FALLING 	= 0x1

} SMC_ClkCaptureMode;

typedef enum SMC_ClkGenMode {

	SMC_CLKGEN_COUNTER 		= 0x0,
	SMC_CLKGEN_DEFAULT 		= SMC_CLKGEN_COUNTER,
	SMC_CLKGEN_DONTCARE 	= SMC_CLKGEN_COUNTER,
	SMC_CLKGEN_SLICE_OR_PIN = 0x1

} SMC_ClkGenMode;

typedef enum SMC_InvOutClk {

	SMC_INVOUT_NORMAL 	= 0x0,
	SMC_INVOUT_DEFAULT 	= SMC_INVOUT_NORMAL,
	SMC_INVOUT_DONTCARE = SMC_INVOUT_NORMAL,
	SMC_INVERTED 		= 0x1

} SMC_InvOutClk;

typedef	enum SMC_DataCapMode {

	SMC_DATACAP_RISING 		= 0x0,
	SMC_DATACAP_DEFAULT 	= SMC_DATACAP_RISING,
	SMC_DATACAP_DONTCARE 	= SMC_DATACAP_RISING,
	SMC_DATACAP_FALLING 	= 0x1,
	SMC_DATACAP_LOW 		= 0x2,
	SMC_DATACAP_HIGH 		= 0x3

} SMC_DataCapMode;

typedef	enum SMC_ParallelMode {

	SMC_PAR_1BPCK 		= 0x0,
	SMC_PAR_DEFAULT 	= SMC_PAR_1BPCK,
	SMC_PAR_DONTCARE 	= SMC_PAR_1BPCK,
	SMC_PAR_2BPCK 		= 0x1,
	SMC_PAR_4BPCK 		= 0x2,
	SMC_PAR_8BPCK 		= 0x3

} SMC_ParallelMode;

typedef enum SMC_InvQualifier {

	SMC_INVQUAL_NORMAL 		= 0x0,
	SMC_INVQUAL_DEFAULT 	= SMC_INVQUAL_NORMAL,
	SMC_INVQUAL_DONTCARE 	= SMC_INVQUAL_NORMAL,
	SMC_INVQUAL_INVERTED 	= 0x1

} SMC_InvQualifier;

/*****************************************************************************/

/******************************************************************************
 * SGPIO_MUX_CFG register definitions
 *****************************************************************************/

typedef enum MC_ExtClkEnable {

	MC_CLK_INTERNAL	= 0x0,
	MC_CLK_DEFAULT 	= MC_CLK_INTERNAL,
	MC_CLK_DONTCARE = MC_CLK_INTERNAL,
	MC_CLK_PIN 		= 0x1

} MC_ExtClkEnable;

typedef enum MC_ClkSrcPin {

	MC_CLKSRC_SGPIO_8 		= 0x0,
	MC_CLKSRC_PIN_DEFAULT 	= MC_CLKSRC_SGPIO_8,
	MC_CLKSRC_PIN_DONTCARE 	= MC_CLKSRC_SGPIO_8,
	MC_CLKSRC_SGPIO_9 		= 0x1,
	MC_CLKSRC_SGPIO_10 		= 0x2,
	MC_CLKSRC_SGPIO_11 		= 0x3

} MC_ClkSrcPin;

typedef enum MC_ClkSrcSlice {

	MC_CLKSRC_SLICE_D 			= 0x0,
	MC_CLKSRC_SLICE_DEFAULT 	= MC_CLKSRC_SLICE_D,
	MC_CLKSRC_SLICE_DONTCARE 	= MC_CLKSRC_SLICE_D,
	MC_CLKSRC_SLICE_H 			= 0x1,
	MC_CLKSRC_SLICE_O 			= 0x2,
	MC_CLKSRC_SLICE_P 			= 0x3

 } MC_ClkSrcSlice;

typedef enum MC_QualMode {

	MC_QUALMODE_ENABLE 		= 0x0,
	MC_QUALMODE_DEFAULT		= MC_QUALMODE_ENABLE,
	MC_QUALMODE_DONTCARE	= MC_QUALMODE_ENABLE,
	MC_QUALMODE_DISABLE 	= 0x1,
	MC_QUALMODE_SLICE 		= 0x2,
	MC_QUALMODE_EXTPIN 		= 0x3

} MC_QualMode;

typedef enum MC_QualPinMode {

	MC_QUALPIN_SGPIO_8 	= 0x0,
	MC_QUALPIN_DEFAULT 	= MC_QUALPIN_SGPIO_8,
	MC_QUALPIN_DONTCARE = MC_QUALPIN_SGPIO_8,
	MC_QUALPIN_SGPIO_9 	= 0x1,
	MC_QUALPIN_SGPIO_10 = 0x2,
	MC_QUALPIN_SGPIO_11 = 0x3

} MC_QualPinMode;

typedef enum MC_QualSliceMode {

	MC_QUALSLICE_A_D 		= 0x0,
	MC_QUALSLICE_DEFAULT 	= MC_QUALSLICE_A_D,
	MC_QUALSLICE_DONTCARE 	= MC_QUALSLICE_A_D,
	MC_QUALSLICE_H_O 		= 0x1,
	MC_QUALSLICE_I_D 		= 0x2,
	MC_QUALSLICE_P_O 		= 0x3

} MC_QualSliceMode;

typedef enum MC_ConcatEnable {

	MC_EXT_DATA_PIN 		= 0x0,
	MC_CONCATEN_DEFAULT 	= MC_EXT_DATA_PIN,
	MC_CONCATEN_DONTCARE 	= MC_EXT_DATA_PIN,
	MC_CONCAT_DATA 			= 0x1

} MC_ConcatEnable;

typedef enum MC_ConcatOrder {

	MC_CONCAT_SELF_LOOP 		= 0x0,
	MC_CONCAT_ORDER_DEFAULT 	= MC_CONCAT_SELF_LOOP,
	MC_CONCAT_ORDER_DONTCARE	= MC_CONCAT_SELF_LOOP,
	MC_CONCAT_TWO_SLICES 		= 0x1,
	MC_CONCAT_FOUR_SLICES 		= 0x2,
	MC_CONCAT_EIGHT_SLICES 		= 0x3

} MC_ConcatOrder;

/*****************************************************************************/

/*****************************************************************************/
/* OUT_MUX_CFG register */
/*****************************************************************************/
typedef enum OMC_PinOutCfg {

	OMC_DOUTM1 			= 0x0,
	OMC_PINOUT_DEFAULT 	= OMC_DOUTM1,
	OMC_PINOUT_DONTCARE = OMC_DOUTM1,
	OMC_DOUTM2A 		= 0x1,
	OMC_DOUTM2B 		= 0x2,
	OMC_DOUTM2C 		= 0x3,
	OMC_GPIO_OUT		= 0x4,
	OMC_DOUTM4A 		= 0x5,
	OMC_DOUTM4B 		= 0x6,
	OMC_DOUTM4C 		= 0x7,
	OMC_CLKOUT 			= 0x8,
	OMC_DOUTM8A 		= 0x9,
	OMC_DOUTM8B 		= 0xA,
	OMC_DOUTM8C 		= 0xB

} OMC_PinOutCfg;

typedef enum OMC_PinOeCfg {

	OMC_GPIO_OE			= 0x0,
	OMC_PINOE_DEFAULT 	= OMC_GPIO_OE,
	OMC_PINOE_DONTCARE 	= OMC_GPIO_OE,
	OMC_1BIT_OE 		= 0x4,
	OMC_2BIT_OE 		= 0x5,
	OMC_4BIT_OE 		= 0x6,
	OMC_8BIT_OE			= 0x7

} OMC_PinOeCfg;

/*****************************************************************************/

typedef uint32_t 	dataReg32;
typedef uint8_t		sliceFunc;

/* these define the register values that can be changed dynamically via ioctl */
typedef enum  sliceIoctl {
	RD_COUNT,
	WR_COUNT,
	RD_COUNT_RELOAD,
	WR_COUNT_RELOAD,
	RD_BIT_COUNT,
	WR_BIT_COUNT,
	RD_DATA,
	WR_DATA,
	RD_DATASS,
	WR_DATASS

} sliceIoctl;

/*****************************************************************************/
/* basic slice configuration */
/*****************************************************************************/
typedef struct SgpioSliceCfg  {

	SGPIO_Slice			sliceId;  		// slice identification
	SGPIO_PinFunction	sliceFunc;		// slice function
	SGPIO_Pin			pinId;			// which device pin

} SgpioSliceCfg;

typedef uint32_t SGPIO_SliceMuxConfig;
/* function to make the slice mux register contents */
STATIC INLINE SGPIO_SliceMuxConfig SGPIO_makeSliceMuxConfig (
	SMC_MatchMode 		matchMode,
	SMC_ClkCaptureMode	clkCaptureMode,
	SMC_ClkGenMode		clkGenMode,
	SMC_InvOutClk		invOutClk,
	SMC_DataCapMode		dataCaptureMode,
	SMC_ParallelMode	parallelMode,
	SMC_InvQualifier	invQualifier)
{
    return (SGPIO_SliceMuxConfig)(
        (matchMode << 0)		|
        (clkCaptureMode << 1) 	|
        (clkGenMode << 2)     	|
        (invOutClk << 3)  		|
        (dataCaptureMode << 4)	|
		(parallelMode << 6)  	|
		(invQualifier << 8)
	);
}

typedef uint32_t SGPIO_MuxConfig;
/* function to make the mux register contents */
STATIC INLINE SGPIO_SliceMuxConfig SGPIO_makeMuxConfig (
	MC_ExtClkEnable 	extClkEnable,
	MC_ClkSrcPin 		clkSrcPin,
	MC_ClkSrcSlice 		clkSrcSlice,
	MC_QualMode 		qualMode,
	MC_QualPinMode 		qualPinMode,
	MC_QualSliceMode 	qualSliceMode,
	MC_ConcatEnable 	concatEnable,
	MC_ConcatOrder 		concatOrder)
{
    return (SGPIO_SliceMuxConfig)(
        (extClkEnable << 0)	|
        (clkSrcPin << 1) 	|
        (clkSrcSlice << 3)  |
        (qualMode << 5)  	|
        (qualPinMode << 7)	|
		(qualSliceMode << 9)|
		(concatEnable << 11)|
		(concatOrder << 12)
	);
}

typedef uint32_t SGPIO_OutMuxConfig;
/* function to make the out mux register contents */
STATIC INLINE SGPIO_OutMuxConfig SGPIO_makeOutMuxConfig (
	OMC_PinOutCfg 	pinOutCfg,
	OMC_PinOeCfg 	pinOeCfg)
{
    return (SGPIO_OutMuxConfig)(
        (pinOutCfg << 0)	|
        (pinOeCfg << 4)
	);
}

STATIC INLINE void SGPIO_configMuxReg (const SGPIO_Slice sliceId, const SGPIO_MuxConfig config) {

	LPC_SGPIO->SGPIO_MUX_CFG[sliceId] = config;
}

STATIC INLINE void SGPIO_configSliceMuxReg (const SGPIO_Slice sliceId, const SGPIO_MuxConfig config) {

	LPC_SGPIO->SLICE_MUX_CFG[sliceId] = config;
}

STATIC INLINE void SGPIO_configOutMuxReg (const SGPIO_Pin pinId, const SGPIO_MuxConfig config) {

	LPC_SGPIO->OUT_MUX_CFG[pinId] = config;
}

STATIC INLINE void SGPIO_setOeReg (const SGPIO_Pin pinId, const SGPIO_OutMuxConfig config) {

	if((config & 0x70) == OMC_GPIO_OE)
	LPC_SGPIO->GPIO_OENREG |= (0x1 << pinId);
}

STATIC INLINE void SGPIO_clearOeReg (const SGPIO_Pin pinId) {

	LPC_SGPIO->GPIO_OENREG &= (~(0x1 << pinId));
}

STATIC INLINE void SGPIO_disableSlices(const uint32_t sliceMask) {

	LPC_SGPIO->CTRL_ENABLED	 &= (~sliceMask);
	LPC_SGPIO->CTRL_DISABLED &= (~sliceMask);
}


STATIC INLINE void SGPIO_enableSlices(const bool stop, const uint32_t sliceMask) {

	if(stop == true) LPC_SGPIO->CTRL_DISABLED |= sliceMask;
	LPC_SGPIO->CTRL_ENABLED	 |= sliceMask;
}

STATIC INLINE void SGPIO_disableSlice(SGPIO_Slice sliceId) {

	LPC_SGPIO->CTRL_ENABLED	 &= (~(1 << sliceId));
	LPC_SGPIO->CTRL_DISABLED	 &= (~(1 << sliceId));
}

STATIC INLINE void SGPIO_enableSlice(const bool stop, const SGPIO_Slice sliceId) {

	LPC_SGPIO->CTRL_ENABLED |= (1 << sliceId);
	if(stop == true) LPC_SGPIO->CTRL_DISABLED |= (1 << sliceId);
}

STATIC INLINE void SGPIO_setCountReg(const SGPIO_Slice sliceId, const uint16_t param) {

	LPC_SGPIO->COUNT[sliceId] = (uint32_t) param & 0xFFF;
}

STATIC INLINE void SGPIO_setCountReloadReg(const SGPIO_Slice sliceId, const uint16_t param) {

	LPC_SGPIO->PRESET[sliceId] = ((uint32_t)param & 0x1FFF) - 1;
}

STATIC INLINE void SGPIO_setBitCountReg(const SGPIO_Slice sliceId, const uint16_t param) {

	LPC_SGPIO->POS[sliceId] = ((((uint32_t)param & 0x1FF) - 1) << 8) | (((uint32_t)param & 0x1FF) - 1);
}

STATIC INLINE void SGPIO_writeDataReg(const SGPIO_Slice sliceId, const uint32_t param) {

	LPC_SGPIO->REG[sliceId] = param;
}

STATIC INLINE void SGPIO_readDataReg(const SGPIO_Slice sliceId, const uint8_t wordLength, uint32_t* param) {

	*((uint32_t*)param) = LPC_SGPIO->REG[sliceId] >> (32 - (wordLength));
}

STATIC INLINE void SGPIO_writeDataShadowReg(const SGPIO_Slice sliceId, const uint32_t param) {

	LPC_SGPIO->REG_SS[sliceId] = (uint32_t) param;
}

STATIC INLINE void SGPIO_readDataShadowReg(const SGPIO_Slice sliceId, const uint8_t wordLength, uint32_t* param) {

	*((uint32_t*)param) = LPC_SGPIO->REG_SS[sliceId] >> (32 - (wordLength));
}

#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SGPIO_43XX_H_ */
