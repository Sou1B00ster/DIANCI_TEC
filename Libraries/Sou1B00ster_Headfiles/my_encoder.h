#ifndef __MY_ENCODER_H
#define __MY_ENCODER_H
#include "headfile.h"
#include "Parameter.h"

/***********��������**********/
void Catch_encoder_value(void);
/***********��������**********/
extern float motorl_encoder_speed,motorr_encoder_speed;
extern int encoder_flag;
extern float motor_total_encoder;

#endif