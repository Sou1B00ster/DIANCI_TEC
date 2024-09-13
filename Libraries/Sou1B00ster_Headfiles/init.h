#ifndef _INIT_H_
#define _INIT_H_
#include "headfile.h"
#include "Parameter.h"
#include "my_encoder.h"
#include "my_control.h"
#include "my_adc.h"
#include "motor_ctrl.h"
#include "element.h"
#include "20602_CTRL.h"
#include "my_sb.h"

void adc_all_init(void);
void Motor_pwm_init(void);
void encoder_init(void);
void INIT_ALL(void);


#endif