/*
 * CJoy.h
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#ifndef CJOY_H_
#define CJOY_H_

#include <stm32l476g_discovery.h>


class CJoy {
public:

	typedef enum
	{
	  JS_PRESS   = 0,
	  JS_LEFT    = 1,
	  JS_RIGHT   = 2,
	  JS_DOWN    = 3,
	  JS_UP      = 4,
	  JS_NONE    = 5
	}JState;

	static void init();
	static void update();
	static JState getState();
	static void setJoyState(JState state);
protected:
	static JState acctualState;
	static JState backupState;

};

#endif /* CJOY_H_ */
