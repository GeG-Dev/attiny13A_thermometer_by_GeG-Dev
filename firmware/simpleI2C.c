#include "simpleI2C.h"
#include "Arduino.h"

void i2c_init(){
    PORTB &= ~((1 << SDA_PIN) | (1 << SCL_PIN));
}

void i2c_start(){
    set_sda(1);
    set_scl(1);
    set_sda(0);
    set_scl(0);
}
void i2c_stop(){
    set_sda(0);
    set_scl(1);
    set_sda(1);
}
bool i2c_send_data(uint8_t data){
    for(uint8_t i = 0; i < 8;i++){
        if(data & 0x80)set_sda(1);
        else set_sda(0);
        
        set_scl(1);
        set_scl(0);
        
        data <<= 1;
    }
    set_sda(1);
    set_scl(1);

    bool ack = !(PINB & (1 << SDA_PIN));
    set_scl(0);
    return ack;

}
uint8_t i2c_read_data(uint8_t ACK){
    uint8_t data = 0;
    set_sda(1);
    for(uint8_t i = 0; i < 8;i++){
        data <<= 1;
        set_scl(1);

        if(PINB & (1 << SDA_PIN)) data |= 0x01;
        set_scl(0);
    }
    if (ACK)set_sda(0);
    else set_sda(1);
    set_scl(1);
    set_scl(0);

    return data;
}