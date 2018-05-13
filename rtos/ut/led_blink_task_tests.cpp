/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <trompeloeil.hpp>
#include <testing/loops.hpp>
#include <freertos/fakes.hpp>

#include <rtos/led_blink_task.hpp>

namespace trompeloeil {
template <>
void reporter<specialized>::send(severity s, const char* file, unsigned long line, const char* msg)
{
  std::ostringstream os;
  if(line)
    os << file << ':' << line << '\n';
  os << msg;
  auto failure = os.str();
  if(s == severity::fatal)
  {
    FAIL(failure);
  }
  else
  {
    CAPTURE(failure);
    CHECK(failure.empty());
  }
}
} // namespace trompeloeil

namespace rtos {

TEST_CASE("Led blink task", "[rtos]")
{
  constexpr std::chrono::milliseconds blink_delay{ 500 };
  stm32::gpio::memory_layout          fake_memory{ 0x0U };

  stm32::gpio   gpio_port{ fake_memory };
  stm32::io_pin pin{ 13 };

  SECTION("should configure gpio for given pin")
  {
    led_blink_task<once> task{ gpio_port, pin, blink_delay };

    REQUIRE(0x00000000U == fake_memory.OSPEEDR);
    REQUIRE(0x00000000U == fake_memory.PUPDR);
    REQUIRE(0x04000000U == fake_memory.MODER);
  }

  SECTION("should toggle pin with one loop iteration")
  {
    REQUIRE_CALL(testing::fake_rtos(), vTaskDelay(blink_delay.count()));

    led_blink_task<once> task{ gpio_port, pin, blink_delay };
    task.run();

    REQUIRE(0x00002000U == fake_memory.ODR);
  }

  SECTION("should leave pin state unchanged after 2 iterations")
  {
    REQUIRE_CALL(testing::fake_rtos(), vTaskDelay(blink_delay.count())).TIMES(2);

    led_blink_task<twice> task{ gpio_port, pin, blink_delay };
    task.run();

    REQUIRE(0x0U == fake_memory.ODR);
  }
}

} // namespace rtos
