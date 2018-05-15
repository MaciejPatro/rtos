project(led_blink)

set(headers led_blink/task.hpp)
set(sources led_blink/task.cpp)

add_library(${PROJECT_NAME} STATIC ${headers} ${sources})

if(testing)
    target_link_libraries(${PROJECT_NAME} PRIVATE stm32 rtos_fakes rtos)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE stm32 freertos rtos)
endif()

target_include_directories(${PROJECT_NAME}
        PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>)
