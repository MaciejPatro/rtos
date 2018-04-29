project(product_tests)

add_executable(product_tests led_blink_task_tests.cpp)

target_link_libraries(product_tests PUBLIC catch product)
add_test(NAME product_tests COMMAND product_tests "-r junit" "-o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.xml")
