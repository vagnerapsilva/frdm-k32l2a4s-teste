# Add set(CONFIG_USE_device_startup true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_TOOLCHAIN STREQUAL mcux)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_k32l2a41a.c "" device_startup.K32L2A41A)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_k32l2a41a.cpp "" device_startup.K32L2A41A)
endif()

if(CONFIG_TOOLCHAIN STREQUAL iar)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/iar/startup_K32L2A41A.s "" device_startup.K32L2A41A)
endif()

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/gcc/startup_K32L2A41A.S "" device_startup.K32L2A41A)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/arm/startup_K32L2A41A.S "" device_startup.K32L2A41A)
endif()



