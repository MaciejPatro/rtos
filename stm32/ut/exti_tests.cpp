/***********************************************
*
* Created by mpatro on 5/19/18.
*
***********************************************/

#include <catch.hpp>
#include <stm32/exti.hpp>

namespace stm32 {

TEST_CASE("Exti", "[stm32][exti]")
{
  exti::memory_layout fake_layout{};
  exti                interrupts{ fake_layout };

  SECTION("should set correctly rising trigger detection")
  {
    interrupts.set(exti::trigger_detection::rising, 12_pin);
    interrupts.set(exti::trigger_detection::rising, 5_pin);
    interrupts.set(exti::trigger_detection::rising, 2_pin);

    REQUIRE(0x00001024U == fake_layout.RTSR);
    REQUIRE(0x0U == fake_layout.FTSR);

    SECTION("should correctly update triggers for rising_falling trigger")
    {
      interrupts.set(exti::trigger_detection::rising_falling, 12_pin);
      interrupts.set(exti::trigger_detection::rising_falling, 8_pin);

      REQUIRE(0x00001124U == fake_layout.RTSR);
      REQUIRE(0x00001100U == fake_layout.FTSR);

      SECTION("should clear rising trigger when only falling is set")
      {
        interrupts.set(exti::trigger_detection::falling, 12_pin);
        interrupts.set(exti::trigger_detection::falling, 0_pin);
        interrupts.set(exti::trigger_detection::falling, 5_pin);

        REQUIRE(0x00000104U == fake_layout.RTSR);
        REQUIRE(0x00001121U == fake_layout.FTSR);
      }
    }
  }
}

} // namespace stm32
