project(stm32)

set(headers stm32/gpio.hpp
            stm32/utils.hpp
            stm32/pin.hpp
            stm32/memory_address.hpp)

set(sources stm32/gpio.cpp)

add_library(stm32 STATIC ${headers} ${sources})

target_include_directories(stm32
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)