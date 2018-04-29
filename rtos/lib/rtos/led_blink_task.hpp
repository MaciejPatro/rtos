/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#pragma once

#include "loops.hpp"
#include <stm32/gpio.hpp>

namespace rtos {

template <typename LoopType = forever>
class led_blink_task
{
public:
  explicit led_blink_task(stm32::gpio& port) : gpio_port{ port } {}

  void run();

private:
  stm32::gpio& gpio_port;
};

int some_function();

} // namespace rtos
