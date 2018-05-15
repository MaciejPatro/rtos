project(rtos_fakes)

set(headers freertos/task.h
            freertos/portable/portmacro.h
            freertos/FreeRTOS.h
            testing/loops.hpp)

set(sources freertos/fakes.cpp)

add_library(rtos_fakes STATIC ${headers} ${sources})

target_link_libraries(rtos_fakes PRIVATE fluent trompeloeil)

target_include_directories(rtos_fakes
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)
