project(product)

set(headers product/led_blink_task.hpp)
set(sources product/led_blink_task.cpp)


add_library(product STATIC ${headers} ${sources})

target_link_libraries(product PUBLIC stm32)

target_include_directories(product
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)
