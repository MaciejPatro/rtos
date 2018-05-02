/***********************************************
*
* Created by mpatro on 4/22/18.
*
***********************************************/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <stm32/gpio.hpp>

namespace stm32 {

TEST_CASE("Gpio", "[stm32][gpio]")
{
  gpio_memory_layout fake_memory{};
  gpio               tested{ fake_memory };

  SECTION("should correctly setup IO mode as output for given pin")
  {
    tested.set_mode(gpio::mode::output_pp, 5_pin);
    REQUIRE(0x00000400U == fake_memory.MODER);
    REQUIRE(0x00000020U == fake_memory.OTYPER);

    SECTION("additional setup should not reset previous setting")
    {
      tested.set_mode(gpio::mode::output_pp, 0_pin);
      REQUIRE(0x00000401U == fake_memory.MODER);
      REQUIRE(0x00000021U == fake_memory.OTYPER);

      SECTION("new setup should override previous without changing other pins")
      {
        tested.set_mode(gpio::mode::input, 5_pin);
        REQUIRE(0x00000001U == fake_memory.MODER);
        REQUIRE(0x00000001U == fake_memory.OTYPER);
      }
    }
  }

  SECTION("should correctly set pull resistor state")
  {
    tested.set_pull_resistor(gpio::pull_resistor::pull_up, 6_pin);
    tested.set_pull_resistor(gpio::pull_resistor::pull_down, 5_pin);
    REQUIRE(0x00001800U == fake_memory.PUPDR);

    SECTION("should change only 5th pin state to clean")
    {
      tested.set_pull_resistor(gpio::pull_resistor::no_pull, 5_pin);
      REQUIRE(0x00001000U == fake_memory.PUPDR);
    }
  }

  SECTION("should set proper bit via first toggle")
  {
    tested.toggle_pin(0_pin);
    tested.toggle_pin(1_pin);
    tested.toggle_pin(3_pin);
    REQUIRE(0x0000000BU == fake_memory.BSRR);

    SECTION("second time it should clear the state")
    {
      tested.toggle_pin(1_pin);
      REQUIRE(0x00000009U == fake_memory.BSRR);
    }
  }
}

} // namespace stm32
