/***
 *
 * 初始化串口1和串口3
 * 串口1作为上位机调试工具
 * 串口3用于接收MV数据
 * 如需使用其他串口根据数据手册引脚复用更改其引脚
 * tips:使用printf与上位机通信请在keil->魔术棒->Target 中勾选 "use MicroLib"
 *
 */
#include "usart.h"

uint8_t Serial1_RxData; // 接收串口1的数据
uint8_t Serial2_RxData; // 接收串口2的数据
uint8_t Serial3_RxData; // 接收串口3数据(MV通信数据)
int32_t openmv[7];		// stm32接收数据数组
int32_t openmv_2[7];	// stm32接收数据数组
uint8_t i;
uint8_t flag = 0;



#ifdef Serial1_printf

void Serial1_Init(uint32_t Baud_rate) // 串口1初始化 用于上位机调试
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 使能USART1时钟

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  //	GPIOA9 复用为USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //	GPIOA10复用为USART1

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // GPIOA9->TX ; GPIOA10->RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			// 复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   // 上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baud_rate;									// 波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// 收发模式
	USART_Init(USART1, &USART_InitStructure);										// 初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									// 开启相关中断

	NVIC_InitTypeDef NVIC_InitStructure; // 配置串口中断
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE); // 使能串口1
}

#endif


#ifdef HC05

#define HC05_Master_Addr "98d3:71:fd702d" // 主机蓝牙地址


void Serial2_Init(uint16_t Baud_rate) // 串口2初始化 用于蓝牙通信
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // 使能USART2时钟

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2); //	GPIOD5 	复用为USART2
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); //	GPIOD6	复用为USART2

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; // GPIOD5->TX ; GPIOD6->RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		   // 复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   // 上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baud_rate;									// 波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// 收发模式
	USART_Init(USART2, &USART_InitStructure);										// 初始化串口2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									// 开启相关中断

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2, ENABLE); // 使能串口2
}

#endif



void Serial3_Init(uint32_t Baud_rate) // 串口3初始化 用于接收MV数据
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  // 使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // 使能USART3时钟

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); //	GPIOB9复用为USART3
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); //	GPIOB10复用为USART3

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // GPIOB10->TX ; GPIOB11->RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			 // 复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   // 上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baud_rate;									// 波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// 收发模式
	USART_Init(USART3, &USART_InitStructure);										// 初始化串口1
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);									// 开启相关中断0

	NVIC_InitTypeDef NVIC_InitStructure; // 配置串口中断
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART3, ENABLE); // 使能串口3
}


void Serial_SendByte(USART_TypeDef *USARTx, uint8_t Byte) // 串口发送1字节
{
	USART_SendData(USARTx, Byte);
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
		;
}


int fputc(int ch, FILE *f) // 重定向 printf 函数 -> 定向至串口1 方便上位机调试
{
	Serial_SendByte(USART1, ch);
	return ch;
}

uint8_t Serial_GetRxData(uint8_t USARTx) // 接收的数据,返回0表示未接收到数据
{
	uint8_t temp1, temp2, temp3;
	switch (USARTx)
	{
	case 1:
	{
		temp1 = Serial1_RxData;
		Serial1_RxData = 0;
		return temp1;
	}
	case 2:
	{
		temp2 = Serial1_RxData;
		Serial1_RxData = 0;
		return temp2;
	}
	case 3:
	{
		temp3 = openmv[2];
		return temp3;
	}
	default:
		return ERROR;
	}
}

uint8_t USART1_IRQHandler(void) // 返回1表示成功进入中断 0则是没有进入
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Serial1_RxData = USART_ReceiveData(USART1);
		Serial_SendByte(USART2, Serial1_RxData);		// 接收到串口数据马上发送到蓝牙
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志位
		return SUCCESS;
	}
	return ERROR;
}


void USART2_IRQHandler(void) // 串口2用于蓝牙通信
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		Serial2_RxData = USART_ReceiveData(USART2);



		USART_ClearITPendingBit(USART2,USART_IT_RXNE);	
	}
}


uint8_t USART3_IRQHandler(void) // 串口3用于与MV通信
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		Serial3_RxData = USART_ReceiveData(USART3);
		if (Serial3_RxData == 0x2C && flag == 0) // 接收帧头
		{
			flag = 1;
			openmv[0] = 0x2C;
		}
		else if (Serial3_RxData == 0x12 && flag == 1) // 二次验证帧头
		{
			flag = 2;
			openmv[1] = 0x12;
		}
		else if (flag == 2) // 开始接收有用数据
		{
			flag = 3;
			openmv[2] = Serial3_RxData;
		}
		else if (flag == 3)
		{
			flag = 4;
			openmv[3] = Serial3_RxData;
		}
		else if (flag == 4)
		{
			flag = 5;
			openmv[4] = Serial3_RxData;
		}
		else if (flag == 5)
		{
			flag = 6;
			openmv[5] = Serial3_RxData;
	
		} // 到此接收数据结束
		else if (flag == 6)
		{
			if (Serial3_RxData == 0x5B) // 判断是否为帧尾
			{
				flag = 0;
				openmv[6] = 0x5B;
			}
			else if (Serial3_RxData != 0x5B) // 不是帧尾 清除数据 重新来过
			{
				flag = 0;
				for (i = 0; i < 7; i++)
				{
					// memset(openmv,0,4);
					openmv[i] = 0x00;
				}
			}
		}
		else // 数据异常清除数据
		{
			flag = 0;
			for (i = 0; i < 7; i++)
			{
				openmv[i] = 0x00;
			}
		}
		USART_ClearITPendingBit(USART3, USART_IT_RXNE); // 清除中断标志位
		return SUCCESS;
	}
	return ERROR;
}

void Send_code_to_openmv(uint8_t data,uint8_t number)
{
	uint8_t send_num = 0;
	for (send_num = 0;send_num < number ; send_num++)
	{
		Serial_SendByte(USART3,data); // 告诉openmv返回5号棋盘
	}
}

void clear_openmv(void)
{
	for (i = 0; i < 7; i++)
	{
		openmv[i] = 0x00;
	}
}

