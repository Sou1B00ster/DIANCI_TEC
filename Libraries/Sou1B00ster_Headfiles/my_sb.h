#ifndef __MY_SB_H
#define __MY_SB_H
#include "headfile.h"
#include "Parameter.h"
#include "my_encoder.h"
#include "my_control.h"
#include "my_adc.h"
#include "motor_ctrl.h"
#include "element.h"
#include "20602_CTRL.h"


/**************************************变量定义**************************************/
extern float write_in_num[8];
extern float flash_read_num[8];
extern int write_in_flag;

void Key_action(void);
void eeprom_read_back(void);
void Key_Menu_main(void);
void Key_Menu_HOME(void);	
void Key_Menu_ONE(void);
void Key_Menu_TWO(void);
void Key_Menu_THREE(void);
void Key_Menu_FOUR(void);
void Key_Menu_FIVE(void);

void flash_write(float *buff, uint32 len,uint32 len_float);
void flash_read(uint16 len,uint32 len_float);

unsigned long ex_float_int(float value); 
float ex_int_float(unsigned long value); 

#endif