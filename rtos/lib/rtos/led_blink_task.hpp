/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#pragma once

#include "loops.hpp"
#include <stm32/gpio.hpp>
#include <freertos/CMSIS_RTOS/cmsis_os.h>

namespace rtos {

template <typename LoopType = forever>
class led_blink_task
{
public:
  explicit led_blink_task(stm32::gpio& port) : gpio_port{ port } {}

  void run()
  {
    LoopType loop_control;

    while(loop_control())
    {
      gpio_port.toggle_pin(stm32::io_pin<2>::value);
      osDelay(blink_delay);
    }
  }

private:
  static constexpr std::uint32_t blink_delay = 200;
  stm32::gpio&                   gpio_port;
};

} // namespace rtos
