/***********************************************
*
* Created by mpatro on 2/17/18.
*
***********************************************/

#pragma once

#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace utils {

template<typename T, T N, T M, typename = typename std::enable_if<std::is_integral<T>::value>::type>
struct is_greater_than: public std::integral_constant<bool, (N > M)>::type
{
};

} // utils
} // stm32