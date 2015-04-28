/*
 * Stepper.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: Fisher
 */

#include "Stepper.h"
#include  "Arduino.h"

#define TRUE	1
#define FALSE	0

#define PORT 	PORTD
#define DDR		DDRD

#define BitA1	2
#define BitA2	3
#define BitB1	5
#define BitB2	6
#define BitEn	7

#define PhaseA	0
#define PhaseB	1
#define Positive	1
#define Negative	0

#define TRUE 	1
#define FALSE	0

#define SetSign(bit,x) ((x)==0?(PORT &= ~(1<<bit)):(PORT |= 1<<bit))

void Stepper_InitDevice(void)
{
	DDR |= (1<<BitA1)|(1<<BitA2)|(1<<BitB1)|(1<<BitB2)|(1<<BitEn);//set pins output

	Stepper_EnDrive(FALSE);

}

void Stepper_EnDrive(unsigned char En)
{
	if(En == TRUE)PORT |= 1<<BitEn;
	else PORT &= ~(1<<BitEn);
}

void SingleStep(unsigned char phase, unsigned char sign )
{
	if(phase == PhaseA){
		SetSign(BitB1,0);
		SetSign(BitB2,0);
		if(sign == Positive){
			SetSign(BitA1,1);
			SetSign(BitA2,0);
		}
		else
		{
			SetSign(BitA1,0);
			SetSign(BitA2,1);
		}
	}
	else
	{
		SetSign(BitA1,0);
		SetSign(BitA2,0);
		if(sign == Positive){
			SetSign(BitB1,1);
			SetSign(BitB2,0);
		}
		else
		{
			SetSign(BitB1,0);
			SetSign(BitB2,1);
		}
	}
}
unsigned long stepper_delayTime = 0;
void delay_01ms(unsigned long t) {
	TIMSK2 = 1<<OCIE2A;//enable interrupter
	stepper_delayTime = 0;

	while(stepper_delayTime < t){
//			Serial.print(stepper_delayTime);
//			Serial.print(" ");

	}
}
void Stepper_SetStep(unsigned char dir, unsigned int steps, unsigned int speed)
{
	unsigned int i;
	if(speed > 100)speed = 100;
	Stepper_EnDrive(1);
	for(i=0;i<steps;i++){
//		SingleStep(PhaseA, Positive);
//
//		delay(100);
//		SingleStep(PhaseA, Negative);
//		delay(100);
//		SingleStep(PhaseB, Positive);
//		delay(100);
//		SingleStep(PhaseB, Negative);
//				delay(100);
		SetSign(BitA1,1);
		SetSign(BitA2,0);
		SetSign(BitB1,0);
		SetSign(BitB2,1);
		delay_01ms(speed);
		SetSign(BitA1,1);
		SetSign(BitA2,0);
		SetSign(BitB1,1);
		SetSign(BitB2,0);
		delay_01ms(speed);

		SetSign(BitA1,0);
		SetSign(BitA2,1);
		SetSign(BitB1,1);
		SetSign(BitB2,0);
		delay_01ms(speed);
		SetSign(BitA1,0);
		SetSign(BitA2,1);
		SetSign(BitB1,0);
		SetSign(BitB2,1);
		delay_01ms(speed);

	}
//
	Stepper_EnDrive(0);

}
