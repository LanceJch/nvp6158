/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: video_output.c
*  Description	:
*  Author		:
*  Date         :
*  Version		: Version 1.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#include <linux/string.h>
#include <linux/delay.h>
#include "video_output.h"
#include "clock.h"
#include "video_auto_detect.h"
#include "gpio_i2c.h"
#include "common.h"
#include "coax_protocol.h"

extern unsigned int raptor3_i2c_addr[4];
static char g_MergeEn[4];
extern unsigned int VideoLoss[16];
extern int chip_id[4];

extern unsigned char RSch_mode_status[16];

void video_output_colorbar_set( unsigned char devnum )
{
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x00);
	// colorbar off
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x78, 0x88);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x79, 0x88);
	// colorbar on
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x78, 0xab);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x79, 0xcd);

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x68, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x69, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x6a, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x6b, 0x00);

	//  Colorbar on
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x05);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x08);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x06);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x08);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x07);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x08);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x08);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x08);
	// Colorbar off
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x05);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x06);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x07);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x08);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2c, 0x00);

	// moving cursor
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x05);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x6a, 0xb0);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x06);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x6a, 0xb0);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x07);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x6a, 0xb0);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xff, 0x08);
//	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x6a, 0xb0);
}

void video_output_channel_sequence_set(video_output_sequence *vout_seq)
{
	gpio_i2c_write(raptor3_i2c_addr[vout_seq->devnum], 0xff, 0x01);

	#if 0
	printk("[DRV] vout_seq->port = %x\n", vout_seq->port);
	printk("[DRV] vout_seq->ch01 = %x\n", vout_seq->ch01);
	printk("[DRV] vout_seq->ch23 = %x\n", vout_seq->ch23);
	#endif

	gpio_i2c_write(raptor3_i2c_addr[vout_seq->devnum], 0xc0 + (vout_seq->port * 2), vout_seq->ch01);
	gpio_i2c_write(raptor3_i2c_addr[vout_seq->devnum], 0xc1 + (vout_seq->port * 2), vout_seq->ch23);
}

void video_output_channel_sequence_get(video_output_sequence_reg *vout_seq_reg)
{
	gpio_i2c_write(raptor3_i2c_addr[vout_seq_reg->devnum], 0xff, 0x01);

	vout_seq_reg->b1c0 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc0);
	vout_seq_reg->b1c1 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc1);
	vout_seq_reg->b1c2 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc2);
	vout_seq_reg->b1c3 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc3);
	vout_seq_reg->b1c4 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc4);
	vout_seq_reg->b1c5 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc5);
	vout_seq_reg->b1c6 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc6);
	vout_seq_reg->b1c7 = gpio_i2c_read(raptor3_i2c_addr[vout_seq_reg->devnum], 0xc7);
}

void video_output_port_mux_mode_set(video_output_port_mux_mode *vout_port_mux_mode)
{
	unsigned char val;

	#if 0
	printk("[DRV] vout_port_mux_mode->port = %x\n", vout_port_mux_mode->port);
	printk("[DRV] vout_port_mux_mode->mode = %x\n", vout_port_mux_mode->mode);
	printk("[DRV] vout_port_mux_mode->devnum = %x\n", vout_port_mux_mode->devnum);
	#endif

	gpio_i2c_write(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xff, 0x01);
	switch(vout_port_mux_mode->port)
	{
		case PORTA:
					val = gpio_i2c_read(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc8) & 0xf0;
					val |= (vout_port_mux_mode->mode & 0xf);
					gpio_i2c_write(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc8, val);
					break;
		case PORTB:
					val = gpio_i2c_read(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc8) & 0x0f;
					val |= ((vout_port_mux_mode->mode & 0xf) << 4);

					gpio_i2c_write(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc8, val);
					break;
		case PORTC:
					val = gpio_i2c_read(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc9) & 0xf0;
					val |= (vout_port_mux_mode->mode & 0xf);

					gpio_i2c_write(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc9, val);
					break;
		case PORTD:
					val = gpio_i2c_read(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc9) & 0x0f;
					val |= ((vout_port_mux_mode->mode & 0xf) << 4);

					gpio_i2c_write(raptor3_i2c_addr[vout_port_mux_mode->devnum], 0xc9, val);
					break;
	}
}

