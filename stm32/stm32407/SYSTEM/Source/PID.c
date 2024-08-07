#include "PID.h"

/**
 * @brief PWM限幅
 * @param PWM_MAX PWM最大值
 * @param PWM_MIN PWM最小值
 */
void PWM_OUT_LIMIT(float *PWM_out, int32_t PWM_MAX, int32_t PWM_MIN)
{
    if (*PWM_out > PWM_MAX)
    {
        *PWM_out = PWM_MAX;
    }
    if (*PWM_out < PWM_MIN)
    {
        *PWM_out = PWM_MIN;
    }
}

/**
 * @brief 积分限幅 -> 用于位置式PID
 * @param INTER_MAX 积分最大值
 * @param INTER_MIN 积分最小值
 */
void INTER_LIMIT(float *error_inter, int32_t INTER_MAX, int32_t INTER_MIN)
{
    if (*error_inter > INTER_MAX)
    {
        *error_inter = INTER_MAX;
    }
    if (*error_inter < INTER_MIN)
    {
        *error_inter = INTER_MIN;
    }
}

int16_t MyAbs(int16_t p) // 绝对值函数
{
    return (p > 0 ? p : (-p));
}

/**
 * @brief 速度环PID -> 增量式
 * @param target_V:目标车速
 * @param cal_V:当前车速
 * @retval PWM
 */

int16_t V_PID_Left(int16_t target_V, int16_t cal_V) // 输入目标值和当前测量值
{
    // static float V_Kp = 18, V_Ki = 0.7, V_kd = 0.3;
    static float V_Kp = 1, V_Ki = 20, V_kd = 0.5;
    static float error, PWM_out; // 误差
    static float last_error = 0, last_last_error = 0.06;
    error = target_V - cal_V;

    PWM_out += V_Kp * (error - last_error) + V_Ki * error + V_kd * (error - 2 * last_error - last_last_error); // PID运算
    last_last_error = last_error;
    last_error = error;
    return PWM_out;
}

/**
 * @brief 速度环PID -> 增量式
 * @param target_V:目标车速
 * @param cal_V:当前车速
 * @retval PWM
 */
int16_t V_PID_Right(int16_t target_V, int16_t cal_V) // 输入目标值和当前测量值
{
    static float V_Kp = 1, V_Ki = 22, V_kd = 0.5;
    static float error, PWM_out; // 误差
    static float last_error = 0, last_last_error = 0;
    error = target_V - cal_V;

    PWM_out += V_Kp * (error - last_error) + V_Ki * error + V_kd * (error - 2 * last_error - last_last_error); // PID运算
    last_last_error = last_error;
    last_error = error;
    return PWM_out;
}

/**
 * @brief 循迹PID -> 位置式
 * @param rho:当前车身角度
 * @param Taget_rho:目标车身角度
 * @retval PWM
 */
int16_t Line_PID(int16_t rho, int16_t Taget_rho)
{
    static float rho_Kp = 3, rho_Kd = 0, rho_ki = 0;
    static float PWM_out, error;
    static float last_error = 0;
    static float error_diffrence;
    static float error_inter = 0;

    error = Taget_rho - rho;              // 误差
    error_inter += error;                 // 累计误差
    error_diffrence = error - last_error; // 本次误差与上次误差之差

    PWM_out = rho_Kp * error + rho_Kd * error_diffrence + rho_ki * error_inter; // PID运算
    last_error = error;
    return -PWM_out+1500;
}

/**
 * @brief 转向PID -> 位置式
 * @param pluse:当前车身角度
 * @param Taget_pluse:目标车身角度差
 * @retval PWM
 */
int16_t Turn_PID(int16_t pluse, int16_t Taget_pluse)
{
    static float rho_Kp = 0, rho_Kd = 0, rho_ki = 0;
    static float PWM_out, error;
    static float last_error = 0;
    static float error_diffrence;
    static float error_inter = 0;

    error = Taget_pluse - pluse;          // 误差
    error_inter += error;                 // 累计误差
    error_diffrence = error - last_error; // 本次误差与上次误差之差

    PWM_out += rho_Kp * error + rho_Kd * error_diffrence + rho_ki * error_inter; // PID运算
    last_error = error;
    return -PWM_out;
}

/**
 * @brief 舵机X轴控制 PID-> 增量式
 * @param Fx:当前Fx坐标值
 * @param Taget_Fx:目标X坐标值  -> 360度舵机
 * @retval PWM -> PE5
 */
int16_t Servo_Fx_PID(int16_t Fx, int16_t Taget_Fx)
{
    static float Fx_Kp = 0.2, Fx_Kd = 0, Fx_ki = 0.1;
    static float error, PWM_out; // 误差
    static float last_error = 0, last_last_error = 0;
    error = Taget_Fx - Fx;

    PWM_out += Fx_Kp * (error - last_error) + Fx_ki * error + Fx_Kd * (error - 2 * last_error - last_last_error); // PID运算
    last_last_error = last_error;
    last_error = error;
    return -PWM_out + 1500;
}

/**
 * @brief 舵机Y轴控制 PID-> 增量式
 * @param Fy:当前Fy坐标值
 * @param Taget_Fy:目标Y坐标值
 * @retval PWM -> PE6
 */
int16_t Servo_Fy_PID(int16_t Fy, int16_t Taget_Fy)
{
    static float Fy_Kp = 0.10, Fy_Kd = 0, Fy_ki = 0.1;
    //static float Fy_Kp = 0, Fy_Kd = 0, Fy_ki = 10;
    // static float Fy_Kp = 0.29, Fy_Kd = 0, Fy_ki = 0.;
    //static float Fy_Kp = 0.1, Fy_Kd = 0, Fy_ki = 0.3;
    static float error, PWM_out; // 误差
    static float last_error = 0, last_last_error = 0;
    error = Taget_Fy - Fy;

    PWM_out += Fy_Kp * (error - last_error) + Fy_ki * error + Fy_Kd * (error - 2 * last_error - last_last_error); // PID运算
    last_last_error = last_error;
    last_error = error;
    return -PWM_out + 1500;
}
