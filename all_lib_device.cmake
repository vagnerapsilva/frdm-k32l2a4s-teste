# Copy variable into project config.cmake to use software component
#set.board.frdmk32l2a4s
#  # description: Board_project_template frdmk32l2a4s
#  set(CONFIG_USE_board_project_template true)

#set.device.K32L2A41A
#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: Utility notifier
#  set(CONFIG_USE_utility_notifier true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: Used to include slave core binary into master core binary.
#  set(CONFIG_USE_utility_incbin true)

#  # description: common Driver
#  set(CONFIG_USE_driver_common true)

#  # description: Driver ektf2k
#  set(CONFIG_USE_driver_ektf2k true)

#  # description: Touch panel controller FT3267 driver
#  set(CONFIG_USE_driver_ft3267 true)

#  # description: Driver ft5406
#  set(CONFIG_USE_driver_ft5406 true)

#  # description: Driver gt911
#  set(CONFIG_USE_driver_gt911 true)

#  # description: Driver tma525b
#  set(CONFIG_USE_driver_tma525b true)

#  # description: Component serial_manager_swo
#  set(CONFIG_USE_component_serial_manager_swo true)

#  # description: Component serial_manager_virtual
#  set(CONFIG_USE_component_serial_manager_virtual true)

#  # description: Component rnga_adapter
#  set(CONFIG_USE_component_rnga_adapter true)

#  # description: Component reset_adapter
#  set(CONFIG_USE_component_reset_adapter true)

#  # description: Component panic
#  set(CONFIG_USE_component_panic true)

#  # description: Driver mx25r_flash
#  set(CONFIG_USE_driver_mx25r_flash true)

#  # description: Component software_crc_adapter
#  set(CONFIG_USE_component_software_crc_adapter true)

#  # description: Component ak4497 adapter for single codec
#  set(CONFIG_USE_component_ak4497_adapter true)

#  # description: Component codec adapters for multi codec
#  set(CONFIG_USE_component_codec_adapters true)

#  # description: Component cs42448 adapter for single codec
#  set(CONFIG_USE_component_cs42448_adapter true)

#  # description: Component cs42888 adapter for single codec
#  set(CONFIG_USE_component_cs42888_adapter true)

#  # description: Component da7212 adapter for single codec
#  set(CONFIG_USE_component_da7212_adapter true)

#  # description: Component pcm186x adapter for single codec
#  set(CONFIG_USE_component_pcm186x_adapter true)

#  # description: Component pcm512x adapter for single codec
#  set(CONFIG_USE_component_pcm512x_adapter true)

#  # description: Component sgtl5000 adapter for single codec
#  set(CONFIG_USE_component_sgtl_adapter true)

#  # description: Component tfa9896 adapter for single codec
#  set(CONFIG_USE_component_tfa9896_adapter true)

#  # description: Component tfa9xxx adapter for single codec
#  set(CONFIG_USE_component_tfa9xxx_adapter true)

#  # description: Component wm8524 adapter for single codec
#  set(CONFIG_USE_component_wm8524_adapter true)

#  # description: Component wm8904 adapter for single codec
#  set(CONFIG_USE_component_wm8904_adapter true)

#  # description: Component wm8960 adapter for single codecs
#  set(CONFIG_USE_component_wm8960_adapter true)

#  # description: Component wm8962 adapter for single codecs
#  set(CONFIG_USE_component_wm8962_adapter true)

#  # description: Driver codec
#  set(CONFIG_USE_driver_codec true)

#  # description: Devices_project_template K32L2A41A
#  set(CONFIG_USE_device_project_template true)

#  # description: Rte_device
#  set(CONFIG_USE_device_RTE true)

#  # description: Device K32L2A41A_cmsis
#  set(CONFIG_USE_device_CMSIS true)

#  # description: Device K32L2A41A_system
#  set(CONFIG_USE_device_system true)

#  # description: Device K32L2A41A_startup
#  set(CONFIG_USE_device_startup true)

#  # description: Utility str
#  set(CONFIG_USE_utility_str true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: Utility debug_console
#  set(CONFIG_USE_utility_debug_console true)

#  # description: Utility debug_console Template Config
#  set(CONFIG_USE_utility_debug_console_template_config true)

#  # description: Utility assert
#  set(CONFIG_USE_utility_assert true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: LPUART Freertos Driver
#  set(CONFIG_USE_driver_lpuart_freertos true)

#  # description: LPSPI FreeRTOS Driver
#  set(CONFIG_USE_driver_lpspi_freertos true)

#  # description: LPI2C FreeRTOS Driver
#  set(CONFIG_USE_driver_lpi2c_freertos true)

#  # description: WDOG32 Driver
#  set(CONFIG_USE_driver_wdog32 true)

#  # description: VREF Driver
#  set(CONFIG_USE_driver_vref true)

#  # description: TSTMR Driver
#  set(CONFIG_USE_driver_tstmr true)

#  # description: TSI Driver
#  set(CONFIG_USE_driver_tsi_v4 true)

#  # description: TRNG Driver
#  set(CONFIG_USE_driver_trng true)

#  # description: TRGMUX Driver
#  set(CONFIG_USE_driver_trgmux true)

#  # description: TPM Driver
#  set(CONFIG_USE_driver_tpm true)

#  # description: SMC Driver
#  set(CONFIG_USE_driver_smc true)

#  # description: SMARTCARD PHY GPIO, use only one SMARTCARD PHY in the project
#  set(CONFIG_USE_driver_smartcard_phy_gpio true)

#  # description: SMARTCARD PHY TDA8035, use only one SMARTCARD PHY in the project
#  set(CONFIG_USE_driver_smartcard_phy_tda8035 true)

#  # description: SMARTCARD UART Driver
#  set(CONFIG_USE_driver_smartcard_uart true)

#  # description: SIM Driver
#  set(CONFIG_USE_driver_sim true)

#  # description: RTC Driver
#  set(CONFIG_USE_driver_rtc.K32L2A41A true) 

#  # description: RCM Driver
#  set(CONFIG_USE_driver_rcm true)

#  # description: PORT Driver
#  set(CONFIG_USE_driver_port true)

