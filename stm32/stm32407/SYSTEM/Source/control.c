/**
 *
 * 内部外设使用情况说明:
 *
 * 定时器中断: TIM4
 * USART3 : GPIOB10->TX ; GPIOB11->RX (openmv 通信)
 * PG1(x轴)| PG4(Y轴) | PC1(抓取轴) -> CLK产生
 * PG2(x轴)| PG5(Y轴) | PC2(抓取轴) -> 步进电机方向控制
 * PG3(x轴)| PG6(Y轴) | PC3(抓取轴) -> 步进电机使能端
 *	
 * 线圈吸取chess:  PC4
 *
 * 矩阵键盘按键扫描 4*4 (行扫描)
 * PF1 -> PF8
 *
 *
 *  L1  L2  L3  L4
 *
 * 	S1	S2	S3	S4		H1
 *
 * 	S5	S6	S7	S8		H2
 *
 * 	S9	S10	S11	S12		H3
 *
 * 	S13	S14	S15	S16		H4
 *
 * S1 for Position_one
 * S2 for Position_two
 * S3 for Position_three
 * S4 for Position_four
 *
 *	to do list :
 * 
 * 控制方案:状态机控制方式 :
 *
 * current_state = state_pause    	棋盘编号位置状态
 * current_state = position_one   	棋盘编号位置状态
 * current_state = position_two   	棋盘编号位置状态
 * current_state = position_three 	棋盘编号位置状态
 * current_state = position_four  	棋盘编号位置状态
 * current_state = position_five  	棋盘编号位置状态
 * current_state = position_six   	棋盘编号位置状态
 * current_state = position_seven 	棋盘编号位置状态
 * current_state = position_eight 	棋盘编号位置状态 
 * current_state = position_reset	棋盘位置复位
 * 
 * 
 *    1    2    3
 *    4    5    6
 *    7    8    9
 *
 * 
 * 抓取指定位置棋子之后 -> 回到初始位置 -> 开始在棋盘放置棋子 -> 回到初始位置
 * 
 * case 1: 棋子放在五号棋盘,
 * 		current_state = positon_five
 *		
 *
 *
 * 
 * 两个格点之间的坐标差值:
 * (193,185)
 * (196,127)
 * (198,68)
 * One_grid = 58 (坐标距离为58左右 所对应的脉冲数为1500)
 * 63  1800
 *    
 * 58 1500
 * x(x为坐标距离)  z
 * 
 * z = 1500 * x / 58
 * 
 * 
 * 
 * 第四问通信流程如下: 
 * 
 * 
 * 
 * 
 * 
 */

#include "control.h"

uint8_t mode_select = 0; 
int32_t current_state = state_pause;
uint16_t remaining_steps = 0;
uint8_t judge_chess_code = chess_white_3; // 首先抓取
uint8_t judge_chess_code_black = chess_black_1; // 首先抓取
uint8_t sure_key = 0;


void Control_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4|GPIO_Pin_5|
								  GPIO_Pin_6;

	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4;

	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
}

/**
 * @brief 步进电机使能端控制
 * @retval 无
 */
void Driver_Control_Enable_or_Disable(uint8_t motor_number, uint8_t status)
{
	if (DISABLE == status)
	{
		switch (motor_number)
		{
		case Motor_X: // X轴失能
			GPIO_WriteBit(GPIOG, GPIO_Pin_3, Bit_SET);
			break;
		case Motor_Y: // Y轴失能
			GPIO_WriteBit(GPIOG, GPIO_Pin_6, Bit_SET);
			break;
		case Motor_Crawl: // 抓取轴失能
			GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_SET);
		default:
			break;
		}
	}
	else if(ENABLE == status)
	{
		switch (motor_number)
		{
		case Motor_X: // X轴使能
			GPIO_WriteBit(GPIOG, GPIO_Pin_3, Bit_RESET);
			break;
		case Motor_Y: // Y轴使能
			GPIO_WriteBit(GPIOG, GPIO_Pin_6, Bit_RESET);
			break;
		case Motor_Crawl: // 抓取轴使能
			GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_RESET);
		default:
			break;
		}
	}
}


