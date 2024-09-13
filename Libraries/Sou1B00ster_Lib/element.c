#include "element.h"
#include "20602_CTRL.h"

int cir_rec_1=0,cir_rec_2=0,cir_rec_3=0;									
int circ_diuxian_flag=0;													
int left_pre_flag=0,left_jin_flag=0,left_into_flag=0,left_chu_flag=0; 		
int right_pre_flag=0,right_jin_flag=0,right_into_flag=0,right_chu_flag=0;	
float Angle_circ=0;

void circ_recognition(void)
{
	if(ADC_L>cir_rec_1&&ADC_LIL>cir_rec_2&&ADC_LIR>cir_rec_3&&circ_diuxian_flag==0)
	{
		left_pre_flag=encoder_flag=1;
	}
	if(ADC_R>cir_rec_1&&ADC_LIR>cir_rec_2&&ADC_LIL>cir_rec_3&&circ_diuxian_flag==0)
	{
		right_pre_flag=encoder_flag=1;
	}

}
void circ_handler(void)
	 
if(left_pre_flag)
	{

		circ_diuxian_flag=1;
		if(motor_total_encoder>0)
			{	
				cha_a=0; 
				cha_b=cha_c=0;
				encoder_flag=0;
				left_pre_flag=0;
				left_jin_flag=0;
			}
		else	
			{
				cha_a=0;
				cha_b=cha_c=0;
			}
	}
if(right_pre_flag)
  	{ 

		circ_diuxian_flag=0;
		if(motor_total_encoder>0)
			{		
				cha_a=0; 
				cha_b=cha_c=0;
				encoder_flag=0;
				right_pre_flag=0;
				right_jin_flag=0;
			}
	    else	
			{
				cha_a=0;
				cha_b=cha_c=0;
			}
	}
if(left_jin_flag)
	{ 
		Angle_circ += icm20602_gyro_z*0.04 / 65.5;
	    if(Angle_circ>0)
			{			
				left_into_flag=0;
				left_jin_flag=0;
			}
    	else 
			{
				left_setspeed=0;
				right_setspeed=0;
			}
    }
if(right_jin_flag)
	{
		Angle_circ += icm20602_gyro_z*0.04 / 65.5;
	    if(Angle_circ<-0)
			{
				right_into_flag=0;
				right_jin_flag=0;
			}
    	else 
			{
				left_setspeed=0;
				right_setspeed=0;
			 }
	}
if(left_into_flag)
	{
		Angle_circ += icm20602_gyro_z*0.04 / 65.5;
		if(Angle_circ>0)
			{ 
				cha_a=0;
				cha_b=cha_c=0;
				dif_kp_two=0;
				left_chu_flag=encoder_flag=0;
				left_into_flag=0;
			}	 
	}
if(right_into_flag)
	{
		Angle_circ += icm20602_gyro_z*0.04 / 65.5;
		if(Angle_circ<0)
			{ 
				cha_a=0;
				cha_b=cha_c=0;
				dif_kp_two=0;
				right_chu_flag=encoder_flag=0;
				right_into_flag=0;
			}	 
	}
if(left_chu_flag)
	{		 
		if(motor_total_encoder>0)
			{		 
				cha_a=0; 
				cha_b=cha_c=0;		
				dif_kp_two=0;				
			 	circ_diuxian_flag=0;
			    encoder_flag=0;		
			 	left_chu_flag=0;
				Angle_circ=0;			
			}	
	 }
if(right_chu_flag)
	{	
		if(motor_total_encoder>0)
			{ 
				cha_a=0; 
				cha_b=cha_c=0;	 
				dif_kp_two=0;			
				circ_diuxian_flag=0;
				encoder_flag=0;		
				right_chu_flag=0;
				Angle_circ=0;	
			}	
	}
}






int chuxian_flag=0;
int block_Dir=0;
int timepi=0;
int flag_block_detected;
float Angle_block=0;
int flag_block_adjust=0;
int flag_block_back=0;
void block_recognition(void)
{	
	if(dl1b_distance_mm<0&&circ_diuxian_flag==0&&timepi==0)		
		{
			flag_block_detected=chuxian_flag=0; 							
		}	
}
void block_handler_L(void)
{	
	if(flag_block_detected)
		{		
			timepi=1;
			left_setspeed=0;
			right_setspeed=0;
			Angle_block += icm20602_gyro_z*0.04 / 65.5;
	    }
		if(Angle_block>0)
			{
				flag_block_detected = 0;
				flag_block_back = 0;
			}
		if(flag_block_back)
			{
				Angle_block += icm20602_gyro_z*0.04 / 65.5;
				if(Angle_block >-0)
					{
						right_setspeed =0;
						left_setspeed = 0;
					}
				else
					{
						flag_block_adjust = 0;
					}
				if(flag_block_adjust)
					{
						left_setspeed= 0;
						right_setspeed = 0;
					}
			}
    if(Angle_block < 0 && Angle_block > -0 && flag_block_adjust)
		{
		  	chuxian_flag=0;
			flag_block_detected = 0;
			flag_block_back=0;
			flag_block_adjust = 0;
			Angle_block = 0;
		}
}
void block_handler_R(void)
{	
	if(flag_block_detected)
		{			
			timepi=0;
			left_setspeed=0;  
			right_setspeed=0;
			Angle_block += icm20602_gyro_z*0.04 / 65.5;
		}
    if(Angle_block<-0)
		{
			flag_block_detected = 0;
			flag_block_back = 0;
		}
	if(flag_block_back)
		{
			Angle_block += icm20602_gyro_z*0.04 / 65.5;
			if(Angle_block<0)
				{
					right_setspeed =0;
					left_setspeed = 0;
				}
			else
				{
					flag_block_adjust = 0;
				}
		if(flag_block_adjust)
			{
				left_setspeed= 0;
				right_setspeed = 0;
			}
		}
if(Angle_block < 0 && Angle_block > -0 && flag_block_adjust)
    {
//	    	left_setspeed=0;  
//	    	right_setspeed=0;
		chuxian_flag=0;
		flag_block_detected = 0;
		flag_block_back=0;
        flag_block_adjust = 0;
        Angle_block = 0;
    }
}

