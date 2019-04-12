/**
 * @file 
 * @brief Compile Defines
 *
 * This is skeleton to make own Compile_Defines.h
 * Despite of this defines some code are added or subtract from sources to use or not some options.
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
 * This file is a part of JB_Lib_V2.
 */

#ifndef __COMPILE_DEFINES_H_
#define __COMPILE_DEFINES_H_

#ifdef CORE_M4

#define USE_CONSOLE
#define USE_THREAD_SAFE_MALLOC

#endif

#ifdef CORE_M0APP

#define USE_CONSOLE
#define USE_LWIP
#define USE_THREAD_SAFE_MALLOC

#endif

#ifdef CORE_M0SUB

#define USE_THREAD_SAFE_MALLOC

#endif

#endif /* COMPILE_DEFINES_H_ */
