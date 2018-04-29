/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#pragma once

namespace rtos {

struct forever
{
  bool operator()() const { return true; };
};

} // namespace rtos