/*
 * dht11.c
 *
 *  Created on: 2018Äê4ÔÂ15ÈÕ
 *      Author: weihaochen
 */


#include "project.h"

#define                 THIS                this

DHT11* dht11_new_device(void)
{
    DHT11* p_dev = (DHT11*) malloc(sizeof(DHT11));
    p_dev->init             =   &dht11_init;
    p_dev->reset            =   &dht11_reset;
    p_dev->pin_set          =   &dht11_pin_set;
    p_dev->scan             =   &dht11_scan;
    p_dev->read_line        =   &dht11_read_line;
    p_dev->read_bit         =   &dht11_read_bit;
    p_dev->read_byte        =   &dht11_read_byte;
    p_dev->read_sensor      =   &dht11_read_sensor;
    p_dev->get_temp_float   =   &dht11_get_temp_float;
    p_dev->get_humi_float   =   &dht11_get_humi_float;
    p_dev->get_all_value    =   &dht11_get_all_value;
    p_dev->float_2_ascii    =   &dht11_float_2_ascii;

    p_dev->init(p_dev);
    return p_dev;
}

ErrorStatus    dht11_init( DHT11 *this )
{
    this->pin_set( this );

    if ( this->scan( this ) == SUCCESS )
        return SUCCESS;
    return ERROR;
}


void    dht11_pin_set( DHT11 *this )
{
    P4SEL &= ~BIT2;
    P4DIR |= BIT2;
    P4OUT |= BIT2;
}

void    dht11_reset( DHT11 *this )
{

    DHT11_LINE_HIGH(this);
    DHT11_LINE_LOW(this);
    DELAY_MS(25);
    DHT11_LINE_HIGH(this);
    DELAY_US(30);

}

ErrorStatus    dht11_scan( DHT11 *this )
{

    if( DHT11_LINE_READ(this) == 1) {
        return SUCCESS;
    }else {
        return ERROR;
    }
}

uint8   dht11_read_line( DHT11 *this )
{
    return DHT11_LINE_READ(this);
}


FlagStatus     dht11_read_bit( DHT11 *this )
{
    //while ( this->read_line(this) == RESET ) ;
    //DELAY_US(40);
    if ( this->read_line(this) == SET ) {
        //while( this->read_line(this) == SET );
        return SET;
    }else {
        return RESET;
    }

}

uint16  dht11_read_byte( DHT11 *this )
{
    uint16 i = 0;
    uint16 data = 0;
    uint16 j = 0;
    for ( i = 0; i < 8; i++ ) {

        data    <<= 1;
        while( this->read_line(this) == RESET );
        while( this->read_line(this) == SET ) {
            DELAY_US(1);
            j++;
        }
        if( j >= 10 ) {
            data = data | 0x01;
            j = 0;
        }
        j = 0;
    }
    return data;

}


ErrorStatus  dht11_read_sensor( DHT11 *this )
{
    uint16  i = 0;
    uint8   checksum = 0;

    this->reset(this);

    if ( !this->read_line(this) ) {

       while ( this->read_line(this) == RESET );
       while ( this->read_line(this) == SET );
       for ( i = 0; i < 5; i++ ) {
           *(this->save_buffer + i) = this->read_byte(this);
       }

       DHT11_LINE_HIGH(this);

       checksum = *( this->save_buffer ) + *(this->save_buffer + 1) + *(this->save_buffer + 2) + *(this->save_buffer + 3);
       if ( checksum != *(this->save_buffer + 4) ) {
           return ERROR;
       }
    }
    return SUCCESS;

}

float       dht11_get_temp_float( DHT11 *this )
{

    if ( this->read_sensor(this)  ==  SUCCESS ) {
        memcpy( this->humi_str,this->save_buffer,  2 );
        memcpy( this->temp_str,this->save_buffer + 2,  2 );
        this->temperature_value  =  ( (float)( *(this->humi_str) + *(this->humi_str + 1) ) ) /  10.0f;
    }else {
        this->temperature_value    =   0;
    }

    return this->temperature_value;

}


float       dht11_get_humi_float( DHT11 *this )
{
    if ( this->read_sensor(this)  ==  SUCCESS ) {
        memcpy( this->humi_str, this->save_buffer,  2 );
        memcpy( this->temp_str, this->save_buffer + 2,  2 );
        this->humidity_value  =  ( (float)( *(this->humi_str) + *(this->humi_str + 1) ) ) /  10.0f;
    }else {
        this->humidity_value    =   0;
    }

    return this->humidity_value;
}


ErrorStatus     dht11_get_all_value( DHT11 *this )
{
    if ( this->read_sensor(this)  ==  SUCCESS ) {
        memcpy( this->humi_str, this->save_buffer,  2 );
        memcpy( this->temp_str, this->save_buffer + 2,  2 );
        this->humidity_value  =  ( (float)( *(this->humi_str) + *(this->humi_str + 1) ) ) ;
        this->float_2_ascii( this, this->humidity_value, this->humi_str );
        this->temperature_value  =  ( (float)( *(this->temp_str) + *(this->temp_str + 1) ) ) ;
        this->float_2_ascii( this, this->temperature_value, this->temp_str );
        return SUCCESS;
    }else {
        this->humidity_value  =  0;
        this->float_2_ascii( this, this->humidity_value, this->humi_str );
        this->temperature_value  =  0;
        this->float_2_ascii( this, this->temperature_value, this->temp_str );
        return ERROR;
    }

}



void    dht11_float_2_ascii( DHT11  *self, float f_data, uint8 *fltBuffer)
{

    if (f_data < 0) {
        fltBuffer[0] = (long)'-';
        f_data = -f_data;
    } else {
        fltBuffer[0] = (long)' ';
    }
    if (f_data < 999 && f_data > 99) {
        fltBuffer[1] = (long)((long)(f_data) / 100) % 1000 + 0x30;
        fltBuffer[2] = (long)((long)(f_data) / 10) % 10 + 0x30;
        fltBuffer[3] = (long)((long)(f_data) / 1) % 10 + 0x30;
        fltBuffer[4] = (long)('.');
        fltBuffer[5] = (long)(f_data * 10) % 10 + 0x30;
        fltBuffer[6] = (long)(f_data * 100) % 10 + 0x30;
        fltBuffer[7] = (long)'\0';
    } else if (f_data < 99 && f_data > 9) {
        fltBuffer[1] = (long)' ';
        fltBuffer[2] = (long)((long)(f_data) / 10) % 10 + 0x30;
        fltBuffer[3] = (long)((long)(f_data) / 1) % 10 + 0x30;
        fltBuffer[4] = (long)('.');
        fltBuffer[5] = (long)(f_data * 10) % 10 + 0x30;
        fltBuffer[6] = (long)(f_data * 100) % 10 + 0x30;
        fltBuffer[7] = (long)'\0';
    } else if (f_data < 9) {
        fltBuffer[1] = (long)' ';
        fltBuffer[2] = (long)' ';
        fltBuffer[3] = (long)((long)(f_data) / 1) % 10 + 0x30;
        fltBuffer[4] = (long)('.');
        fltBuffer[5] = (long)(f_data * 10) % 10 + 0x30;
        fltBuffer[6] = (long)(f_data * 100) % 10 + 0x30;
        fltBuffer[7] = (long)'\0';
    }
}

