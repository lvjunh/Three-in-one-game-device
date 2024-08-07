#ifndef __PID_H
#define __PID_H
#include "stm32f4xx.h"
#include "Common_filter.h"
#include "lcd.h"

int16_t V_PID_Left(int16_t target_V, int16_t cal_V); // 输入目标值和当前测量值
int16_t V_PID_Right(int16_t target_V, int16_t cal_V); // 输入目标值和当前测量值
int16_t Line_PID(int16_t rho, int16_t Taget_rho); // 循迹角度环闭环
int16_t MyAbs(int16_t p);
void PWM_OUT_LIMIT(float *PWM_out, int32_t PWM_MAX, int32_t PWM_MIN); 
int16_t Turn_PID(int16_t pluse, int16_t Taget_pluse);
int16_t Servo_Fx_PID(int16_t Fx, int16_t Taget_Fx);
int16_t Servo_Fy_PID(int16_t Fy, int16_t Taget_Fy);
#endif
