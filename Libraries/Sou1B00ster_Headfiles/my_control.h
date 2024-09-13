#ifndef __MY_CONTROL_H
#define __MY_CONTROL_H
#include "headfile.h"
#include "Parameter.h"
#include "my_encoder.h"
#include "my_control.h"
#include "my_adc.h"
#include "motor_ctrl.h"
#include "element.h"
#include "20602_CTRL.h"
#include "my_sb.h"

/***********变量声明**********/
extern float basicspeed;
extern float left_setspeed,right_setspeed;
extern float dif_kp,dif_kp_two;
extern float dif_kd,dif_kd_two;
extern float cha_a,cha_b,cha_c;
/***********函数声明**********/
void Dif_speed_control(void);
void been_err(void);

#endif