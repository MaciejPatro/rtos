/***********************************************
*
* Created by mpatro on 4/23/18.
*
***********************************************/

#pragma once

#include <type_traits>
#include <stm32/utils.hpp>

namespace stm32 {

template <std::uint16_t N>
struct is_io_pin : public std::integral_constant<bool, (N >= 0 && N < 16)>::type
{
};

template <std::uint16_t N>
struct io_pin
{
  static_assert(is_io_pin<N>::value, "N must be a pin");
  static constexpr uint16_t value = N;
};

} // namespace stm32
