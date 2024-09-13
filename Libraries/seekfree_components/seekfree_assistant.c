/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		seekfree_assistant
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/
 

#include "seekfree_assistant.h"

seekfree_assistant_oscilloscope_struct          seekfree_assistant_oscilloscope_data;                         // 虚拟示波器数据


static fifo_struct      seekfree_assistant_fifo;
static uint8            seekfree_assistant_buffer[SEEKFREE_ASSISTANT_BUFFER_SIZE];              		// 数据存放数组
float                   seekfree_assistant_parameter[SEEKFREE_ASSISTANT_SET_PARAMETR_COUNT] = {0};    	// 保存接收到的参数
vuint8					seekfree_assistant_parameter_update_flag[SEEKFREE_ASSISTANT_SET_PARAMETR_COUNT] = {0};
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     逐飞助手求和函数
// 参数说明     *buffer         需要校验的数据地址
// 参数说明     length          校验长度
// 返回参数     uint8           和值
// 使用示例
//-------------------------------------------------------------------------------------------------------------------
static uint8 seekfree_assistant_sum (uint8 *buffer, uint32 length)
{
    uint8 temp_sum = 0;

    while(length--)
    {
        temp_sum += *buffer++;
    }

    return temp_sum;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     逐飞助手 虚拟示波器发送函数
// 参数说明     *seekfree_assistant_oscilloscope  示波器数据结构体
// 返回参数     void
// 使用示例     seekfree_assistant_oscilloscope_send(&seekfree_assistant_oscilloscope_data);
//-------------------------------------------------------------------------------------------------------------------
void seekfree_assistant_oscilloscope_send (seekfree_assistant_oscilloscope_struct *seekfree_assistant_oscilloscope)
{
    uint8 packet_size;
	uint8 i = 0;
	seekfree_assistant_oscilloscope_struct temp_oscilloscope;
	
	temp_oscilloscope.channel_num = seekfree_assistant_oscilloscope->channel_num & 0x0f;
	
	// 由于大小端不匹配，所以需要交换。
	for(i = 0; i < temp_oscilloscope.channel_num; i++)
	{
		((uint8 *)&temp_oscilloscope.dat[i])[0] = ((uint8 *)&seekfree_assistant_oscilloscope->dat[i])[3];
		((uint8 *)&temp_oscilloscope.dat[i])[1] = ((uint8 *)&seekfree_assistant_oscilloscope->dat[i])[2];
		((uint8 *)&temp_oscilloscope.dat[i])[2] = ((uint8 *)&seekfree_assistant_oscilloscope->dat[i])[1];
		((uint8 *)&temp_oscilloscope.dat[i])[3] = ((uint8 *)&seekfree_assistant_oscilloscope->dat[i])[0];
	}

    // 帧头
    temp_oscilloscope.head         = SEEKFREE_ASSISTANT_SEND_HEAD;

    // 写入包长度信息
    packet_size                     = sizeof(temp_oscilloscope) - (SEEKFREE_ASSISTANT_SET_OSCILLOSCOPE_COUNT - temp_oscilloscope.channel_num) * 4;
    temp_oscilloscope.length       = packet_size;

    // 写入功能字与通道数量
    temp_oscilloscope.channel_num |= SEEKFREE_ASSISTANT_CAMERA_OSCILLOSCOPE;

    // 和校验计算
    temp_oscilloscope.check_sum    = 0;
    temp_oscilloscope.check_sum    = seekfree_assistant_sum((uint8 *)&temp_oscilloscope, packet_size);

    // 数据在调用本函数之前，由用户将需要发送的数据写入temp_oscilloscope.data[]

    seekfree_assistant_transfer((const uint8 *)&temp_oscilloscope, packet_size);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     逐飞助手解析接收到的数据
// 参数说明     void
// 返回参数     void
// 使用示例     函数只需要放到周期运行的PIT中断或者主循环即可
//-------------------------------------------------------------------------------------------------------------------
void seekfree_assistant_data_analysis (void)
{
    uint8  temp_sum;
    uint32 read_length;
    seekfree_assistant_parameter_struct *receive_packet;

    // 这里使用uint32进行定义，目的是为了保证数组四字节对齐
    uint32  temp_buffer[SEEKFREE_ASSISTANT_BUFFER_SIZE / 4];

	uint32 i = 0;
    // 尝试读取数据, 如果不是自定义的传输方式则从接收回调中读取数据
    read_length = seekfree_assistant_receive((uint8 *)temp_buffer, SEEKFREE_ASSISTANT_BUFFER_SIZE);
    if(read_length)
    {
        // 将读取到的数据写入FIFO
        fifo_write_buffer(&seekfree_assistant_fifo, (uint8 *)temp_buffer, read_length);
    }

    while(sizeof(seekfree_assistant_parameter_struct) <= fifo_used(&seekfree_assistant_fifo))
    {
        read_length = sizeof(seekfree_assistant_parameter_struct);
        fifo_read_buffer(&seekfree_assistant_fifo, (uint8 *)temp_buffer, &read_length, FIFO_READ_ONLY);
        if(SEEKFREE_ASSISTANT_RECEIVE_HEAD != ((uint8 *)temp_buffer)[0])
        {
            // 没有帧头则从FIFO中去掉第一个数据
            read_length = 1;
        }
        else
        {
            // 找到帧头
            receive_packet = (seekfree_assistant_parameter_struct *)temp_buffer;
            temp_sum = receive_packet->check_sum;
            receive_packet->check_sum = 0;

            if(temp_sum == seekfree_assistant_sum((uint8 *)temp_buffer, sizeof(seekfree_assistant_parameter_struct)))
            {
                // 和校验成功保存数据
			
				// 由于大小端不匹配，所以需要交换。
				((uint8 *)&seekfree_assistant_parameter[receive_packet->channel - 1])[3] = ((uint8 *)&receive_packet->dat)[0];
				((uint8 *)&seekfree_assistant_parameter[receive_packet->channel - 1])[2] = ((uint8 *)&receive_packet->dat)[1];
				((uint8 *)&seekfree_assistant_parameter[receive_packet->channel - 1])[1] = ((uint8 *)&receive_packet->dat)[2];
				((uint8 *)&seekfree_assistant_parameter[receive_packet->channel - 1])[0] = ((uint8 *)&receive_packet->dat)[3];
				seekfree_assistant_parameter_update_flag[receive_packet->channel - 1] = 1;
            }
            else
            {
                read_length = 1;
            }
        }

        // 丢弃无需使用的数据
        fifo_read_buffer(&seekfree_assistant_fifo, (uint8 *)temp_buffer, &read_length, FIFO_READ_AND_CLEAN);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     逐飞助手 初始化
// 参数说明
// 返回参数     void
// 使用示例
//-------------------------------------------------------------------------------------------------------------------
void seekfree_assistant_init ()
{
    fifo_init(&seekfree_assistant_fifo,  FIFO_DATA_8BIT, seekfree_assistant_buffer, SEEKFREE_ASSISTANT_BUFFER_SIZE);
}


