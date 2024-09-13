#include "my_encoder.h"

float motorl_encoder_raw,motorr_encoder_raw;
float motorl_encoder_speed,motorr_encoder_speed;
int  encoder_flag=0;
float motor_total_encoder=0;
void Catch_encoder_value(void)
{  
	
	motorl_encoder_raw=ctimer_count_read(Pluse_left);
	ctimer_count_clean(Pluse_left);
	
	motorr_encoder_raw=ctimer_count_read(Pluse_right);
	ctimer_count_clean(Pluse_right);

	if(!dir_left) 
	{
		motorl_encoder_speed = (-1)*motorl_encoder_raw;
	}
	else
	{
		motorl_encoder_speed = motorl_encoder_raw;
	}
	if(dir_right)
	{
		motorr_encoder_speed = (-1)*motorr_encoder_raw;
	}
	else
	{
		motorr_encoder_speed = motorr_encoder_raw;
	}
}