project(stm32_tests)

add_executable(stm32_tests
               gpio_tests.cpp
               pin_tests.cpp
               utils_tests.cpp)

target_link_libraries(stm32_tests catch stm32)
add_test(NAME stm32_tests COMMAND stm32_tests)
