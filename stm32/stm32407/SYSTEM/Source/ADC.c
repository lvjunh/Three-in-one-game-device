// /**
//  * 电池初始电压测量
//  * 
// */
// #include "ADC.h"

// uint16_t DAC_Datas[Dot_X] = {0};
// #define DAC_DHR12R1_ADDRESS 0x40007408


// void AD_Init(void)
// {
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
//     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; // 模拟输入
//     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//     GPIO_Init(GPIOA,&GPIO_InitStructure);

//     ADC_CommonInitTypeDef ADC_CommonInitStructure;
//     ADC_CommonInitStructure.ADC_DMAAccessMode =  ADC_DMAAccessMode_Disabled; // DMA失能
//     ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;  // 独立模式
//     ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
//     ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
//     ADC_CommonInit(&ADC_CommonInitStructure);

//     ADC_InitTypeDef ADC_InitStructure;
//     ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
//     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//     ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//     ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//     ADC_InitStructure.ADC_NbrOfConversion = 1;
//     ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;

//     ADC_Init(ADC1,&ADC_InitStructure);
//     ADC_Cmd(ADC1,ENABLE);
// }


// uint16_t Get_Battery_Voltage(uint8_t ch)
// {
//     ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
// 	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
// 	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

// 	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
// }

// uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)  // 取一下平均值
// {
// 	uint8_t temp_val=0;
// 	u8 t;
// 	for(t=0;t<times;t++)
// 	{
// 		temp_val+=Get_Battery_Voltage(ch);
// 		delay_ms(5);
// 	}
// 	return temp_val/times;
// } 


// void TIM1_Init(uint16_t arr, uint16_t psc)
// {
//     TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//     TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//     TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;
//     TIM_TimeBaseInitStructure.TIM_Period = arr;
//     TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
//     TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
//     TIM_SelectOutputTrigger(TIM1,TIM_TRGOSource_Update);
//     TIM_Cmd(TIM1,ENABLE);
// }

// void Generate_Wave(uint8_t Wave_mode,short Votage_Max,uint16_t Wave[])
// {
//     short i=0;
//     float temp;
//     short temp2;
//     switch (Wave_mode)
//     {
//     case /* constant-expression */:
//         /* code */
//         break;
    
//     default:
//         break;
//     }

// }













