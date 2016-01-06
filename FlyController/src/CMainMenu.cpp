/*
 * CMainMenu.cpp
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#include <CMainMenu.h>


CMainMenu::CMainMenu() {

	joyState = CJoy::JS_NONE;

}

void CMainMenu::init()
{

	CPeripherials::peripherialInit();
	CComm::init();
	timer.reconfigure(1, CTimer::CT_SEC);
	readTimer.reconfigure(100, CTimer::CT_MS);

	initComplet();


}

void CMainMenu::initComplet()
{
	BSP_LED_On(LED_GREEN);

	sprintf(printBuffer, "Wruum!");
	for (uint8_t iterator = 0; iterator <= 10; iterator++) {
		BSP_LED_Toggle(LED_RED);
		BSP_LED_Toggle(LED_GREEN);
		HAL_Delay(100);
	}
	BSP_LED_Off(LED_GREEN);
	BSP_LED_Off(LED_RED);
	HAL_Delay(100);



//	sprintf(printBuffer, "Transmision start\n");
//	send(printBuffer);



}

bool CMainMenu::caneEnter(CJoy::JState state)
{
	if(joyState != state)
	{
		joyState = state;
		timer.resetTimer();
		return true;
	}
	return false;
}

void CMainMenu::execCalc(CJoy::JState state)
{
	if(caneEnter(state))
	{
	  CFilter::calibration();
	  sprintf(printBuffer,"CALC   ");
	    BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);

	}
}

void CMainMenu::resetCalibration(CJoy::JState state)
{
	if(caneEnter(state))
	{
	  CFilter::resetCalibration();
	  sprintf(printBuffer,"RESET_C");
	    BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);

	}
}

void CMainMenu::update()
{

  while (1)
  {
//	  BSP_LED_Toggle(LED_RED);

	  CJoy::update();
	  timer.update();
	  readTimer.update();
	  CComm::update();

	  if(readTimer.timeUp())
		  CDriver::update();
		  CFilter::update();


	  switch(CJoy::getState())
	  {
	  case CJoy::JS_UP:
	  {
		  execCalc(CJoy::JS_UP);
	  }break;

	  case CJoy::JS_DOWN:
	  {
		  resetCalibration(CJoy::JS_DOWN);
	  }break;

	  case CJoy::JS_LEFT:
	  {	if(caneEnter(CJoy::JS_LEFT))
		{
		  sprintf(printBuffer,"LEFT   ");
		    BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);
		    BSP_COMPASS_DeInit();
		    BSP_COMPASS_Init();
		}
	  }break;

	  case CJoy::JS_RIGHT:
	  {	if(caneEnter(CJoy::JS_RIGHT))
		{
		  sprintf(printBuffer,"RIGHT  ");
		    BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);
		}
	  }break;

	  case CJoy::JS_PRESS:
	  {	if(caneEnter(CJoy::JS_PRESS))
		{
		  sprintf(printBuffer,"PRESS  ");
		    BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);
		}
	  }break;

	  case CJoy::JS_NONE:
	  default:
		  break;

	  }
	  if(CJoy::getState() == CJoy::JS_UP)
	  {
		  CFilter::calibration();
		  sprintf(printBuffer,"CACLC  ");
		    BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);

	  }

	  if(timer.timeUp())
	  {
		 joyState = CJoy::JS_NONE;
		 BSP_LED_Toggle(LED_GREEN);
		 sprintf(printBuffer,"   (:     ");
		 BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);

	  }

}

}
