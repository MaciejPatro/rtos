/***********************************************
*
* Created by mpatro on 2/17/18.
*
***********************************************/

#pragma once

#include "memory_address.hpp"
#include "utils.hpp"
#include "io_pin.hpp"

namespace stm32 {

class gpio
{
public:
  struct memory_layout
  {
    memory_address MODER;
    memory_address OTYPER;
    memory_address OSPEEDR;
    memory_address PUPDR;
    memory_address IDR;
    memory_address ODR;
    memory_address BSRR;
    memory_address LCKR;
    memory_address AFR[2];
  };

  gpio(memory_layout& mem) : memory(mem) {}

  enum class mode : std::uint32_t
  {
    input     = 0x00000000U,
    output_pp = 0x00000001U,
    output_od = 0x00000011U
  };

  enum class pull_state : std::uint32_t
  {
    no_pull = 0x00000000U,
    pull_up = 0x00000001U
  };

  enum class speed : std::uint32_t
  {
    low    = 0x00000000U,
    medium = 0x00000001U
  };

  enum class pull_resistor : std::uint32_t
  {
    no_pull   = 0x00000000U,
    pull_up   = 0x00000001U,
    pull_down = 0x00000002U
  };

  void set(mode m, io_pin pin)
  {
    fill_setting<mode, 2>(memory.MODER, m, pin.get());
  }

  void set(speed s, io_pin pin)
  {
    fill_setting<speed, 2>(memory.OSPEEDR, s, pin.get());
  }

  void set(pull_resistor p, io_pin pin)
  {
    fill_setting<pull_resistor, 2>(memory.PUPDR, p, pin.get());
  }

  void toggle(io_pin pin)
  {
    memory.ODR ^= 1 << pin.get();
  }

private:
  enum class io_type
  {
    input  = 0x00000000U,
    output = 0x00000001U
  };

  memory_layout& memory;
};

} // namespace stm32
