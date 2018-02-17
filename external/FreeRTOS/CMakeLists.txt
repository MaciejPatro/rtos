project(freertos)

set(headers freertos/include/croutine.h
        freertos/include/event_groups.h
        freertos/include/FreeRTOS.h
        freertos/include/FreeRTOSConfig_template.h
        freertos/include/list.h
        freertos/include/mpu_prototypes.h
        freertos/include/mpu_wrappers.h
        freertos/include/portable.h
        freertos/include/projdefs.h
        freertos/include/queue.h
        freertos/include/semphr.h
        freertos/include/StackMacros.h
        freertos/include/task.h
        freertos/include/timers.h
        freertos/CMSIS_RTOS/cmsis_os.h
        freertos/portable/GCC/ARM_CM4F/portmacro.h)

set(sources freertos/croutine.c
        freertos/event_groups.c
        freertos/list.c
        freertos/queue.c
        freertos/tasks.c
        freertos/timers.c
        freertos/CMSIS_RTOS/cmsis_os.c
        freertos/portable/GCC/ARM_CM4F/port.c
        freertos/portable/MemMang/heap_4.c)

add_library(freertos STATIC ${headers} ${sources})
target_include_directories(freertos PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)
