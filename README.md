# Description
This repository includes low-level drivers for LPC43XX. Despite it based on [LPCOpen Library](https://www.nxp.com/support/developer-resources/software-development-tools/lpc-developer-resources-/lpcopen-libraries-and-examples:LPC-OPEN-LIBRARIES) v.3.02, some files are deleted, some added from other versions of LPCOpen, and some are modified.
Repository also contains a part of Cortex Microcontroller Software Interface Standard (CMSIS) Library includes.

# Requirements
To use this library you must do this:
1. Add global defines :
    * **CORE_M4** or **CORE_M0**
    * **CORE_M0APP** or **CORE_M0SUB** (if you use one of two M0 cores)
2. Include **chip.h** in all files, where you want to use this library.
3. Define **ETH_PHY_SMSC87X0** or **ETH_PHY_DP83848** depending on the phy you use for Ethernet. If you don't do this, **ETH_PHY_SMSC87X0** will be used as default.

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
    * AES
    * Alarm Timer
    * CCAN
    * CGU/CCU
    * CREG
    * DAC
    * EEPROM
    * External Memory Controller (EMC)
    * Ethernet
    * Event router
    * FLASH Memory Controller (FMC)
    * FPU init code
    * Global Input Multiplexer Array (GIMA)
    * General Purpose DMA
    * GPIO
    * GPIO group
    * HS ADC
    * I2C
    * I2S
    * Flash IAP
    * Ethernet PHY with support following devices:
        * SMSC87x0
        * DP83848
    * Motor Control PWM
    * OTP Controller
    * Pin Interrupt and Pattern Match
    * Power Management Controller (PMC)
    * Quadrature Encoder Interface (QEI)
    * Reset Generator Unit (RGU)
    * RI Timer
    * ROM API
    * RTC
    * State Configurable Timer (SCT)
    * SCU
    * Serial GPIO
    * SSP
    * SPI
    * SDMMC
    * 16/32-bit Timer/PWM
    * UART
    * High-Speed USB
    * WWDT
    * Common ring buffer support functions