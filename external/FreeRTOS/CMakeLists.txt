project(freertos)

set(headers Source/include/croutine.h
            Source/include/event_groups.h
            Source/include/FreeRTOS.h
            Source/include/FreeRTOSConfig_template.h
            Source/include/list.h
            Source/include/mpu_prototypes.h
            Source/include/mpu_wrappers.h
            Source/include/portable.h
            Source/include/projdefs.h
            Source/include/queue.h
            Source/include/semphr.h
            Source/include/StackMacros.h
            Source/include/task.h
            Source/include/timers.h
            Source/CMSIS_RTOS/cmsis_os.h
            Source/portable/GCC/ARM_CM4F/portmacro.h)

set(sources Source/croutine.c
            Source/event_groups.c
            Source/list.c
            Source/queue.c
            Source/tasks.c
            Source/timers.c
            Source/CMSIS_RTOS/cmsis_os.c
            Source/portable/GCC/ARM_CM4F/port.c
            Source/portable/MemMang/heap_4.c)

add_library(freertos STATIC ${headers} ${sources})
target_include_directories(freertos PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>)
