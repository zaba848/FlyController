/*
 * CComm.cpp
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#include <CComm.h>

CTimer CComm::communicationTimer;
char CComm::printBuffer[];

void CComm::init() {

	communicationTimer.reconfigure(COMMUNICATION_DELAY, CTimer::CT_MS);

}

void CComm::update()
{
	communicationTimer.update();
	if(communicationTimer.timeUp())
	{
//		  sprintf(printBuffer,"X %.1f, %d, Y %.1f, %d, Z %.1f, %d\n",CFilter::getAccX()/DIVIDED_BY,CDriver::getACC_X(),CFilter::getAccY()/DIVIDED_BY,CDriver::getACC_Y(),CFilter::getAccZ()/DIVIDED_BY,CDriver::getACC_Z());
		sprintf(printBuffer,"Y: %.1f*   X: %.1f*\n", CFilter::getAccX()/DIVIDED_BY, CFilter::getAccY()/DIVIDED_BY);
//		sprintf(printBuffer,"X %.2f		Y %.2f		Z %.2f\n", CFilter::getAccX()/DIVIDED_BY, CFilter::getAccY()/DIVIDED_BY,CFilter::getAccZ()/DIVIDED_BY);

//		sprintf(printBuffer,"X%f;Y%f;Z%f\n", CFilter::getAccX()/DIVIDED_BY, CFilter::getAccY()/DIVIDED_BY,CFilter::getAccZ()/DIVIDED_BY);
//		sprintf(printBuffer,"P: %.1f* R: %.1f*\n", CMainMenu::getPich(), CMainMenu::getPich());

		send(printBuffer);

	}
}
