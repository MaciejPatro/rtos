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
  exti                exti_settings{ fake_layout };

  SECTION("should set type as interrupt exclusively")
  {
    exti_settings.set(exti::type::interrupt, 4_pin);
    exti_settings.set(exti::type::interrupt, 3_pin);
    exti_settings.set(exti::type::interrupt, 8_pin);
    exti_settings.set(exti::type::interrupt, 2_pin);

    REQUIRE(0x0000011CU == fake_layout.IMR);
    REQUIRE(0x0U == fake_layout.EMR);

    SECTION("should override type for event if needed")
    {
      exti_settings.set(exti::type::event, 4_pin);
      exti_settings.set(exti::type::event, 3_pin);
      exti_settings.set(exti::type::event, 0_pin);

      REQUIRE(0x00000104U == fake_layout.IMR);
      REQUIRE(0x00000019U == fake_layout.EMR);

      SECTION("interrupt should also override event")
      {
        exti_settings.set(exti::type::interrupt, 0_pin);

        REQUIRE(0x00000105U == fake_layout.IMR);
        REQUIRE(0x00000018U == fake_layout.EMR);
      }
    }
  }

  SECTION("should set correctly rising trigger detection")
  {
    exti_settings.set(exti::trigger_detection::rising, 12_pin);
    exti_settings.set(exti::trigger_detection::rising, 5_pin);
    exti_settings.set(exti::trigger_detection::rising, 2_pin);

    REQUIRE(0x00001024U == fake_layout.RTSR);
    REQUIRE(0x0U == fake_layout.FTSR);

    SECTION("should correctly update triggers for rising_falling trigger")
    {
      exti_settings.set(exti::trigger_detection::rising_falling, 12_pin);
      exti_settings.set(exti::trigger_detection::rising_falling, 8_pin);

      REQUIRE(0x00001124U == fake_layout.RTSR);
      REQUIRE(0x00001100U == fake_layout.FTSR);

      SECTION("should clear rising trigger when only falling is set")
      {
        exti_settings.set(exti::trigger_detection::falling, 12_pin);
        exti_settings.set(exti::trigger_detection::falling, 0_pin);
        exti_settings.set(exti::trigger_detection::falling, 5_pin);

        REQUIRE(0x00000104U == fake_layout.RTSR);
        REQUIRE(0x00001121U == fake_layout.FTSR);
      }
    }
  }
}

} // namespace stm32
