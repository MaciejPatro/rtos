project(stm32_hal)

add_library(hal_gpio STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_gpio.c)
target_include_directories(hal_gpio PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_tim STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_tim.c)
target_include_directories(hal_tim PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_tim_ex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_tim_ex.c)
target_include_directories(hal_tim_ex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_spi STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_spi.c)
target_include_directories(hal_spi PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_rcc STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_rcc.c)
target_include_directories(hal_rcc PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_rcc_ex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_rcc_ex.c)
target_include_directories(hal_rcc_ex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_pwr STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_pwr.c)
target_include_directories(hal_pwr PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_pwr_ex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_pwr_ex.c)
target_include_directories(hal_pwr_ex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)