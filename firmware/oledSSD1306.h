#ifndef OLEDSSD1306_H
#define OLEDSSD1306_H

#include "Arduino.h"
#include "avr\pgmspace.h"

#ifdef __cplusplus
extern "C"{
#endif
    
#define OLED_ADDRES 0x3C



void oled_init();
void oled_set_cursor(uint8_t x , uint8_t y);
void oled_clear();
void oled_drawNum(uint8_t x , uint8_t y , uint8_t num);

#ifdef __cplusplus
}
#endif
#endif