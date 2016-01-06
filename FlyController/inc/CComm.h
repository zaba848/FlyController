/*
 * CComm.h
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#ifndef CCOMM_H_
#define CCOMM_H_

#include <stdint.h>
#include <stdio.h>

#include <CFilter.h>
#include <CTimer.h>
#include <usart.h>
#include <stm32l476g_discovery_compass.h>


class CComm {
public:

	static const uint8_t COMMUNICATION_DELAY = 50;

	static void init();
	static void update();

protected:

//	static const uint8_t INTERNAL_DELAY = 8;


	static int16_t accBuffer[3];
	static 	char printBuffer[100];
	static CTimer communicationTimer;

};

#endif /* CCOMM_H_ */