void video_output_port_format_mode_set( video_output_port_fmt_s *pformat )
{
	unsigned char val_5x69,ch;

	if(strcmp(pformat->name, "CVI_HD_30P_EX") == 0 && VideoLoss[pformat->ch]==0)
	{
		return;	
	}
	gpio_i2c_write(raptor3_i2c_addr[pformat->devnum], 0xff, 1);
	gpio_i2c_write(raptor3_i2c_addr[pformat->devnum], 0xed, pformat->merge & 0xff);

	for(ch=0;ch<4;ch++)
	{
		//if(((pformat->merge>>ch)&0x1) || !((pformat->merge>>ch) & 0x1))
		{
			gpio_i2c_write(raptor3_i2c_addr[pformat->devnum], 0xff, 0x05+ch);
			val_5x69 = gpio_i2c_read(raptor3_i2c_addr[pformat->devnum], 0x69)&0x0F;
			if((pformat->merge>>ch) & 0x1)
				gpio_i2c_write(raptor3_i2c_addr[pformat->devnum], 0x69, 0x10|val_5x69);
			else
				gpio_i2c_write(raptor3_i2c_addr[pformat->devnum], 0x69, 0x00|val_5x69);
		}
	}
}

void video_out_port_enable(video_output_port_enable_s *portenable )
{
	gpio_i2c_write(raptor3_i2c_addr[portenable->devnum], 0xff, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[portenable->devnum], 0xca, portenable->enable & 0xff);
}

void video_output_port_mux_chid_set(video_output_port_mux_chid *vout_chid)
{
	gpio_i2c_write(raptor3_i2c_addr[vout_chid->devnum], 0xFF, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[vout_chid->devnum], 0x55, 0x10);
	gpio_i2c_write(raptor3_i2c_addr[vout_chid->devnum], 0x56, 0x10);
}


