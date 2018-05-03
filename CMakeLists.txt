set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.10)

option(testing "testing" OFF)

if(testing)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wpedantic -Wno-c++98-compat")

    if(asan)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    elseif(msan)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
    elseif(tsan)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    elseif(coverage)
        # does -g option is needed?
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()

    enable_testing()
    add_subdirectory(testing/catch2)
    add_subdirectory(testing/support)
    add_subdirectory(external/fluent)
    add_subdirectory(stm32)
    add_subdirectory(rtos)
else()
    # specify the cross compiler
    set(CMAKE_C_COMPILER_WORKS 1)
    set(CMAKE_CXX_COMPILER_WORKS 1)
    set(TOOLCHAIN_PATH /home/mpatro/Downloads/dev_tools/gcc-arm/gcc-arm-none-eabi-7-2017-q4-major/bin)
    set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
    set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-g++)
    set(AS ${TOOLCHAIN_PATH}/arm-none-eabi-as)
    set(AR ${TOOLCHAIN_PATH}/arm-none-eabi-ar)
    set(OBJCOPY ${TOOLCHAIN_PATH}/arm-none-eabi-objcopy)
    set(OBJDUMP ${TOOLCHAIN_PATH}/arm-none-eabi-objdump)
    set(SIZE ${TOOLCHAIN_PATH}/arm-none-eabi-size)

    set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld)

    add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING)
    set(FLOATING_POINT_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
    set(MTHUMB_FLAGS "-mthumb -mthumb-interwork")
    set(COMMON_FLAGS "-mcpu=cortex-m4 ${FLOATING_POINT_FLAGS} ${MTHUMB_FLAGS} -ffunction-sections -fdata-sections -g \
    -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs")

    set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++1z")
    set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu11")
    set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections -T ${LINKER_SCRIPT}")

    PROJECT(deployed_rtos CXX C ASM)

    add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\) -DUSE_HAL_DRIVER -DSTM32F407xx )

    file(GLOB_RECURSE SOURCES "startup/*.*" "base/*.*")

    include_directories(base)

    add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
    add_subdirectory(external)
    add_subdirectory(rtos)
    add_subdirectory(stm32)
    target_link_libraries(${PROJECT_NAME}.elf PUBLIC
            freertos
            rtos
            hal
            hal_rcc
            hal_gpio
            hal_tim
            hal_cortex
            hal_tim_ex
            hal_rcc_ex)

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
endif()
