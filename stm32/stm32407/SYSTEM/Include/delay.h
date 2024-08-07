
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H
 
 
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_rcc.h"
#include "core_cm4.h"
#include "stm32f4xx_it.h"
#include "misc.h"
 
 
 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 
void Delay_Init(void);					//延时系统初始化
void delay_us(u16 us);				//微秒延时
void delay_ms(u16 ms);				//毫秒延时
void delay_us_2(u32 us);				//微秒延时，范围更大
 
 
 
 
#endif /* __DELAY_H */




























