project(rtos)

set(headers rtos/loops.hpp rtos/task_supervision.hpp)
set(sources rtos/task_supervision.cpp)

add_library(rtos STATIC ${headers} ${sources})

if(testing)
    target_link_libraries(rtos PUBLIC stm32 rtos_fakes)
else()
    target_link_libraries(rtos PUBLIC stm32 freertos)
endif()

target_include_directories(rtos
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)
