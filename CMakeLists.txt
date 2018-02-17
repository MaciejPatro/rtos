SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.10)

# specify the cross compiler
SET(CMAKE_C_COMPILER_WORKS 1)
SET(TOOLCHAIN_PATH /home/mpatro/Downloads/dev_tools/gcc-arm/gcc-arm-none-eabi-7-2017-q4-major/bin)
SET(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
SET(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-g++)
set(AS ${TOOLCHAIN_PATH}/arm-none-eabi-as)
set(AR ${TOOLCHAIN_PATH}/arm-none-eabi-ar)
set(OBJCOPY ${TOOLCHAIN_PATH}/arm-none-eabi-objcopy)
set(OBJDUMP ${TOOLCHAIN_PATH}/arm-none-eabi-objdump)
set(SIZE ${TOOLCHAIN_PATH}/arm-none-eabi-size)

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld)

add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING)
SET(COMMON_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -mthumb-interwork -ffunction-sections
        -fdata-sections -g -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs")

SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++1z")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu11")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections -T ${LINKER_SCRIPT}")

PROJECT(rtos C ASM)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\) -DUSE_HAL_DRIVER -DSTM32F407xx )

file(GLOB_RECURSE SOURCES "startup/*.*" "external/*.*" "Drivers/*.*" "Src/*.*" "Inc/*.*")

include_directories(Inc
        external/Drivers/STM32F4xx_HAL_Driver/Inc
        external/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
        external/FreeRTOS/Source/portable/GCC/ARM_CM4F
        external/Drivers/CMSIS/Device/ST/STM32F4xx/Include
        external/FreeRTOS/Source/include
        external/FreeRTOS/Source/CMSIS_RTOS
        external/Drivers/CMSIS/Include
        stm32/gpio)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

add_custom_target(UPLOAD
        ${TOOLCHAIN_PATH}/arm-none-eabi-gdb -iex "target remote tcp:127.0.0.1:3333"
        -iex "monitor program $<TARGET_FILE:${PROJECT_NAME}.elf>"
        -iex "monitor reset init"
        -iex "disconnect" -iex "quit")

add_subdirectory(external)