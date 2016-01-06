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
static const float PI = 3.1415;


	 typedef struct  {
		float x;
		float y;
		float z;
	} sensor_data_t;

	static float getAccX(void);
	static float getAccY(void);
	static float getAccZ(void);



	static void init();
	static void update();
	static void calibration();
	static void resetCalibration();


protected:

	static sensor_data_t alfa;
	static sensor_data_t beta;

	static sensor_data_t x_pri;
	static sensor_data_t x_post;
	static sensor_data_t v_pri;
	static sensor_data_t v_post;

	static float dt;
	static int16_t accBuffer[3];
	static int16_t angle[3];



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
