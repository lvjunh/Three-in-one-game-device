// /**
//  * 以下是超声波模块的应用
//  */

// #include "ultrasonic.h"
// uint16_t distance;  // 测算的距离
// uint8_t Time_Temp;

// void TIM5_Init(void) // 定时器5设置为计数模式
// {
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

//     TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//     TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//     TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//     TIM_TimeBaseInitStructure.TIM_Period = 100000 - 1;
//     TIM_TimeBaseInitStructure.TIM_Prescaler = 168 - 1; // 20ms
//     TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
//     TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);

//     TIM_Cmd(TIM5, DISABLE);
// }

// void Ultrasonic_Init(void)
// {
//     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

//     GPIO_InitTypeDef GPIO_InitStructure;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//     GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//     GPIO_InitStructure.GPIO_Pin = Trig;
//     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
//     GPIO_Init(GPIOC, &GPIO_InitStructure);
// }

// BoolState _ERROER_PROCESS(void) // 超时处理
// {
//     uint8_t i = 100000;
//     while (i--)
//         ;
//     return FALSE;
// }

// uint16_t Ultrasonic_Get_Distance(void)
// {
//     GPIO_SetBits(GPIOC, Trig); // 发送一段波
//     delay_us(10);
//     GPIO_ResetBits(GPIOC, Trig);
//     TIM_Cmd(TIM5,ENABLE);
//     while (GPIO_ReadInputDataBit(GPIOC, Echo) == RESET) // 等待返回高电平
//     {
//         if (!_ERROER_PROCESS()) // 超时重新来
//         {
//             break;
//         }
//     }
//     Time_Temp = TIM5->CNT;
//     TIM5->CNT = 0;
//     TIM_Cmd(TIM5,DISABLE);
//     distance = low_pass_filtering(distance);
//     distance = 340 * Time_Temp / 10000;
//     return distance; // 距离做一下滤波
// }
