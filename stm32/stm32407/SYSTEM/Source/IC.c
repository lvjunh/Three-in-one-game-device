// /**
//  * TIM 输入捕获模式
// */

// #include "IC.h"

// void IC_Init(void)
// {
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // to do 修改为定时器3指定的channel引脚
	
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
// 	TIM_InternalClockConfig(TIM3);
	
// 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
// 	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
// 	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
// 	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
// 	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
// 	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
// 	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
// 	TIM_ICInitTypeDef TIM_ICInitStructure;
// 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
// 	TIM_ICInitStructure.TIM_ICFilter = 0xF;
// 	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
// 	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
// 	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
// 	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
// 	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
// 	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
// 	TIM_Cmd(TIM3, ENABLE);

// }

// uint32_t Read_Encoder(uint8_t TIMX)
// {	
// 	uint32_t cnt;
// 	switch (TIMX)
// 	{
// 	case 2:
// 		cnt = TIM2->CNT;
// 		TIM2->CNT=0;
// 		return cnt;
// 	case 3:
// 		cnt = TIM3->CNT;
// 		TIM3->CNT = 0;
// 		return cnt;
// 	}
// 	return 0;
	
// }
