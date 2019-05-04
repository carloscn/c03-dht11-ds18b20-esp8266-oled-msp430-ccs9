/*
 * esp8266.c
 *
 *  Created on:
 *      Author: delvis
 */
#include "project.h"


bool strcmp_user(char *str1, char *str2, int len);
inline void esp8266_write_reg(const char *cmd);
inline void esp8266_write_str(const char *cmd);
inline void esp8266_write_byte(char e);

const char* cmd_at_mode = "AT\r\n";
const char* cmd_at_hoc_mode = "AT+CWMODE=3\r\n";
const char* cmd_at_connect_to_wifi = "AT+CWLAP\r\n";
const char* cmd_at_user_ssid_passwd = "AT+CWJAP=\"ARM-LINUX-GCC\",\"hao3834832\"\r\n";
const char* cmd_at_air_mode = "AT+CIPMODE=1\r\n";
const char* cmd_at_start = "AT+CIPSEND\r\n";
const char* cmd_at_set_ip = "AT+CIPSTART=\"TCP\",\"192.168.1.135\",5555\r\n";
const char* cmd_at_reset = "AT_RST\r\n";

bool is_enable_send = false;


void scia_xmit(char e)
{
    uart_0_put_char(e);
}

void scia_msg(char *cmd)
{
    uart_0_send_str((unsigned char*)cmd);
}

void esp8266_init(void)
{
    esp8266_write_reg(cmd_at_mode);
    led_set(D1);
    esp8266_write_reg(cmd_at_hoc_mode);
    esp8266_write_reg(cmd_at_connect_to_wifi);
    DELAY_MS(4000);
    led_set(D2);
    esp8266_write_reg(cmd_at_user_ssid_passwd);
    DELAY_MS(15000);
    led_set(D3);
    esp8266_write_reg(cmd_at_air_mode);
    esp8266_write_reg(cmd_at_set_ip);
    esp8266_write_reg(cmd_at_start);

    led_set(D4);
}

void esp8266_reset(void)
{
    esp8266_write_reg(cmd_at_reset);
}
inline void esp8266_write_reg(const char *cmd)
{
    scia_msg(cmd);
    DELAY_MS(1000);
}

inline void esp8266_write_str(const char *cmd)
{
    scia_msg(cmd);
}

inline void esp8266_write_byte(char e)
{
    scia_xmit(e);
}

void esp8266_write_to_host(float *data)
{
    uint16_t i;
    uint8_t f_buffer[5];

    // send the head of frame.
    esp8266_write_byte('#');
    //send temp value;
    sprintf(f_buffer,"%2.2f",data[0]);
    for( i = 0; i < 5; i ++) {
        esp8266_write_byte(f_buffer[i]);
    }
    // send rotation speed;
    esp8266_write_byte('#');
    //send humi value;
    sprintf(f_buffer,"%2.2f",data[1]);
    for( i = 0; i < 5; i ++) {
        esp8266_write_byte(f_buffer[i]);
    }
    // send rotation speed;
    esp8266_write_byte('#');

}

// &star
void esp8266_read_signal(char e)
{
    char cmd_1[] = "&start";
    char cmd_2[] = "&stops";
    char temp[7];
    memset(temp,'\n',7);
    rx_buffer[rx_count] = e;
    if (rx_count == 0 && rx_buffer[0] != '&') {
        memset(rx_buffer, 0, 50);
        return;
    }
    rx_count ++;
    if (rx_count == 6 ) {
        memcpy(temp, rx_buffer,6);
        if ( strcmp_user(temp, cmd_1, 6) == true ) {
            is_enable_send = true;
        }
        if ( strcmp_user(temp, cmd_2, 6) == true ) {
            is_enable_send = false;
        }
        if ( is_enable_send == true ) {
            printf("enable!\n");
        } else {
            printf("disble!\n");
        }
        rx_count = 0;
        memset(rx_buffer, 0, 50);
    }

}

bool strcmp_user(char *str1,char *str2, int len)
{
    int i = 0;

    for (i = 0; i < len; i ++) {
        if (str1[i] != str2[i] )
            return false;
    }
    return true;
}


