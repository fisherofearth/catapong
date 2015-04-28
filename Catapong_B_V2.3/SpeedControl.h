/*
 * SpeedControl.h
 *
 *  Created on: Apr 25, 2015
 *      Author: Fisher
 */

#ifndef SPEEDCONTROL_H_
#define SPEEDCONTROL_H_

void InitSpeedControl(void);
void InterruptEvent_SpeedControl(void);

void TurnOnSpeedControl(signed int targetSpeed);
void TurnOffSpeedControl(void);

void SetSpeed(signed int targetSpeed);


extern signed char flg_DCMChange;
extern signed int currentSpeed;
//extern signed int targetSpeed;

#endif /* SPEEDCONTROL_H_ */
