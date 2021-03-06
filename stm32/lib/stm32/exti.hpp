/***********************************************
*
* Created by mpatro on 5/19/18.
*
***********************************************/

#pragma once

#include "memory_address.hpp"
#include "io_pin.hpp"
#include "utils.hpp"

namespace stm32 {

class exti
{
public:
  struct memory_layout
  {
    memory_address IMR;
    memory_address EMR;
    memory_address RTSR;
    memory_address FTSR;
    memory_address SWIER;
    memory_address PR;
  };

  enum class type
  {
    interrupt,
    event
  };

  enum class trigger_detection
  {
    rising,
    falling,
    rising_falling
  };

  explicit exti(memory_layout& layout) : memory(layout) {}

  void set(type t, io_pin pin)
  {
    if(type::event == t)
    {
      fill_setting(memory.IMR, state::clear, pin.get());
      fill_setting(memory.EMR, state::set, pin.get());
    }
    else
    {
      fill_setting(memory.IMR, state::set, pin.get());
      fill_setting(memory.EMR, state::clear, pin.get());
    }
  }

  void set(trigger_detection detection, io_pin pin)
  {
    fill_setting(memory.RTSR, state::set, pin.get());
    fill_setting(memory.FTSR, state::set, pin.get());

    if(trigger_detection::rising == detection)
      fill_setting(memory.FTSR, state::clear, pin.get());
    else if(trigger_detection::falling == detection)
      fill_setting(memory.RTSR, state::clear, pin.get());
  }

private:
  enum class state
  {
    set   = 1,
    clear = 0
  };
  memory_layout& memory;
};

} // namespace stm32