project(freertos)

set(headers freertos/croutine.h
        freertos/event_groups.h
        freertos/FreeRTOS.h
        freertos/FreeRTOSConfig_template.h
        freertos/list.h
        freertos/mpu_prototypes.h
        freertos/mpu_wrappers.h
        freertos/portable.h
        freertos/projdefs.h
        freertos/queue.h
        freertos/semphr.h
        freertos/StackMacros.h
        freertos/task.h
        freertos/timers.h
        freertos/CMSIS_RTOS/cmsis_os.h
        freertos/portable/portmacro.h)

set(sources freertos/croutine.c
        freertos/event_groups.c
        freertos/list.c
        freertos/queue.c
        freertos/tasks.c
        freertos/timers.c
        freertos/CMSIS_RTOS/cmsis_os.c
        freertos/portable/port.c
        freertos/portable/heap_4.c)

add_library(freertos STATIC ${headers} ${sources})
target_include_directories(freertos PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(freertos cmsis_lib)