//////		nvp6134_set_portmode
void RS_VD_VO_Mode_Set_New( unsigned char ch, unsigned char devnum, int port, video_output_port_fmt_s *pPortFmt,
						  unsigned char SEQ0, unsigned char SEQ1, unsigned char SEQ2, unsigned char SEQ3)
{
	//unsigned char ClockDelay;
	clock_video_output VOutClk;
	video_output_sequence VOutSeq;
	video_output_port_mux_chid VoutChID;
	//video_output_port_mux_mode VOutPortMuxMode;
	video_output_port_enable_s sPortEnable;
	//unsigned char tmp;

	VOutSeq.devnum = devnum;
	VoutChID.devnum = devnum;

	/********************************
	 * Set sequence
     ********************************/
	//VOutSeq.port = port;
	//VOutSeq.ch01= ((SEQ0 & 0x0f) | ((SEQ1 & 0xf)<<4));   // [7:4] Sequence2 or 4, [3:0] Sequence1 or 3
	//VOutSeq.ch23= ((SEQ2 & 0x0f) | ((SEQ3 & 0xf)<<4));  // [7:4] Sequence2 or 4, [3:0] Sequence1 or 3
	//NC_VD_VO_CHN_Sequence_Set(&VOutSeq);
	//video_output_channel_sequence_set(&VOutSeq);		//使用默认值 不需配置

	if( RS__IsOver3MRTVideoFormat( pPortFmt->name ) == 0 )
		g_MergeEn[devnum] |= (0x1 << port);
	else
		g_MergeEn[devnum] &= (~(0x1 << port));

	/********************************
	 * Mux YC merge
	 ********************************/
	pPortFmt->merge = g_MergeEn[devnum];
	pPortFmt->devnum = devnum;
	//printk("\033[1;34m  CH[%d]    g_MergeEn=%d  port=%d  \033[0;39m \n",ch+devnum*4,g_MergeEn[devnum],port);
	video_output_port_format_mode_set(pPortFmt);		// 3MRT 以上拔插卡住!!

	/* Output Port Data Ch Number Selection */
	//VOutPortMuxMode.devnum = devnum;
	//VOutPortMuxMode.port = port;
	//VOutPortMuxMode.mode = 0x08; 	//1MUX:0x0, 2MUX:0x02, 4MUX:0x08, PORTA/C[3:0], PORTB/D[7:4]

	//video_output_port_mux_mode_set(&VOutPortMuxMode);		//使用默认值 不需配置
	//video_output_port_mux_chid_set(&VoutChID);

	/********************************
	 * Video Output Clock and delay
	 ********************************/
	VOutClk.port = port;	// PORT_A, PORTB, PORTC, PORTD
	VOutClk.devnum = devnum;
	VOutClk.clk_sel= pPortFmt->vo_clk;	//[7:4] Port Clock SEL, [3:0] Port Clock Delay
	video_out_auto_vclk_set(&VOutClk);		//时钟设置
	
	/********************************
	 * Output Port CLK Enable
	 ********************************/
	sPortEnable.devnum= devnum;
	//sPortEnable.enable = 0xff;
	#if 0
	//sPortEnable.enable = 0xff;
	//video_out_port_enable(&sPortEnable);		//端口使能
	//#else		//临时解决 接3MP以上枪机绿屏问题
	if(chip_id[sPortEnable.devnum] == RAPTOR3_4PORT_R0_ID)
	{
		//if (strcmp(pPortFmt->name, "CVI_HD_30P_EX") == 0 && VideoLoss[ch]==0)		//no video状态
		//{}
		//else
		//{
			gpio_i2c_write(raptor3_i2c_addr[sPortEnable.devnum],0xff,0x00);
			tmp=gpio_i2c_read(raptor3_i2c_addr[sPortEnable.devnum],0xa8);
			
			sPortEnable.enable = ~tmp;
			video_out_port_enable(&sPortEnable);		//端口使能
		//}
	}
	#endif

}
/*
nvp6158和nvp6158c共用同一函数
portsel上有差异，nvp6158c只能使用1和2，nvp6158有4个port，可以使用0~3。
chip:chip select[0,1,2,3];
portsel: port select->6158c[1,2],6158[0,1,2,3];
portmode: port mode select[1mux,2mux,4mux]
chid:  channel id, 1mux[0,1,2,3], 2mux[0,1], 4mux[0]
*/
/*******************************************************************************
*	Description		: select port
*	Argurments		: chip(chip select[0,1,2,3]),
*					  portsel(port select->6158c[1,2],6158[0,1,2,3];)
*					  portmode(port mode select[1mux,2mux,4mux]),
*					  chid(channel id, 1mux[0,1,2,3], 2mux[0,1], 4mux[0])
*	Return value	: 0
*	Modify			:
*	warning			:
*******************************************************************************/
int nvp6158_set_portmode(const unsigned char chip, const unsigned char portsel, const unsigned char portmode, const unsigned char chid)
{
	unsigned char chipaddr = raptor3_i2c_addr[chip];
	unsigned char tmp=0, tmp1=0, reg1=0, reg2=0;
	
	if((portsel!=1) && (portsel!=2) && (chip_id[chip]==NVP6158C_R0_ID))
	{
		printk("nvp6158C_set_portmode portsel[%d] error!!!\n", portsel);
		//return -1;
	}
	
	switch(portmode)
	{
		case NVP6158_OUTMODE_1MUX_SD:
			/*输出720H或者960H单通道,数据37.125MHz,时钟37.125MHz,单沿采样.*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, (chid<<4)|chid);
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, (chid<<4)|chid);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x86);			
		break;
		case NVP6158_OUTMODE_1MUX_HD:
			/*输出720P或者1280H或者1440H单通道,数据74.25MHz,时钟74.25MHz,单沿采样.*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, (chid<<4)|chid); 
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, (chid<<4)|chid);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x16);   
		break;
		case NVP6158_OUTMODE_1MUX_FHD:
			/*输出720P@5060或者1080P单通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, (chid<<4)|chid);  
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, (chid<<4)|chid);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x58);
			break;
		case NVP6158_OUTMODE_2MUX_SD:
			/*输出720H或者960H 2通道,数据74.25MHz,时钟74.25MHz,单沿采样.*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, chid==0?0x10:0x32);
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, chid==0?0x10:0x32);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x16);
			break;			
		case NVP6158_OUTMODE_2MUX_HD:
			/*输出HD 2通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, chid==0?0x10:0x32);
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, chid==0?0x10:0x32);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x58);			
			break;
		case NVP6158_OUTMODE_4MUX_SD:
			/*输出720H或者960H 4通道,数据148.5MHz,时钟148.5MHz,单沿采样.*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x32);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, 0x10);    
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, 0x32);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x58);  
			break;
		case NVP6158_OUTMODE_4MUX_HD:	
			/*输出720P 4通道,数据297MHz,时钟297MHz,单沿采样.*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x32);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, 0x98);    
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, 0xba);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x58);
			//gpio_i2c_write(chipaddr, 0xCC+portsel, 0x66);  //single up
			break;
		case NVP6158_OUTMODE_2MUX_FHD:	
			/*5M_20P,5M_12P,4M_RT,4M_15P,3M_RT/NRT,FHD,3840H,HDEX 2mux任意混合,数据297MHz,时钟148.5MHz,双沿采样.
			SOC VI端通过丢点，实现3840H->960H, HDEX->720P  */
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			#if 1
			//CHANNEL 1 JUDGE
			tmp  = gpio_i2c_read(chipaddr, 0x81)&0x0F;
			tmp1 = gpio_i2c_read(chipaddr, 0x85)&0x0F;
			if(((tmp == 0x02) || (tmp == 0x03)) && (tmp1 == 0x04))
				reg1 |= 0x08;							//3M_RT, THEN OUTPUT 3M_CIF DATA
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && (tmp1 == 0x00))
				reg1 |= 0x08;							//4M, THEN OUTPUT 4M_CIF DATA
			else if((tmp == 0x01)  && (tmp1 == 0x05))  //ahd 5m20p
				reg1 |= 0x08;
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && ((tmp1 == 0x02) || (tmp1 == 0x03)))  //tvi/cvi 4m rt
				reg1 |= 0x08;
			else if(((tmp == 0x01) || (tmp == 0x02)) && ((tmp1 == 0x08) || (tmp1 == 0x0a)))  //8M
				reg1 |= 0x08;
			else				
				reg1 &= 0xF0;
			//printk("CHANNEL 1 JUDGE===========tmp:0x%x,tmp1:0x%x,reg1:0x%x\n",tmp,tmp1,reg1);
			
			//CHANNEL 2 JUDGE			
			tmp  = gpio_i2c_read(chipaddr, 0x82)&0x0F;
			tmp1 = gpio_i2c_read(chipaddr, 0x86)&0x0F;
			if(((tmp == 0x02) || (tmp == 0x03)) && (tmp1 == 0x04))
				reg1 |= 0x80;
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && (tmp1 == 0x00))
				reg1 |= 0x80;
			else if((tmp == 0x01)  && (tmp1 == 0x05))
				reg1 |= 0x80;
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && ((tmp1 == 0x02) || (tmp1 == 0x03)))  //tvi/cvi 4m rt
				reg1 |= 0x80;
			else if(((tmp == 0x01) || (tmp == 0x02)) && ((tmp1 == 0x08) || (tmp1 == 0x0a)))  //8M
				reg1 |= 0x80;
			else
				reg1 &= 0x0F;
			//printk("CHANNEL 2 JUDGE===========tmp:0x%x,tmp1:0x%x,reg1:0x%x\n",tmp,tmp1,reg1);
			
			//CHANNEL 3 JUDGE
			tmp  = gpio_i2c_read(chipaddr, 0x83)&0x0F;
			tmp1 = gpio_i2c_read(chipaddr, 0x87)&0x0F;
			if(((tmp == 0x02) || (tmp == 0x03)) && (tmp1 == 0x04))
				reg2 |= 0x08;
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && (tmp1 == 0x00))
				reg2 |= 0x08;
			else if((tmp == 0x01)  && (tmp1 == 0x05))
				reg2 |= 0x08;
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && ((tmp1 == 0x02) || (tmp1 == 0x03)))  //tvi/cvi 4m rt
				reg2 |= 0x08;
			else if(((tmp == 0x01) || (tmp == 0x02)) && ((tmp1 == 0x08) || (tmp1 == 0x0a)))  //8M
				reg2 |= 0x08;
			else
				reg2 &= 0xF0;
			//printk("CHANNEL 3 JUDGE===========tmp:0x%x,tmp1:0x%x,reg2:0x%x\n",tmp,tmp1,reg2);
			
			//CHANNEL 4 JUDGE
			tmp  = gpio_i2c_read(chipaddr, 0x84)&0x0F;
			tmp1 = gpio_i2c_read(chipaddr, 0x88)&0x0F;
			if(((tmp == 0x02) || (tmp == 0x03)) && (tmp1 == 0x04))
				reg2 |= 0x80;
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && (tmp1 == 0x00))
				reg2 |= 0x80;
			else if((tmp == 0x01)  && (tmp1 == 0x05))
				reg2 |= 0x80;
			else if(((tmp == 0x0E) || (tmp == 0x0F)) && ((tmp1 == 0x02) || (tmp1 == 0x03)))  //tvi/cvi 4m rt
				reg2 |= 0x80;
			else if(((tmp == 0x01) || (tmp == 0x02)) && ((tmp1 == 0x08) || (tmp1 == 0x0a)))  //ahd 8M
				reg2 |= 0x80;
			else
				reg2 &= 0x0F;
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, chid==0?(0x10|reg1):(0x32|reg2));
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, chid==0?(0x10|reg1):(0x32|reg2));
			#else
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, chid==0?0x10:0x32);
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, chid==0?0x10:0x32);
			#endif
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x56);
			//gpio_i2c_write(chipaddr, 0xCC+portsel, 0x66);  //single up
			//printk("======NVP6158_OUTMODE_2MUX_FHD,chip:%d, portsel:%d,portmode:%d,chid:%d,reg1:0x%x,reg2:0x%x,tmp:0x%x\n",chip,portsel,portmode,chid,reg1,reg2,tmp);
			break;	
		case NVP6158_OUTMODE_4MUX_MIX: 
			/*HD,1920H,FHD-X 4mux任意混合,数据297MHz,时钟148.5MHz,双沿采样
			SOC VI端通过丢点，实现1920H->960H  */
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x32);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, 0x98);    
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, 0xba);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x80:0x08);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x58);  
			//gpio_i2c_write(chipaddr, 0xCC+portsel, 0x66);  //single up
			break;	
		case NVP6158_OUTMODE_2MUX_MIX: 
			/*HD,1920H,FHD-X 2MUX任意混合,数据148.5MHz,时钟148.5MHz,单沿采样	
			SOC VI端通过丢点，实现1920H->960H  */
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, chid==0?0x98:0xba);
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, chid==0?0x98:0xba);
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			tmp |= (portsel%2?0x20:0x02);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x58); 				
			break;	
		case NVP6158_OUTMODE_1MUX_BT1120S:	
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			if(chip_id[chip] == NVP6158C_R0_ID)
			{
				//6158C makes 2 bt656 ports to 1 bt1120 port.  portsel=[1,2] to choose clock.
				gpio_i2c_write(chipaddr, 0xC2, (((chid%4)+0x0C)<<4)|((chid%4)+0x0C));
				gpio_i2c_write(chipaddr, 0xC3, (((chid%4)+0x0C)<<4)|((chid%4)+0x0C));
				gpio_i2c_write(chipaddr, 0xC4, (((chid%4)+0x04)<<4)|((chid%4)+0x04));   
				gpio_i2c_write(chipaddr, 0xC5, (((chid%4)+0x04)<<4)|((chid%4)+0x04));
				gpio_i2c_write(chipaddr, 0xC8, 0x00);
				gpio_i2c_write(chipaddr, 0xC9, 0x00);
				gpio_i2c_write(chipaddr, 0xCC+portsel, 0x06);		//74.25MHz clock
			}
			else
			{
				//6158 makes 4 bt656 ports to 2 bt1120 port.   portsel=[0,1] to choose clock.
				gpio_i2c_write(chipaddr, 0xC0+portsel*4, (((chid%4)+0x0C)<<4)|((chid%4)+0x0C));   
				gpio_i2c_write(chipaddr, 0xC1+portsel*4, (((chid%4)+0x0C)<<4)|((chid%4)+0x0C));
				gpio_i2c_write(chipaddr, 0xC2+portsel*4, (((chid%4)+0x04)<<4)|((chid%4)+0x04));   
				gpio_i2c_write(chipaddr, 0xC3+portsel*4, (((chid%4)+0x04)<<4)|((chid%4)+0x04));
				gpio_i2c_write(chipaddr, 0xC8+(portsel), 0x00);
				gpio_i2c_write(chipaddr, 0xCC+portsel*2, 0x06);		//74.25MHz clock
			}
			break;
		case NVP6158_OUTMODE_1MUX_297MHz:
			/*1MUX数据输出，时钟是297MHZ输出*/
			gpio_i2c_write(chipaddr, 0xFF, 0x00);
			gpio_i2c_write(chipaddr, 0x56, 0x10);
			gpio_i2c_write(chipaddr, 0xFF, 0x01);
			gpio_i2c_write(chipaddr, 0xC0+portsel*2, (chid<<4)|chid);   /* Port selection */
			gpio_i2c_write(chipaddr, 0xC1+portsel*2, (chid<<4)|chid);   /* Port selection */
			tmp = gpio_i2c_read(chipaddr, 0xC8+(portsel/2)) & (portsel%2?0x0F:0xF0);
			gpio_i2c_write(chipaddr, 0xC8+(portsel/2), tmp);
			gpio_i2c_write(chipaddr, 0xCC+portsel, 0x66);
			break;
		default:
			printk("portmode %d not supported yet\n", portmode);
			break;		
  	}
	
	printk("nvp6158(b)_set_portmode portsel %d portmode %d setting\n", portsel, portmode);
	return 0;
}

