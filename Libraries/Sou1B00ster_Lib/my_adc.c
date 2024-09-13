#include "my_adc.h"

static float AD_value_raw[ADC_NUM][SAMP_FRE]={{0}};					
float AD_value[ADC_NUM]={{0}};

void ADC_ctrl(void)
{
	Catch_ADC();													
	ADC_fliter();													
}
void Catch_ADC(void)
{
int i;
for (i=0;i<SAMP_FRE;i++)
	{
		AD_value_raw[0][i] = adc_once(ADC_P06,ADC_12BIT);			
		AD_value_raw[1][i] = adc_once(ADC_P11,ADC_12BIT);
		AD_value_raw[2][i] = adc_once(ADC_P14,ADC_12BIT);
		AD_value_raw[3][i] = adc_once(ADC_P15,ADC_12BIT);
		AD_value_raw[4][i] = adc_once(ADC_P05,ADC_12BIT);
		AD_value_raw[5][i] = adc_once(ADC_P03,ADC_12BIT);
		AD_value_raw[6][i] = adc_once(ADC_P01,ADC_12BIT);
	}
	}
void ADC_fliter(void)												
{
	
float AD_sum[ADC_NUM]={{0}};
float AD_max[2][ADC_NUM]={{3660,3660,3660,3660,3650,3650,3650},{0,0,0,0,0,0,0}};
float AD_set_max[ADC_NUM]={3660,3660,3660,3660,3650,3650,3650};
int i,num;
for (i=0;i<SAMP_FRE;i++)
	{
		for(num=0;num<ADC_NUM;num++)
		{
			AD_sum[num]+=AD_value_raw[num][i];
			if(AD_value_raw[num][i]<=AD_max[0][num])
			{
				AD_max[0][num]=AD_value_raw[num][i];
			}
			if(AD_value_raw[num][i]>=AD_max[1][num])
			{	
				AD_max[1][num]=AD_value_raw[num][i];
			}
		}
	}
for (num=0;num<ADC_NUM;num++)
	{
		AD_value[num]=(AD_sum[num]-AD_max[0][num]-AD_max[1][num])/8;
		AD_value[num]=(100*AD_value[num]/AD_set_max[num]);
	}
}
