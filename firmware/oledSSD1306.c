#include "Arduino.h"
#include "oledSSD1306.h"
#include "simpleI2C.h"

const uint8_t numArr[13][5] PROGMEM = {
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 0
    {0x00, 0x04, 0x02, 0x7F, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x22, 0x41, 0x49, 0x49, 0x36}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3E, 0x49, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E},  // 9
    {0xC0, 0xC0, 0x00, 0x00, 0x00},  // .
    {0x03, 0x03, 0x7C, 0x44, 0x44}, // °C
    {0x23, 0x13, 0x08, 0x64, 0x62} // %
};
const uint8_t doubleTable[] PROGMEM  = {
    0x00, 0x03, 0x0C, 0x0F, 0x30, 0x33, 0x3C, 0x3F,
    0xC0, 0xC3, 0xCC, 0xCF, 0xF0, 0xF3, 0xFC, 0xFF
};

void oled_write(uint8_t control , uint8_t data){
    i2c_start();
    i2c_send_data(OLED_ADDRES << 1);
    i2c_send_data(control);
    i2c_send_data(data);
    i2c_stop();
    
}

void oled_init(){
    static const uint8_t data[] PROGMEM = {
        0xAE, // display off
        0xA8 , 0x3F, //set MUX (64)
        0xD3 , 0x00, // set Display offset (0)
        0x8D , 0x14, //charge pump settings (0x14 - enable | 0x10 - disable)
        0xA1, //flip Horizontal
        0xC8, //flip Vertical
        0xAF // display on
    };
    i2c_start();
    i2c_send_data(OLED_ADDRES << 1);
    i2c_send_data(0x00);
    for(uint8_t i= 0; i < sizeof(data);i++){
        i2c_send_data(pgm_read_byte(&data[i]));
    }
    i2c_stop();
}

void oled_set_cursor(uint8_t x , uint8_t y){
    i2c_start();
    i2c_send_data(OLED_ADDRES << 1);
    i2c_send_data(0x00);
    i2c_send_data(0x00 | (x & 0x0F));
    i2c_send_data(0x10 | (x >> 4));
    i2c_send_data(0xB0 | y);
    i2c_stop();
}

void oled_clear(){
    for(uint8_t y = 0; y < 8;y++){
        oled_set_cursor(0,y);
        i2c_start();
        i2c_send_data(OLED_ADDRES << 1);
        i2c_send_data(0x40);

        for(uint8_t x = 0; x < 128;x++){
            i2c_send_data(0x00);
        }
        i2c_stop();
    }
}

void oled_drawNum(uint8_t x , uint8_t y , uint8_t num){
    for(uint8_t part = 0;part < 2;part++ ){
        oled_set_cursor(x,y + part);
        i2c_start();
        i2c_send_data(OLED_ADDRES << 1);
        i2c_send_data(0x40);
        for(uint8_t i = 0; i < 5;i++){
            uint8_t b = pgm_read_byte(&numArr[num][i]);
            if(part == 1) b >>= 4;
            uint8_t d = pgm_read_byte(&doubleTable[b & 0x0F]);
            i2c_send_data(d);
            i2c_send_data(d);
        }
        i2c_stop();
    }
    
}