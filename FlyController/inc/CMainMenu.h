/*
 * CMainMenu.h
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#ifndef CMAINMENU_H_
#define CMAINMENU_H_

#include <stdint.h>
#include <stdio.h>
#include <CFilter.h>
#include <CComm.h>
#include <CJoy.h>
#include <CPeripherials.h>
#include <stm32l476g_discovery.h>
#include <stm32l476g_discovery_glass_lcd.h>


#include <CTimer.h>


class CMainMenu {
public:

	CMainMenu();
	void init();
	void update();


protected:

	char printBuffer[40];
	CTimer timer;
	CTimer readTimer;

	void initComplet();

private:
	void execCalc(CJoy::JState state);
	void resetCalibration(CJoy::JState state);
	bool caneEnter(CJoy::JState state);
	CJoy::JState joyState;
};

#endif /* CMAINMENU_H_ */
