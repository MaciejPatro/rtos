/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#include "led_blink_task.hpp"
#include <stm32/gpio.hpp>

namespace product {

int some_function()
{
  return stm32::bit_mask<5>::value;
}

} // namespace product
