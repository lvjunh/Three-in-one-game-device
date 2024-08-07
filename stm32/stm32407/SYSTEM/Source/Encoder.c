/***
 * 配置编码器模式
 * 用于电机测速等
 * arr：自动重装值(TIM2,TIM5是32位的!!)
*/
#include "Encoder.h"

void TIM3_Encoder_Init(uint32_t arr,uint32_t psc)      //TIM3的编码器模式初始化
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;  // 设置复用
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);  // 复用映射 -> AF3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);			//初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1; 		
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);     

    TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);	//初始化输入捕获->默认通道1
	TIM_ICInitStruct.TIM_ICFilter=10;       //设置滤波
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter = 10;
	TIM_ICInit(TIM3,&TIM_ICInitStruct);

	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;		//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);						//根据指定的参数初始化VIC寄存器、
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);	//允许更新中断
	TIM_SetCounter(TIM3,0);						//清零定时器计数值
	TIM_Cmd(TIM3,ENABLE);						//开启定时器	
}


void TIM2_Encoder_Init(uint32_t arr,uint32_t psc)      //TIM2的编码器模式初始化
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;    // 设置复用
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);			//初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1; 		
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);     
	
   	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);	//初始化输入捕获->默认通道1
	TIM_ICInitStruct.TIM_ICFilter=10;       //设置滤波
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter = 10;
	TIM_ICInit(TIM2,&TIM_ICInitStruct);

	TIM_ICInitStruct.TIM_ICFilter = 10;
	TIM_ICInit(TIM2,&TIM_ICInitStruct);

	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);						//根据指定的参数初始化VIC寄存器、
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);	//允许更新中断
	TIM_SetCounter(TIM2,0);						//清零定时器计数值
	TIM_Cmd(TIM2,ENABLE);						//开启定时器	
}


void TIM3_IRQHandler(void) 	//进入TIM5中断
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

	
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}


int16_t Read_Encoder(uint8_t TIMX)   	// 读取编码器的值
{	
	int16_t cnt2,cnt3;
	switch (TIMX)
	{
		case 2:{cnt2 = (int16_t)TIM2->CNT ; TIM2->CNT = 0 ; return cnt2;}
		case 3:{cnt3 = (int16_t)TIM3->CNT ; TIM3->CNT = 0 ; return cnt3;}	
		default: return 1;
	}
}
