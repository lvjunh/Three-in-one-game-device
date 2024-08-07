/* Freq = CK_PSC/(PSC+1)/(ARR+1)
 * Duty = CRR/(ARR+1)
 * Reso = 1/(ARR+1)
 * 
 * 对于stm32f407 168M主频，因为系统初始化SystemInit函数里初始化APB1总线时钟为4分频即42M，
 * 所以TIM2~TIM7、TIM12~TIM14的时钟为APB1的时钟的两倍即84M；APB2总线时钟为2分频即84M，TIM1、TIM8~TIM11的时钟为APB2时钟的两倍即168M。
 * 
*/

#include "PWM.h"

void TIM12_PWM_Init(uint32_t arr,uint32_t psc)   // 用于控制电机
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;                  // 初始化GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	TIM_InternalClockConfig(TIM12);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);  // 设置一下引脚复用
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;      // 配置定时器
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = arr ;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc ; 	//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseInitStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;     // 配置定时器为输出PWM
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	
	TIM_OC1Init(TIM12,&TIM_OCInitStructure);      // 选择通道 
	// TIM_OC2Init(TIM12,&TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM12,TIM_OCPreload_Enable); // 使能TIM1 在CCR1上的预装载寄存器
	// TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM12,ENABLE); 	//ARPE 使能
	    
	TIM_SetCompare1(TIM12,0);

	TIM_Cmd(TIM12, ENABLE);    // 打开定时器
}


void TIM9_PWM_Init(uint32_t arr,uint32_t psc) // -> servo
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;                  // 初始化GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	TIM_InternalClockConfig(TIM9);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);  // 设置一下引脚复用
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;      // 配置定时器
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = arr - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1; 	//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;     // 配置定时器为输出PWM
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	
	TIM_OC1Init(TIM9,&TIM_OCInitStructure);      // 选择通道 
	//TIM_OC2Init(TIM9,&TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Enable); // 使能TIM1 在CCR1上的预装载寄存器
	//TIM_OC2PreloadConfig(TIM9,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM9,ENABLE); 	//ARPE 使能

	TIM_Cmd(TIM9, ENABLE);    // 打开定时器
}

