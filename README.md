# Description
This repository includes low-level drivers for LPC43XX. Despite it based on [LPCOpen Library](https://www.nxp.com/support/developer-resources/software-development-tools/lpc-developer-resources-/lpcopen-libraries-and-examples:LPC-OPEN-LIBRARIES) v.3.02, some files are deleted, some added from other versions of LPCOpen, and some are modified to use with JB Library.
Repository also contains Cortex Microcontroller Software Interface Standard (CMSIS) Library includes.

# Requirements
To use this library you must do this:
1. Add global defines :
    * **CORE_M4** or **CORE_M0**
    * **CORE_M0APP** or **CORE_M0SUB** (if you use one of two M0 cores)
2. Add files (see Examples folder):
    * **PCB_Defines.h** Contains description of using hardware.
    * **Compile_Defines.h** Despite of this defines some code are added or subtract from sources to use or not some options.
    * **Workspace_defines.h** Contains global defines used in whole workspace in spite of what core was used. Commonly used for addresses description.
3. Include **chip.h** in all files, where you want to use this library or corresponding defines.

# Content
1. **Drivers**:
    * SPIFI with support of the following devices:
         * S25FL016K {W25Q16DV}
         * S25FL032P
         * S25FL064P
         * S25FL129P 64k Sector
         * S25FL129P 256k Sector {S25FL128S}
         * S25FL164K
         * S25FL256S (untested)
         * S25FL512S (untested)
         * MX25L1635E
         * MX25L3235E
         * MX25L6435E
         * MX25L8035E
         * W25Q32FV
         * W25Q64FV
         * W25Q80BV
    * USB device ROM Stack
    * ADC
    * Alarm Timer
    * CGU/CCU
    * CREG
    * DAC
    * EEPROM
    * Ethernet
    * Event router
    * FLASH Memory Controller (FMC)
    * FPU init code
    * General Purpose DMA
    * GPIO
    * GPIO group
    * I2C
    * I2S
    * Flash IAP
    * Ethernet PHY with support following devices:
        * SMSC87x0
        * DP83848
    * Motor Control PWM
    * OTP Controller
    * Pin Interrupt and Pattern Match
    * Reset Generator Unit (RGU)
    * RI Timer
    * ROM API
    * State Configurable Timer (SCT)
    * SCU
    * Serial GPIO
    * SSP
    * 16/32-bit Timer/PWM
    * UART
    * High-Speed USB
    * WWDT
    * Common ring buffer support functions
2. **Documents:** Datasheets, application notes, etc. For LPC43XX.
3. **Examples:** Templates of necessary user files.

#### Thread safe malloc/free realization
It's recomended to always use mallos_s/free_s instead of malloc/free. If USE_THREAD_SAFE_MALLOC define in Compile_Defines.h thread safe realization will be used, if not - library uses standard realization. 