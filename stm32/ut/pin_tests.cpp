/***********************************************
*
* Created by mpatro on 4/23/18.
*
***********************************************/

#include <catch.hpp>
#include <stm32/pin.hpp>

namespace stm32 {

TEST_CASE("Pin handling", "[stm32][pin]")
{
  SECTION("Only 0-15 pins are correct")
  {
    static_assert(is_pin<0>::value);
    static_assert(is_pin<1>::value);
    static_assert(is_pin<2>::value);
    static_assert(is_pin<3>::value);
    static_assert(is_pin<4>::value);
    static_assert(is_pin<5>::value);
    static_assert(is_pin<6>::value);
    static_assert(is_pin<7>::value);
    static_assert(is_pin<8>::value);
    static_assert(is_pin<9>::value);
    static_assert(is_pin<10>::value);
    static_assert(is_pin<11>::value);
    static_assert(is_pin<12>::value);
    static_assert(is_pin<13>::value);
    static_assert(is_pin<14>::value);
    static_assert(is_pin<15>::value);
    static_assert(!is_pin<16>::value);
  }

  SECTION("Pin should correctly indicate bit in memory")
  {
    static_assert(0x0001 == pin<0>::value);
    static_assert(0x0002 == pin<1>::value);
    static_assert(0x0004 == pin<2>::value);
    static_assert(0x0008 == pin<3>::value);
    static_assert(0x0010 == pin<4>::value);
    static_assert(0x0020 == pin<5>::value);
    static_assert(0x0040 == pin<6>::value);
    static_assert(0x0080 == pin<7>::value);
    static_assert(0x0100 == pin<8>::value);
    static_assert(0x0200 == pin<9>::value);
    static_assert(0x0400 == pin<10>::value);
    static_assert(0x0800 == pin<11>::value);
    static_assert(0x1000 == pin<12>::value);
    static_assert(0x2000 == pin<13>::value);
    static_assert(0x4000 == pin<14>::value);
    static_assert(0x8000 == pin<15>::value);
  }
}

} // namespace stm32
