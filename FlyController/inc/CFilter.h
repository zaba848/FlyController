/*
 * CFilter.h
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */

#ifndef CFILTER_H_
#define CFILTER_H_
#include <stdint.h>
#include <stdio.h>
#include <CDriver.h>
#include <cmath>

//#include <cstdint>

class CFilter {
public:
static const uint8_t NUBER_OF_SAMPLES = 3;
static const float PI = 3.1415926535;//15;


	 typedef struct  {
		float x;
		float y;
		float z;
	} sensor_data_t;

	static float getAccX(void);
	static float getAccY(void);
	static float getAccZ(void);

//	static float rate_gyr_x;
//	static float rate_gyr_y ;
//	static float rate_gyr_z ;
//
//	static float CFangleX;
//	static float CFangleY;

	static void init();
	static void calibration();
	static void update();
//	static void calibration();
	static void resetCalibration();


protected:

	typedef struct
	{
		int32_t min;
		int32_t max;
	}backup;

	static sensor_data_t alfa;
	static sensor_data_t beta;

	static sensor_data_t x_pri;
	static sensor_data_t x_post;
	static sensor_data_t v_pri;
	static sensor_data_t v_post;

	static float dt;
	static int16_t accBuffer[3];
	static float angle[3];
// new one
	static backup xCal;
	static backup yCal;
	static backup zCal;

	static int16_t magBuffer[3];
	static float heading;
	static float Magx;
	static float Magy;
	static float Magz;
	static float AccXnorm;
	static float AccYnorm;
	static float Xh;
	static float Yh;
	static float Pitch;
	static float Roll;
	static float Temp;
//
	static void internalValueUpdate();
	static void mainAlgorithm();
	static void getAngle();

	static sensor_data_t x_backupPosition;

private:

	static uint8_t internalIterator;
	static sensor_data_t x_correction;

	static int16_t compareValue[3*NUBER_OF_SAMPLES];
	static void check();


};

#endif /* CFILTER_H_ */
