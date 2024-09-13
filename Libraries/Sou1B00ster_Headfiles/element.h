#ifndef __ELEMENT_H
#define __ELEMENT_H
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
extern int cir_rec_1,cir_rec_2,cir_rec_3;
extern int circ_diuxian_flag,chuxian_flag;
extern int left_pre_flag,left_jin_flag,left_into_flag,left_chu_flag; 
extern int right_pre_flag,right_jin_flag,right_into_flag,right_chu_flag;
extern int block_Dir;
extern int timepi;
extern int flag_block_detected;
extern float Angle_block;
extern int flag_block_adjust;

/***********函数声明**********/
void circ_recognition(void);
void circ_handler(void);
void block_recognition(void);//识别
void block_handler_L(void);
void block_handler_R(void);

#endif