void nvp6158_acp_RT2NRT(unsigned char ch, unsigned char vfmt)
{
	if(RSch_mode_status[ch] == NVP6134_VI_3M)
	{
		gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x00);
		gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x81+(ch%4), (vfmt==PAL?0x03:0x02));
		acp_isp_write(ch, 0xB101, 0x00);
		printk("\n\n3M@%s change to 3M@NRT\n\n",vfmt==PAL?"PAL":"NTSC");
		msleep(300);
	}
	else if(RSch_mode_status[ch] == NVP6134_VI_4M)
	{
		gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x00);
		gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x81+(ch%4), (vfmt==PAL?0x0F:0x0E));
		acp_isp_write(ch, 0xB101, 0x00);
		printk("\n\n4M@%s change to 4M@NRT\n\n",vfmt==PAL?"PAL":"NTSC");
		msleep(300);
	}
	else if(RSch_mode_status[ch] == NVP6134_VI_5M_20P)
	{
		acp_isp_write(ch, 0xB101, 0x00);
		printk("\n\n5M@%s change to 5M@NRT\n\n",vfmt==PAL?"PAL":"NTSC");
		msleep(300);
	}
	else
	{
		printk("\n\nRT change to NRT not support!\n\n");
	}
}

/*
support AHD 3M/4M/5M non real-time to real-time switch
*/
void nvp6158_acp_NRT2RT(unsigned char ch)
{
	if(	RSch_mode_status[ch] == NVP6134_VI_3M_NRT 	||
	RSch_mode_status[ch] == NVP6134_VI_4M_NRT		||
	RSch_mode_status[ch] == NVP6134_VI_5M_NRT )
	{
		acp_isp_write(ch, 0xB100, 0x00);
		printk("\n\n3M@NR/4M@NR/5M@NR change to 3M/4M/5M\n\n");
		msleep(300);
	}
	else
	{
		printk("\n\nNRT change to RT not support!\n\n");
	}
}

