#include "lightsensor.h"


void Lightsensor_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}


uint8_t Test_drugs(void)  // 检测药品是否放下
{           
    if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == RESET)
    {
        return PUT_DOWM;
    }
    else
    {
        return PICK_UP;
    }
}








