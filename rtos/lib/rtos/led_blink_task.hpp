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
  explicit led_blink_task(stm32::gpio& port, stm32::io_pin pin) : gpio_port{ port }, led_pin(pin) {}

  void run()
  {
    LoopType     loop_control;

    while(loop_control())
    {
      gpio_port.toggle(led_pin);
      osDelay(blink_delay);
    }
  }

private:
  static constexpr std::uint32_t blink_delay = 500;

  stm32::gpio&  gpio_port;
  stm32::io_pin led_pin;
};

} // namespace rtos
