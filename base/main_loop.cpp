/***********************************************
*
* Created by mpatro on 4/30/18.
*
***********************************************/

#include "main_loop.hpp"
#include <rtos/loops.hpp>

void main_loop()
{
  rtos::forever forever_loop;
  while(forever_loop())
  {
  }
}
