/***********************************************
*
* Created by mpatro on 5/3/18.
*
***********************************************/

#pragma once
#include <freertos/task.h>

namespace rtos {

template <typename T>
void execute_task(void* const task_object)
{
  static_cast<T*>(task_object)->run();
}

template <typename T>
void create_task(T* task_object, const char* const name, uint16_t depth, unsigned long priority)
{
  // TODO: care about failure of task creation
  (void)xTaskCreate(execute_task<T>, name, depth, task_object, priority, nullptr);
}

} // namespace rtos
