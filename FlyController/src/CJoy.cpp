/*
 * CJoy.cpp
 *
 *  Created on: 6 sty 2016
 *      Author: User
 */

#include <CJoy.h>

CJoy::JState CJoy::acctualState;
CJoy::JState CJoy::backupState;

void CJoy::init()
{
	acctualState = JS_NONE;
	backupState = acctualState;
}

void CJoy::update()
{
	if(acctualState == JS_NONE)
	acctualState = (JState)BSP_JOY_GetState();
}

CJoy::JState CJoy::getState()
{
	backupState = acctualState;
	acctualState = JS_NONE;
	return backupState;
}

void CJoy::setJoyState(JState state)
{
	acctualState = state;
}
