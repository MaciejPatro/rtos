#include "main.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wregister"

#include <hal/stm32f4xx_hal.h>
#include <freertos/CMSIS_RTOS/cmsis_os.h>

#pragma GCC diagnostic pop

#include <rtos/loops.hpp>
#include <rtos/task_supervision.hpp>
#include <led_blink/led_blink_task.hpp>

void        SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void EXTI_Init();

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  EXTI_Init();

  constexpr std::chrono::milliseconds t1_delay{ 250 };
  constexpr std::chrono::milliseconds t2_delay{ 500 };
  constexpr std::chrono::milliseconds t3_delay{ 125 };

  static stm32::gpio::memory_layout& layout = *(stm32::gpio::memory_layout*)(LD4_GPIO_Port);

  static stm32::gpio gpio{ layout };

  static led_blink::led_blink_task<> my_task{ gpio, stm32::io_pin(13), t1_delay };
  static led_blink::led_blink_task<> my1_task{ gpio, stm32::io_pin(12), t2_delay };
  static led_blink::led_blink_task<> my2_task{ gpio, stm32::io_pin(14), t3_delay };
  static led_blink::led_blink_task<> my3_task{ gpio, stm32::io_pin(15), t3_delay };

  rtos::create_task(&my_task, "blinky", 128, osPriorityNormal);
  rtos::create_task(&my1_task, "blinky1", 128, osPriorityNormal);
  rtos::create_task(&my2_task, "blink2", 128, osPriorityNormal);

  vTaskStartScheduler();

  rtos::forever forever;
  while(forever())
  {
  }
}

void EXTI_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef       RCC_OscInitStruct;
  RCC_ClkInitTypeDef       RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /**Configure the main internal regulator output voltage
    */
  do
  {
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    (void)READ_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
  } while(0U);
  do
  {
    MODIFY_REG(PWR->CR, PWR_CR_VOS, (PWR_REGULATOR_VOLTAGE_SCALE1));
    (void)READ_BIT(PWR->CR, PWR_CR_VOS);
  } while(0U);

  /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM       = 8;
  RCC_OscInitStruct.PLL.PLLN       = 336;
  RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ       = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  }

  /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN       = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR       = 2;
  if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
  }

  /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

static void MX_GPIO_Init(void)
{
  do
  {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
    (void)READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
  } while(0U);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
  if(htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_PIN_0 == GPIO_Pin)
  {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
