# CROSS COMPILER SETTING
set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
return()
endif()


set(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
set(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
set(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(lpi2c_polling_b2b_slave)

enable_language(ASM)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME lpi2c_polling_b2b_slave.elf)

if (NOT DEFINED SdkRootDirPath)
SET(SdkRootDirPath ${ProjDirPath}/)
endif()


include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME}
"${ProjDirPath}/board/app.h"
"${ProjDirPath}/board/board.c"
"${ProjDirPath}/board/board.h"
"${ProjDirPath}/board/clock_config.c"
"${ProjDirPath}/board/clock_config.h"
"${ProjDirPath}/board/hardware_init.c"
"${ProjDirPath}/board/peripherals.c"
"${ProjDirPath}/board/peripherals.h"
"${ProjDirPath}/board/pin_mux.c"
"${ProjDirPath}/board/pin_mux.h"
"${ProjDirPath}/source/main.c"
"${ProjDirPath}/source/mcux_config.h"
"${ProjDirPath}/Ssd1306/Src/image.c"
"${ProjDirPath}/Ssd1306/Src/ssd1306.c"
"${ProjDirPath}/Ssd1306/Inc/ssd1306.h"
"${ProjDirPath}/Ssd1306/Src/ssd1306_fonts.c"
"${ProjDirPath}/Ssd1306/Inc/ssd1306_fonts.h"
"${ProjDirPath}/Ssd1306/Inc/ssd1306_conf.h"
"${ProjDirPath}/source/generated/usb_device_config.h"
"${ProjDirPath}/source/generated/usb_device_composite.c"
"${ProjDirPath}/source/generated/usb_device_composite.h"
"${ProjDirPath}/source/generated/usb_device_descriptor.c"
"${ProjDirPath}/source/generated/usb_device_descriptor.h"
"${ProjDirPath}/source/usb_device_interface_0_cic_vcom.c"
"${ProjDirPath}/source/usb_device_interface_0_cic_vcom.h"
"${ProjDirPath}/source/fsl_os_abstraction_config.h"
"${ProjDirPath}/fxas_21002c/src/fxas_21002c.c"
"${ProjDirPath}/fxas_21002c/inc/fxas_21002c.h"
"${ProjDirPath}/encoder/src/encoder_ky_040.c"
"${ProjDirPath}/encoder/inc/encoder_ky_040.h"
"${ProjDirPath}/fxos_8700cq/src/fxos_8700cq.c" 
"${ProjDirPath}/fxos_8700cq/inc/fxos_8700cq.h"
"${ProjDirPath}/usart/inc/usart.h"
"${ProjDirPath}/usart/src/usart.c"
"${ProjDirPath}/light_sensor/src/light_sensor.c"
"${ProjDirPath}/light_sensor/inc/light_sensor.h"
"${ProjDirPath}/rtc/inc/rtc.h"
"${ProjDirPath}/rtc/src/rtc.c"
"${ProjDirPath}/mmcau/src/mmcau_api.c"
"${ProjDirPath}/board/display_lib.c"
"${ProjDirPath}/board/display_lib.h"
"${ProjDirPath}/led/src/led.c"
"${ProjDirPath}/led/inc/led.h"
"${ProjDirPath}/crc/src/crc.c"
"${ProjDirPath}/crc/inc/crc.h"
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
"${ProjDirPath}/.."
"${ProjDirPath}/source"
"${ProjDirPath}/board"
"${ProjDirPath}/Ssd1306/Inc"
"${ProjDirPath}/source/generated"
"${ProjDirPath}/component/lists"
"${ProjDirPath}/component/osa"
"${ProjDirPath}/fxas_21002c/inc"
"${ProjDirPath}/fxos_8700cq/inc"
"${ProjDirPath}/encoder/inc"
"${ProjDirPath}/usart/inc"
"${ProjDirPath}/light_sensor/inc"
"${ProjDirPath}/rtc/inc"
"${ProjDirPath}/led/inc"
"${ProjDirPath}/crc/inc"
"${ProjDirPath}/mmcau/inc"

)

set_source_files_properties("${ProjDirPath}/source/fsl_os_abstraction_config.h" PROPERTIES COMPONENT_CONFIG_FILE "component_osa_template_config")
set_source_files_properties("${ProjDirPath}/source/generated/usb_device_config.h" PROPERTIES COMPONENT_CONFIG_FILE "middleware_usb_device_khci_config_header")

include(${ProjDirPath}/all_lib_device.cmake)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)
SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")
ENDIF()

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/lpi2c_polling_b2b_slave.bin)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map;${EXECUTABLE_OUTPUT_PATH}/lpi2c_polling_b2b_slave.bin")

# wrap all libraries with -Wl,--start-group -Wl,--end-group to prevent link order issue
group_link_libraries()

