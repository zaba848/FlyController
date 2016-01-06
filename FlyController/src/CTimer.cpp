/*
 * CTimer.cpp
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */

#include <CTimer.h>

uint16_t CTimer::tick;

void CTimer::initCTimer()
{
	tick = 0;

}

void CTimer::timerTick()
{
	tick++;
}

CTimer::CTimer() {
	this->timer.isEnable = false;
	this->timer.timeUp	 = true;
	this->timer.unit 	 = Time::CT_MS;
	this->timer.interupt = 0;
	this->interupt		 = 0;
	this->timer.time 	 = 0;

}

void CTimer::reconfigure(uint16_t interupt, Time unit, bool setEnable)
{
	this->timer.isEnable = setEnable;
	this->timer.unit 	 = unit;
	this->timer.interupt = interupt;
	this->interupt		 = interupt;
	this->timer.time 	 = tick;
	this->timer.timeUp	 = false;


}
void CTimer::update()
 {
	if (this->timer.isEnable && (tick != this->timer.time))
	{
		if ((this->timer.time - tick) >= this->timer.unit)
		{
			this->timer.time = tick;
			if(this->timer.interupt > 0)
			{
				this->timer.interupt--;
			}else
			{
				this->timer.isEnable = false;
				this->timer.timeUp 	 = true;
			}

		}
	}

}
bool CTimer::isGoing()
{
	if((this->timer.interupt == 0 ? false : true) && this->timer.isEnable)
	{
		return true;
	}else
	{
		return false;
	}
}
bool CTimer::isEnable()
{
	return this->timer.isEnable;
}
bool CTimer::timeUp()
{
	return this->timer.timeUp;
}
void CTimer::setState(bool isEnable)
{
	this->timer.timeUp = isEnable;
	this->timer.isEnable = isEnable;
}

void CTimer::reset()
{
	this->timer.timeUp   = true;
	this->timer.isEnable = true;
	this->timer.time 	 = tick;
	this->timer.interupt = interupt;


}

