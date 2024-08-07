#ifndef __BEEP_H
#define __BEEP_H
#include "stm32f4xx.h"

#define Beep_Pin GPIO_Pin_8 
#define Beep_Port GPIOF
#define Beep_CLK RCC_AHB1Periph_GPIOF

#define Beep_ON   GPIO_SetBits(Beep_Port,1) 
#define Beep_OFF  GPIO_ResetBits(Beep_Port,Beep_Pin)
#define Beep_turn  GPIO_ToggleBits(Beep_Port,Beep_Pin)

void Beep_Init(void);	//LED初始化函数

#endif 
