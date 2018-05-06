/***********************************************
*
* Created by mpatro on 5/6/18.
*
***********************************************/

#pragma once

#include <trompeloeil.hpp>

namespace testing {
namespace fake {

class rtos
{
public:
  virtual void vTaskDelay(const std::uint32_t) = 0;
};

} // namespace fake

class mock_rtos : public trompeloeil::mock_interface<fake::rtos>
{
public:
  static mock_rtos& get_fake();
  IMPLEMENT_MOCK1(vTaskDelay);
};

} // namespace testing
