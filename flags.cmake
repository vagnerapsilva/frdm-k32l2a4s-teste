IF(NOT DEFINED FPU)  
    SET(FPU "-mfloat-abi=soft")  
ENDIF()  

IF(NOT DEFINED SPECS)  
    SET(SPECS "--specs=nano.specs --specs=nosys.specs")  
ENDIF()  

IF(NOT DEFINED DEBUG_CONSOLE_CONFIG)  
    SET(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=1")  
ENDIF()  

SET(CMAKE_ASM_FLAGS_DEBUG " \
    ${CMAKE_ASM_FLAGS_DEBUG} \
    -D__STARTUP_CLEAR_BSS \
    -DMCUXPRESSO_SDK \
    -DCPU_K32L2A41VLL1A \
    -DK32L2A41A_SERIES \
    -DOSA_USED \
    -g \
    -mthumb \
    -mcpu=cortex-m0plus \
    ${FPU} \
")
SET(CMAKE_ASM_FLAGS_RELEASE " \
    ${CMAKE_ASM_FLAGS_RELEASE} \
    -D__STARTUP_CLEAR_BSS \
    -DMCUXPRESSO_SDK \
    -DCPU_K32L2A41VLL1A \
    -DK32L2A41A_SERIES \
    -DOSA_USED \
    -mthumb \
    -mcpu=cortex-m0plus \
    ${FPU} \
")
SET(CMAKE_C_FLAGS_DEBUG " \
    ${CMAKE_C_FLAGS_DEBUG} \
    -include ${ProjDirPath}/source/mcux_config.h \
    -DDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -DUSB_STACK_BM \
    -DUSB_STACK_USE_DEDICATED_RAM=1 \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DCPU_K32L2A41VLL1A \
    -DK32L2A41A_SERIES \
    -DOSA_USED \
    -DUSE_RTOS=0 \
    -g \
    -O0 \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -std=gnu99 \
    -mcpu=cortex-m0plus \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_C_FLAGS_RELEASE " \
    ${CMAKE_C_FLAGS_RELEASE} \
    -include ${ProjDirPath}/source/mcux_config.h \
    -DNDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -DUSB_STACK_BM \
    -DUSB_STACK_USE_DEDICATED_RAM=1 \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DCPU_K32L2A41VLL1A \
    -DK32L2A41A_SERIES \
    -DOSA_USED \
    -DUSE_RTOS=0 \
    -Os \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -std=gnu99 \
    -mcpu=cortex-m0plus \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_CXX_FLAGS_DEBUG " \
    ${CMAKE_CXX_FLAGS_DEBUG} \
    -DDEBUG \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DCPU_K32L2A41VLL1A \
    -DK32L2A41A_SERIES \
    -DOSA_USED \
    -DUSE_RTOS=0 \
    -g \
    -O0 \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
    -mcpu=cortex-m0plus \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_CXX_FLAGS_RELEASE " \
    ${CMAKE_CXX_FLAGS_RELEASE} \
    -DNDEBUG \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DCPU_K32L2A41VLL1A \
    -DK32L2A41A_SERIES \
    -DOSA_USED \
    -DUSE_RTOS=0 \
    -Os \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
    -mcpu=cortex-m0plus \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG " \
    ${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
    -g \
    -Xlinker \
    --defsym=__heap_size__=0x2000 \
    -Xlinker \
    --defsym=__stack_size__=0x2000 \
    -Xlinker \
    -Map=output.map \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Wl,--gc-sections \
    -Wl,-static \
    -Wl,--print-memory-usage \
    -mcpu=cortex-m0plus \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/K32L2A41A/armgcc/K32L2A41xxxxA_flash.ld\" -static \
    -u _printf_float \
")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
    -Xlinker \
    --defsym=__heap_size__=0x2000 \
    -Xlinker \
    --defsym=__stack_size__=0x2000 \
    -Xlinker \
    -Map=output.map \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Wl,--gc-sections \
    -Wl,-static \
    -Wl,--print-memory-usage \
    -mcpu=cortex-m0plus \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/K32L2A41A/armgcc/K32L2A41xxxxA_flash.ld\" -static \
")
