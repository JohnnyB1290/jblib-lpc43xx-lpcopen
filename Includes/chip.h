/*
 * @brief Chip inclusion selector file
 *
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
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
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __CHIP_H_
#define __CHIP_H_

#include "sys_config.h"
#include "cmsis.h"

//#include "PCB_Defines.h"
//#include "Compile_Defines.h"


#ifdef __cplusplus
extern "C"
{
#endif


#if defined(CHIP_LPC18XX)
#include "chip_lpc18xx.h"

#elif defined(CHIP_LPC43XX)
#include "chip_lpc43xx.h"

#else
#error CHIP_LPC18XX or CHIP_LPC43XX must be defined
#endif


#include "PCB_Defines.h"
#include "Compile_Defines.h"
#include "Workspace_defines.h"

#define LongToBin(n) (((n >> 21 ) & 0x80) | ((n >> 18 ) & 0x40) | ((n >> 15 ) & 0x20) | ((n >> 12 ) & 0x10) | ((n >> 9 ) & 0x08) | ((n >> 6 ) & 0x04) | ((n >> 3 ) & 0x02) |  ((n ) & 0x01) )

#define Bin(n) LongToBin(0x##n##l)

///* Aliasing for Chip_USB_Init */
//#define Chip_USB_Init  Chip_USB0_Init
//

typedef void (*VOID_CALLBACK_t)(void);
typedef bool (*Out_packet_callback_t)(EthernetFrame* Frame_ptr, uint16_t frame_size);

#if !defined(MAX)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#if !defined(MIN)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define D_A_MIN_B_MOD_C(a,b,c) ((a >= b)? ((a - b)):((a + c) - b))

#ifdef USE_THREAD_SAFE_MALLOC
#include "stdlib.h"

__inline void* malloc_s(size_t size)
{
	void* ret_ptr = NULL;
	__disable_irq();
	ret_ptr = malloc(size);
	__enable_irq();
	return ret_ptr;
}

__inline void free_s(void * ptr)
{
	__disable_irq();
	free(ptr);
	__enable_irq();
}
#else
#define malloc_s malloc
#define free_s free
#endif


typedef struct IODescription_struct{
	uint32_t port;
	uint32_t pin;
	uint32_t gpioPort;
	uint32_t gpioPin;
	uint32_t scuModeFunc;
}IODescription_t;

/** @ingroup CHIP_18XX_43XX_DRIVER_OPTIONS
 * @{
 */

/**
 * @brief	System oscillator rate
 * This value is defined externally to the chip layer and contains
 * the value in Hz for the external oscillator for the board. If using the
 * internal oscillator, this rate can be 0.
 */
extern const uint32_t OscRateIn;

/**
 * @brief	Clock rate on the CLKIN pin
 * This value is defined externally to the chip layer and contains
 * the value in Hz for the CLKIN pin for the board. If this pin isn't used,
 * this rate can be 0.
 */
extern const uint32_t ExtRateIn;

/**
 * @}
 */

/** @defgroup SUPPORT_18XX_43XX_FUNC CHIP: LPC18xx/43xx support functions
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	Current system clock rate, mainly used for sysTick
 */
extern uint32_t SystemCoreClock;

/**
 * @brief	Update system core clock rate, should be called if the
 *			system has a clock rate change
 * @return	None
 */
void SystemCoreClockUpdate(void);

/**
 * @brief USB0 Pin and clock initialization
 * Calling this function will initialize the USB0 pins and the clock
 * @note This function will assume that the chip is clocked by an
 * external crystal oscillator of frequency 12MHz
 */
void Chip_USB0_Init(void);

/**
 * @brief USB1 Pin and clock initialization
 * Calling this function will initialize the USB0 pins and the clock
 * @note This function will assume that the chip is clocked by an
 * external crystal oscillator of frequency 12MHz
 */
void Chip_USB1_Init(void);

/**
 * @brief	Set up and initialize hardware prior to call to main()
 * @return	None
 * @note	Chip_SystemInit() is called prior to the application and sets up
 * system clocking prior to the application starting.
 */
void Chip_SystemInit(void);

/**
 * @brief	Clock and PLL initialization based input given in @a clkin
 * @param	clkin		: Input reference clock to PLL1 (MAINPLL) see #CHIP_CGU_CLKIN_T
 * @param	core_freq	: Desired output frequency of the PLL1 (Base clock to CPU Core)
 * @param	setbase		: Setup default base clock of peripherals (see notes)
 * @return	None
 * @note	This API will initialize the MAINPLL (PLL1) to the frequency given by
 * 			@a core_freq, and will use this	PLL's output as the base clock for CPU
 * 			Core. If @a clkin is #CLKIN_CRYSTAL then External Crystal Oscillator
 * 			of frequency 12MHz will be used as the input reference clock to PLL1.<br>
 * 			Parameter @a setbase if true will set APB[1,3], SSP[0,1], UART[0,1,2,3],
 * 			SPI base clocks to MAINPLL's output clock. If @a setbase is false then
 * 			the base clock settings for the peripherals will not be modified, only
 * 			CPU Core's base clock will be updated to use clock generated by PLL1.
 */
void Chip_SetupCoreClock(CHIP_CGU_CLKIN_T clkin, uint32_t core_freq, bool setbase);

/**
 * @brief	Clock and PLL initialization based on the external oscillator
 * @return	None
 * @note	This API will initialize the MAINPLL (PLL1) to the maximum
 * 			frequency (180MHz[LPC18xx] or 204MHz[LPC43xx]) and uses this
 * 			PLL's output as the base clock for CPU Core. External Crystal Oscillator
 * 			of frequency 12MHz will be used as the input reference clock to PLL1.
 */
void Chip_SetupXtalClocking(void);

/**
 * @brief	Clock and PLL initialization based on the internal oscillator
 * @return	None
 * @note	This API will initialize the MAINPLL (PLL1) to the maximum
 * 			frequency (180MHz[LPC18xx] or 204MHz[LPC43xx]) and uses this
 * 			PLL's output as the base clock for CPU Core. Internal RC Oscillator
 * 			will be used as the input reference clock to PLL1.
 */
void Chip_SetupIrcClocking(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_H_ */
