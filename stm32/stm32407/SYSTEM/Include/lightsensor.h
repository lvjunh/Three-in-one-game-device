#ifndef __LIGHTSENSOR_H
#define __LIGHTSENSOR_H
#include "stm32f4xx.h"


#define PUT_DOWM 1
#define PICK_UP 0


void Lightsensor_Init(void);
uint8_t Test_drugs(void);  // 检测药品是否放下

#endif
