#ifndef __KEY_H
#define __KEY_H
#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "control.h"


//Row:F5~F8
#define R1_PIN             GPIO_Pin_5
#define R1_GPIO_PORT       GPIOF
#define R1_GPIO_CLK        RCC_AHB1Periph_GPIOF
 
#define R2_PIN             GPIO_Pin_6
#define R2_GPIO_PORT       GPIOF
#define R2_GPIO_CLK        RCC_AHB1Periph_GPIOF
 
#define R3_PIN             GPIO_Pin_7
#define R3_GPIO_PORT       GPIOF
#define R3_GPIO_CLK        RCC_AHB1Periph_GPIOF
 
#define R4_PIN             GPIO_Pin_8
#define R4_GPIO_PORT       GPIOF
#define R4_GPIO_CLK        RCC_AHB1Periph_GPIOF
 
// Column:F1~F4
#define C1_PIN             GPIO_Pin_1    
#define C1_GPIO_PORT       GPIOF
#define C1_GPIO_CLK        RCC_AHB1Periph_GPIOF
 
#define C2_PIN             GPIO_Pin_2
#define C2_GPIO_PORT       GPIOF
#define C2_GPIO_CLK        RCC_AHB1Periph_GPIOF
 
#define C3_PIN             GPIO_Pin_3
#define C3_GPIO_PORT       GPIOF
#define C3_GPIO_CLK        RCC_AHB1Periph_GPIOF
 
#define C4_PIN             GPIO_Pin_4
#define C4_GPIO_PORT       GPIOF
#define C4_GPIO_CLK        RCC_AHB1Periph_GPIOF



// extern volatile uint16_t num;

void GPIO_SET(void);
void EXTIX_Init(void);
extern int key_code;  

#endif 
