/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,逐飞科技
 * All rights reserved.
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		DL1B
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32F12K
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2021-08-27
 * @note		
 * 接线定义：
 *                   ------------------------------------
 *                   模块管脚            单片机管脚
 *                   SCL                 查看 SEEKFREE_DL1B.h 中 DL1B_SCL_PIN   宏定义
 *                   SDA                 查看 SEEKFREE_DL1B.h 中 DL1B_SDA_PIN   宏定义
 *					 XS					 查看 SEEKFREE_DL1B.h 中 DL1B_XSHUT_PIN 宏定义
 *                   VCC                 5V 电源
 *                   GND                 电源地
 *                   ------------------------------------
********************************************************************************************************************/

#ifndef _ZF_DEVICE_DL1B_H_
#define _ZF_DEVICE_DL1B_H_

#include "common.h"
#include "board.h"

// 需要注意的是 DL1B 最高支持 400KHz 的 IIC 通信速率
// 需要注意的是 DL1B 最高支持 400KHz 的 IIC 通信速率
// 需要注意的是 DL1B 最高支持 400KHz 的 IIC 通信速率

//====================================================软件 IIC 驱动====================================================
#define DL1B_SOFT_IIC_DELAY         ( 0 )                                        // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define DL1B_SCL_PIN             	( P32)                                       // 软件 IIC SCL 引脚 连接 DL1B 的 SCL 引脚
#define DL1B_SDA_PIN             	( P33)                                       // 软件 IIC SDA 引脚 连接 DL1B 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================


#define DL1B_XS_PIN                 ( P07 )

#define DL1B_TIMEOUT_COUNT          ( 1000 )                                    // DL1B 超时计数

//================================================定义 DL1B 内部地址================================================

#define DL1B_DEV_ADDR                                           ( 0x52 >> 1 )   // 0b0101001

#define DL1B_I2C_SLAVE__DEVICE_ADDRESS                          ( 0x0001 )
#define DL1B_GPIO__TIO_HV_STATUS                                ( 0x0031 )
#define DL1B_SYSTEM__INTERRUPT_CLEAR                            ( 0x0086 )
#define DL1B_RESULT__RANGE_STATUS                               ( 0x0089 )
#define DL1B_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0     ( 0x0096 )
#define DL1B_FIRMWARE__SYSTEM_STATUS                            ( 0x00E5 )

//================================================定义 DL1B 内部地址================================================

extern uint8 dl1b_finsh_flag;
extern uint16 dl1b_distance_mm;

void   dl1b_get_distance (void);

void   dl1b_int_handler  (void);
uint8  dl1b_init         (void);

#endif

