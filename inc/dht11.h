/*
 * dht11.h
 *
 *  Created on: 2018Äê4ÔÂ15ÈÕ
 *      Author: weihaochen
 */

#ifndef DHT11_H_
#define DHT11_H_


#include "project.h"

#define  uint16 uint16_t
#define  uint32 uint32_t
#define  uint8 uint8_t
#define  ErrorStatus uint8

#define  SUCCESS 0
#define  ERROR 1
#define  FlagStatus uint8
#define  SET 1
#define  RESET 0

#define       DHT11_LINE_IN(this)                     (P4DIR &= ~(BIT2) )
#define       DHT11_LINE_OUT(this)                    (P4DIR |= (BIT2) )
#define       DHT11_LINE_HIGH(this)                   (P4OUT |= (BIT2) )
#define       DHT11_LINE_LOW(this)                    (P4OUT &= ~(BIT2) )
#define       DHT11_LINE_READ(this)                    ( P4IN&(BIT2) )

struct  dht11_hw_t {

    uint16              line_pin;
    struct              dht11_hw_t *self;
    uint32              line_io_clk;

    void      (*set_high)   ( struct dht11_hw_t *self );
    void      (*set_low)    ( struct dht11_hw_t *self );
    uint8     (*read_line)  ( struct dht11_hw_t *self );

};

typedef struct  dht11_t{

    struct dht11_hw_t hw;
    struct dht11_t    *self;

    float   temperature_value;
    float   humidity_value;
    uint8   temp_str[8];
    uint8   humi_str[8];
    uint8   save_buffer[16];
    uint8   *op;
    uint8   id_buffer[8];

    ErrorStatus     (*init)             ( struct dht11_t *self );
    void            (*reset)            ( struct dht11_t *self );
    void            (*write_byte)       ( struct dht11_t *self, uint8 val );
    uint8           (*read_byte)        ( struct dht11_t *self );
    float           (*get_temp_float)   ( struct dht11_t *self );
    float           (*get_humi_float)   ( struct dht11_t *self );
    void            (*float_2_ascii)    ( struct dht11_t *self, float val, uint8 *ascii_str );
    void            (*pin_set)          ( struct dht11_t *self );
    ErrorStatus     (*scan)             ( struct dht11_t *self );
    uint8           (*read_line)        ( struct dht11_t *self );
    ErrorStatus     (*read_sensor)      ( struct dht11_t *self );
    ErrorStatus     (*get_all_value)    ( struct dht11_t *self );
    FlagStatus      (*read_bit)         ( struct dht11_t *self );
} DHT11;


extern ErrorStatus      dht11_init( DHT11 *this );
extern void             dht11_reset( DHT11 *this );
extern void             dht11_pin_set( DHT11 *this );
extern ErrorStatus      dht11_scan( DHT11 *this );
extern uint8            dht11_read_line( DHT11 *this );
extern FlagStatus       dht11_read_bit( DHT11 *this );
extern uint16           dht11_read_byte( DHT11 *this );
extern ErrorStatus      dht11_read_sensor( DHT11 *this );
extern float            dht11_get_temp_float( DHT11 *this );
extern float            dht11_get_humi_float( DHT11 *this );
extern ErrorStatus      dht11_get_all_value( DHT11 *this );
extern void             dht11_float_2_ascii( DHT11 *self, float f_data, uint8 *fltBuffer);
extern DHT11* dht11_new_device(void);
#endif /* DHT11_H_ */
