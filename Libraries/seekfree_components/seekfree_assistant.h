/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          seekfree_assistant
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                                     备注
* 2023-11-29     大W             first version
********************************************************************************************************************/
#ifndef _seekfree_assistant_h_
#define _seekfree_assistant_h_


#include "headfile.h"

// 定义接收FIFO大小
#define SEEKFREE_ASSISTANT_BUFFER_SIZE             ( 0x80 )

// 定义示波器的最大通道数量
#define SEEKFREE_ASSISTANT_SET_OSCILLOSCOPE_COUNT  ( 0x08 )

// 定义参数调试的最大通道数量
#define SEEKFREE_ASSISTANT_SET_PARAMETR_COUNT      ( 0x08 )

// 定义图像边线最大数量
#define SEEKFREE_ASSISTANT_CAMERA_MAX_BOUNDARY     ( 0x08 )

// 单片机往上位机发送的帧头
#define SEEKFREE_ASSISTANT_SEND_HEAD               ( 0xAA )

// 摄像头类
#define SEEKFREE_ASSISTANT_CAMERA_FUNCTION         ( 0x02 )
#define SEEKFREE_ASSISTANT_CAMERA_DOT_FUNCTION     ( 0x03 )
#define SEEKFREE_ASSISTANT_CAMERA_OSCILLOSCOPE     ( 0x10 )

// 上位机往单片机发送的帧头
#define SEEKFREE_ASSISTANT_RECEIVE_HEAD            ( 0x55 )

// 参数设置类
#define SEEKFREE_ASSISTANT_RECEIVE_SET_PARAMETER   ( 0x20 )


typedef struct
{
    uint8 head;                                     // 帧头
    uint8 channel_num;                              // 高四位为功能字  低四位为通道数量
    uint8 check_sum;                                // 和校验
    uint8 length;                                   // 包长度
    float dat[SEEKFREE_ASSISTANT_SET_OSCILLOSCOPE_COUNT];    // 通道数据
}seekfree_assistant_oscilloscope_struct;


typedef struct
{
    uint8 head;                                     // 帧头
    uint8 function;                                 // 功能字
    uint8 channel;                                  // 通道
    uint8 check_sum;                                // 和校验
    float dat;                                      // 数据
}seekfree_assistant_parameter_struct;


extern seekfree_assistant_oscilloscope_struct               seekfree_assistant_oscilloscope_data;                         // 虚拟示波器数据
extern float                                                seekfree_assistant_parameter[SEEKFREE_ASSISTANT_SET_PARAMETR_COUNT];    // 保存接收到的参数
extern vuint8												seekfree_assistant_parameter_update_flag[SEEKFREE_ASSISTANT_SET_PARAMETR_COUNT];

extern uint32 (*seekfree_assistant_transfer)  	 			(const uint8 *buff, uint32 length);
extern uint32 (*seekfree_assistant_receive)    				(uint8 *buff, uint32 length);

void    seekfree_assistant_oscilloscope_send                (seekfree_assistant_oscilloscope_struct *seekfree_assistant_oscilloscope);

void    seekfree_assistant_data_analysis                    (void);
void    seekfree_assistant_init                             (void);


#endif
