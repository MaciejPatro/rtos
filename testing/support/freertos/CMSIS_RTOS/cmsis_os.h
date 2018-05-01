/***********************************************
*
* Created by mpatro on 5/1/18.
*
***********************************************/

#pragma once

typedef enum
{
  osOK = 0
} osStatus;

osStatus osDelay(std::uint32_t)
{
  return osOK;
}
