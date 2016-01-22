/*
 * CCFilter.cpp
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */


#include <CFilter.h>
#include <stm32l476g_discovery_compass.h>




CFilter::sensor_data_t CFilter::alfa;
CFilter::sensor_data_t CFilter::beta;

CFilter::sensor_data_t CFilter::x_pri;
CFilter::sensor_data_t CFilter::x_post;
CFilter::sensor_data_t CFilter::v_pri;
CFilter::sensor_data_t CFilter::v_post;

CFilter::sensor_data_t CFilter::x_backupPosition;
CFilter::sensor_data_t CFilter::x_correction;

int16_t CFilter::accBuffer [] = {0,0,0} ;
float CFilter::angle [] = {0,0,0} ;
int16_t CFilter::magBuffer[] = {0,0,0};

int16_t CFilter::compareValue [];

uint8_t CFilter::internalIterator;
float CFilter::dt;

//float CFilter::rate_gyr_x ;
//float CFilter::rate_gyr_y ;
//float CFilter::rate_gyr_z ;
//float CFilter::CFangleX;
//float CFilter::CFangleY;

float CFilter::heading;
float CFilter::Magx;
float CFilter::Magy;
float CFilter::Magz;
float CFilter::AccXnorm;
float CFilter::AccYnorm;
float CFilter::Xh;
float CFilter::Yh;
float CFilter::Pitch;
float CFilter::Roll;
float CFilter::Temp;

CFilter::backup CFilter::xCal;
CFilter::backup CFilter::yCal;
CFilter::backup CFilter::zCal;


#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define COMPASS_OFFSET     280


void CFilter::init()
{
	internalIterator = 0;
	for(uint8_t iterator = 0; iterator < 3*NUBER_OF_SAMPLES; iterator++)
	compareValue[iterator] = 0;

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



//	 rate_gyr_x = 0;
//	 rate_gyr_y = 0;
//	 rate_gyr_z = 0;
//	 CFangleX = 0;
//	 CFangleY = 0;

	 heading   = 0;
	 Magx      = 0;
	 Magy      = 0;
	 Magz      = 0;
	 AccXnorm  = 0;
	 AccYnorm  = 0;
	 Xh        = 0;
	 Yh        = 0;
	 Pitch     = 0;
	 Roll      = 0;
	 Temp	   = 0;

	 xCal.min = 0;
	 xCal.max = 0;
	 yCal.min = 0;
	 yCal.max = 0;
	 zCal.min = 0;
	 zCal.max = 0;




}
float CFilter::getAccX(void) {
//	return x_post.x;
	return angle[0];

}

float CFilter::getAccY(void) {
//	return x_post.y;
	return angle[1];
}

float CFilter::getAccZ(void) {
	return angle[2];
}

//void CFilter::calibration()
//{
////	 BSP_COMPASS_AccGetXYZ(accBuffer);
//
//	 x_correction.x = CDriver::getACC_X();
//	 x_correction.y = CDriver::getACC_Y();
//	 x_correction.z = CDriver::getACC_Z();
//}

void CFilter::resetCalibration()
{
//	 x_correction.x = 0;
//	 x_correction.y = 0;
//	 x_correction.z = 0;
}

//void CFilter::internalValueUpdate() {
//
//	accBuffer[0] = (CDriver::getACC_X() * 0.004 ) - x_correction.x;
//	accBuffer[1] = (CDriver::getACC_Y() * 0.004 ) - x_correction.y;
//	accBuffer[2] = (CDriver::getACC_Z() * 0.004 ) - x_correction.z;
//
//	if (accBuffer[0] >180)
//	{
//		accBuffer[0] -= (float)360.0;
//	}
//	         if (accBuffer[1] >180)
//	        	 accBuffer[1] -= (float)360.0;
//
//}

//void CFilter::mainAlgorithm()
//{
//	x_pri.x = x_post.x + dt * v_post.x;
//	x_pri.y = x_post.y + dt * v_post.y;
//	x_pri.z = x_post.z + dt * v_post.z;
//
//	v_pri.x = v_post.x;
//	v_pri.y = v_post.y;
//	v_pri.z = v_post.z;
//
//	x_post.x = x_pri.x + alfa.x * (accBuffer[0] - x_pri.x);
//	x_post.y = x_pri.y + alfa.y * (accBuffer[1] - x_pri.y);
//	x_post.z = x_pri.z + alfa.z * (accBuffer[2] - x_pri.z);
//	v_post.x = v_pri.x + beta.x * (accBuffer[0] - x_pri.x) / dt;
//	v_post.y = v_pri.y + beta.y * (accBuffer[1] - x_pri.y) / dt;
//	v_post.z = v_pri.z + beta.z * (accBuffer[2] - x_pri.z) / dt;
//}

