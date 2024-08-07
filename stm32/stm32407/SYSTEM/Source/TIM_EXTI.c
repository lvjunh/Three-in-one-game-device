#include "TIM_EXTI.h"

void TIM_EXTI_Init(uint32_t arr,uint32_t psc)  
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision =TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period =arr-1;
    TIM_TimeBaseInitStructure.TIM_Prescaler =psc-1;   
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
    
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}
