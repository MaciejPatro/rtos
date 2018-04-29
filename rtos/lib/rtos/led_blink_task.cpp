/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#include "led_blink_task.hpp"

namespace rtos {

template <typename LoopType>
void led_blink_task<LoopType>::run()
{
  LoopType loop_control;

  while(loop_control())
  {
    gpio_port.toggle_pin(stm32::io_pin<2>::value);
    vTaskDelay(blink_delay);
  }
}

} // namespace rtos
