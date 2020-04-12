/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		eru_dma
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
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
//  @brief      eru����dma��ʼ��
//  @param      dma_ch           	ѡ��DMAͨ��
//  @param      source_addr         ����Դ��ַ
//  @param      destination_addr    ����Ŀ�ĵ�ַ
//  @param      eru_pin				���ô�����eruͨ��
//  @param      trigger				���ô�����ʽ
//  @param      dma_count			����dma���ƴ���
//	@return		void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void eru_dma_init(IfxDma_ChannelId dma_ch, uint8 *source_addr, uint8 *destination_addr, ERU_PIN_enum eru_pin, TRIGGER_enum trigger, uint16 dma_count)
{
	IfxDma_Dma_Channel dmaChn;
	//eru����DMAͨ����   ��eru�ļ�������eru�����ȼ�����Ϊ������ͨ��
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
//  @brief      dmaֹͣ
//  @param      dma_ch           	ѡ��DMAͨ��
//	@return		void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void dma_stop(IfxDma_ChannelId dma_ch)
{
	IfxDma_disableChannelTransaction(&MODULE_DMA, dma_ch);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      dma����
//  @param      dma_ch           	ѡ��DMAͨ��
//	@return		void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void dma_start(IfxDma_ChannelId dma_ch)
{
	IfxDma_enableChannelTransaction(&MODULE_DMA, dma_ch);
}