#  # description: PMC Driver
#  set(CONFIG_USE_driver_pmc true)

#  # description: MMDVSQ Driver
#  set(CONFIG_USE_driver_mmdvsq true)

#  # description: LPUART Driver
#  set(CONFIG_USE_driver_lpuart true)

#  # description: LPUART Driver
#  set(CONFIG_USE_driver_lpuart_edma true)

#  # description: LPUART CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_lpuart true)

#  # description: LPTMR Driver
#  set(CONFIG_USE_driver_lptmr true)

#  # description: LPSPI Driver
#  set(CONFIG_USE_driver_lpspi true)

#  # description: LPSPI Driver
#  set(CONFIG_USE_driver_lpspi_edma true)

#  # description: LPSPI CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_lpspi true)

#  # description: LPIT Driver
#  set(CONFIG_USE_driver_lpit true)

#  # description: LPI2C Driver
#  set(CONFIG_USE_driver_lpi2c true)

#  # description: LPI2C Driver
#  set(CONFIG_USE_driver_lpi2c_edma true)

#  # description: LPI2C CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_lpi2c true)

#  # description: LLWU Driver
#  set(CONFIG_USE_driver_llwu true)

#  # description: INTMUX Driver
#  set(CONFIG_USE_driver_intmux true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_gpio true)

#  # description: FLEXIO UART Driver
#  set(CONFIG_USE_driver_flexio_uart true)

#  # description: FLEXIO UART EDMA Driver
#  set(CONFIG_USE_driver_flexio_uart_edma true)

#  # description: FLEXIO SPI Driver
#  set(CONFIG_USE_driver_flexio_spi true)

#  # description: FLEXIO SPI EDMA Driver
#  set(CONFIG_USE_driver_flexio_spi_edma true)

#  # description: FLEXIO I2S Driver
#  set(CONFIG_USE_driver_flexio_i2s true)

#  # description: FLEXIO I2S EDMA Driver
#  set(CONFIG_USE_driver_flexio_i2s_edma true)

#  # description: FLEXIO I2C Driver
#  set(CONFIG_USE_driver_flexio_i2c_master true)

#  # description: FLEXIO Driver
#  set(CONFIG_USE_driver_flexio true)

#  # description: Flash Driver
#  set(CONFIG_USE_driver_flash true)

#  # description: EDMA Driver
#  set(CONFIG_USE_driver_edma true)

#  # description: DMAMUX Driver
#  set(CONFIG_USE_driver_dmamux true)

#  # description: DAC Driver
#  set(CONFIG_USE_driver_dac true)

#  # description: CRC Driver
#  set(CONFIG_USE_driver_crc true)

#  # description: CMP Driver
#  set(CONFIG_USE_driver_cmp true)

#  # description: ADC16 Driver
#

#  # description: Component lpuart_adapter
#  set(CONFIG_USE_component_lpuart_adapter true)

#  # description: Component lpuart_dma_adapter
#  set(CONFIG_USE_component_lpuart_dma_adapter true)

#  # description: Driver ft5406_rt
#  set(CONFIG_USE_driver_ft5406_rt true)

#  # description: Driver ft6x06
#  set(CONFIG_USE_driver_ft6x06 true)

#  # description: Component timer_manager
#  set(CONFIG_USE_component_timer_manager true)

#  # description: Component lpit_adapter
#  set(CONFIG_USE_component_lpit_adapter true)

#  # description: Component lptmr_adapter
#  set(CONFIG_USE_component_lptmr_adapter true)

#  # description: Component tpm_adapter
#  set(CONFIG_USE_component_tpm_adapter true)

#  # description: Component lpit time stamp adapter
#  set(CONFIG_USE_component_lpit_time_stamp_adapter true)

#  # description: Component lptmr time stamp adapter
#  set(CONFIG_USE_component_lptmr_time_stamp_adapter true)

#  # description: Component lpspi_adapter
#  set(CONFIG_USE_component_lpspi_adapter true)

#  # description: Utility shell
#  set(CONFIG_USE_utility_shell true)

#  # description: Component serial_manager
#  set(CONFIG_USE_component_serial_manager true)

#  # description: Component serial_manager_spi
#  set(CONFIG_USE_component_serial_manager_spi true)

#  # description: Component serial_manager_uart
#  set(CONFIG_USE_component_serial_manager_uart true)

#  # description: Component serial_manager_usb_cdc
#  set(CONFIG_USE_component_serial_manager_usb_cdc true)

#  # description: Driver fxas21002cq
#

#  # description: Driver fxls8974cf
#  set(CONFIG_USE_driver_fxls8974cf true)

#  # description: Driver fxos8700cq
#

#  # description: Driver htu21d
#  set(CONFIG_USE_driver_htu21d true)

#  # description: Driver icm42688p
#  set(CONFIG_USE_driver_icm42688p true)

#  # description: Driver lsm6dso
#  set(CONFIG_USE_driver_lsm6dso true)

#  # description: Driver max30101
#  set(CONFIG_USE_driver_max30101 true)

#  # description: Driver mma8451q
#  set(CONFIG_USE_driver_mma8451q true)

#  # description: Driver mma8652fc
#  set(CONFIG_USE_driver_mma8652fc true)

#  # description: Driver nmh1000
#  set(CONFIG_USE_driver_nmh1000 true)

#  # description: Driver p3t1755
#  set(CONFIG_USE_driver_p3t1755 true)

#  # description: Driver tsl2561
#  set(CONFIG_USE_driver_tsl2561 true)

#  # description: Component rtc
#  set(CONFIG_USE_component_rtc_adapter true)

#  # description: Component rng_adapter_interface
#  set(CONFIG_USE_component_rng_adapter_interface true)

#  # description: Component software_rng_adapter
#  set(CONFIG_USE_component_software_rng_adapter true)

#  # description: Component trng_adapter
#  set(CONFIG_USE_component_trng_adapter true)

#  # description: Component pwm_tpm_adapter
#  set(CONFIG_USE_component_pwm_tpm_adapter true)

#  # description: Driver pf1550
#  set(CONFIG_USE_driver_pf1550 true)

#  # description: Driver pf3000
#  set(CONFIG_USE_driver_pf3000 true)

