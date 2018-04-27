/***********************************************
*
* Created by mpatro on 2/17/18.
*
***********************************************/

#pragma once

#include "memory_address.hpp"
#include <iostream>

namespace stm32 {

template <std::uint32_t N = 1>
struct bit_mask
{
  static constexpr std::uint32_t value = (1 << N) - 1;
};

template <>
struct bit_mask<0U>
{
  static constexpr std::uint32_t value = 0;
};

template <typename Setting, std::uint32_t MaskSize = 1>
constexpr void fill_setting(memory_address& address, Setting setting, std::uint32_t shift)
{
  address &= ~(bit_mask<MaskSize>::value << shift * MaskSize);
  address |= static_cast<std::uint32_t>(setting) << (shift * MaskSize);
}

} // namespace stm32
