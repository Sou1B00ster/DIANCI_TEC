#include "my_control.h"

float DIFF=0;
float basicspeed=0;												
float left_setspeed,right_setspeed;									
float err=0;
float err_last=0;
int   Limit=0;
float dif_kp=0,dif_kp_two=0;
float dif_kd=0,dif_kd_two=0;
float cha_a=0,cha_b=0,cha_c=0;										

void Dif_speed_control(void)										
{
	err_last=err;
	if(ADC_LVER>=ADC_RVER)
	{
		err=Limit*(cha_a*(ADC_L-ADC_R)+cha_b*(ADC_LVER-ADC_RVER))/(cha_a*(ADC_L+ADC_R)+cha_c*(ADC_LVER-ADC_RVER));
	}
    if(ADC_LVER<ADC_RVER)
	{
		err=Limit*(cha_a*(ADC_L-ADC_R)+cha_b*(ADC_LVER-ADC_RVER))/(cha_a*(ADC_L+ADC_R)+cha_c*(ADC_RVER-ADC_LVER)); 
	}
	if (abs(err)<3)													
	{
		err=0;
	}
	DIFF = dif_kp*err + dif_kp_two*abs(err)*err/100 + dif_kd*(err-err_last)+dif_kd_two*icm20602_gyro_z;
		
	if(DIFF>120)
	{	
		DIFF =120;
	}															
	if(DIFF<-120)
	{ 
		DIFF =-120;
	}

	left_setspeed =basicspeed-DIFF;									
	right_setspeed=basicspeed+DIFF;

}

void been_err(void)
{
	if(left_pre_flag||right_pre_flag||left_chu_flag||right_chu_flag||flag_block_detected)
	{
	    BEEN=0;
	}
	else
	{
		BEEN=1;
	}

} 