#  # description: Driver pf5020
#  set(CONFIG_USE_driver_pf5020 true)

#  # description: Component messaging
#  set(CONFIG_USE_component_messaging true)

#  # description: Component mem_manager
#  set(CONFIG_USE_component_mem_manager true)

#  # description: Component mem_manager_legacy
#  set(CONFIG_USE_component_mem_manager_legacy true)

#  # description: Component mem_manager_freertos
#  set(CONFIG_USE_component_mem_manager_freertos true)

#  # description: Component mem_manager_light
#  set(CONFIG_USE_component_mem_manager_light true)

#  # description: Component log
#  set(CONFIG_USE_component_log true)

#  # description: Component log backend debug console
#  set(CONFIG_USE_component_log_backend_debug_console true)

#  # description: Component log backend debug console lite
#  set(CONFIG_USE_component_log_backend_debug_console_lite true)

#  # description: Component log backend ring buffer
#  set(CONFIG_USE_component_log_backend_ringbuffer true)

#  # description: Component lists
#  set(CONFIG_USE_component_lists true)

#  # description: Component led
#  set(CONFIG_USE_component_led true)

#  # description: Component Legacy_flash_adapter
#  set(CONFIG_USE_component_Legacy_flash_adapter true)

#  # description: Component flash_adapter
#  set(CONFIG_USE_component_flash_adapter true)

#  # description: Component lpi2c_adapter
#  set(CONFIG_USE_component_lpi2c_adapter true)

#  # description: Component i2c_adapter_interface
#  set(CONFIG_USE_component_i2c_adapter_interface true)

#  # description: Component i2c_mux_pca954x
#  set(CONFIG_USE_component_i2c_mux_pca954x true)

#  # description: Component enable_pca9544
#  set(CONFIG_USE_component_enable_pca9544 true)

#  # description: Component enable_pca9548
#  set(CONFIG_USE_component_enable_pca9548 true)

#  # description: Component at_least_one_i2c_mux_device_enabled
#  set(CONFIG_USE_component_at_least_one_i2c_mux_device_enabled true)

#  # description: Component gpio_adapter
#  set(CONFIG_USE_component_gpio_adapter true)

#  # description: Driver ili9341
#  set(CONFIG_USE_driver_ili9341 true)

#  # description: Driver psp27801
#  set(CONFIG_USE_driver_psp27801 true)

#  # description: Component crc_adapter
#  set(CONFIG_USE_component_crc_adapter true)

#  # description: Component codec_i2c
#  set(CONFIG_USE_component_codec_i2c true)

#  # description: Driver ak4497
#  set(CONFIG_USE_driver_ak4497 true)

#  # description: Driver cs42448
#  set(CONFIG_USE_driver_cs42448 true)

#  # description: Driver cs42888
#  set(CONFIG_USE_driver_cs42888 true)

#  # description: Driver dialog7212
#  set(CONFIG_USE_driver_dialog7212 true)

#  # description: Driver pcm186x
#  set(CONFIG_USE_driver_pcm186x true)

#  # description: Driver pcm512x
#  set(CONFIG_USE_driver_pcm512x true)

#  # description: Driver sgtl5000
#  set(CONFIG_USE_driver_sgtl5000 true)

#  # description: Driver tfa9896
#  set(CONFIG_USE_driver_tfa9896 true)

#  # description: Driver tfa9xxx
#  set(CONFIG_USE_driver_tfa9xxx true)

#  # description: Driver tfa9xxx_hal
#  set(CONFIG_USE_driver_tfa9xxx_hal true)

#  # description: Driver wm8524
#  set(CONFIG_USE_driver_wm8524 true)

#  # description: Driver wm8904
#  set(CONFIG_USE_driver_wm8904 true)

#  # description: Driver wm8960
#  set(CONFIG_USE_driver_wm8960 true)

#  # description: Driver wm8962
#  set(CONFIG_USE_driver_wm8962 true)

#  # description: Component button
#  set(CONFIG_USE_component_button true)

#set.CMSIS_DSP_Lib
#  # description: CMSIS-DSP Library Header
#  set(CONFIG_USE_CMSIS_DSP_Include true)

#  # description: CMSIS-DSP Library
#  set(CONFIG_USE_CMSIS_DSP_Source true)

#set.CMSIS
#  # description: Device interrupt controller interface
#  set(CONFIG_USE_CMSIS_Device_API_OSTick true)

#  # description: CMSIS-RTOS API for Cortex-M, SC000, and SC300
#  set(CONFIG_USE_CMSIS_Device_API_RTOS2 true)

#  # description: Access to #include Driver_CAN.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_CAN true)

#  # description: Access to #include Driver_ETH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet true)

#  # description: Access to #include Driver_ETH_MAC.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_MAC true)

#  # description: Access to #include Driver_ETH_PHY.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_PHY true)

#  # description: Access to #include Driver_Flash.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Flash true)

#  # description: Access to #include Driver_GPIO.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_GPIO true)

#  # description: Access to #include Driver_I2C.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_I2C true)

#  # description: Access to #include Driver_MCI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_MCI true)

#  # description: Access to #include Driver_NAND.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_NAND true)

#  # description: Access to #include Driver_SAI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SAI true)

#  # description: Access to #include Driver_SPI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SPI true)

#  # description: Access to #include Driver_USART.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USART true)

#  # description: Access to #include Driver_USBD.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Device true)

#  # description: Access to #include Driver_USBH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Host true)

#  # description: Access to #include Driver_WiFi.h file
#  set(CONFIG_USE_CMSIS_Driver_Include_WiFi true)

#  # description: CMSIS-NN Library
#  set(CONFIG_USE_CMSIS_NN_Source true)

#  # description: CMSIS-CORE for Cortex-M, ARMv8-M, ARMv8.1-M
#  set(CONFIG_USE_CMSIS_Include_core_cm true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_RTX true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_RTX_LIB true)

#set.middleware.mcu-boot
#  # description: CMSIS cm7 headers
#  set(CONFIG_USE_middleware_mcu-boot_CMSIS_cm7_headers true)

#  # description: MCUBOOT microseconds sysclk
#  set(CONFIG_USE_middleware_mcu-boot_drv_microseconds true)

