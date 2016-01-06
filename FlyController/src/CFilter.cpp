/*
 * CCFilter.cpp
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */


#include <CFilter.h>
#include <stm32l476g_discovery_compass.h>
#include "stm32l476g_discovery_gyroscope.h"




CFilter::sensor_data_t CFilter::alfa;
CFilter::sensor_data_t CFilter::beta;

CFilter::sensor_data_t CFilter::x_pri;
CFilter::sensor_data_t CFilter::x_post;
CFilter::sensor_data_t CFilter::v_pri;
CFilter::sensor_data_t CFilter::v_post;

CFilter::sensor_data_t CFilter::x_backupPosition;
CFilter::sensor_data_t CFilter::x_correction;

uint8_t CFilter::internalIterator;
float CFilter::dt;
float  CFilter::gyroBuffer[] = {0,0,0} ;
int16_t CFilter::accBuffer[] = {0,0,0} ;
int16_t CFilter::magBuffer[] = {0,0,0} ;

void CFilter::init()
{
	internalIterator = 0;
	  dt = 0.1;

	 alfa.x = 0.2;
	 alfa.y = 0.2;
	 alfa.z = 0.2;

	 beta.x = 0.05;
	 beta.y = 0.05;
	 beta.z = 0.05;

	 x_pri.x = 0;
	 x_pri.y = 0;
	 x_pri.z = 0;

	 x_post.x = 0;
	 x_post.y = 0;
	 x_post.z = 0;

	 x_backupPosition.x = 0;
	 x_backupPosition.y = 0;
	 x_backupPosition.z = 0;



	 v_pri.x = 0;
	 v_pri.y = 0;
	 v_pri.z = 0;

	 v_post.x = 0;
	 v_post.y = 0;
	 v_post.z = 0;


	 x_correction.x = 0;
	 x_correction.y = 0;
	 x_correction.z = 0;

}
float CFilter::getAccX(void) {
	return x_post.x;

}

float CFilter::getAccY(void) {
	return x_post.y;
}

float CFilter::getAccZ(void) {
	return x_post.z;
}

void CFilter::calibration()
{
	 BSP_COMPASS_AccGetXYZ(accBuffer);

	 x_correction.x = accBuffer[0];
	 x_correction.y = accBuffer[1];
	 x_correction.z = accBuffer[2];
}

void CFilter::internalValueUpdate() {

	BSP_COMPASS_AccGetXYZ(accBuffer);
	accBuffer[0] = accBuffer[0] - x_correction.x;
	accBuffer[1] = accBuffer[1] - x_correction.y;
	accBuffer[2] = accBuffer[2] - x_correction.z;

	BSP_COMPASS_MagGetXYZ(magBuffer);
	BSP_GYRO_GetXYZ(gyroBuffer);

}

void CFilter::mainAlgorithm()
{
	x_pri.x = x_post.x + dt * v_post.x;
	x_pri.y = x_post.y + dt * v_post.y;
	x_pri.z = x_post.z + dt * v_post.z;

	v_pri.x = v_post.x;
	v_pri.y = v_post.y;
	v_pri.z = v_post.z;

	x_post.x = x_pri.x + alfa.x * (accBuffer[0] - x_pri.x);
	x_post.y = x_pri.y + alfa.y * (accBuffer[1] - x_pri.y);
	x_post.z = x_pri.z + alfa.z * (accBuffer[2] - x_pri.z);
	v_post.x = v_pri.x + beta.x * (accBuffer[0] - x_pri.x) / dt;
	v_post.y = v_pri.y + beta.y * (accBuffer[1] - x_pri.y) / dt;
	v_post.z = v_pri.z + beta.z * (accBuffer[2] - x_pri.z) / dt;
}

void CFilter::update() {

	internalValueUpdate();
	mainAlgorithm();

}

