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
  stm32::gpio_memory_layout fake_memory{ 0x0U };
  stm32::gpio               gpio_port{ fake_memory };

  SECTION("should toggle pin with one loop iteration")
  {
    led_blink_task<once> task{ gpio_port };
    task.run();
    REQUIRE(0x00000004U == fake_memory.BSRR);
  }

  SECTION("should leave pin state unchanged after 2 iterations")
  {
    led_blink_task<twice> task{ gpio_port };
    task.run();
    REQUIRE(0x0U == fake_memory.BSRR);
  }
}

} // namespace rtos
