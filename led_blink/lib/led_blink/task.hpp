/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#pragma once

#include <rtos/loops.hpp>
#include <rtos/task_supervision.hpp>

#include <stm32/gpio.hpp>

namespace led_blink {

template <typename LoopType = rtos::forever>
class task
{
public:
  explicit task(stm32::gpio& port, stm32::io_pin pin, std::chrono::milliseconds delay)
      : gpio_port{ port }, led_pin(pin), blink_delay(delay)
  {
    using namespace stm32;
    gpio_port.set(gpio::mode::output_pp, pin);
    gpio_port.set(gpio::speed::low, pin);
    gpio_port.set(gpio::pull_resistor::no_pull, pin);
  }

  void run()
  {
    LoopType loop_control;

    while(loop_control())
    {
      gpio_port.toggle(led_pin);
      rtos::delay_task(blink_delay);
    }
  }

private:
  stm32::gpio&  gpio_port;
  stm32::io_pin led_pin;

  std::chrono::milliseconds blink_delay;
};

} // namespace rtos
