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
#include <stm32l476g_discovery_compass.h>
#include <stm32l4xx_hal.h>
#include <KalmanFilter.h>


#include <cmath>


#include <CTimer.h>


class CMainMenu {
public:

	CMainMenu();
	void init();
	void update();

	static float getPich();
	static float getRoll();


protected:

	char printBuffer[40];
	CTimer timer;
	CTimer readTimer;

	void initComplet();
	void kalman();
	void updateWithOutFilter();

private:
	void execCalc(CJoy::JState state);
	void resetCalibration(CJoy::JState state);
	bool caneEnter(CJoy::JState state);
	CJoy::JState joyState;

	static float kalPitch ;
	static float kalRoll  ;
	float accPitch ;
	float accRoll  ;
	double accX;
	double accY;
	double accZ;

	double gyrX;
	double gyrY;


	KalmanFilter kalmanX;
	KalmanFilter kalmanY;

};

#endif /* CMAINMENU_H_ */
