/***********************************************
*
* Created by mpatro on 2/17/18.
*
***********************************************/

#pragma once

#include "utils.hpp"

namespace stm32 {
namespace gpio {

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

memory_layout& place_at(uint32_t addr)
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

private:
  memory_layout& memory;
};

} // namespace gpio
} // namespace stm32
