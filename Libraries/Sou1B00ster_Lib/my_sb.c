#include "my_sb.h"

int16 Page=0;
int16 canshu=0;
float cnt=1;
float write_in_num[8];												
int write_in_flag=0;												
																	
void key_action(void)
{	
	if(!key_add)
		{
			lcd_clear(PINK);
			canshu++;
			delay_ms(200);
			if(canshu==6)
				canshu=0;	
			if(canshu<0)
				canshu=0;	
		}
	if(!key_sub)
		{
			lcd_clear(PINK);
			canshu--;
			delay_ms(200);
			if(canshu==7)
				canshu=0;
			if(canshu<0)
				canshu=5;
		}
}

void Key_Menu_main(void)
{
	
switch(Page)																	
{
	case 0:
		Key_Menu_HOME();														
		break;
	case 1:
		Key_Menu_ONE();
		break;
	case 2:
		Key_Menu_TWO();
		break;
	case 3:
		Key_Menu_THREE();
		break;
	case 4:
		Key_Menu_FOUR();
		break;
	case 5:
		Key_Menu_FIVE();
		break;
}
}
void Key_Menu_HOME(void)	
{
	key_action();																
	lcd_showstr(0,1,"ADC");
	lcd_showstr(0,2,"SPEED_PID");
	lcd_showstr(0,3,"DIR_PID");
	lcd_showstr(0,4,"ADJ");
	lcd_showstr(0,5,"DANWEI");
	lcd_showint16(0,6,canshu);
	if(canshu==0)
	{
		lcd_showstr(0,0,"ADJUST--off");
	}
	else
	{
		lcd_showstr(0,0,"ADJUST--on");
		lcd_showstr(100,canshu,"<--");
	}
	if(key_enter==0)
	{
		switch(canshu)
		{
			case 0 :
				Page = 0;	    
				break;
			case 1 :
				Page = 1;
				lcd_clear(PINK);
				break;
			case 2 :
				Page = 2;
				canshu=1;
				lcd_clear(PINK);
				break;
			case 3 :
				Page = 3;
				canshu=0;
				lcd_clear(PINK);
				break;
			case 4 :
				Page = 4;
				canshu=1;
				lcd_clear(PINK);
				break;
			case 5 :
				Page = 5;	
				canshu=0;	
				lcd_clear(PINK);
				break;
		}
	}
}	
void Key_Menu_ONE(void)
{
	 lcd_showstr(0,0,"ADC_L:"),		lcd_showfloat(40,0,ADC_L,5,2);   
	 lcd_showstr(0,1,"ADC_LVER:"),	lcd_showfloat(40,1,ADC_LVER,5,2);   
	 lcd_showstr(0,2,"ADC_RVER:"),	lcd_showfloat(40,2,ADC_RVER,5,2);   
	 lcd_showstr(0,3,"ADC_R:"), 	lcd_showfloat(40,3,ADC_R,5,2);   
	 lcd_showstr(0,4,"ADC_LIL:"),	lcd_showfloat(40,4,ADC_LIL,5,2);   
	 lcd_showstr(0,5,"ADC_MID:"),	lcd_showfloat(40,5,ADC_MID,5,2);   
	 lcd_showstr(0,6,"ADC_LIR:"),	lcd_showfloat(40,6,ADC_LIR,5,2);   
	 if(!key_return)
		{
			Page = 0;
			canshu=0;
			lcd_clear(PINK);
		}		
}	
void Key_Menu_TWO(void)
{
	if(!key_add)
	{
		lcd_clear(PINK);
		canshu++;
		delay_ms(200);
		if(canshu==7)
			canshu=0;	
		if(canshu<0)
			canshu=0;	
	}
	lcd_showstr(0,0,"lekp:");	lcd_showstr(60,0,"108");
	lcd_showstr(0,1,"leki:");	lcd_showstr(60,1,"2.3");
	lcd_showstr(0,2,"lepd:");	lcd_showstr(60,2,"20");
	lcd_showstr(0,3,"rikp:");	lcd_showstr(60,3,"108");
	lcd_showstr(0,4,"riki:");	lcd_showstr(60,4,"2.3");
	lcd_showstr(0,5,"rikd:");	lcd_showstr(60,5,"20");
	if(!key_return)
		{
			Page = 0;
			canshu=0;
			lcd_clear(PINK);
		}	
}	
void Key_Menu_THREE(void)
{
	 if(!key_add)
		{
			lcd_clear(PINK);
			canshu++;
			delay_ms(200);
			if(canshu==3)
				canshu=0;	
		}
	 lcd_showstr(0,0,"dirkp:");    lcd_showfloat(60,0,dif_kp_two,5,2);         
	 lcd_showstr(0,1,"dirkd:");    lcd_showfloat(60,1,dif_kd,5,2);
     lcd_showint16(0,4,canshu);
	 if(!key_return)
	    {
			Page = 0;
			canshu=0;
			lcd_clear(PINK);
	    }	
}	
																		
