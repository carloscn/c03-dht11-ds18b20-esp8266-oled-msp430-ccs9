/*
 * i2c.c
 *
 *  Created on: 2019Äê3ÔÂ10ÈÕ
 *      Author: multimicro
 */

#include "iic.h"
#include <stdlib.h>


//i2c start
void i2c_start(EI2C *self){
    SCK_HIGH();
    SDA_HIGH();
    SDA_LOW();
    SCK_LOW();
}

//i2c stop
void i2c_stop(EI2C *self) {
    SCK_HIGH();
    SDA_LOW();
    SDA_HIGH();
}

//i2c write data
void i2c_write_byte(EI2C *self, unsigned char i2c_byte) {
    unsigned char i;
    SCK_LOW();
    for (i = 0; i < 8; ++i) {
        if (i2c_byte & 0x80) {
            SDA_HIGH();
        } else {
            SDA_LOW();
        }
        SCK_HIGH();
        SCK_LOW();
        i2c_byte<<=1;
    }
}

//i2c write command
void i2c_write_command(EI2C *dev,unsigned char i2c_command) {
    dev->start(dev);
    dev->write(dev, 0x78);     //slave address, SA0 = 0;
    dev->waitack(dev);
    dev->write(dev, 0x00);     //write data
    dev->waitack(dev);
    dev->write(dev, i2c_command);
    dev->waitack(dev);
    dev->stop(dev);
}

//i2c write data
void i2c_write_data(EI2C *dev,unsigned char i2c_data) {
    dev->start(dev);
    dev->write(dev, 0x78);     //slave address, SA0 = 0;
    dev->waitack(dev);
    dev->write(dev, 0x40);     //write data
    dev->waitack(dev);
    dev->write(dev, i2c_data);
    dev->waitack(dev);
    dev->stop(dev);
}

//i2c wait ack;
void i2c_wait_ack(EI2C *self) {

    SCK_HIGH();
    SCK_LOW();
}

void i2c_init(EI2C *self) {

//    self->init          =   &i2c_init;
    self->start         =   &i2c_start;
    self->stop          =   &i2c_stop;
    self->write         =   &i2c_write_byte;
    self->waitack       =   &i2c_wait_ack;

    SET_SCK_PIN();
    SET_SDA_PIN();
}

