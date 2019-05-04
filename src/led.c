/*
 * led.c
 *
 *  Created on: 2019Äê3ÔÂ10ÈÕ
 *      Author: lifim
 */

#include "project.h"


void led_init(void)
{
    P6SEL &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
    P6DIR |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
    P6OUT |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
}

void led_set(uint16_t bit)
{
    P6OUT &= ~(bit);
}

void led_clear(uint16_t bit)
{
    P6OUT |= (bit);
}





