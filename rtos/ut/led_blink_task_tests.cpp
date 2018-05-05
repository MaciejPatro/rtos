/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <rtos/led_blink_task.hpp>
#include <testing/loops.hpp>

namespace rtos {

TEST_CASE("Led blink task", "[rtos]")
{
  stm32::gpio::memory_layout fake_memory{ 0x0U };

  stm32::gpio   gpio_port{ fake_memory };
  stm32::io_pin pin{ 13 };

  SECTION("should toggle pin with one loop iteration")
  {
    led_blink_task<once> task{ gpio_port, pin };
    task.run();
    REQUIRE(0x00002000U == fake_memory.ODR);
  }

  SECTION("should leave pin state unchanged after 2 iterations")
  {
    led_blink_task<twice> task{ gpio_port, pin };
    task.run();
    REQUIRE(0x0U == fake_memory.ODR);
  }
}

} // namespace rtos
