/*
 * InterruptEvent.h
 *
 *  Created on: Apr 25, 2015
 *      Author: Fisher
 */

#ifndef INTERRUPTEVENT_H_
#define INTERRUPTEVENT_H_

void requestEvent();
void receiveEvent(int howMany);

extern unsigned char speedState[100];
#endif /* INTERRUPTEVENT_H_ */
