#include "aht20.h"
#include "Arduino.h"
#include "simpleI2C.h"
#include "util/delay.h"

int16_t temp  = 0;
int16_t humid = 0;

void aht_init(){
    _delay_ms(100);
    i2c_start();
    i2c_send_data((AHT_ADDRES << 1) | 0x01);
    if(i2c_read_data(0) != 0x18){
        i2c_stop();
        i2c_start();
        i2c_send_data(AHT_ADDRES << 1);
        i2c_send_data(0xBE);
        i2c_send_data(0x08);
        i2c_send_data(0x00);
    }

    i2c_stop();
    _delay_ms(10);
}

bool aht_read_data(){
    i2c_start();
    i2c_send_data(AHT_ADDRES << 1);
    i2c_send_data(0xAC);
    i2c_send_data(0x33);
    i2c_send_data(0x00);
    i2c_stop();
    _delay_ms(100);
    i2c_start();
    i2c_send_data((AHT_ADDRES << 1) | 0x01);
    if((i2c_read_data(1) & 0x80) != 0){
        i2c_stop();
        return false;
    }

    uint8_t data[5];
    for(uint8_t i = 0; i < 4;i++){
        data[i] = i2c_read_data(1);
    }
    data[4] = i2c_read_data(0);
    i2c_stop();

    uint8_t t_high = data[2] & 0x0F;
    uint8_t t_mid = data[3];
    temp = (t_high * 125) + (((uint16_t)t_mid * 125) >> 8) - 500;
    uint8_t h_high = data[0] >> 4;
    uint8_t h_mid = ((data[0] & 0x0F) << 4) | (data[1] >> 4);
    humid = (((uint16_t)h_high * 125) >> 1) + (((uint16_t)h_mid * 125) >> 9);

    return true;
}