/*
 * CTimer.h
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */

#ifndef CTIMER_H_
#define CTIMER_H_

class CTimer {
public:

	typedef enum
	{
		CT_MS  = 1,
		CT_DCS = 100,
		CT_SEC = 1000,
		CT_MIN = 60000,
	}Time;

	CTimer();

	static void initCTimer();
	static void timerTick();
	void reconfigure(uint16_t interupt, Time unit, bool setEnable);
	void update();
	bool isGoing();
	bool isEnable();
	bool timeUp();
	void setState(bool isEnable);
	void reset();

protected:

	typedef struct
	{
		uint16_t time;
		uint16_t interupt;
		Time unit;
		bool isEnable;
		bool timeUp;
	}Timer;

	Timer timer;
	uint16_t interupt;


private:

	static uint16_t tick;

};

#endif /* CTIMER_H_ */
