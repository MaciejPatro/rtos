/***********************************************
*
* Created by mpatro on 4/23/18.
*
***********************************************/

#include <catch.hpp>
#include <stm32/io_pin.hpp>

namespace stm32 {

TEST_CASE("Pin handling", "[stm32][pin]")
{
  SECTION("Only 0-15 pins are correct")
  {
    static_assert(is_io_pin<0>::value);
    static_assert(is_io_pin<1>::value);
    static_assert(is_io_pin<2>::value);
    static_assert(is_io_pin<3>::value);
    static_assert(is_io_pin<4>::value);
    static_assert(is_io_pin<5>::value);
    static_assert(is_io_pin<6>::value);
    static_assert(is_io_pin<7>::value);
    static_assert(is_io_pin<8>::value);
    static_assert(is_io_pin<9>::value);
    static_assert(is_io_pin<10>::value);
    static_assert(is_io_pin<11>::value);
    static_assert(is_io_pin<12>::value);
    static_assert(is_io_pin<13>::value);
    static_assert(is_io_pin<14>::value);
    static_assert(is_io_pin<15>::value);
    static_assert(!is_io_pin<16>::value);
  }

  SECTION("Should allow comparisons between strong types and get operator")
  {
    REQUIRE(5_pin == io_pin(5));
    REQUIRE(5_pin != io_pin(4));
    REQUIRE(2 == io_pin(2).get());
  }
}

} // namespace stm32
