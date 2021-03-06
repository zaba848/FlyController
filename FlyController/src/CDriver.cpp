/*
 * CDriver.cpp
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#include <CDriver.h>


float   CDriver::gyroBuffer[] = {0,0,0} ;
int16_t CDriver::accBuffer [] = {0,0,0} ;
int16_t CDriver::magBuffer [] = {0,0,0} ;


void    CDriver::update	  ()
{
	BSP_COMPASS_AccGetXYZ(accBuffer );
	BSP_COMPASS_MagGetXYZ(magBuffer );
	BSP_GYRO_GetXYZ		 (gyroBuffer);
}

int16_t CDriver::getACC_X ()
{
	return accBuffer[0];
}
int16_t CDriver::getACC_Y ()
{
	return accBuffer[1];

}
int16_t CDriver::getACC_Z ()
{
	return accBuffer[2];
}

void CDriver::getACC_XD (double& x)
{
	x = (double)accBuffer[0];
}
void CDriver::getACC_YD (double& y)
{
	y = (double)accBuffer[1];

}
void CDriver::getACC_ZD (double& z)
{
	uint16_t a = accBuffer[2];
	z = (double)a;
}

int16_t CDriver::getACC (uint8_t number)
{
	if(number < 3)
	return accBuffer[number];
	return 0;

}

int16_t CDriver::getMAG_X ()
{
	return magBuffer[0];
}
int16_t CDriver::getMAG_Y ()
{
	return magBuffer[1];

}
int16_t CDriver::getMAG_Z ()
{
	return magBuffer[2];

}
int16_t CDriver::getMAG (uint8_t number)
{
	if(number < 3)
	return magBuffer[number];
	return 0;

}

float   CDriver::getGYRO_X()
{
	return gyroBuffer[0];
}
float   CDriver::getGYRO_Y()
{
	return gyroBuffer[1];

}
float   CDriver::getGYRO_Z()
{
	return gyroBuffer[2];

}

void   CDriver::getGYRO_XD(double& x)
{
	x = (double)gyroBuffer[0];
}
void   CDriver::getGYRO_YD(double& y)
{
	y = (double)gyroBuffer[1];

}
void   CDriver::getGYRO_ZD(double& z)
{
	z = (double)gyroBuffer[2];

}
float CDriver::getGYRO    (uint8_t number)
{
	if(number < 3)
	return gyroBuffer[number];
	return 0;

}
