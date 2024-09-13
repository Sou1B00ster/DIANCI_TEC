#include "init.h"
#include "20602_CTRL.h"

void adc_all_init(void)					
{ 
	adc_init(ADC_P06,ADC_SYSclk_DIV_2);
	adc_init(ADC_P11,ADC_SYSclk_DIV_2);
	adc_init(ADC_P14,ADC_SYSclk_DIV_2);
	adc_init(ADC_P15,ADC_SYSclk_DIV_2);
	adc_init(ADC_P05,ADC_SYSclk_DIV_2);
	adc_init(ADC_P03,ADC_SYSclk_DIV_2);
	adc_init(ADC_P01,ADC_SYSclk_DIV_2);
}	

void Motor_pwm_init(void)				
{
    gpio_mode(L_GPIO,GPO_PP);
	gpio_mode(R_GPIO,GPO_PP);
	pwm_init(L_PWM,15000,0);
	pwm_init(R_PWM,15000,0);
}

void encoder_init(void)					
{
	ctimer_count_init(Pluse_left);
	ctimer_count_init(Pluse_right);
}


int j;
void INIT_ALL(void)						
{
	adc_all_init();
	Motor_pwm_init();
	if(!LCD_SWITCH)
	{
		lcd_init();						
	}
	encoder_init();						
	ICM_Init();  
	dl1b_init();
	iap_init();							
	flash_read(7,2);
	pit_timer_ms(TIM_1,10);
	
	for(j=0;j<7;j++)
	{
		write_in_num[j]=flash_read_num[j];/
	}
	if(write_in_num[0]>=0&&write_in_num[1]>=0&&write_in_num[2]>=0&&write_in_num[3]>=0&&write_in_num[4]>=0&&write_in_num[5]>=0)
	{
			dif_kp_two=write_in_num[0];	 
			dif_kd=write_in_num[1];
			cir_rec_1=write_in_num[2];
			cir_rec_2=write_in_num[3];
			cir_rec_3=write_in_num[4];
			basicspeed=write_in_num[5];
			block_Dir=write_in_num[6];
	}
	else
	{
			write_in_num[0]=dif_kp_two;
			write_in_num[1]=dif_kd;
			write_in_num[2]=cir_rec_1;
			write_in_num[3]=cir_rec_2;
			write_in_num[4]=cir_rec_3;
			write_in_num[5]=basicspeed;
			write_in_num[6]=block_Dir;
	}
}
