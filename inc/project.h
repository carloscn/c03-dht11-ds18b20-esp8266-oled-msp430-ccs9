/*
 * project.h
 *
 *  Created on: 2019Äê3ÔÂ9ÈÕ
 *      Author: lifim
 */

#ifndef INC_PROJECT_H_
#define INC_PROJECT_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"
#include <msp430.h>

#include "dht11.h"
#include "sci.h"
#include "esp8266.h"
#include "ds18b20.h"
#include "led.h"
#include "oled.h"





#define CPU_CLOCK 4000000ul

#if CPU_CLOCK == 4000000ul
#define DELAY_US(us) __delay_cycles((unsigned long)8*((unsigned long)us))
#define DELAY_MS(ms) __delay_cycles((unsigned long)8000*((unsigned long)ms))
#else
#pragma error "CPU_CLOCK is defined implicitly!"
#endif
#endif /* INC_PROJECT_H_ */
