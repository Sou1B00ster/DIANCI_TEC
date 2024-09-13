#ifndef __ADC_H
#define __ADC_H
#include "headfile.h"
#include "Parameter.h"

/***********函数声明**********/
void ADC_ctrl(void);
void Catch_ADC(void);
void ADC_fliter(void);

/***********变量声明**********/
extern float AD_value[ADC_NUM];
#endif