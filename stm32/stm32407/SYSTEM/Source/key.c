#include "key.h"

u8 flag_key = 0;
 
void GPIO_GIVE() {  //全部置为低电平，中断检测
    GPIO_ResetBits(C1_GPIO_PORT, C1_PIN);
    GPIO_ResetBits(C2_GPIO_PORT, C2_PIN);
    GPIO_ResetBits(C3_GPIO_PORT, C3_PIN);
    GPIO_ResetBits(C4_GPIO_PORT, C4_PIN);
}
 
void EXTI9_5_IRQHandler(void) {  //中断服务函数
    delay_ms(10);
    if (EXTI_GetFlagStatus(EXTI_Line5) != RESET) {
        delay_ms(20);
        GPIO_ResetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0));
            flag_key = 1;
            current_state = 1;
            EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_ResetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0));
            flag_key = 1;
            current_state = 2;
            EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_ResetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0));
            flag_key = 1;
            current_state = 3;
            EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_ResetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN) == 0));
            flag_key = 1;
            current_state = 4;
            EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
    }
    else if (EXTI_GetFlagStatus(EXTI_Line6) != RESET) {
        delay_ms(10);
        GPIO_ResetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0) {
            delay_ms(20);
            while (GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0);
            flag_key = 1;
            current_state = 5;
            EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_ResetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0) {
            delay_ms(20);
            while (GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0);
            flag_key = 1;
            current_state = 6;
            EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_ResetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0));
            flag_key = 1;
            current_state = 7;
            EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_ResetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN) == 0));
            flag_key = 1;
            current_state = 8;
            EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
    }
    else if (EXTI_GetFlagStatus(EXTI_Line7) != RESET) {
        delay_ms(10);
        GPIO_ResetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0) {
            delay_ms(20);
            while (GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0);
            flag_key = 1;
            current_state = 9;
            EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_ResetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0) {
            delay_ms(20);
            while (GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0);
            flag_key = 1;
            current_state = 10;
            EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_ResetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0));
            flag_key = 1;
            current_state = 11;
            EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_ResetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN) == 0));
            flag_key = 1;
            current_state = 12;
            EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
    }
    else if (EXTI_GetFlagStatus(EXTI_Line8) != RESET) {
        delay_ms(10);
 
        GPIO_ResetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0));
            flag_key = 1;
            current_state = 13;
            EXTI_ClearITPendingBit(EXTI_Line8); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_ResetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0) {
 
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0));
            flag_key = 1;
            current_state = 14;
            EXTI_ClearITPendingBit(EXTI_Line8); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
 
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_ResetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_SetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0));
            flag_key = 1;
            mode_select++;   // 模式 +1
            current_state = state_pause;
            EXTI_ClearITPendingBit(EXTI_Line8); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
 
        GPIO_SetBits(C1_GPIO_PORT, C1_PIN);
        GPIO_SetBits(C2_GPIO_PORT, C2_PIN);
        GPIO_SetBits(C3_GPIO_PORT, C3_PIN);
        GPIO_ResetBits(C4_GPIO_PORT, C4_PIN);
        if (GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0) {
            delay_ms(20);
            while ((GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN) == 0));
            flag_key = 1;
            sure_key = !sure_key;  // 确定按键
            current_state = state_pause;
            EXTI_ClearITPendingBit(EXTI_Line8); //清除LINE0上的中断标志位
            GPIO_GIVE();
            return;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE5上的中断标志位
    EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE6上的中断标志位
    EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE7上的中断标志位
    EXTI_ClearITPendingBit(EXTI_Line8); //清除LINE8上的中断标志位
    GPIO_GIVE();
}
 
 
 
//GPIO初始化程序
void GPIO_SET(void) 
{             
    RCC_AHB1PeriphClockCmd(C1_GPIO_CLK | C2_GPIO_CLK | C3_GPIO_CLK | C4_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(R1_GPIO_CLK | R2_GPIO_CLK | R3_GPIO_CLK | R4_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);


    GPIO_InitTypeDef GPIO_InitStructure;
 
    GPIO_InitStructure.GPIO_Pin = C1_PIN;//列输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_Init(C1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = C2_PIN;//C2列输出
    GPIO_Init(C2_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = C3_PIN;//C3列输出
    GPIO_Init(C3_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = C4_PIN;//C4列输出
    GPIO_Init(C4_GPIO_PORT, &GPIO_InitStructure);
 
    GPIO_InitStructure.GPIO_Pin = R1_PIN;//R1_PIN 行输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(R1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = R2_PIN;//R2_PIN 行输入
    GPIO_Init(R2_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = R3_PIN;//R3_PIN 行输入
    GPIO_Init(R3_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = R4_PIN;//R4_PIN 行输入
    GPIO_Init(R4_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//列输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//列输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_GIVE();
}
 
void EXTIX_Init(void) 
{          
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
    GPIO_SET(); //按键对应的IO口初始化
 
    /* 配置EXTI_Line5~8 */
    EXTI_InitTypeDef EXTI_InitStructure;
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource5);//PF5 连接到中断线5
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE5
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能
    EXTI_Init(&EXTI_InitStructure);//配置
 
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6);//PF6 连接到中断线6
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;//LINE6
    EXTI_Init(&EXTI_InitStructure);//配置
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7);//PF7 连接到中断线7
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;//LINE7
    EXTI_Init(&EXTI_InitStructure);//配置
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8);//PF8 连接到中断线8
    EXTI_InitStructure.EXTI_Line = EXTI_Line8;//LINE8
    EXTI_Init(&EXTI_InitStructure);//配置

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);//PB2 连接到中断线2
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;//LINE5
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能
    EXTI_Init(&EXTI_InitStructure);//配置

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);//PB3连接到中断线3
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;//LINE5
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能
    EXTI_Init(&EXTI_InitStructure);//配置
 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);//配置
 
}
 


