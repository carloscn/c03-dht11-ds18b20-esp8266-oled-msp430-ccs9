// Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : DS18B20.c                                                 */
/*  @Copyright  : Lifi.MLT (c) 2015 MULTIBEANS_ORG All rights reserved.     */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2018.01.15 Realse.                                        */
/*  @Belong     : PROJECT.                                                  */
/*                                                                          */
/*  **code : (GBK/GB2312) in Windows 10_x64. CCS v6.1 platform.             */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer     |          Content         |   */
/*  | 2018.01.15 |   create  |DelvisBeans(M) | ceate the document.      |   */
/*  ---------------------------------------------------------------------   */
/*                                                            MULTIBEANS.   */
/****************************************************************************/

/**
 * \brief   This project about ds18b20 on common channels DS18B20 .
 *
 * \License  THIS FILE IS PART OF MULTIBEANS PROJECT ;
 *           all of the files  - The core part of the project;
 *           THIS PROGRAM IS FREE SOFTWARE, JUST NEED GPL 3.0 LICENSE;
 *           YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT,
 *           MULTIBEANS WILL TAKE APPROPRIATE MEASURES.
 *
 *           * You can download the license on our Github. ->
 *           * -> https://github.com/multibeans  <-
 *           * Copyright (c) 2013-2018 MULTIBEANS ORG. http://www.mltbns.org/
 *           * Copyright (c) 2018 Wei Haochen.  Email: carlos@mltbns.top
 *
 *  \note    void.
 */

/**
 * \brief    connection.
 *
 * \offer    Wei Haochen
 *
 *
 * \return   None.
 *
 *              MSP430
 *             ---------------
 *            |               |
 *   line <-->|P4.0           |
 *            |               |
 *
 */

#ifndef DS18B20_H_
#define DS18B20_H_

#include <project.h>

#define             DS_SET_LINE_IN(self)                 (P4DIR &= ~(self->hw.line_pin) )
#define             DS_SET_LINE_OUT(self)                (P4DIR |= (self->hw.line_pin) )
#define             DS_LINE_HIGH(self)                   (P4OUT |= (self->hw.line_pin) )
#define             DS_LINE_LOW(self)                    (P4OUT &= ~(self->hw.line_pin) )
#define             DS_LINE_DATA(self)                   ( P4IN&(self->hw.line_pin) )

typedef struct  ds18b20_t DS18B20;

struct  ds18b20_hw_t{

    uint16_t line_pin;
    uint16_t line_port;
    struct  ds18b20_hw_t *self;

    void        (*set_high)( DS18B20 *self );
    void        (*set_low)( DS18B20 *self );
    uint8_t     (*read_line)( DS18B20 *self );
};

struct  ds18b20_t{

    struct ds18b20_hw_t hw;
    DS18B20    *self;
    float       temp_value;
    uint8_t     temp_str[8];
    uint8_t     read_buffer[16];
    uint8_t     *op;
    uint8_t     id_buffer[8];

    void        (*init)( DS18B20   *self );
    void        (*pin_set)(DS18B20 *self, uint16_t port, uint16_t pin_num);
    void        (*reset)( DS18B20   *self );
    void        (*config)( DS18B20  *self );
    void        (*write_byte)(DS18B20 *self, uint8_t val );
    uint8_t     (*read_byte)( DS18B20 *self );
    void        (*read_bytes)( DS18B20 *self, uint8_t length );
    uint8_t     (*check_crc)( DS18B20 *self, uint8_t checksum );
    float       (*get_temp_float)( DS18B20 *self );
    void        (*save_temp_string)( DS18B20 *self, uint8_t *dis_str );
    void        (*read_id)( DS18B20 *self, uint8_t *id_str );
    void        (*float_2_ascii)( DS18B20 *self, float val, uint8_t *ascii_str );

};
void         ds18b20_pin_set(DS18B20* dev, uint16_t port, uint16_t pin_num);
void         ds18b20_float_2_ascii( DS18B20* self, float f_data, uint8_t *fltBuffer);
void         ds18b20_save_temp_string( DS18B20* self , uint8_t *dis_str);
float        ds18b20_get_temp( DS18B20* self );
void         ds18b20_read_id( DS18B20* self, uint8_t *id_val );
uint8_t      ds18b20_check_crc( DS18B20 *self, uint8_t checksum );
void         ds18b20_read_bytes( DS18B20 *self, uint8_t length );
uint8_t      ds18b20_read_byte( DS18B20 *self );
void         ds18b20_write_byte( DS18B20 *self, uint8_t val );
void         ds18b20_reset( DS18B20 *self );
void         ds18b20_init( DS18B20 *self );
void         ds18b20_config( DS18B20 *self );
uint8_t      ds18b20_hw_read_line( DS18B20  *self );
void         ds18b20_hw_set_low(DS18B20 *self );
void         ds18b20_hw_set_high( DS18B20 *self );
extern DS18B20*     ds18b20_new_device(uint16_t port, uint16_t pin_num);

#endif /* DS18B20_H_ */
