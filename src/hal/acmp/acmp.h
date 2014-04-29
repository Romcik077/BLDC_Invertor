/*
 * acmp.h
 *
 *  Created on: Mar 11, 2014
 *      Author: proman
 */

#ifndef ACMP_H_
#define ACMP_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <global.h>

void acmpInit(void);

void acmpStart(void);

void acmpStop(void);

void acmp0SetIntHandler(void (*handlerFunc)(void));

void acmp1SetIntHandler(void (*handlerFunc)(void));

void acmp2SetIntHandler(void (*handlerFunc)(void));

#endif /* ACMP_H_ */
