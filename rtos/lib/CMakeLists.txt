project(rtos)

set(headers rtos/led_blink_task.hpp rtos/loops.hpp)
set(sources rtos/led_blink_task.cpp)


add_library(rtos STATIC ${headers} ${sources})

target_link_libraries(rtos PUBLIC stm32)

target_include_directories(rtos
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)
