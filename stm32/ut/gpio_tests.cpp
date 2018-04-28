/***********************************************
*
* Created by mpatro on 4/22/18.
*
***********************************************/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <stm32/gpio.hpp>

namespace stm32 {
namespace gpio {

TEST_CASE("GPIO basic testing", "[stm32][gpio]")
{
  memory_layout fake_memory{};
  gpio          tested{ fake_memory };

  SECTION("Gpio should correctly setup IO mode as output for given pin")
  {
    tested.set_mode(mode::output_pp, io_pin<5>::value);
    REQUIRE(0x00000400U == fake_memory.MODER);
    REQUIRE(0x00000020U == fake_memory.OTYPER);

    SECTION("Additional setup should not reset previous setting")
    {
      tested.set_mode(mode::output_pp, io_pin<0>::value);
      REQUIRE(0x00000401U == fake_memory.MODER);
      REQUIRE(0x00000021U == fake_memory.OTYPER);

      SECTION("New setup should override previous without changing other pins")
      {
        tested.set_mode(mode::input, io_pin<5>::value);
        REQUIRE(0x00000001U == fake_memory.MODER);
        REQUIRE(0x00000001U == fake_memory.OTYPER);
      }
    }
  }

  SECTION("Gpio should correctly set pull resistor state")
  {
    tested.set_pull_resistor(pull_resistor::pull_up, io_pin<6>::value);
    tested.set_pull_resistor(pull_resistor::pull_down, io_pin<5>::value);
    REQUIRE(0x00001800U == fake_memory.PUPDR);

    SECTION("Should change only 5th pin state to clean")
    {
      tested.set_pull_resistor(pull_resistor::no_pull, io_pin<5>::value);
      REQUIRE(0x00001000U == fake_memory.PUPDR);
    }
  }
}

} // namespace gpio
} // namespace stm32
