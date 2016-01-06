/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include <CFilter.h>
#include <CPeripherials.h>
#include <stdint.h>
#include <stdio.h>
#include <stm32l476g_discovery_compass.h>
#include <stm32l476g_discovery_glass_lcd.h>
#include <stm32l4xx_hal.h>
#include <usart.h>

//void SystemClock_Config(void);

int main(void)
{

	CPeripherials::peripherialInit();


	int16_t accBuffer[3];
  char printBuffer[40];

  sprintf(printBuffer,"MOVE");
  BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);
  sprintf(printBuffer,"");


//  BSP_LED_On(LED_GREEN);

  sprintf(printBuffer,"Transmision start\n");
  send(printBuffer);
  while (1)
  {
//	  BSP_LED_Toggle(LED_RED);
	  CFilter::update();
	  BSP_COMPASS_AccGetXYZ(accBuffer);
	  sprintf(printBuffer,"X %.2f, %d",CFilter::getAccX(),accBuffer[0]);
	  HAL_Delay(50);
	  send(printBuffer);
	  sprintf(printBuffer,", Y %.2f, %d",CFilter::getAccY(),accBuffer[1]);
	  HAL_Delay(50);
	  send(printBuffer);
	  sprintf(printBuffer,", Z %.2f, %d",CFilter::getAccZ(),accBuffer[2]);
	  send(printBuffer);
	  sprintf(printBuffer,"\n");
	  send(printBuffer);
	  HAL_Delay(330);


  }

}
