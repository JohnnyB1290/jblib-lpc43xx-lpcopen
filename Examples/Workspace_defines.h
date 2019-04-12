/**
 * @file 
 * @brief Workspace defines
 *
 * Contains global defines used in whole workspace in spite 
 * of what core was used. 
 * Commonly used for addresses description.
 *
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
 * All rights reserved.
 * @note
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 * @note
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @note
 * This file is a part of JB_Lib.
 */
 
#ifndef WORKSPACE_DEFINES_H_
#define WORKSPACE_DEFINES_H_

/*********************************ADRESSES************************************************************/

#define FLASH_A_BASE 0x1A000000
#define FLASH_B_BASE 0x1B000000
#define FLASH_PAGE_SIZE (512UL)

#define M4_APP_START_ADDR 0x1A050000
#define M4_APP_END_ADDR 0x1A080000
#define M4_APP_FIRST_SECT_NUM 12
#define M4_APP_LAST_SECT_NUM 14

#define M0APP_APP_START_ADDR 0x1B010000
#define M0APP_APP_END_ADDR 0x1B070000
#define M0APP_APP_FIRST_SECT_NUM 8
#define M0APP_APP_LAST_SECT_NUM 13

#define M0SUB_APP_START_ADDR 0x1B070000
#define M0SUB_APP_END_ADDR 0x1B080000
#define M0SUB_APP_FIRST_SECT_NUM 14
#define M0SUB_APP_LAST_SECT_NUM 14

#define M0SUB_APP_RAM_START_ADDR 	0x18000000
#define M0SUB_APP_RAM_END_ADDR 		0x18004800

#define SHARED_MEM_M4_M0APP			0x10007F40 //IPC Queue structs
#define SHARED_MEM_M4_M0SUB			0x10007F60
#define SHARED_MEM_M0APP_M4			0x10007F80
#define SHARED_MEM_M0APP_M0SUB		0x10007FA0
#define SHARED_MEM_M0SUB_M4			0x10007FC0
#define SHARED_MEM_M0SUB_M0APP		0x10007FE0

/* On LPC18xx/43xx the USB controller requires endpoint queue heads to start on
   a 4KB aligned memory. Hence the mem_base value passed to USB stack init should
   be 4KB aligned.
 */
#define USB0_STACK_MEM_BASE     		0x20008000
#define USB0_STACK_MEM_SIZE      		0x00004000

#define USB1_STACK_MEM_BASE     		0x2000C000
#define USB1_STACK_MEM_SIZE      		0x00004000

#define NXPUSBLIB_STACK_MEM_BASE     	USB0_STACK_MEM_BASE

/******************************************************************************************************/

#endif /* WORKSPACE_DEFINES_H_ */
