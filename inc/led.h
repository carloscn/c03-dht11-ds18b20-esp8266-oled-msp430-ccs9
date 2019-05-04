/*
 * led.h
 *
 *  Created on: 2019Äê3ÔÂ10ÈÕ
 *      Author: lifim
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "project.h"

#define             D0          BIT0
#define             D1          BIT1
#define             D2          BIT2
#define             D3          BIT3
#define             D4          BIT4
#define             D5          BIT5
#define             D6          BIT6
#define             D7          BIT7

extern void led_clear(uint16_t bit);
extern void led_set(uint16_t bit);
extern void led_init(void);

#endif /* INC_LED_H_ */
