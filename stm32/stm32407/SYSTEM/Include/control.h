#ifndef __CONTROL_H
#define __CONTROL_H

#include <sys.h>
#include "PWM.h"
#include "PID.h"
#include "Encoder.h"
#include "usart.h"
#include "Common_filter.h"
#include "LCD.h"
#include "led.h"

typedef struct 
{
    int16_t chess_x_steps;
    int16_t chess_y_steps;
    int16_t Origin_X;   // 原点坐标初始化
    int16_t Origin_Y;
}Chess_Steps;

void Control_Init(void); 
void Driver_Control_Enable_or_Disable(uint8_t motor_number, uint8_t status);
void Stepper_Move(int steps, uint8_t motor_number);
void Servo_Set_Angle(float Angle);
int32_t Motor_Steps_Calculation(int32_t chess_x,int32_t chess_y,Chess_Steps* chess_step);
void Stretch_chess(uint8_t chess_number); // 抓取
void Motor_Arrive_designed_location(int16_t step_x ,int16_t step_y);
void Stretch_ON_OR_OFF(uint8_t status);
void Chess_Steps_Init(Chess_Steps* chess_step);
void Go_to_designed_location_reset(int16_t step_x ,int16_t step_y,uint8_t status);
void Order_Stretch_chess(uint8_t statue);

extern int32_t current_state; //当前状态
extern uint8_t mode_select;
extern uint8_t sure_key;
extern uint8_t judge_chess_code;

#define Motor_X     1   // X轴电机
#define Motor_Y     2   // Y轴电机
#define Motor_Crawl 3   // 抓取电机

#define mode_one   15  // 模式1
#define mode_tow   16  // 模式2

#define state_pause     0       
                            
#define position_one       1   //格子编号
#define position_two       2
#define position_three     3
#define position_four      4
#define position_five      5
#define position_six       6
#define position_seven     7
#define position_eight     8
#define position_nine      9
#define position_ten       10
#define position_eleven    11
#define position_twelve    12
#define position_thirteen  13
#define position_fourteen  14
#define position_fifteen   15
#define position_sixteen   16

#define chess_black_1   0  // 棋子编号
#define chess_black_2   1
#define chess_black_3   2
#define chess_black_4   3
#define chess_black_5   4

#define chess_white_1   5
#define chess_white_2   6
#define chess_white_3   7
#define chess_white_4   8
#define chess_white_5   9


/******* 取棋子的脉冲信号******/
#define chess_One_grid 1500
#define grid_expend 300


#define chess_black_1_step_x   4 * One_grid + 700 
#define chess_black_1_step_y   -2*chess_One_grid

#define chess_black_2_step_x   4 * One_grid + 700 
#define chess_black_2_step_y   -chess_One_grid

#define chess_black_3_step_x   4 * One_grid + 700
#define chess_black_3_step_y   0

#define chess_black_4_step_x   4 * One_grid + 700
#define chess_black_4_step_y   chess_One_grid

#define chess_black_5_step_x   4 * One_grid + 700
#define chess_black_5_step_y   2*chess_One_grid


#define chess_white_1_step_x   0
#define chess_white_1_step_y   -2*chess_One_grid

#define chess_white_2_step_x   0
#define chess_white_2_step_y   -1*chess_One_grid

#define chess_white_3_step_x   0
#define chess_white_3_step_y   0

#define chess_white_4_step_x   0
#define chess_white_4_step_y   chess_One_grid

#define chess_white_5_step_x   0
#define chess_white_5_step_y   2*chess_One_grid


#define One_grid 1600   // 一个格子移动的脉冲数

#define Stretch_PULL_UP_Steps   200  //拉起脉冲个数
#define Stretch_PULL_DOWN_Steps 200  //放下脉冲个数
#define Stretch_ON   0             // 拉起
#define Stretch_OFF  1             // 放下


#define finish_game 0x00

#define finish_motion 0x01



#define Order_Black 0
#define Order_White 1



#define finish_flag openmv[4]  // 完成此局游戏标志

#define position openmv[5]   // 落点点位

#define F_x openmv[2]  
#define F_y openmv[3]


#endif
