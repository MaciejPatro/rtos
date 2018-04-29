project(stm32_tests)

add_executable(${PROJECT_NAME}
               gpio_tests.cpp
               pin_tests.cpp
               utils_tests.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC catch stm32)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} "-r junit" "-o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.xml")
