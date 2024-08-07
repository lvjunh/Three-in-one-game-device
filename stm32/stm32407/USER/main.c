#include "stm32f4xx.h"
#include "usart.h"
#include "PWM.h"
#include "control.h"
#include "TIM_EXTI.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "oled.h"
#include "MYIIC.h"

Chess_Steps chess_step;// 实例化坐标

void BSP_Init(void)
{
	Control_Init();
	Delay_Init();
	LED_Init();
	GPIO_SET();
	EXTIX_Init();
	LCD_Init();
	Serial3_Init(115200); // 串口3 接收openmv
	TIM_EXTI_Init(200, 205); // 步进电机脉冲信号
	Chess_Steps_Init(&chess_step); // 初始化坐标原点
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}


/**
 * @brief 开环状态机控制,到达指定棋盘号
 * @retval 无
 */
void mode1_2_state_control(int32_t* state) // 控制电机取坐标落点
{
	switch (*state)
	{
	case state_pause: // 暂停状态，失能定时器与电机
	{
		Driver_Control_Enable_or_Disable(Motor_X, DISABLE);
		Driver_Control_Enable_or_Disable(Motor_Y, DISABLE);
		Driver_Control_Enable_or_Disable(Motor_Crawl, DISABLE);
		break;
	}
	case position_five: 
		Go_to_designed_location_reset(2 * One_grid + grid_expend,0,Stretch_OFF); // 到达指定位置后放下棋子
		break;
	case position_four:
		Go_to_designed_location_reset(One_grid + grid_expend,0,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_seven:
		Go_to_designed_location_reset(One_grid + grid_expend, One_grid,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_one:
		Go_to_designed_location_reset(One_grid + grid_expend, -One_grid,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_two:
		Go_to_designed_location_reset(2 * One_grid + grid_expend, -One_grid,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_eight:
		Go_to_designed_location_reset(2 * One_grid + grid_expend, One_grid,Stretch_OFF);// 到达指定位置后放下棋子
		break; 
	case position_six:
		Go_to_designed_location_reset(2 * One_grid + grid_expend + One_grid, 0,Stretch_OFF);// 到达指定位置后放下棋子
		break; 
	case position_nine:
		Go_to_designed_location_reset(2 * One_grid + grid_expend + One_grid, One_grid,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_three:
		Go_to_designed_location_reset(2 * One_grid + grid_expend + One_grid, -One_grid,Stretch_OFF);// 到达指定位置后放下棋子
		break;		   
	case position_ten: // 指定抓取
		Stretch_chess(chess_white_4);
		break;
	case position_eleven:
		Stretch_chess(chess_white_5);
		break; 
	case position_twelve:
		Stretch_chess(chess_black_4);
		break;
	case position_thirteen:
		Stretch_chess(chess_black_5);
		break;
	default:
		break;
	}
}

/**
 * @brief  第三题之后
 * @retval 无
 */
void mode3_state_control(int32_t* state)
{
	switch (*state)
	{
	case state_pause: // 暂停状态，失能定时器与电机
	{
		Driver_Control_Enable_or_Disable(Motor_X, DISABLE);
		Driver_Control_Enable_or_Disable(Motor_Y, DISABLE);
		Driver_Control_Enable_or_Disable(Motor_Crawl, DISABLE);
		break;
	}
	case position_five: 
		Go_to_designed_location_reset(2 * One_grid + grid_expend+200,grid_expend-100,Stretch_OFF); // 到达指定位置后放下棋子
		break;
	case position_four:
		Go_to_designed_location_reset(One_grid + grid_expend+200,-250,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_seven:
		Go_to_designed_location_reset(One_grid + grid_expend-350, One_grid-500,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_one:
		Go_to_designed_location_reset(One_grid + grid_expend+900, -One_grid-250,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_two:
		Go_to_designed_location_reset(2 * One_grid + grid_expend+900, -One_grid+300,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_eight:
		Go_to_designed_location_reset(2 * One_grid + grid_expend-300, One_grid,Stretch_OFF);// 到达指定位置后放下棋子
		break; 
	case position_six:
		Go_to_designed_location_reset(2 * One_grid + grid_expend + One_grid,700 ,Stretch_OFF);// 到达指定位置后放下棋子
		break; 
	case position_nine:
		Go_to_designed_location_reset(2 * One_grid + grid_expend + One_grid-400, One_grid+600,Stretch_OFF);// 到达指定位置后放下棋子
		break;
	case position_three:
		Go_to_designed_location_reset(2 * One_grid + grid_expend + One_grid+500, -One_grid+900,Stretch_OFF);// 到达指定位置后放下棋子
		break;		   
	case position_fourteen:  					// 第四问单一按键控制
		Order_Stretch_chess(Order_Black); 		// 首先抓取棋子
		while (*(openmv+5) == 0); 				// 阻塞线程等待openmv返回落点坐标
		delay_ms(100);							// 延时100ms
		current_state = position_one;  			// 调用下次时需要进行状态复位
		mode1_2_state_control(openmv+5); 		// 此时需要将 落点位置与棋盘格子相对应
		clear_openmv();							// 放置完成清除Openmv接收信息
		delay_ms(2000);							// 等待白棋下落
		Send_code_to_openmv(0x01,1);  			// 给openmv发送装置黑白棋已经落下的信号
		LCD_ShowNum(130,10,*(openmv+5),2,16,BLUE);
		break;
	case position_ten: // 指定抓取棋子
		Stretch_chess(chess_white_4);
		break;
	case position_eleven:
		Stretch_chess(chess_white_5);
		break; 
	case position_twelve:
		Stretch_chess(chess_black_4);
		break;
	case position_thirteen:
		Stretch_chess(chess_black_5);
		break;
	default:
		break;
	}
}
 
/**
 * @brief  第五题
 * @retval 无
 */
void mode4_state_control(int32_t* state)
{
	switch (*state)
	{
	case state_pause: // 暂停状态，失能定时器与电机
	{
		Driver_Control_Enable_or_Disable(Motor_X, DISABLE);
		Driver_Control_Enable_or_Disable(Motor_Y, DISABLE);
		Driver_Control_Enable_or_Disable(Motor_Crawl, DISABLE);
		break;
	}   
	case position_fourteen:  					// 第五问单一按键控制
		Order_Stretch_chess(Order_Black); 		// 首先抓取棋子
		while (*(openmv+5) == 0); 				// 阻塞线程等待openmv返回落点坐标
		delay_ms(100);							// 延时100ms
		current_state = position_one;  			// 调用下次时需要进行状态复位
		mode1_2_state_control(openmv+5); 		// 此时需要将 落点位置与棋盘格子相对应
		clear_openmv();							// 放置完成清除Openmv接收信息
		delay_ms(2000);							// 等待白棋下落
		Send_code_to_openmv(0x01,1);  			// 给openmv发送装置黑白棋已经落下的信号
		LCD_ShowNum(130,10,*(openmv+5),2,16,BLUE);
		break;
	default:
		break;
	}
}


void Mode_Select(void)
{
	
	if (sure_key == SET)  // 确定按键被按下
	{
		LCD_ShowNum(50,60,sure_key,1,16,BLUE); // 显示确认按键
		switch (mode_select)
		{
			case 1 : mode1_2_state_control(&current_state); break;   // 模式1 负责 1 2 两问
			case 2 : mode3_state_control(&current_state)  ;LCD_ShowNum(130,10,*(openmv+5),2,16,BLUE);break; // 模式2 负责 3 4 两问
			case 3 : mode4_state_control(&current_state)  ;LCD_ShowNum(130,10,*(openmv+5),2,16,BLUE);break; // 模式3 负责 5
		default:
			break;
		}	
	}
	else	// 查看按键模式
	{
		LCD_ShowNum(50,40,mode_select,1,16,BLUE);
		LCD_ShowNum(50,60,sure_key,1,16,BLUE); // 显示确认按键
	}
}


int main(void)
{
	BSP_Init();
	LCD_ShowString(10,10,150,10,16,BLUE,"motion_positon:");
	LCD_ShowString(10,40,120,10,16,BLUE,"mode:");
	LCD_ShowString(10,60,120,10,16,BLUE,"sure:");
	while (1) // 后台状态机设定
	{
		Mode_Select();
	}
}



