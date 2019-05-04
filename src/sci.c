/*
 * rs232.c
 *
 *  Created on: 2019-3-4
 *      Author: lifim
 */

#include "project.h"
#include "sci.h"

uint32_t rx_count = 0;
uint8_t rx_buffer[80];

void    uart_gpio_init(void)
{
    P3DIR |= BIT4 + BIT5 + BIT6 + BIT7;
    P3OUT |= BIT4 + BIT5 + BIT6 + BIT7;
    P3SEL |= 0xF0;
}

void    uart_0_init( void )
{
    ME1 |= UTXE0 + URXE0;                     // ʹ��USART0�ķ��ͺͽ���
    UCTL0 |= CHAR;                            // ѡ��8λ�ַ�
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // ������9600
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4A;                            // Modulation
    UCTL0 &= ~SWRST;                          // ��ʼ��UART״̬��
    IE1 |= URXIE0;                            // ʹ��USART0�Ľ����ж�
}


void    uart_1_init( void )
{
    ME2 |= UTXE1 + URXE1;                     // ʹ��USART0�ķ��ͺͽ���
    UCTL1 |= CHAR;                            // ѡ��8λ�ַ�
    UTCTL1 |= SSEL0;                          // UCLK = ACLK
    UBR01 = 0x03;                             // ������9600
    UBR11 = 0x00;                             //
    UMCTL1 = 0x4A;                            // Modulation
    UCTL1 &= ~SWRST;                          // ��ʼ��UART״̬��
    IE2 |= URXIE1;                            // ʹ��USART0�Ľ����ж�
}

void msg(unsigned char *p)
{
    uart_1_send_str(p);
}

void    uart_0_send_str( unsigned char *ptr )
{
    while( (*ptr != '\0') ) {

        while ( !( IFG1 & UTXIFG0 ) );              // TX������У�
        TXBUF0 = *ptr++;                                // ��������
    }
}

void    uart_1_send_str( unsigned char *ptr )
{
    while( (*ptr != '\0') ) {

        while ( !( IFG2 & UTXIFG1 ) );              // TX������У�
        TXBUF0 = *ptr++;                                // ��������
    }
}

void    uart_0_put_char( unsigned char ch )
{
    while ( !( IFG1 & UTXIFG0 ) );              // TX������У�
    TXBUF0 = ch;                                // ��������
}

void    uart_1_put_char( unsigned char ch )
{
    while ( !( IFG2 & UTXIFG1 ) );              // TX������У�
    TXBUF0 = ch;                                // ��������
}

