#include "motor_ctrl.h"

float Spe_left_kp=0;
float Spe_left_ki=0;
float Spe_left_kd=0;
float Spe_right_kp=0;
float Spe_right_ki=0;
float Spe_right_kd=0;
float Spe_kf=0;											
float motorl_end_value,motorr_end_value;

float increasel_pid (float Target,float Measure)			
{  
	float Err_pid;
	static float Err_pid_sum,Err_pid_last,inc;
	Err_pid = Target - Measure; 							
	Err_pid_sum+=Err_pid;
	if(Err_pid_sum>1000)
		Err_pid_sum =1000;									
	else if(Err_pid_sum<-1000)
		Err_pid_sum=-1000; 
	inc=Spe_kf*Target+Spe_left_kp*Err_pid+Spe_left_ki*Err_pid_sum+Spe_left_kd*(Err_pid-Err_pid_last);
	if(inc>9800)
		inc =9800;											 
	else if(inc<-9800)
		inc=-9800; 
															
	Err_pid_last = Err_pid;
	return inc;
	
}
float increaser_pid (float Target,float Measure)			
{  
 	float Err_pid;
	static float Err_pid_sum,Err_pid_last,inc;
	Err_pid = Target - Measure;
	Err_pid_sum+=Err_pid;	
	if(Err_pid_sum>1000)
		Err_pid_sum =1000;									
	else if(Err_pid_sum<-1000)
		Err_pid_sum=-1000;
	inc=Spe_kf*Target+Spe_right_kp*Err_pid+Spe_right_ki*Err_pid_sum+Spe_right_kd*(Err_pid-Err_pid_last);
	if(inc>9800)
		inc =9800;											
	else if(inc<-9800)
		inc=-9800;
															
	Err_pid_last = Err_pid;
	return inc;
}

void speed_loop_control(void)
{ 
	motorl_end_value=increasel_pid(left_setspeed,motorl_encoder_speed);
	motorr_end_value=increaser_pid(right_setspeed,motorr_encoder_speed);
}	
void motor_duty_control(void)
{
	static int L_Dir_last=0,R_Dir_last=0,L_Dir=0,R_Dir=0;
	if(motorl_end_value >= 0)
	{
		L_Dir=0;
	}
	else 
	{
		L_Dir=1;
	}
	if(motorr_end_value >= 0)
	{
		R_Dir=0;
	}
	else
	{
		R_Dir=1;
	}
 if(L_Dir_last!=L_Dir||R_Dir_last!=R_Dir)
 {	
	  if(L_Dir_last!=L_Dir)
		{
			pwm_duty(L_PWM,0);
		}
		
	  if(R_Dir_last!=R_Dir)
		{
			pwm_duty(R_PWM,0);
		}
		delay_ms(1);
 }
 
	 if(!L_Dir)
	 {
		 P13=0;
		 pwm_duty(L_PWM,motorl_end_value);
	 }
	 else
	 {
		 P13=1;
		 pwm_duty(L_PWM,-motorl_end_value);
	 }

 
	 if(!R_Dir)
	 {
		 P26=0;
		 pwm_duty(R_PWM,motorr_end_value);
	 }
	 else
	 {
		P26=1;
		pwm_duty(R_PWM,-motorr_end_value);
	 }	
 
	 L_Dir_last=L_Dir;
	 R_Dir_last=R_Dir;

}

void chuxian_stop(void)
{
	if(ADC_L<1&&ADC_LVER<1&&ADC_RVER<1&&chuxian_flag==0) 
		motorl_end_value=motorr_end_value=0;					
}
