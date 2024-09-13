#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "headfile.h"
//#include "Parameter.h"

#define ADC_L 	 AD_value[0]													
#define ADC_MID  AD_value[5]													
#define ADC_R 	 AD_value[3]												
#define ADC_LVER AD_value[1]													
#define ADC_RVER AD_value[2]												
#define ADC_LIL  AD_value[4]													
#define ADC_LIR  AD_value[6]													
#define ADC_NUM 7																
#define SAMP_FRE 10																

#define L_PWM  PWMA_CH1P_P10
#define R_PWM  PWMA_CH3P_P24
#define L_GPIO P1_3
#define R_GPIO P2_6

#define Pluse_left  CTIM0_P34													
#define Pluse_right CTIM3_P04													
#define dir_left P35
#define dir_right P53

#define PI 3.14159f																
#define RAD_TO_ANGLE(rad) ((rad) * 180.0 / PI)									

#define LCD_SWITCH P16															
#define BEEN P52
#define key_enter     P17 														
#define key_return    P51														
#define key_write      P36														
//#define key_up        P51
#define key_add       P37														
#define key_sub       P50														



#endif