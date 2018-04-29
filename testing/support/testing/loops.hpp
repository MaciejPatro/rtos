/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#pragma once

namespace rtos {

template <std::size_t T>
struct times
{
  mutable std::size_t run_count = T;

  bool operator()() const
  {
    run_count-- != 0;
  };
};

using once = times<1>;
using twice = times<2>;

} // namespace rtos