/**
 * @brief 步进电机节拍设置
 * @retval 无
 */
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		if (remaining_steps > 0)
		{
			GPIO_ToggleBits(GPIOG, GPIO_Pin_1);  	// Motor_X CLK
			GPIO_ToggleBits(GPIOG, GPIO_Pin_4);		// Motor_Y CLK 
			GPIO_ToggleBits(GPIOC, GPIO_Pin_1);		// Motor_Crawl CLK
			remaining_steps--;
		}
		else
		{
			current_state = state_pause;
			TIM_Cmd(TIM4, DISABLE);	  // 停止中断
			Driver_Control_Enable_or_Disable(Motor_X, 	  DISABLE);	// 禁用驱动器
			Driver_Control_Enable_or_Disable(Motor_Y, 	  DISABLE);	// 禁用驱动器
			Driver_Control_Enable_or_Disable(Motor_Crawl, DISABLE);	// 禁用驱动器
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}


/**
 * @brief 步进电机启动函数
 * @retval 无
 */
void Stepper_Move(int steps, uint8_t motor_number)
{
	if (steps > 0)
	{
		switch (motor_number)
		{
		case Motor_X:
			GPIO_WriteBit(GPIOG, GPIO_Pin_2, Bit_SET); // 设置方向
			break;
		case Motor_Y:
			GPIO_WriteBit(GPIOG, GPIO_Pin_5, Bit_SET); // 设置方向
			break;
		case Motor_Crawl:
			GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET); // 设置方向
			break;
		default:
			break;
		}
	}
	else
	{
		switch (motor_number)
		{
		case Motor_X:
			GPIO_WriteBit(GPIOG, GPIO_Pin_2, Bit_RESET); // 设置方向
			break;
		case Motor_Y:
			GPIO_WriteBit(GPIOG, GPIO_Pin_5, Bit_RESET); // 设置方向
			break;
		case Motor_Crawl:
			GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET); // 设置方向
			break;
		default:
			break;
		}
		steps = -steps;
	}
	remaining_steps = steps;
	Driver_Control_Enable_or_Disable(motor_number, ENABLE);	// 使能驱动器 
	TIM_Cmd(TIM4, ENABLE); // 使能定时器
}



/**
 * @brief 坐标原点距离初始化		
 * @retval 
 */
void Chess_Steps_Init(Chess_Steps* chess_step)
{
	chess_step->Origin_X = 164;
	chess_step->Origin_Y = 1;
}


/**
 * @brief 抓取棋子,通过传入的棋盘对应点的X,Y坐标,通过线性回归拟合出曲线 F(x,y) = k1*x + k2*y = steps
 * 		  计算到达指定坐标位置所需的steps 计算出 steps		
 * @retval 无
 */
int32_t Motor_Steps_Calculation(int32_t chess_x,int32_t chess_y,Chess_Steps* chess_step)
{
	
	int32_t difference_x =  chess_x - chess_step->Origin_X ;
	int32_t difference_y =  chess_y - chess_step->Origin_Y ;

	if (difference_x < 15 && difference_x > -15) // 滤除微小像素点的误差
	{
		difference_x = 0;
	}
	if (difference_y < 15 && difference_y > -15) // 滤除微小像素点的误差
	{
		difference_y = 0;
	}
	chess_step->chess_y_steps = 1500 * (difference_x) / 58 ;
	chess_step->chess_x_steps = 1500 * (difference_y) / 58 ;
	return TRUE;
}


/**
 * @brief 到达指定位置后 选择抓棋子还是放棋子	
 * @retval 无
 */
void Go_to_designed_location_reset(int16_t step_x ,int16_t step_y,uint8_t status)
{
	if (Stretch_ON == status) // 抓取
	{
		Motor_Arrive_designed_location(step_x, step_y);
		Stretch_ON_OR_OFF(Stretch_ON); // 抓起
		delay_ms(1200);
		current_state = position_one;  // 调用下次时需要进行状态复位
		Motor_Arrive_designed_location(-step_x, -step_y); 	// 回到起始位置
	}
	else 
	{
		Motor_Arrive_designed_location(step_x, step_y);
		Stretch_ON_OR_OFF(Stretch_OFF); // 到达指定位置后放下
		delay_ms(1200);
		current_state = position_one;  // 调用下次时需要进行状态复位
		Motor_Arrive_designed_location(-step_x, -step_y); 	// 回到起始位置
	}
}



/**
 * @brief 抓取指定坐标棋子后返回起始位置, 可以将棋子位置固定	
 * @retval 无
 */
