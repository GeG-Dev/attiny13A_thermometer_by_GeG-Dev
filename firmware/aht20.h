
#ifndef AHT20_H
#define AHT20_H
#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif

#define AHT_ADDRES 0x38

extern int16_t temp ;
extern int16_t humid ;

void aht_init();
bool aht_read_data();

#ifdef __cplusplus
}
#endif



#endif