#  # description: MCUBOOT microseconds pit
#  set(CONFIG_USE_middleware_mcu-boot_drv_microseconds_pit true)

#  # description: MCUBOOT microseconds lpit
#  set(CONFIG_USE_middleware_mcu-boot_drv_microseconds_lpit true)

#  # description: Bootloader common sources
#  set(CONFIG_USE_middleware_mcu-boot_bootsources true)

#  # description: Bootloader sources for Kinetis devices
#  set(CONFIG_USE_middleware_mcu-boot_bootsources_kinetis true)

#  # description: Flashloader_loader sources
#  set(CONFIG_USE_middleware_mcu-boot_loadersources true)

#  # description: Bootloader startup sources
#  set(CONFIG_USE_middleware_mcu-boot_src_startup true)

#  # description: Postaction scripts for flashloader
#  set(CONFIG_USE_middleware_mcu-boot_postaction true)

#  # description: Bootloader bm usb sources
#  set(CONFIG_USE_middleware_mcu-boot_src_bm_usb true)

#  # description: Bootloader usb device controller driver
#  set(CONFIG_USE_middleware_mcu-boot_usb_device_controller_driver true)

#  # description: Bootloader security sources
#  set(CONFIG_USE_middleware_mcu-boot_src_security true)

#  # description: MCUBOOT mmcau driver
#  set(CONFIG_USE_middleware_mcu-boot_drv_mmcau true)

#  # description: MCUBOOT K32L2A41A startup sources
#  set(CONFIG_USE_middleware_mcu-boot_K32L2A41A_startup true)

#  # description: MCUBOOT K32L2A41A sources
#  set(CONFIG_USE_middleware_mcu-boot_K32L2A41A_sources true)

#  # description: Middleware mcu-boot usb device hid
#  set(CONFIG_USE_middleware_mcu-boot_usb_device_hid true)

#  # description: Middleware mcu-boot usb device stack
#  set(CONFIG_USE_middleware_mcu-boot_usb_device_stack true)

#  # description: Middleware mcu-boot usb device khci
#  set(CONFIG_USE_middleware_mcu-boot_usb_device_khci true)

#  # description: Middleware mcu-boot usb device msd
#  set(CONFIG_USE_middleware_mcu-boot_usb_device_msd true)

#  # description: Middleware mcu-boot usb common_header
#  set(CONFIG_USE_middleware_mcu-boot_usb_common_header true)

#set.middleware.touch
#  # description: NXP Touch Library
#  set(CONFIG_USE_middleware_touch true)

#  # description: Touch driver for frdmke1xz
#  set(CONFIG_USE_middleware_touch_sources_frdmke1xz true)

#  # description: Touch driver for frdmk32l2a4s
#  set(CONFIG_USE_middleware_touch_sources_frdmk32l2a4s true)

#  # description: Touch driver for frdmmcxn
#  set(CONFIG_USE_middleware_touch_sources_frdmmcxn true)

#set.middleware.tinycbor
#  # description: Concise Binary Object Representation (CBOR) Library
#  set(CONFIG_USE_middleware_tinycbor true)

#set.middleware.pkcs11
#  # description: Public Key Cryptography Standard #11 defines generic cryptographic token interface.
#  set(CONFIG_USE_middleware_pkcs11 true)

#set.middleware.mmcau
#  # description: MMCAU common library source files
#  set(CONFIG_USE_middleware_mmcau_common_files true)

#  # description: MMCAU security function library source files
#  set(CONFIG_USE_middleware_mmcau_mmcau_files true)

#  # description: MMCAU library for ARM Cortex M0+ core
#  set(CONFIG_USE_middleware_mmcau_cm0p true)

#set.middleware.mbedtls
#  # description: mbedTLS test suite
#  set(CONFIG_USE_middleware_mbedtls_tests true)

#  # description: mbedTLS 3rdparty code
#  set(CONFIG_USE_middleware_mbedtls_3rdparty true)

#  # description: mbedTLS port library for KPSDK
#  set(CONFIG_USE_middleware_mbedtls_port_ksdk true)

#  # description: mbedTLS library
#  set(CONFIG_USE_middleware_mbedtls true)

#set.middleware.fatfs
#  # description: FatFs
#  set(CONFIG_USE_middleware_fatfs true)

#  # description: FatFs template MMC
#  set(CONFIG_USE_middleware_fatfs_template_mmc true)

#  # description: FatFs template NAND
#  set(CONFIG_USE_middleware_fatfs_template_nand true)

#  # description: FatFs template RAM
#  set(CONFIG_USE_middleware_fatfs_template_ram true)

#  # description: FatFs template SD
#  set(CONFIG_USE_middleware_fatfs_template_sd true)

#  # description: FatFs template SDSPI
#  set(CONFIG_USE_middleware_fatfs_template_sdspi true)

#  # description: FatFs template USB
#  set(CONFIG_USE_middleware_fatfs_template_usb true)

#  # description: FatFs_RAM
#  set(CONFIG_USE_middleware_fatfs_ram true)

#  # description: FatFs_USB
#  set(CONFIG_USE_middleware_fatfs_usb true)

#set.component.osa
#  # description: Component osa template config
#  set(CONFIG_USE_component_osa_template_config true)

#  # description: Component osa
#  set(CONFIG_USE_component_osa true)

#  # description: Component osa_bm
#  set(CONFIG_USE_component_osa_bm true)

#  # description: Component osa_free_rtos
#  set(CONFIG_USE_component_osa_free_rtos true)

#  # description: Component common_task
#  set(CONFIG_USE_component_common_task true)

#set.middleware.freertos-kernel
#  # description: FreeRTOS kernel
#  set(CONFIG_USE_middleware_freertos-kernel true)

#  # description: FreeRTOS NXP extension
#  set(CONFIG_USE_middleware_freertos-kernel_extension true)

#  # description: FreeRTOS NXP Newlib Reentrant
#  set(CONFIG_USE_middleware_freertos-kernel_use_newlib_reentrant true)

#  # description: FreeRTOS NXP Picolibc TLS
#  set(CONFIG_USE_middleware_freertos-kernel_use_picolibc_tls true)

