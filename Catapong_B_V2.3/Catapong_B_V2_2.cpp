// import Arduino
#include "Catapong_B_V2_2.h"

//import public library
#include "Wire.h"

//import private library
#include ".\Hardware\Hardware.h"


//import project header
#include "InterruptEvent.h"
#include "PublicDef.h"
#include "SpeedControl.h"


/* Timer arrangement
 * Timer 0	- Encoder pulse counting (never use delay function because delay will occupy timer 0)
 * Timer 1 	- DC motor PWM (dual mode)
 * Timer 2	- Timer interrupt for PD speed control
 */

#define CMD_SPIN 	1
#define CMD_STOP	5

#define ABS(x)	((x)<0?(-(x)):(x))


unsigned char IICcmd = 0;
unsigned int IICData=0;
unsigned char Flg_IICCmd = 0;
void OnIICReceive(int howMany)
{
	 char c;
	  while (3 < Wire.available()) // loop through all but the last
	  {
	     c = Wire.read(); // receive byte as a character
//	    Serial.print(c);         // print the character
	  }
	  IICcmd = Wire.read();
	  IICData = Wire.read();
	  IICData |= ((unsigned int)Wire.read())<<8;
	  Flg_IICCmd = 1;
}

unsigned char flg_launch = 0;
void OnIICRequest(void)
{
	if(flg_launch == 0)Wire.write(0);
	else Wire.write(1);
}


void setup()
{

	noInterrupts();
	Serial.begin(9600);

//	init I2C
	Wire.begin(2);
	Wire.onRequest(OnIICRequest); // register event
	Wire.onReceive(OnIICReceive); // register event

	Encoder_InitDevice();
	Motor_InitDevice(); //set PWM: freq = 10KHz
	InitSpeedControl();
//	TurnOnSpeedControl(100);


//	Stepper_InitDevice();

//	TCCR2A = (1<<COM2A1)|(0<<COM2A0);
//	TCCR2B = (1<<CS22)|(1<<CS21)|(0<<CS20);
//	OCR2A = 62;
//	TIMSK2 = 1<<OCIE2A;//enable interrupter


	interrupts();

}

int targetSpeed = 150;
void loop()
{
	unsigned int i;
	unsigned int sum =0;
	if(Flg_IICCmd == 1)
	{
		switch(IICcmd)
		{
			case CMD_SPIN:
				Serial.print("SPINNING");
				flg_launch = 0;
				targetSpeed = IICData;
				TurnOnSpeedControl(targetSpeed);

				break;
			case CMD_STOP:
				Serial.print("STOP");
				TurnOffSpeedControl();
				break;
		}
		Flg_IICCmd = 0;
	}

	for(i=0;i<100;i++)
	{
		sum += ABS(speedState[i] - targetSpeed);
	}

	if(sum < 200)flg_launch = 1;


//	delay(10);

}
