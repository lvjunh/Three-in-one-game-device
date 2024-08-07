#include "exti.h"

// void Exti_Init(void)
// {
//     RCC_AHB1PeriphClockCmd(EXTI_CLK,ENABLE);
//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
//     GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//     GPIO_InitStructure.GPIO_Pin = EXTI_PIN;
//     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(EXTI_PORT,&GPIO_InitStructure);

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);          //使能SYSCFG时钟
// 	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);       //PA0 连接到中断线0

//     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//     EXTI_InitTypeDef EXTI_InitStructure;
// 	EXTI_InitStructure.EXTI_Line = EXTI_Line0;          //LINE0
// 	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         //中断事件
// 	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;      //上升沿触发 
// 	EXTI_InitStructure.EXTI_LineCmd = ENABLE;       //使能LINE0
// 	EXTI_Init(&EXTI_InitStructure);             //配置

//     NVIC_InitTypeDef   NVIC_InitStructure;
// 	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;        //外部中断0
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;        //抢占优先级0
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;       //子优先级2
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //使能外部中断通道
// 	NVIC_Init(&NVIC_InitStructure); //配置

// }

// void EXTI0_IRQHandler(void)
// {
// 	if(EXTI_GetITStatus(EXTI_Line0) == SET)  // 发生中断
//     {
//         ;
//     }		 
// 	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
// }	



