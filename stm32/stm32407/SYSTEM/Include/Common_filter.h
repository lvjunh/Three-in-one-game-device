#ifndef __Common_filter_H
#define __Common_filter_H
#include "stm32f4xx.h"


#define filter


uint16_t Mean_filtering(void);      // 均值滤波
uint16_t low_pass_filtering(uint16_t value);  // 低通滤波
#define ABS(X)  ((X) > 0 ? (X) : -(X))

typedef struct // 1阶kalman滤波
{
    float x;
    float A;   /* x(n)=A*x(n-1)+u(n), u(n)~N(0,q) */
    float H;   /* z(n)=H*x(n)+w(n),w(n)~N(0,r)   */
    float q;  /* process(predict) noise convariance */
    float r;     /* measure noise convariance */
    float p;  /* estimated error convariance */
    float gain;  

} kalman1_state;

typedef struct // 2阶kalman滤波
{
    float x[2];     /* state: [0]-angle [1]-diffrence of angle, 2x1 */
    float A[2][2];  /* X(n)=A*X(n-1)+U(n),U(n)~N(0,q), 2x2 */
    float H[2];     /* Z(n)=H*X(n)+W(n),W(n)~N(0,r), 1x2   */
    float q[2];     /* process(predict) noise convariance,2x1 [q0,0; 0,q1] */
    float r;        /* measure noise convariance */
    float p[2][2];  /* estimated error convariance,2x2 [p0 p1; p2 p3] */
    float gain[2];  /* 2x1 */

} kalman2_state;

// typedef struct
// {
//     void (*Kalman1_Init)(kalman1_state *state, float init_x, float init_p);
//     float (*Kalman1_filter)(kalman1_state *state, float z_measure);
//     void (*Kalman2_Init)(kalman2_state *state, float *init_x, float (*init_p)[2]);
//     float (*Kalman2_filter)(kalman2_state *state, float z_measure);
//     void (*Kalman_Filter)(float Accel,float Gyro);
//     void (*Yijielvbo)(float angle_m, float gyro_m);   
//     uint16_t (*Mean_filtering)(void);
//     uint16_t (*low_pass_filtering)(uint16_t conf);  
// }Common_filter;

extern void Kalman1_Init(kalman1_state *state, float init_x, float init_p);
extern float Kalman1_filter(kalman1_state *state, float z_measure);
extern void Kalman2_Init(kalman2_state *state, float *init_x, float (*init_p)[2]);
extern float Kalman2_filter(kalman2_state *state, float z_measure);
extern void Kalman_Filter(float Accel,float Gyro);
extern void Yijielvbo(float angle_m, float gyro_m);
extern float angle, angle_dot;

#endif
