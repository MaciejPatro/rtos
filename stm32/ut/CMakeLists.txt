project(stm32_tests)

add_executable(${PROJECT_NAME}
               gpio_tests.cpp
               pin_tests.cpp
               utils_tests.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE catch stm32)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} "-s" "-r junit" "-o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.xml")
