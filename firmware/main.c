#include <Arduino.h>
#include "simpleI2C.h"
#include "oledSSD1306.h"
#include "aht20.h"
#include "util/delay.h"

void setup() {
    i2c_init();
    oled_init();
    aht_init();
    oled_clear();

}

void loop() {
    if(aht_read_data()){
        uint16_t realTemp = temp;
        if (realTemp < 0) realTemp = 0;
        uint8_t hundred = 0;
        uint8_t tens = 0;
        while(realTemp >=100){realTemp -= 100; hundred += 1;}
        while(realTemp >=10){realTemp -= 10; tens += 1;}
        oled_drawNum(32,1,hundred);
        oled_drawNum(44,1,tens);
        oled_drawNum(56,1,10);
        oled_drawNum(63,1,realTemp);
        oled_drawNum(75,1,11);

        realTemp = humid;
        if (realTemp < 0) realTemp = 0;
        hundred = 0;
        tens = 0;
        while(realTemp >=100){realTemp -= 100; hundred += 1;}
        while(realTemp >=10){realTemp -= 10; tens += 1;}
        oled_drawNum(32,4,hundred);
        oled_drawNum(44,4,tens);
        oled_drawNum(56,4,10);
        oled_drawNum(63,4,realTemp);
        oled_drawNum(75,4,12);
    }
    _delay_ms(500);

}