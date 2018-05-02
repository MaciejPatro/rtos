/***********************************************
*
* Created by mpatro on 4/23/18.
*
***********************************************/

#pragma once

#include <type_traits>
#include <stm32/utils.hpp>
#include <fluent/named_type.hpp>

namespace stm32 {

template <unsigned long long N>
struct is_io_pin : public std::integral_constant<bool, (N >= 0 && N < 16)>::type
{
};

using io_pin = fluent::NamedType<std::uint16_t, struct PinParameter, fluent::Comparable, fluent::Printable>;

constexpr io_pin operator"" _pin(unsigned long long value)
{
  if(value < 16)
    return io_pin(static_cast<std::uint16_t>(value));
  return io_pin(0);
}

} // namespace stm32
