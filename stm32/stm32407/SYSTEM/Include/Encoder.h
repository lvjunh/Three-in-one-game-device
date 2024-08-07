#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"

#define IC_ARR 65535
#define IC_PSC 0


void TIM3_Encoder_Init(uint32_t arr,uint32_t psc);      //TIM5的编码器模式初始化
void TIM2_Encoder_Init(uint32_t arr,uint32_t psc);      //TIM2的编码器模式初始化
int16_t Read_Encoder(uint8_t TIMX);   // 读取编码器的值

#endif

