project(catch_support)

set(headers freertos/task.h freertos/portable/portmacro.h testing/loops.hpp)
set(sources freertos/task.cpp)

add_library(catch_support STATIC ${headers} ${sources})

target_link_libraries(catch_support PUBLIC fluent)

target_include_directories(catch_support
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)
