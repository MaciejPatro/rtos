/***********************************************
*
* Created by mpatro on 4/27/18.
*
***********************************************/

#include <catch.hpp>

#include <stm32/utils.hpp>

#include <type_traits>
#include <iostream>

namespace stm32 {

TEST_CASE("Compile time bit mask generation", "[stm32][utils][bit_mask]")
{
  SECTION("Should correctly generate masks up to 16 bits")
  {
    static_assert(0x0001U == bit_mask<1>::value);
    static_assert(0x0003U == bit_mask<2>::value);
    static_assert(0x0007U == bit_mask<3>::value);
    static_assert(0x00FFU == bit_mask<8>::value);
    static_assert(0x07FFU == bit_mask<11>::value);
    static_assert(0x3FFFU == bit_mask<14>::value);
  }

  SECTION("Ensure default parameter is equal to 1")
  {
    static_assert(bit_mask<>::value == bit_mask<1>::value);
  }
}

} // namespace stm32