void Key_Menu_FOUR(void)
{
			
      if(!key_enter)
			{
				lcd_clear(PINK);
				canshu++;
				delay_ms(200);
				if(canshu==9)
					canshu=0;	
				if(canshu<0)
					canshu=0;	
			}
     lcd_showstr(0,0,"dif_kp_two:");  lcd_showfloat(100,0,write_in_num[0],5,2);         
	 lcd_showstr(0,1,"dif_kd:");      lcd_showfloat(100,1,write_in_num[1],5,2);
	 lcd_showstr(0,2,"cir_rec_1:");   lcd_showfloat(100,2,write_in_num[2],5,2);
	 lcd_showstr(0,3,"cir_rec_2:");	  lcd_showfloat(100,3,write_in_num[3],5,2);
	 lcd_showstr(0,4,"cir_rec_3:");	  lcd_showfloat(100,4,write_in_num[4],5,2);
	 lcd_showstr(0,5,"basicspeed:");  lcd_showfloat(100,5,write_in_num[5],5,2);
	 lcd_showstr(0,6,"block_Dir:");	  lcd_showfloat(100,6,write_in_num[6],5,2);
	 lcd_showstr(0,7,"res");			
	 lcd_showstr(140,canshu-1,"<--");
switch(canshu)
{
	case 1: 
	if(!key_add){write_in_num[0]+=0.1;delay_ms(200);} else if(!key_sub){write_in_num[0]-=0.1;delay_ms(200);}break;
	case 2:
	if(!key_add){write_in_num[1]+=0.1;delay_ms(200);} else if(!key_sub){write_in_num[1]-=0.1;delay_ms(200);}break;
	case 3:
	if(!key_add){write_in_num[2]+=1;delay_ms(200);}   else if(!key_sub){write_in_num[2]-=1;delay_ms(200);}break;
	case 4:
	if(!key_add){write_in_num[3]+=1;delay_ms(200);}   else if(!key_sub){write_in_num[3]-=1;delay_ms(200);}break;
	case 5:
	if(!key_add){write_in_num[4]+=1;delay_ms(200);}   else if(!key_sub){write_in_num[4]-=1;delay_ms(200);}break;
	case 6:
	if(!key_add){write_in_num[5]+=5;delay_ms(200);}   else if(!key_sub){write_in_num[5]-=5;delay_ms(200);}break;
	case 7:
	if(!key_add){write_in_num[6]+=1;delay_ms(200);}   else if(!key_sub){write_in_num[6]-=1;delay_ms(200);}break;
	case 8:
	if(!key_add)
		{	
			iap_erase_page(0x50);
			write_in_num[0]=2.34,
			write_in_num[1]=0.7,
			write_in_num[2]=60,
			write_in_num[3]=40,
			write_in_num[4]=63,
			write_in_num[5]=100,
			write_in_num[6]=0;
		}break;
}
	if(!key_write)
	    {
			flash_write(write_in_num,7,2);
//			write_in_flag=1;
			lcd_clear(PINK);
			lcd_showstr(0,0,"write successful");
			delay_ms(2000);
			Page = 0;
			canshu=0;
			lcd_clear(PINK);
			
	    }
	if(!key_return)
	    {
			Page = 0;
			canshu=0;
			lcd_clear(PINK);
	    }	

}

void Key_Menu_FIVE(void)
{
if(!key_add)
	{
		lcd_clear(PINK);
		canshu++;
		delay_ms(200);
		if(canshu==7)
			canshu=0;	
		if(canshu<0)
			canshu=0;	
	}
	lcd_showfloat(0,2,cnt,5,2);
	lcd_showint16(0,5,canshu);
	switch(canshu)
	  {
		case 1:cnt=0.01;break;	
		case 2:cnt=0.1; break;	
		case 3:cnt=1;   break;	
		case 4:cnt=10;  break;	
		case 5:cnt=20;	break;	
		case 6:cnt=50;	break;	
		}	
if(!key_return)
	{	
		Page = 0;
		canshu=0;
		lcd_clear(PINK);
	}	
}


uint8 flash_write_buff[32];													
void flash_write(float*buff, uint32 len,uint32 len_float)					
{
	int i;
	uint32 buff_handled[8];
	uint32 addr=0x00;
	float buff_linshi;
	iap_erase_page(0x50);
	for(i=0;i<=len_float-1;i++)
	{
		buff_linshi=*buff * 100;
		buff_handled[i]=(int)buff_linshi;									
		buff++;
	}
	for(i=len_float;i<=len-1;i++)
	{
		buff_handled[i]=*buff++;											
	}
	for(i=0;i<=len-1;i++)
	{
	flash_write_buff[i*4] = buff_handled[i];        						
	flash_write_buff[i*4+1] = (buff_handled[i] >> 8);
	flash_write_buff[i*4+2] = (buff_handled[i] >> 16);
	flash_write_buff[i*4+3] = (buff_handled[i] >> 24);						
	}
	for(i=0;i<=4*len-1;i++)
	{
		iap_write_bytes(addr+i, &flash_write_buff[i],1);					
	}
}
uint8 flash_read_buff[32];
float flash_read_num[8];													

void flash_read(uint16 len,uint32 len_float)								
{
	int i;
	iap_read_bytes(0x00,flash_read_buff,len*4);
	for(i=0;i<(int)len;i++)
	{
		flash_read_num[i]=(float)(flash_read_buff[i*4] | (flash_read_buff[i*4+1] << 8) | (flash_read_buff[i*4+2] << 16) | (flash_read_buff[i*4+3] << 24));
	}
	for(i=0;i<(int)len_float;i++)
	{
		flash_read_num[i]/=100.00;
	}
}

unsigned long ex_float_int(float value) 									
{
																			
    union
    {
        float float_value;
        unsigned long int_value;
    } ex;

																			
    ex.float_value = value;													
    return ex.int_value;    												
}

float ex_int_float(unsigned long value) 									
{
																			
    union
    {
        float float_value;
        unsigned long int_value;
    } ex_back;

																			
    ex_back.int_value = value; 												
    return ex_back.float_value; 											
}
