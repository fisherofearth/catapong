/*
 * Stepper.h
 *
 *  Created on: Apr 25, 2015
 *      Author: Fisher
 */

#ifndef HARDWARE_STEPPER_STEPPER_H_
#define HARDWARE_STEPPER_STEPPER_H_

void Stepper_InitDevice(void);
void Stepper_EnDrive(unsigned char En);
void Stepper_SetStep(unsigned char dir, unsigned int steps, unsigned int reduce);

extern unsigned long stepper_delayTime;

#endif /* HARDWARE_STEPPER_STEPPER_H_ */
