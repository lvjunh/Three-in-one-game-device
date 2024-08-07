#ifndef __EXTI_H
#define __EXTI_H
#include "stm32f4xx.h"

#define EXTI_CLK RCC_AHB1Periph_GPIOA 
#define EXTI_PORT GPIOA
#define EXTI_PIN GPIO_Pin_0


void Exti_Init(void);	

#endif 
