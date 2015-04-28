/*
 * SpeedControl.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: Fisher
 */

#include "SpeedControl.h"
#include "pins_arduino.h"
#include "Arduino.h"
#include ".\Hardware\Hardware.h"

signed int targetSpeedPD;
signed char flg_DCMChange;

void InitSpeedControl(void)
{
	//Initialize timer 2
	TCCR2A = (1<<COM2A1)|(0<<COM2A0);
	TCCR2B = (1<<CS22)|(1<<CS21)|(0<<CS20);
	OCR2A = 62;
//	TIMSK2 = 1<<OCIE2A;//interrupter

}

void TurnOnSpeedControl(signed int targetSpeed)
{
	targetSpeedPD = targetSpeed;
	Motor_EnBridge(1);
	TIMSK2 = 1<<OCIE2A;//enable interrupter
	Encoder_Clear();//clear Encoder data
}

void TurnOffSpeedControl(void)
{
	Motor_EnBridge(0);
	TIMSK2 = 0;//diable interrupter
	Encoder_Clear();//clear Encoder data
}

void SetSpeed(signed int targetSpeed)
{
	targetSpeedPD = targetSpeed;
}

signed int currentSpeed;
float pdSpeed;
#define pram  0.05

void PD(void)
{
	signed int diff;
	currentSpeed = Encoder_Read();
	Encoder_Clear();

	diff = targetSpeedPD - currentSpeed;
	pdSpeed += (pram * (float)diff);

	if(pdSpeed > 300) pdSpeed = 300;
	if(pdSpeed < -100) pdSpeed = -100;
	Motor_SetPower((int)pdSpeed);
}



void InterruptEvent_SpeedControl(void)
{
		flg_DCMChange = 1;
		PD();
}
