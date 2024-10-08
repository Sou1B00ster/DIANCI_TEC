/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		exti
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32F12K
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/


#include "zf_exti.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      外部中断初始化
//  @param      NULL            	
//  @return     void
//  Sample usage:               exit_init(INT0_P32,BOTH) //初始化P32 作为外部中断引脚，双边沿触发。
//-------------------------------------------------------------------------------------------------------------------
void exit_init(INTN_enum int_n,INT_MODE_enum mode)
{
	if(INT0_P32 == int_n)
	{		
		IT0 = mode;
		EX0 = 1; 		//使能INT0中断
	}
//  if(INT0_P34 == int_n)
//	{
//		IT0 = mode;
//		EX0 = 1; 		//使能INT0中断
//	} 
	
	if(INT1_P33 == int_n)
	{
		IT1 = mode;
		EX1 = 1; 		//使能INT1中断
	}
//		if(INT1_P04 == int_n)
//	{
//		IT1 = mode;
//		EX1 = 1; 		//使能INT1中断
//	}
	if(INT2_P36 == int_n)
	{
		INTCLKO |= 1<<4;	//使能INT2中断
	}
	
	if(INT3_P37 == int_n)
	{
		INTCLKO |= 1<<5;	//使能INT3中断
	}
	
	if(INT4_P30 == int_n)
	{
		INTCLKO |= 1<<6;	//使能INT4中断
	}

}