/*
support AHD 3M/4M/5M non real-time to real-time switch
*/
void nvp6158_acp_NTSCorPAL(unsigned char ch, unsigned char vfmt, unsigned char flag)
{
	if(flag == 0)
	{
		if(	RSch_mode_status[ch] == NVP6134_VI_3M_NRT 	||
		RSch_mode_status[ch] == NVP6134_VI_4M_NRT		||
		RSch_mode_status[ch] == NVP6134_VI_5M_NRT ||
		RSch_mode_status[ch] == NVP6134_VI_3M     ||
		RSch_mode_status[ch] == NVP6134_VI_4M     ||
		RSch_mode_status[ch] == NVP6134_VI_5M     )
		{
			acp_isp_write(ch, 0xB102, (vfmt==PAL?0x03:0x02));//0X02/03/04，分别表示30P/25P/15P
			printk("\n\n3M/4M/5M change to 3M/4M/5M(NTSCorPAL)\n\n");
			msleep(300);
		}
		else if( RSch_mode_status[ch] == NVP6134_VI_1080P_2530 )
		{
			acp_isp_write(ch, 0x8219, (vfmt==PAL?0x00:0x01));//0X00/01，分别表示PAL/NTSC
			printk("\n\nNVP6134_VI_1080P_2530 change to (%s)\n\n",vfmt==PAL?"PAL":"NTSC");
			msleep(300);
		}
		else
		{
			printk("\n\nchange to NTSCorPAL not support!\n\n");
			printk("\033[1;32m RSch_mode_status[%d]:%d \033[0;39m \n",ch,RSch_mode_status[ch]);
		}
	}
	else
	{
		if(	RSch_mode_status[ch] == NVP6134_VI_3M_NRT 	||
		RSch_mode_status[ch] == NVP6134_VI_4M_NRT		||
		RSch_mode_status[ch] == NVP6134_VI_5M_NRT )
		{
			acp_isp_write(ch, 0x8219, (vfmt==PAL?0x00:0x01));//0X00/01，分别表示PAL/NTSC
			printk("\n\n3M@NRT/4M@NRT/5M@NRT change to 3M@NRT/4M@NRT/5M@NRT(%s)\n\n",vfmt==PAL?"PAL":"NTSC");
			msleep(300);
		}
		else
		{
			printk("\n\n3M@NRT/4M@NRT/5M@NRT change to NTSCorPAL not support!\n\n");
		}
	}
}

/********************************************************************************
* End of file
********************************************************************************/
