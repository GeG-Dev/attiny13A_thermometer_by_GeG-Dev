
#ifndef SIMPLEI2C_H
#define SIMPLEI2C_H

#include "Arduino.h"

#define SDA_PIN PB0
#define SCL_PIN PB1

#ifdef __cplusplus
extern "C"{
#endif


void i2c_init();
static inline void set_sda(uint8_t state){
    if (state) DDRB &= ~(1 << SDA_PIN);
    else DDRB |= (1 << SDA_PIN);
}
static inline void set_scl(uint8_t state){
    if (state) DDRB &= ~(1 << SCL_PIN);
    else DDRB |= (1 << SCL_PIN);
}
void i2c_start();
void i2c_stop();
bool i2c_send_data(uint8_t data);
uint8_t i2c_read_data( uint8_t ACK);

#ifdef __cplusplus
}
#endif
#endif