#include "beep.h"

void Beep_Init(void)
{
    RCC_AHB1PeriphClockCmd(Beep_CLK,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // 普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // 推挽输出
    GPIO_InitStructure.GPIO_Pin=Beep_Pin;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // 下拉 保证
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(Beep_Port,&GPIO_InitStructure);

    GPIO_ResetBits(Beep_Port,Beep_Pin);
}





