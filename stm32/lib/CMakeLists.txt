project(stm32)

set(headers stm32/gpio.hpp
            stm32/exti.hpp
            stm32/utils.hpp
            stm32/io_pin.hpp
            stm32/memory_address.hpp)

set(sources stm32/gpio.cpp)

add_library(stm32 STATIC ${headers} ${sources})

target_link_libraries(stm32 PUBLIC fluent)

target_include_directories(stm32
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)
