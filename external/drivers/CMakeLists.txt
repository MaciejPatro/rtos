project(stm32_hal)

add_library(cmsis_lib INTERFACE)
target_include_directories(cmsis_lib INTERFACE .)

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

add_library(hal_pwr_i2s STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_i2s.c)
target_include_directories(hal_pwr_i2s PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_pwr_i2s_ex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_i2s_ex.c)
target_include_directories(hal_pwr_i2s_ex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_pwr_i2c_ex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_i2c_ex.c)
target_include_directories(hal_pwr_i2c_ex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_pwr_i2c STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_i2c.c)
target_include_directories(hal_pwr_i2c PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_gpio STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_gpio.c)
target_include_directories(hal_gpio PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_flash STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_flash.c)
target_include_directories(hal_flash PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_flash_ex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_flash_ex.c)
target_include_directories(hal_flash_ex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_flash_ramfunc STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_flash_ramfunc.c)
target_include_directories(hal_flash_ramfunc PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_dma STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_dma.c)
target_include_directories(hal_dma PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_dma_ex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_dma_ex.c)
target_include_directories(hal_dma_ex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal_cortex STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal_cortex.c)
target_include_directories(hal_cortex PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)

add_library(hal STATIC hal/stm32f4xx_hal.h hal/stm32f4xx_hal.c)
target_include_directories(hal PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)
