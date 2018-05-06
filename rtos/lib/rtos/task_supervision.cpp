/***********************************************
*
* Created by mpatro on 5/6/18.
*
***********************************************/

#include "task_supervision.hpp"
#include <freertos/portable/portmacro.h>

namespace rtos {

void delay_task(std::chrono::milliseconds time)
{
  constexpr TickType_t tick_period_in_ms = portTICK_PERIOD_MS;
  TickType_t ticks = time.count() / tick_period_in_ms;
  vTaskDelay(ticks ? ticks : 1);
}

} // namespace rtos
