# Add set(CONFIG_USE_middleware_mmcau_cm0p true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_LIST_DIR}/
)


if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux OR CONFIG_TOOLCHAIN STREQUAL iar))
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
-Wl,--start-group
${CMAKE_CURRENT_LIST_DIR}/asm-cm0p/lib_mmcau-cm0p.a
-Wl,--end-group
)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk)
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
-Wl,--start-group
${CMAKE_CURRENT_LIST_DIR}/asm-cm0p/lib_mmcau-cm0p.lib
-Wl,--end-group
)
endif()