void CFilter::internalValueUpdate() {

	accBuffer[0] = CDriver::getACC_X() ;
	accBuffer[1] = CDriver::getACC_Y() ;
	accBuffer[2] = CDriver::getACC_Z() ;

	BSP_COMPASS_AccGetXYZ(accBuffer);


	magBuffer[0] = CDriver::getMAG_X() ;
	magBuffer[1] = CDriver::getMAG_Y() ;
	magBuffer[2] = CDriver::getMAG_Z() ;

}

void CFilter::mainAlgorithm()
{

    Magx = ((float) magBuffer[0]-xCal.min)/(xCal.max-xCal.min)*2-1;
    Magy = ((float) magBuffer[1]-yCal.min)/(yCal.max-yCal.min)*2-1;
    Magz = ((float) magBuffer[2]-zCal.min)/(zCal.max-zCal.min)*2-1;

    /* Normalize acceleration measurements so they range from 0 to 1 */
    Temp = accBuffer[0]*accBuffer[0]+accBuffer[1]*accBuffer[1]+accBuffer[2]*accBuffer[2];
    AccXnorm =  accBuffer[0]/sqrt(Temp);
    AccYnorm =  accBuffer[1]/sqrt(Temp);


    /* Calculate Pitch and Roll values in radian */
     Pitch = asin(-AccXnorm);
     Roll  = asin(AccYnorm/cos(Pitch));
     angle[0] = Pitch * 180 / PI;
      angle[1] = Roll  * 180 / PI;

    /* Calculate tilted position */
    Xh = Magx*cos(Pitch) + Magz*sin(Pitch);
    Yh = Magx*sin(Roll)*sin(Pitch) + Magy*cos(Roll) - Magz*sin(Roll)*cos(Pitch);

    heading = 180*atan2(Yh,Xh)/(3.14);
    if (heading <0)
      heading += 360;
    /* Revert angle and apply offset*/
    heading = 360 - heading - COMPASS_OFFSET;
    if (heading <0)
      heading += 360;

}

void CFilter::calibration()
{
//	  do {
//	    BSP_COMPASS_MagGetXYZ(magBuffer);
//	    xCal.max = max((int32_t) magBuffer[0],xCal.max);
//	    xCal.min = min((int32_t) magBuffer[0],xCal.min);
//	    yCal.max = max((int32_t) magBuffer[1],yCal.max);
//	    yCal.min = min((int32_t) magBuffer[1],yCal.min);
//	    zCal.max = max((int32_t) magBuffer[2],zCal.max);
//	    zCal.min = min((int32_t) magBuffer[2],zCal.min);
//
//		  CJoy::update();
//
//	  } while(CJoy::getState() != CJoy::JS_NONE);
}

void CFilter::getAngle()
{

//	angle[0] = accBuffer[0];
//	angle[1] = accBuffer[1];
//	angle[2] = accBuffer[2];
	angle[0] = accBuffer[0]* 2.0f / 32768.0f;
	angle[1] = accBuffer[1]* 2.0f / 32678.0f;
	angle[2] = accBuffer[2]* 2.0f / 32678.0f;

//
	angle[1] = atan2f(angle[1], angle[2])* 180 / M_PI + 90;
	angle[0] = atan2f(angle[0], angle[2])* 180 / M_PI + 90;

//    Temp = accBuffer[0]*accBuffer[0]+accBuffer[1]*accBuffer[1]+accBuffer[2]*accBuffer[2];
//    AccXnorm =  accBuffer[0]/sqrt(Temp);
//    AccYnorm =  accBuffer[1]/sqrt(Temp);
//
//
//    /* Calculate Pitch and Roll values in radian */
//    angle[0] =Pitch = asin(-AccXnorm);
//    angle[1] =Roll  = asin(AccYnorm/cos(Pitch));


//// boki
//	angle[0] = (atan2( (accBuffer[0] ),(accBuffer[2] ))) * 180 / PI;
//
//// przod tyl
//	angle[1] = (atan2( (accBuffer[1] ),(accBuffer[2] )) )* 180 / PI;
//

}

void CFilter::update() {

	internalValueUpdate();
//	mainAlgorithm();
	getAngle();

}

