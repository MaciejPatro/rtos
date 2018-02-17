project(stm32_hal)

add_library(hal_gpio STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_gpio.c)
target_include_directories(hal_gpio PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)