#  # description: FreeRTOS heap 1
#  set(CONFIG_USE_middleware_freertos-kernel_heap_1 true)

#  # description: FreeRTOS heap 2
#  set(CONFIG_USE_middleware_freertos-kernel_heap_2 true)

#  # description: FreeRTOS heap 3
#  set(CONFIG_USE_middleware_freertos-kernel_heap_3 true)

#  # description: FreeRTOS heap 4
#  set(CONFIG_USE_middleware_freertos-kernel_heap_4 true)

#  # description: FreeRTOS heap 5
#  set(CONFIG_USE_middleware_freertos-kernel_heap_5 true)

#  # description: old FreeRTOS MPU wrappers used before V10.6.0
#  set(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers true)

#  # description: new V2 FreeRTOS MPU wrappers introduced in V10.6.0
#  set(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers_v2 true)

#  # description: Template configuration file to be edited by user. Provides also memory allocator (heap_x), change variant if needed.
#  set(CONFIG_USE_middleware_freertos-kernel_config true)

#set.middleware.usb_pd
#  # description: Middleware usb_pd
#  set(CONFIG_USE_middleware_usb_pd true)

#  # description: Middleware usb_pd altmode
#  set(CONFIG_USE_middleware_usb_pd_altmode true)

#  # description: Middleware usb_pd phy ptn5110
#  set(CONFIG_USE_middleware_usb_pd_phy_ptn5110 true)

#  # description: USB Type-C PD Stack
#  set(CONFIG_USE_middleware_usb_pd_config_header true)

#  # description: Middleware usb_pd compliance_test_report
#  set(CONFIG_USE_middleware_usb_pd_compliance_test_report true)

#set.middleware.usb
#  # description: Middleware usb common_header
#  set(CONFIG_USE_middleware_usb_common_header true)

#  # description: Middleware usb device common_header
#  set(CONFIG_USE_middleware_usb_device_common_header true)

#  # description: Middleware usb device khci
#  set(CONFIG_USE_middleware_usb_device_khci true)

#  # description: USB device khci config header
#  set(CONFIG_USE_middleware_usb_device_khci_config_header true)

#  # description: Middleware usb device controller driver
#  set(CONFIG_USE_middleware_usb_device_controller_driver true)

#  # description: Middleware usb device stack
#  set(CONFIG_USE_middleware_usb_device_stack true)

#  # description: Middleware usb device audio
#  set(CONFIG_USE_middleware_usb_device_audio true)

#  # description: Middleware usb device cdc
#  set(CONFIG_USE_middleware_usb_device_cdc true)

#  # description: Middleware usb device cdc ecm
#  set(CONFIG_USE_middleware_usb_device_cdc_ecm true)

#  # description: Middleware usb device cdc rndis
#  set(CONFIG_USE_middleware_usb_device_cdc_rndis true)

#  # description: Middleware usb device hid
#  set(CONFIG_USE_middleware_usb_device_hid true)

#  # description: Middleware usb device dfu
#  set(CONFIG_USE_middleware_usb_device_dfu true)

#  # description: Middleware usb device msd
#  set(CONFIG_USE_middleware_usb_device_msd true)

#  # description: Middleware usb device mtp
#  set(CONFIG_USE_middleware_usb_device_mtp true)

#  # description: Middleware usb device phdc
#  set(CONFIG_USE_middleware_usb_device_phdc true)

#  # description: Middleware usb device video
#  set(CONFIG_USE_middleware_usb_device_video true)

#  # description: Middleware usb device ccid
#  set(CONFIG_USE_middleware_usb_device_ccid true)

#  # description: Middleware usb device printer
#  set(CONFIG_USE_middleware_usb_device_printer true)

#  # description: Middleware usb host common_header
#  set(CONFIG_USE_middleware_usb_host_common_header true)

#  # description: Middleware usb host khci
#  set(CONFIG_USE_middleware_usb_host_khci true)

#  # description: USB host khci config header
#  set(CONFIG_USE_middleware_usb_host_khci_config_header true)

#  # description: Middleware usb host stack
#  set(CONFIG_USE_middleware_usb_host_stack true)

#  # description: Middleware usb host audio
#  set(CONFIG_USE_middleware_usb_host_audio true)

#  # description: Middleware usb host cdc
#  set(CONFIG_USE_middleware_usb_host_cdc true)

#  # description: Middleware usb host cdc_ecm
#  set(CONFIG_USE_middleware_usb_host_cdc_ecm true)

#  # description: Middleware usb host cdc_rndis
#  set(CONFIG_USE_middleware_usb_host_cdc_rndis true)

#  # description: Middleware usb host hid
#  set(CONFIG_USE_middleware_usb_host_hid true)

#  # description: Middleware usb host msd
#  set(CONFIG_USE_middleware_usb_host_msd true)

#  # description: Middleware usb host video
#  set(CONFIG_USE_middleware_usb_host_video true)

#  # description: Middleware usb host phdc
#  set(CONFIG_USE_middleware_usb_host_phdc true)

#  # description: Middleware usb host printer
#  set(CONFIG_USE_middleware_usb_host_printer true)

#set.middleware.llhttp
#  # description: HTTP parser in LLVM IR
#  set(CONFIG_USE_middleware_llhttp true)

#set.middleware.fmstr
#  # description: Common FreeMASTER driver code.
#  set(CONFIG_USE_middleware_fmstr true)

#  # description: FreeMASTER driver code for 32bit platforms, enabling communication between FreeMASTER or FreeMASTER Lite tools and MCU application. Supports Serial, CAN, USB and BDM/JTAG physical interface.
#  set(CONFIG_USE_middleware_fmstr_platform_gen32le true)

#  # description: FreeMASTER driver code for DSC platforms, enabling communication between FreeMASTER or FreeMASTER Lite tools and MCU application. Supports Serial, CAN, USB and BDM/JTAG physical interface.
#  set(CONFIG_USE_middleware_fmstr_platform_56f800e true)

#  # description: FreeMASTER driver code for S32 platform.
#  set(CONFIG_USE_middleware_fmstr_platform_s32 true)

