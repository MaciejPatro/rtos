/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <rtos/led_blink_task.hpp>

namespace rtos {

TEST_CASE("Basic test", "[product]")
{
  SECTION("FIRST TEST")
  {
    REQUIRE(0x1f == rtos::some_function());
  }
}

} // namespace rtos
