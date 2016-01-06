/*
 * CMainMenu.cpp
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#include <CMainMenu.h>


CMainMenu::CMainMenu() {

}

void CMainMenu::init()
{

	CPeripherials::peripherialInit();
	CComm::init();
	timer.reconfigure(1, CTimer::CT_SEC);



//	sprintf(printBuffer, "MOVE");
//	BSP_LCD_GLASS_DisplayString((uint8_t*) printBuffer);
//	sprintf(printBuffer, "");

//  BSP_LED_On(LED_GREEN);

	initComplet();


}

void CMainMenu::initComplet()
{
	BSP_LED_Off(LED_RED);
	BSP_LED_On(LED_GREEN);
	HAL_Delay(100);
	BSP_LED_Off(LED_GREEN);
	BSP_LED_On(LED_RED);
	HAL_Delay(100);

	BSP_LED_Off(LED_RED);



//	sprintf(printBuffer, "Transmision start\n");
//	send(printBuffer);



}
void CMainMenu::update()
{

  while (1)
  {
//	  BSP_LED_Toggle(LED_RED);
	  CFilter::update();
	  CJoy::update();
	  timer.update();
	  CComm::update();
	  if(CJoy::getState() == CJoy::JS_UP)
	  {
		  CFilter::calibration();
		  sprintf(printBuffer,"calc");
		    BSP_LCD_GLASS_DisplayString((uint8_t*)printBuffer);

	  }

	  if(timer.timeUp())
	  {
		  	 BSP_LED_Toggle(LED_GREEN);
	  }

}

}
