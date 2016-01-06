/*
 * CComm.cpp
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#include <CComm.h>

CTimer CComm::communicationTimer;
int16_t CComm::accBuffer[];
char CComm::printBuffer[];

void CComm::init() {

	communicationTimer.reconfigure(COMMUNICATION_DELAY, CTimer::CT_SEC);

}


void CComm::update()
{
	communicationTimer.update();
	if(communicationTimer.timeUp())
	{

		  BSP_COMPASS_AccGetXYZ(accBuffer);
		  sprintf(printBuffer,"X %.2f, %d",CFilter::getAccX(),accBuffer[0]);
		  send(printBuffer);
		  sprintf(printBuffer,", Y %.2f, %d",CFilter::getAccY(),accBuffer[1]);
		  send(printBuffer);
		  sprintf(printBuffer,", Z %.2f, %d",CFilter::getAccZ(),accBuffer[2]);
		  send(printBuffer);
		  sprintf(printBuffer,"\n");
		  send(printBuffer);


	}
}
