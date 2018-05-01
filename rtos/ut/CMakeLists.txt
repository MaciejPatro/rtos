project(rtos_tests)

add_executable(${PROJECT_NAME} led_blink_task_tests.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC catch catch_support rtos)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} "-s" "-r junit" "-o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.xml")
