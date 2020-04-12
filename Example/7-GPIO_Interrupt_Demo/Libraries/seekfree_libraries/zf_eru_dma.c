/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		eru_dma
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 

#include "IfxDma_Dma.h"
#include "IfxScuEru.h"
#include "isr_config.h"
#include "zf_eru_dma.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      eru触发dma初始化
//  @param      dma_ch           	选择DMA通道
//  @param      source_addr         设置源地址
//  @param      destination_addr    设置目的地址
//  @param      eru_pin				设置触发的eru通道
//  @param      trigger				设置触发方式
//  @param      dma_count			设置dma搬移次数
//	@return		void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void eru_dma_init(IfxDma_ChannelId dma_ch, uint8 *source_addr, uint8 *destination_addr, ERU_PIN_enum eru_pin, TRIGGER_enum trigger, uint16 dma_count)
{
	IfxDma_Dma_Channel dmaChn;
	//eru触发DMA通道号   在eru文件中设置eru的优先级，即为触发的通道
	eru_init(eru_pin, trigger);

	IfxDma_Dma_Config        dmaConfig;
    IfxDma_Dma_initModuleConfig(&dmaConfig, &MODULE_DMA);

    IfxDma_Dma               dma;
    IfxDma_Dma_initModule(&dma, &dmaConfig);

    IfxDma_Dma_ChannelConfig cfg;
    IfxDma_Dma_initChannelConfig(&cfg, &dma);

    cfg.transferCount                   = dma_count;
    cfg.requestMode                     = IfxDma_ChannelRequestMode_oneTransferPerRequest;
    cfg.moveSize                        = IfxDma_ChannelMoveSize_8bit;

    cfg.busPriority = IfxDma_ChannelBusPriority_high;

    cfg.sourceAddress      				= (unsigned)(source_addr);
    cfg.sourceAddressCircularRange      = IfxDma_ChannelIncrementCircular_none;
    cfg.sourceCircularBufferEnabled     = TRUE;

    cfg.destinationAddress 				= IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), destination_addr);
    cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
    cfg.operationMode       			= IfxDma_ChannelOperationMode_single;
	cfg.channelId          				= (IfxDma_ChannelId)dma_ch;
	cfg.hardwareRequestEnabled  		= TRUE;
	cfg.channelInterruptEnabled       	= TRUE;

	cfg.channelInterruptPriority      	= ERU_DMA_INT_PRIO;
	cfg.channelInterruptTypeOfService 	= (IfxSrc_Tos)ERU_DMA_INT_SERVICE;

	IfxDma_Dma_initChannel(&dmaChn, &cfg);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      dma停止
//  @param      dma_ch           	选择DMA通道
//	@return		void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void dma_stop(IfxDma_ChannelId dma_ch)
{
	IfxDma_disableChannelTransaction(&MODULE_DMA, dma_ch);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      dma启动
//  @param      dma_ch           	选择DMA通道
//	@return		void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void dma_start(IfxDma_ChannelId dma_ch)
{
	IfxDma_enableChannelTransaction(&MODULE_DMA, dma_ch);
}
