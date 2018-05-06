/***********************************************
*
* Created by mpatro on 5/6/18.
*
***********************************************/

#include "task.h"
#include "fakes.hpp"


namespace testing {

mock_rtos mocked_rtos;

mock_rtos& mock_rtos::get_fake()
{
  return mocked_rtos;
}

} // namespace testing

void vTaskDelay(const std::uint32_t ticks)
{
  testing::mocked_rtos.vTaskDelay(ticks);
}