void Stretch_chess(uint8_t chess_number)
{
	switch (chess_number)
	{
		case chess_black_1:
			Go_to_designed_location_reset(chess_black_1_step_x,chess_black_1_step_y,Stretch_ON);
			break;  
		case chess_black_2: 
			Go_to_designed_location_reset(chess_black_2_step_x,chess_black_2_step_y,Stretch_ON);
			break;
		case chess_black_3:
			Go_to_designed_location_reset(chess_black_3_step_x,chess_black_3_step_y,Stretch_ON);
			break;
		case chess_black_4:
			Go_to_designed_location_reset(chess_black_4_step_x,chess_black_4_step_y,Stretch_ON);
			break;
		case chess_black_5:
			Go_to_designed_location_reset(chess_black_5_step_x,chess_black_5_step_y,Stretch_ON);
			break;
		case chess_white_1:
			Go_to_designed_location_reset(chess_white_1_step_x,chess_white_1_step_y,Stretch_ON);
			break; 
		case chess_white_2:
			Go_to_designed_location_reset(chess_white_2_step_x,chess_white_2_step_y,Stretch_ON);
			break;
		case chess_white_3:
			Go_to_designed_location_reset(chess_white_3_step_x,chess_white_3_step_y,Stretch_ON);
			break;
		case chess_white_4:
			Go_to_designed_location_reset(chess_white_4_step_x,chess_white_4_step_y,Stretch_ON);
			break;
		case chess_white_5:
			Go_to_designed_location_reset(chess_white_5_step_x,chess_white_5_step_y,Stretch_ON);
			break;
		default:break;
	}
}

/**
 * @brief 依次抓取棋子	
 * @retval 无
 */
void Order_Stretch_chess(uint8_t statue)
{
	if (Order_Black == statue)
	{
		if(judge_chess_code == chess_white_3+3)
		{
			judge_chess_code = chess_white_2;
		}
		else if(judge_chess_code == chess_white_3+4)
		{
			judge_chess_code = chess_white_1;
		}
		switch (judge_chess_code)
		{
			case chess_white_1:
				Stretch_chess(chess_white_1);  // 先抓取编号一的棋子
				judge_chess_code += 1;
				break;
			case chess_white_2:
				Stretch_chess(chess_white_2);  // 后抓取编号二的棋子
				judge_chess_code += 1;
				break;
			case chess_white_3:
				Stretch_chess(chess_white_3);  // 然后抓取编号三的棋子
				judge_chess_code += 1;
				break;
			case chess_white_4:
				Stretch_chess(chess_white_4);  // 然后抓取编号4的棋子
				judge_chess_code += 1;
				break;
			case chess_white_5:
				Stretch_chess(chess_white_5); 	// 所有棋子抓取完成
				judge_chess_code = chess_white_1; 		// 复位判断棋子代码	
				break;
		default:
			break;
		}
	}
	else if(Order_White == statue)
	{
		switch (judge_chess_code_black)
		{
			case chess_black_3:
				Stretch_chess(chess_black_1);  // 先抓取编号一的棋子
				judge_chess_code_black += 1;
				break;
			case chess_black_4:
				Stretch_chess(chess_black_2);  // 后抓取编号二的棋子
				judge_chess_code_black += 1;
				break;
			case chess_black_2:
				Stretch_chess(chess_black_3);  // 然后抓取编号三的棋子
				judge_chess_code_black += 1;
				break;
			case chess_black_1:
				Stretch_chess(chess_black_4);  // 然后抓取编号4的棋子
				judge_chess_code_black += 1;
				break;
			case chess_black_5:
				Stretch_chess(chess_black_5); 	// 所有棋子抓取完成
				judge_chess_code_black = chess_black_1; 		// 复位判断棋子代码	
				break;
		default:
			break;
		}
	}
}






/**
 * @brief 吸起或放下棋子
 * @retval 无
 */
void Stretch_ON_OR_OFF(uint8_t status)
{
	if(Stretch_ON == status)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
	}
	else 
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	}
}




/**
 * @brief 抓取棋子之后到底指定的位置,先移动X，再移动Y,最后放下
 * @retval 无
 */
void Motor_Arrive_designed_location(int16_t step_x ,int16_t step_y)
{
	/*************** X轴开始移动***************/
	Stepper_Move(step_x,Motor_X);
	while (state_pause != current_state); 		//阻塞主线程 -> 子线程开启控制
	/****************Y轴开始移动**************/
	current_state = position_one;
	Stepper_Move(step_y,Motor_Y);
	while (state_pause != current_state); 		//阻塞主线程 -> 子线程开启控制
	/****************到此到达指定位置**************/
}


/**
 * @brief 舵机设置旋转角度
 * @retval 无
 */
void Servo_Set_Angle(float Angle)
{
	TIM_SetCompare1(TIM9, Angle / 180 * 2000 + 500);
	
}
