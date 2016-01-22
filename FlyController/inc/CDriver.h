/*
 * CDriver.h
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#ifndef CDRIVER_H_
#define CDRIVER_H_

#include <stdint.h>
#include <stdio.h>
#include <stm32l476g_discovery_compass.h>
#include <stm32l476g_discovery_gyroscope.h>

class CDriver {
public:

	static void    update	();

	static int16_t getACC_X ();
	static int16_t getACC_Y ();
	static int16_t getACC_Z ();
	static int16_t getACC   (uint8_t number);

	static void getACC_XD (double& x);
	static void getACC_YD (double& y);
	static void getACC_ZD (double& z);


	static int16_t getMAG_X ();
	static int16_t getMAG_Y ();
	static int16_t getMAG_Z ();
	static int16_t getMAG   (uint8_t number);


	static float   getGYRO_X();
	static float   getGYRO_Y();
	static float   getGYRO_Z();

	static void   getGYRO_XD(double& x);
	static void   getGYRO_YD(double& y);
	static void   getGYRO_ZD(double& z);

	static float   getGYRO  (uint8_t number);


protected:

	static int16_t accBuffer[3];
	static float  gyroBuffer[3];
	static int16_t magBuffer[3];


};

#endif /* CDRIVER_H_ */
