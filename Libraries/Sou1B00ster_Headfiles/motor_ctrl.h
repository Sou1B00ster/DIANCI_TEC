#ifndef __MOTOR_CTRL_H
#define __MOTOR_CTRL_H
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
extern float motorl_end_value,motorr_end_value;

/***********函数声明**********/
float increaser_pid (float Target,float Measure);
float increasel_pid (float Target,float Measure);
void speed_loop_control(void);
void motor_duty_control(void);
void chuxian_stop(void);

#endif