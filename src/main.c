/**
 * \brief   This project about ds18b20 on common channels DS18B20 .
 *
 * \License  THIS FILE IS PART OF MULTIBEANS PROJECT ;
 *           all of the files  - The core part of the project;
 *           THIS PROGRAM IS FREE SOFTWARE, JUST NEED GPL 3.0 LICENSE;
 *           YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT,
 *           MULTIBEANS WILL TAKE APPROPRIATE MEASURES.
 *
 *                ________________     ___           _________________
 *               |    __    __    |   |   |         |______     ______|
 *               |   |  |  |  |   |   |   |                |   |
 *               |   |  |__|  |   |   |   |________        |   |
 *               |___|        |___|   |____________|       |___|
 *
 *                               MULTIBEANS ORG.
 *                     Homepage: http://www.mltbns.com/
 *
 *           * You can download the license on our Github. ->
 *           * -> https://github.com/multibeans  <-
 *           * Copyright (c) 2014-2019 MULTIBEANS ORG. http://www.mltbns.com/
 *           * Copyright (c) 2019 Wei Haochen(Carlos Wei: # weihaochen@mltbns.com).
 *
 *  \note    void.
 ****************************************************************************/
/*                                                                          */
/*  @File       : main.c                                                    */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Date       : 2019.03.01 Realse.                                        */
/*  @Belong     : PROJECT.                                                  */
/*  @GitHub     :                                                           */
/*  @ASCII : (GBK/GB2312) in Windows x64. CCSv5.5以上                                                                                   */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer     |          Content         |   */
/*  |------------|-----------|---------------|--------------------------|   */
/*  | 2019.03.01 |   create  |Carlos Wei(M)  | add all device driver.   |   */
/*  ---------------------------------------------------------------------   */
/*                                                            MULTIBEANS.   */
#include "project.h"
#include "main.h"

OLED oled_dev, *oled_dev_handle;
EI2C i2c_dev;
// 192.168.1.1
//
void main(void){

    DS18B20 *t_sensor;
    DHT11 *h_sensor;
    float temp_value[2];
    float humi_value;
    unsigned char buffer[40];
    unsigned char disp_temp_buffer[20];
    unsigned char disp_humi_buffer[20];
    // Stop watchdog timer
    system_clk_init();
    led_init();
    t_sensor = ds18b20_new_device(4u,BIT0);
    h_sensor = dht11_new_device();
    oled_dev_handle     =   &oled_dev;
    oled_dev_handle->hw.i2c = &i2c_dev;
    oled_init(oled_dev_handle);
    uart_gpio_init();
    uart_0_init();
    uart_1_init();
    led_set(D0);
    esp8266_init();
    led_set(D5);

    while(1) {

        temp_value[0] = t_sensor->get_temp_float(t_sensor);
        temp_value[1] = h_sensor->get_humi_float(h_sensor);
        //sprintf(buffer, "temp:%2.2f .C\nhumi:%2.2f .p\n\0",temp_value[0], temp_value[1]);
        //msg(buffer);
        sprintf(disp_temp_buffer, "temp:%2.2f.c", temp_value[0]);
        sprintf(disp_humi_buffer, "humi:%2.2f%%", temp_value[1]);
        oled_dev_handle->showstring(oled_dev_handle,0,0,"Local Disp");
        oled_dev_handle->showstring(oled_dev_handle,0,2,disp_temp_buffer);
        oled_dev_handle->showstring(oled_dev_handle,0,4,disp_humi_buffer);
        led_set(D6);
        DELAY_MS(800);
        esp8266_write_to_host(temp_value);
        led_clear(D6);
        DELAY_MS(200);
    }

}


void system_clk_init(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    BCSCTL1 =   RSEL2+RSEL1+RSEL0;      // Set clock DCO max
    DCOCTL  =   DCO2 + DCO1 + DCO0;   // Set DCO max
}

#pragma vector = USART0RX_VECTOR
__interrupt void UART0_RXISR(void)
{
    rx_buffer[rx_count] = RXBUF0 & 0xFF;
    TXBUF0 = RXBUF0;
    rx_count ++;
    if (rx_count == 10) {

        rx_count = 0;
    }

    LPM1_EXIT;                 //退出低功耗模式
}
