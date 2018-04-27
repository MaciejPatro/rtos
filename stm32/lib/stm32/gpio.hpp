/***********************************************
*
* Created by mpatro on 2/17/18.
*
***********************************************/

#pragma once

#include "memory_address.hpp"
#include "utils.hpp"
#include "pin.hpp"

namespace stm32 {
namespace gpio {

enum class mode : std::uint32_t
{
  input     = 0x00000000U,
  output_pp = 0x00000001U
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

memory_layout& place_at(std::uint32_t addr)
{
  return *reinterpret_cast<memory_layout*>(addr);
}

memory_layout& gpio_a()
{
  constexpr auto gpio_a_address = 0x12345678;
  return place_at(gpio_a_address);
}

class gpio
{
public:
  gpio(memory_layout& mem) : memory(mem) {}

  void set_mode(mode m, std::uint16_t pin)
  {
    fill_setting<mode, 2>(memory.MODER, m, pin);
    fill_setting<io_type, 1>(memory.OTYPER, get_io_type(m), pin);
  }

  void set_speed(speed s, std::uint16_t pin)
  {
    fill_setting<speed, 2>(memory.OSPEEDR, s, pin);
  }

private:
  enum class io_type
  {
    input  = 0x00000000U,
    output = 0x00000001U
  };

  io_type get_io_type(mode m)
  {
    return m == mode::input ? io_type::input : io_type::output;
  }

  memory_layout& memory;
};

} // namespace gpio
} // namespace stm32
