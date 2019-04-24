/*
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

#ifndef __SYS_CONFIG_H_
#define __SYS_CONFIG_H_

/* LPC43xx chip family */
#define CHIP_LPC43XX

#ifdef CORE_M0APP
/* LPC43xx M0 Core type */
#define LPC43XX_CORE_M0APP
#endif

#ifdef CORE_M0SUB
/* LPC43xx M0 Core type */
#define LPC43XX_CORE_M0SUB
#endif

#ifdef CORE_M4

#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bits for pre-emption priority
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bits for pre-emption priority
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority
                                                                 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority*/
    
#endif



#endif /* __SYS_CONFIG_H_ */
