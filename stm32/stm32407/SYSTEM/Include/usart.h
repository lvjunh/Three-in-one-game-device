#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "stdarg.h"
#include "stm32f4xx.h"
#include "control.h"

void Serial1_Init(uint32_t Baud_rate);   // 串口1初始化 用于上位机调试
void Serial3_Init(uint32_t Baud_rate);   // 串口3初始化 用于接收MV数据
void Serial_SendByte(USART_TypeDef* USARTx,uint8_t Byte);   // 串口发送1字节
uint8_t Serial_GetRxData(uint8_t USARTx);  // 接收的数据,返回0表示未接收到数据
void Serial2_Init(uint16_t Baud_rate);   // 串口2初始化 用于蓝牙通信
void Send_code_to_openmv(uint8_t data,uint8_t number);
void clear_openmv(void);

extern int32_t openmv[7]; // stm32接收数据数组
extern uint8_t Serial1_RxData; 	// 接收串口1的数据
extern uint8_t Serial2_RxData;    // 接收串口2的数据
extern uint8_t Serial3_RxData;   // 接收串口3数据(MV通信数据)		

#define Serial1_printf 1    //开启

#endif
