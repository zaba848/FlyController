/*
 * CPeripherials.cpp
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */

#include <CPeripherials.h>


uint8_t CPeripherials::gyroErr ;
uint8_t CPeripherials::accErr  ;

void CPeripherials::peripherialInit() {

	 gyroErr = 0;
	 accErr  = 0;

	  HAL_Init();
	  SystemClock_Config();
	  MX_GPIO_Init();
	  MX_USART2_UART_Init();
	  BSP_LED_Init(LED_GREEN);
	  BSP_LED_Init(LED_RED);
	  gyroErr = BSP_GYRO_Init();
	  accErr = BSP_COMPASS_Init();
	  BSP_LCD_GLASS_Init();
	  BSP_JOY_Init(JOY_MODE_GPIO);

	  CJoy::init();
	  CFilter::init();

	  errorControll();

}

void CPeripherials::errorControll()
{
	  if(gyroErr != 0)
		  BSP_LED_On(LED_GREEN);
	  if(accErr != 0)
		  BSP_LED_On(LED_RED);
}


void CPeripherials::SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  __PWR_CLK_ENABLE();

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)

#endif