#  # description: FreeMASTER driver code for Power Architecture 32bit platform.
#  set(CONFIG_USE_middleware_fmstr_platform_pa32 true)

#  # description: FreeMASTER driver code for S12Z platform.
#  set(CONFIG_USE_middleware_fmstr_platform_s12z true)

list(APPEND CMAKE_MODULE_PATH
${CMAKE_CURRENT_LIST_DIR}/
${CMAKE_CURRENT_LIST_DIR}/CMSIS
${CMAKE_CURRENT_LIST_DIR}/component/lists
${CMAKE_CURRENT_LIST_DIR}/component/osa
${CMAKE_CURRENT_LIST_DIR}/component/uart
${CMAKE_CURRENT_LIST_DIR}/component/crc
${CMAKE_CURRENT_LIST_DIR}/device
${CMAKE_CURRENT_LIST_DIR}/drivers
${CMAKE_CURRENT_LIST_DIR}/source
${CMAKE_CURRENT_LIST_DIR}/middleware/mmcau
${CMAKE_CURRENT_LIST_DIR}/startup
${CMAKE_CURRENT_LIST_DIR}/usb
${CMAKE_CURRENT_LIST_DIR}/utilities
)
include_if_use(driver_fxas21002cq.K32L2A41A)
include_if_use(CMSIS_DSP_Include)
include_if_use(CMSIS_DSP_Source)
include_if_use(CMSIS_Device_API_OSTick)
include_if_use(CMSIS_Device_API_RTOS2)
include_if_use(CMSIS_Driver_Include_CAN)
include_if_use(CMSIS_Driver_Include_Ethernet)
include_if_use(CMSIS_Driver_Include_Ethernet_MAC)
include_if_use(CMSIS_Driver_Include_Ethernet_PHY)
include_if_use(CMSIS_Driver_Include_Flash)
include_if_use(CMSIS_Driver_Include_GPIO)
include_if_use(CMSIS_Driver_Include_I2C)
include_if_use(CMSIS_Driver_Include_MCI)
include_if_use(CMSIS_Driver_Include_NAND)
include_if_use(CMSIS_Driver_Include_SAI)
include_if_use(CMSIS_Driver_Include_SPI)
include_if_use(CMSIS_Driver_Include_USART)
include_if_use(CMSIS_Driver_Include_USB_Device)
include_if_use(CMSIS_Driver_Include_USB_Host)
include_if_use(CMSIS_Driver_Include_WiFi)
include_if_use(CMSIS_Include_core_cm)
include_if_use(CMSIS_NN_Source)
include_if_use(CMSIS_RTOS2_RTX)
include_if_use(CMSIS_RTOS2_RTX_LIB)
include_if_use(board_project_template)
include_if_use(component_Legacy_flash_adapter.K32L2A41A)
include_if_use(component_ak4497_adapter.K32L2A41A)
include_if_use(component_at_least_one_i2c_mux_device_enabled.K32L2A41A)
include_if_use(component_button.K32L2A41A)
include_if_use(component_codec_adapters.K32L2A41A)
include_if_use(component_codec_i2c.K32L2A41A)
include_if_use(component_common_task)
include_if_use(component_crc_adapter.K32L2A41A)
include_if_use(component_cs42448_adapter.K32L2A41A)
include_if_use(component_cs42888_adapter.K32L2A41A)
include_if_use(component_da7212_adapter.K32L2A41A)
include_if_use(component_enable_pca9544.K32L2A41A)
include_if_use(component_enable_pca9548.K32L2A41A)
include_if_use(component_flash_adapter.K32L2A41A)
include_if_use(component_gpio_adapter.K32L2A41A)
include_if_use(component_i2c_adapter_interface.K32L2A41A)
include_if_use(component_i2c_mux_pca954x.K32L2A41A)
include_if_use(component_led.K32L2A41A)
include_if_use(component_lists.K32L2A41A)
include_if_use(component_log.K32L2A41A)
include_if_use(component_log_backend_debug_console.K32L2A41A)
include_if_use(component_log_backend_debug_console_lite.K32L2A41A)
include_if_use(component_log_backend_ringbuffer.K32L2A41A)
include_if_use(component_lpi2c_adapter.K32L2A41A)
include_if_use(component_lpit_adapter.K32L2A41A)
include_if_use(component_lpit_time_stamp_adapter.K32L2A41A)
include_if_use(component_lpspi_adapter.K32L2A41A)
include_if_use(component_lptmr_adapter.K32L2A41A)
include_if_use(component_lptmr_time_stamp_adapter.K32L2A41A)
include_if_use(component_lpuart_adapter.K32L2A41A)
include_if_use(component_lpuart_dma_adapter.K32L2A41A)
include_if_use(component_mem_manager.K32L2A41A)
include_if_use(component_mem_manager_freertos.K32L2A41A)
include_if_use(component_mem_manager_legacy.K32L2A41A)
include_if_use(component_mem_manager_light.K32L2A41A)
include_if_use(component_messaging.K32L2A41A)
include_if_use(component_osa)
include_if_use(component_osa_bm)
include_if_use(component_osa_free_rtos)
include_if_use(component_osa_template_config)
include_if_use(component_panic.K32L2A41A)
include_if_use(component_pcm186x_adapter.K32L2A41A)
include_if_use(component_pcm512x_adapter.K32L2A41A)
include_if_use(component_pwm_tpm_adapter.K32L2A41A)
include_if_use(component_reset_adapter.K32L2A41A)
include_if_use(component_rng_adapter_interface.K32L2A41A)
include_if_use(component_rnga_adapter.K32L2A41A)
include_if_use(component_rtc_adapter.K32L2A41A)
include_if_use(component_serial_manager.K32L2A41A)
include_if_use(component_serial_manager_spi.K32L2A41A)
include_if_use(component_serial_manager_swo.K32L2A41A)
include_if_use(component_serial_manager_uart.K32L2A41A)
include_if_use(component_serial_manager_usb_cdc.K32L2A41A)
include_if_use(component_serial_manager_virtual.K32L2A41A)
include_if_use(component_sgtl_adapter.K32L2A41A)
include_if_use(component_software_crc_adapter.K32L2A41A)
include_if_use(component_software_rng_adapter.K32L2A41A)
include_if_use(component_tfa9896_adapter.K32L2A41A)
include_if_use(component_tfa9xxx_adapter.K32L2A41A)
include_if_use(component_timer_manager.K32L2A41A)
include_if_use(component_tpm_adapter.K32L2A41A)
include_if_use(component_trng_adapter.K32L2A41A)
include_if_use(component_wm8524_adapter.K32L2A41A)
include_if_use(component_wm8904_adapter.K32L2A41A)
include_if_use(component_wm8960_adapter.K32L2A41A)
include_if_use(component_wm8962_adapter.K32L2A41A)
include_if_use(device_CMSIS.K32L2A41A)
include_if_use(device_RTE.K32L2A41A)
include_if_use(device_project_template.K32L2A41A)
include_if_use(device_startup.K32L2A41A)
include_if_use(device_system.K32L2A41A)
include_if_use(driver_adc16.K32L2A41A)
include_if_use(driver_ak4497.K32L2A41A)
include_if_use(driver_clock.K32L2A41A)
include_if_use(driver_cmp.K32L2A41A)
include_if_use(driver_cmsis_lpi2c.K32L2A41A)
include_if_use(driver_cmsis_lpspi.K32L2A41A)
include_if_use(driver_cmsis_lpuart.K32L2A41A)
include_if_use(driver_codec.K32L2A41A)
include_if_use(driver_common.K32L2A41A)
include_if_use(driver_crc.K32L2A41A)
include_if_use(driver_cs42448.K32L2A41A)
include_if_use(driver_cs42888.K32L2A41A)
include_if_use(driver_dac.K32L2A41A)
include_if_use(driver_dialog7212.K32L2A41A)
include_if_use(driver_dmamux.K32L2A41A)
include_if_use(driver_edma.K32L2A41A)
include_if_use(driver_ektf2k.K32L2A41A)
include_if_use(driver_flash.K32L2A41A)
include_if_use(driver_flexio.K32L2A41A)
include_if_use(driver_flexio_i2c_master.K32L2A41A)
include_if_use(driver_flexio_i2s.K32L2A41A)
include_if_use(driver_flexio_i2s_edma.K32L2A41A)
include_if_use(driver_flexio_spi.K32L2A41A)
include_if_use(driver_flexio_spi_edma.K32L2A41A)
include_if_use(driver_flexio_uart.K32L2A41A)
include_if_use(driver_flexio_uart_edma.K32L2A41A)
include_if_use(driver_ft3267.K32L2A41A)
include_if_use(driver_ft5406.K32L2A41A)
include_if_use(driver_ft5406_rt.K32L2A41A)
include_if_use(driver_ft6x06.K32L2A41A)
include_if_use(driver_fxas21002cq.K32L2A41A)
include_if_use(driver_fxls8974cf.K32L2A41A)
include_if_use(driver_fxos8700cq.K32L2A41A)
include_if_use(driver_gpio.K32L2A41A)
include_if_use(driver_gt911.K32L2A41A)
include_if_use(driver_htu21d.K32L2A41A)
include_if_use(driver_icm42688p.K32L2A41A)
include_if_use(driver_ili9341.K32L2A41A)
include_if_use(driver_intmux.K32L2A41A)
include_if_use(driver_llwu.K32L2A41A)
include_if_use(driver_lpi2c.K32L2A41A)
include_if_use(driver_lpi2c_edma.K32L2A41A)
include_if_use(driver_lpi2c_freertos.K32L2A41A)
include_if_use(driver_lpit.K32L2A41A)
include_if_use(driver_lpspi.K32L2A41A)
include_if_use(driver_lpspi_edma.K32L2A41A)
include_if_use(driver_lpspi_freertos.K32L2A41A)
include_if_use(driver_lptmr.K32L2A41A)
include_if_use(driver_lpuart.K32L2A41A)
include_if_use(driver_lpuart_edma.K32L2A41A)
include_if_use(driver_lpuart_freertos.K32L2A41A)
include_if_use(driver_lsm6dso.K32L2A41A)
include_if_use(driver_max30101.K32L2A41A)
include_if_use(driver_mma8451q.K32L2A41A)
include_if_use(driver_mma8652fc.K32L2A41A)
include_if_use(driver_mmdvsq.K32L2A41A)
include_if_use(driver_mx25r_flash.K32L2A41A)
include_if_use(driver_nmh1000.K32L2A41A)
include_if_use(driver_p3t1755.K32L2A41A)
include_if_use(driver_pcm186x.K32L2A41A)
include_if_use(driver_pcm512x.K32L2A41A)
include_if_use(driver_pf1550.K32L2A41A)
include_if_use(driver_pf3000.K32L2A41A)
include_if_use(driver_pf5020.K32L2A41A)
include_if_use(driver_pmc.K32L2A41A)
include_if_use(driver_port.K32L2A41A)
include_if_use(driver_psp27801.K32L2A41A)
include_if_use(driver_rcm.K32L2A41A)
include_if_use(driver_rtc.K32L2A41A)
include_if_use(driver_sgtl5000.K32L2A41A)
include_if_use(driver_sim.K32L2A41A)
include_if_use(driver_smartcard_phy_gpio.K32L2A41A)
include_if_use(driver_smartcard_phy_tda8035.K32L2A41A)
include_if_use(driver_smartcard_uart.K32L2A41A)
include_if_use(driver_smc.K32L2A41A)
include_if_use(driver_tfa9896.K32L2A41A)
include_if_use(driver_tfa9xxx.K32L2A41A)
include_if_use(driver_tfa9xxx_hal.K32L2A41A)
include_if_use(driver_tma525b.K32L2A41A)
include_if_use(driver_tpm.K32L2A41A)
include_if_use(driver_trgmux.K32L2A41A)
include_if_use(driver_trng.K32L2A41A)
include_if_use(driver_tsi_v4.K32L2A41A)
include_if_use(driver_tsl2561.K32L2A41A)
include_if_use(driver_tstmr.K32L2A41A)
include_if_use(driver_vref.K32L2A41A)
include_if_use(driver_wdog32.K32L2A41A)
include_if_use(driver_wm8524.K32L2A41A)
include_if_use(driver_wm8904.K32L2A41A)
include_if_use(driver_wm8960.K32L2A41A)
include_if_use(driver_wm8962.K32L2A41A)
include_if_use(middleware_fatfs)
include_if_use(middleware_fatfs_ram)
include_if_use(middleware_fatfs_template_mmc)
include_if_use(middleware_fatfs_template_nand)
include_if_use(middleware_fatfs_template_ram)
include_if_use(middleware_fatfs_template_sd)
include_if_use(middleware_fatfs_template_sdspi)
include_if_use(middleware_fatfs_template_usb)
include_if_use(middleware_fatfs_usb)
include_if_use(middleware_fmstr)
include_if_use(middleware_fmstr_platform_56f800e)
include_if_use(middleware_fmstr_platform_gen32le)
include_if_use(middleware_fmstr_platform_pa32)
include_if_use(middleware_fmstr_platform_s12z)
include_if_use(middleware_fmstr_platform_s32)
include_if_use(middleware_freertos-kernel)
include_if_use(middleware_freertos-kernel_config)
include_if_use(middleware_freertos-kernel_extension)
include_if_use(middleware_freertos-kernel_heap_1)
include_if_use(middleware_freertos-kernel_heap_2)
include_if_use(middleware_freertos-kernel_heap_3)
include_if_use(middleware_freertos-kernel_heap_4)
include_if_use(middleware_freertos-kernel_heap_5)
include_if_use(middleware_freertos-kernel_mpu_wrappers)
include_if_use(middleware_freertos-kernel_mpu_wrappers_v2)
include_if_use(middleware_freertos-kernel_use_newlib_reentrant)
include_if_use(middleware_freertos-kernel_use_picolibc_tls)
include_if_use(middleware_llhttp)
include_if_use(middleware_mbedtls)
include_if_use(middleware_mbedtls_3rdparty)
include_if_use(middleware_mbedtls_port_ksdk)
include_if_use(middleware_mbedtls_tests)
include_if_use(middleware_mcu-boot_CMSIS_cm7_headers)
include_if_use(middleware_mcu-boot_K32L2A41A_sources)
include_if_use(middleware_mcu-boot_K32L2A41A_startup)
include_if_use(middleware_mcu-boot_bootsources)
include_if_use(middleware_mcu-boot_bootsources_kinetis)
include_if_use(middleware_mcu-boot_drv_microseconds)
include_if_use(middleware_mcu-boot_drv_microseconds_lpit)
include_if_use(middleware_mcu-boot_drv_microseconds_pit)
include_if_use(middleware_mcu-boot_drv_mmcau)
include_if_use(middleware_mcu-boot_loadersources)
include_if_use(middleware_mcu-boot_postaction)
include_if_use(middleware_mcu-boot_src_bm_usb)
include_if_use(middleware_mcu-boot_src_security)
include_if_use(middleware_mcu-boot_src_startup)
include_if_use(middleware_mcu-boot_usb_common_header)
include_if_use(middleware_mcu-boot_usb_device_controller_driver)
include_if_use(middleware_mcu-boot_usb_device_hid)
include_if_use(middleware_mcu-boot_usb_device_khci)
include_if_use(middleware_mcu-boot_usb_device_msd)
include_if_use(middleware_mcu-boot_usb_device_stack)
include_if_use(middleware_mmcau_cm0p)
include_if_use(middleware_mmcau_common_files)
include_if_use(middleware_mmcau_mmcau_files)
include_if_use(middleware_pkcs11)
include_if_use(middleware_tinycbor)
include_if_use(middleware_touch)
include_if_use(middleware_touch_sources_frdmk32l2a4s)
include_if_use(middleware_touch_sources_frdmke1xz)
include_if_use(middleware_touch_sources_frdmmcxn)
include_if_use(middleware_usb_common_header)
include_if_use(middleware_usb_device_audio)
include_if_use(middleware_usb_device_ccid)
include_if_use(middleware_usb_device_cdc)
include_if_use(middleware_usb_device_cdc_ecm)
include_if_use(middleware_usb_device_cdc_rndis)
include_if_use(middleware_usb_device_common_header)
include_if_use(middleware_usb_device_controller_driver)
include_if_use(middleware_usb_device_dfu)
include_if_use(middleware_usb_device_hid)
include_if_use(middleware_usb_device_khci)
include_if_use(middleware_usb_device_khci_config_header)
include_if_use(middleware_usb_device_msd)
include_if_use(middleware_usb_device_mtp)
include_if_use(middleware_usb_device_phdc)
include_if_use(middleware_usb_device_printer)
include_if_use(middleware_usb_device_stack)
include_if_use(middleware_usb_device_video)
include_if_use(middleware_usb_host_audio)
include_if_use(middleware_usb_host_cdc)
include_if_use(middleware_usb_host_cdc_ecm)
include_if_use(middleware_usb_host_cdc_rndis)
include_if_use(middleware_usb_host_common_header)
include_if_use(middleware_usb_host_hid)
include_if_use(middleware_usb_host_khci)
include_if_use(middleware_usb_host_khci_config_header)
include_if_use(middleware_usb_host_msd)
include_if_use(middleware_usb_host_phdc)
include_if_use(middleware_usb_host_printer)
include_if_use(middleware_usb_host_stack)
include_if_use(middleware_usb_host_video)
include_if_use(middleware_usb_pd)
include_if_use(middleware_usb_pd_altmode)
include_if_use(middleware_usb_pd_compliance_test_report)
include_if_use(middleware_usb_pd_config_header)
include_if_use(middleware_usb_pd_phy_ptn5110)
include_if_use(utilities_misc_utilities.K32L2A41A)
include_if_use(utility_assert.K32L2A41A)
include_if_use(utility_assert_lite.K32L2A41A)
include_if_use(utility_debug_console.K32L2A41A)
include_if_use(utility_debug_console_lite.K32L2A41A)
include_if_use(utility_debug_console_template_config.K32L2A41A)
include_if_use(utility_incbin.K32L2A41A)
include_if_use(utility_notifier.K32L2A41A)
include_if_use(utility_shell.K32L2A41A)
include_if_use(utility_str.K32L2A41A)


