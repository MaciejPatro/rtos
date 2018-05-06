/***********************************************
*
* Created by mpatro on 4/29/18.
*
***********************************************/

#pragma once

#include <cstdint>

using TickType_t = std::uint32_t;
typedef void (*TaskFunction_t)(void*);
typedef void* TaskHandle_t;

void vTaskDelay(const std::uint32_t);

long xTaskCreate(TaskFunction_t      pxTaskCode,
                 const char* const   pcName,
                 const uint16_t      usStackDepth,
                 void* const         pvParameters,
                 long                uxPriority,
                 TaskHandle_t* const pxCreate);
