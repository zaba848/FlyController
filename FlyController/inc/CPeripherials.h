/*
 * CPeripherials.h
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */

#ifndef CPERIPHERIALS_H_
#define CPERIPHERIALS_H_

#include <gpio.h>
#include <stm32l476g_discovery_compass.h>
#include <stm32l476g_discovery_glass_lcd.h>
#include <stm32l476g_discovery_gyroscope.h>
#include <stm32l4xx_hal.h>
#include <usart.h>
#include <stm32_hal_legacy.h>
#include <stm32l476xx.h>
#include <stm32l4xx_hal_cortex.h>
#include <stm32l4xx_hal_flash.h>
#include <stm32l4xx_hal_pwr_ex.h>
#include <stm32l4xx_hal_rcc.h>
#include <stm32l4xx_hal_rcc_ex.h>


#include <CFilter.h>

class CPeripherials {
public:

	static void peripherialInit();
protected:

	static void SystemClock_Config();

};

#endif /* CPERIPHERIALS_H_ */
