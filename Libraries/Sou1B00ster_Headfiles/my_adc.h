#ifndef __ADC_H
#define __ADC_H
#include "headfile.h"
#include "Parameter.h"

/***********��������**********/
void ADC_ctrl(void);
void Catch_ADC(void);
void ADC_fliter(void);

/***********��������**********/
extern float AD_value[ADC_NUM];
#endif