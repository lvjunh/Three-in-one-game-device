#ifndef __PWM_H
#define __PWM_H
#include "stm32f4xx.h"
#include "delay.h"


#define ARR 1000
#define PSC 82

void TIM12_PWM_Init(uint32_t arr,uint32_t psc);
void TIM9_PWM_Init(uint32_t arr,uint32_t psc);
#endif
