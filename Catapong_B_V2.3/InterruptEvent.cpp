/*
 * InterruptEvent.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: Fisher
 */

#include "InterruptEvent.h"
#include "Catapong_B_V2_2.h"
#include "Wire.h"
#include "SpeedControl.h"
#include ".\Hardware\Hardware.h"

unsigned char speedState[100];


unsigned int counter =0;
//unsigned long testCounter=0;
ISR(TIMER2_COMPA_vect){
	counter ++;
	stepper_delayTime ++;
//	testCounter++;
	if(counter%3 == 0)//every 10 ms
	{

//		Serial.print(stepper_delayTime);

		if(counter >= 100){
			counter=0;
		}
		InterruptEvent_SpeedControl();
		speedState[counter] = currentSpeed;
	}

}
//unsigned int c;
//ISR(TIMER1_OVF_vect){
//	c ++;
//
//	if(c%500 == 6) PORTB &= ~(1<<PORTB0);
//
//	if(c%1000 == 0){ //every 20ms
//
//		PORTB |= 1<<PORTB0;
////		if(flg_PDControl == 1)
////		{
////			Event_SpeedControl(targetSpeed);//PD speed control
////		}
////		currentSpeed = Encoder_Read();
////		Encoder_Clear();
//		if(c%20000 == 0)
//		{
//
//			c=0;
////			flg_test = 1;
//		}
//	}
//}
