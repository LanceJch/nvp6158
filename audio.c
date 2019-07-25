/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: Raptor3 Device Driver
*  Description	: audio.c
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
#include "common.h"
#include "audio.h"
#include "gpio_i2c.h"

extern unsigned int raptor3_i2c_addr[4];
extern unsigned int nvp6158_cnt;

static int g_ai_type = NC_AD_AI;
static int g_aud_sample = NC_AD_SAMPLE_RATE_8000;

void audio_default_set(audio_set *audio_default_val)
{
	/* Audio Default Set ... Device 0 - later you have to consider multi device */
	int i;
	for(i=0;i<nvp6158_cnt;i++)
	{
#if 0
	//海思 主
		audio_default_val->devnum  = i;

		audio_default_val->clk_sel = 0x40;
		audio_default_val->bitrate = 0x00;
		audio_default_val->aigain1 = 0x09;
		audio_default_val->aigain2 = 0x09;
		audio_default_val->aigain3 = 0x09;
		audio_default_val->aigain4 = 0x09;
		audio_default_val->migain1 = 0x09;
		audio_default_val->aigain5 = 0x09;
		audio_default_val->aigain6 = 0x09;
		audio_default_val->aigain7 = 0x09;
		audio_default_val->aigain8 = 0x09;
		audio_default_val->aogain  = 0x08;
		audio_default_val->mix_outsel = 0x00;	
		audio_default_val->mux_setting = 0x09;
		audio_default_val->delay_setting = 0x07;
		audio_default_val->live_mute = 0x00;
		audio_default_val->filter_en = 0x00;
		audio_default_val->dc_level = 0xf0;
		audio_default_val->sys_clk = 0x40;
#else
	//海思 从
		audio_default_val->devnum  = i;

		audio_default_val->clk_sel = 0x40;			// 0x94
		audio_default_val->bitrate = 0x80;			// 0x07
		audio_default_val->aigain1 = 0x04;			// 0x01
		audio_default_val->aigain2 = 0x04;			// 0x02
		audio_default_val->aigain3 = 0x04;			// 0x03
		audio_default_val->aigain4 = 0x04;			// 0x04
		audio_default_val->migain1 = 0x04;			// 0x05
		audio_default_val->aigain5 = 0x04;
		audio_default_val->aigain6 = 0x04;
		audio_default_val->aigain7 = 0x04;
		audio_default_val->aigain8 = 0x04;
		audio_default_val->aogain  = 0x08;			// 0x22
		audio_default_val->mix_outsel = 0x00;		// 0x23
		audio_default_val->mux_setting = 0x09;		// 0x31
		audio_default_val->delay_setting = 0x07;		// 0x47
		audio_default_val->live_mute = 0x00;			// 0x49		x
		audio_default_val->filter_en = 0x00;			// 0x44
		audio_default_val->dc_level = 0xf0;			// 0x32
		audio_default_val->sys_clk = 0x40;			// 0x94
		
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x13, 0x80);		//PB mas

#endif
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0xFF, 0x01);
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x94, audio_default_val->clk_sel);		//RS 6134  	0x50
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x07, audio_default_val->bitrate);		//RS 6134  	0x80
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x01, audio_default_val->aigain1);		//RS 6134  	0x05
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x02, audio_default_val->aigain2);
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x03, audio_default_val->aigain3);
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x04, audio_default_val->aigain4);
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x05, audio_default_val->migain1);

		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x22, audio_default_val->aogain);			//RS 6134  	0x08	
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x23, audio_default_val->mix_outsel);		//RS 6134  	0x19		 Audio playback out
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x31, audio_default_val->mux_setting);	// **
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x47, audio_default_val->delay_setting);	// **
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x49, audio_default_val->live_mute);		//RS 6134  	0x88
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x44, audio_default_val->filter_en);		//RS 6134  	0x11

		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x32, audio_default_val->dc_level);		//RS 6134  	0x20
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x94, audio_default_val->sys_clk);		//RS 6134  	0x50	audio system clk = 74.25MHz

		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x38, 0x18);
		msleep(30);
		gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x38, 0x08);

		/*
		CHIP_STAGE : Selection of chip state for cascade [1:0]
		0 : middle stage		2 : first stage
		1 : last stage		3 : single chip operation
		*/	
		if (i == 0)
		{
			if(nvp6158_cnt == 1)
			{
				gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x06, 0x3b);		//只有1片AD
				printk("NVP6158[%d]:0x%x audio default init ok\n",i,raptor3_i2c_addr[audio_default_val->devnum]);
			}
			else
			{
				gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x06, 0x3a);		//第1片AD
				printk("NVP6158[%d]:0x%x audio default init ok\n",i,raptor3_i2c_addr[audio_default_val->devnum]);
			}
		}
		else if(i == nvp6158_cnt-1)
		{
			gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x06, 0x39);			//最后片AD
			printk("NVP6158[%d]:0x%x audio default init ok\n",i,raptor3_i2c_addr[audio_default_val->devnum]);
		}
		else
		{
			gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x06, 0x38);			//中间片AD
			printk("NVP6158[%d]:0x%x audio default init ok\n",i,raptor3_i2c_addr[audio_default_val->devnum]);
		}
	}
	
}

void nvp6168_audio_default_set(audio_set *audio_default_val)
{
	/* Audio Default Set ... Device 0 - later you have to consider multi device */
	audio_default_val->devnum  = 0x00;

	audio_default_val->clk_sel = 0x00;
	audio_default_val->bitrate = 0x88;
	audio_default_val->aigain1 = 0x09;
	audio_default_val->aigain2 = 0x09;
	audio_default_val->aigain3 = 0x09;
	audio_default_val->aigain4 = 0x09;
	audio_default_val->migain1 = 0x09;
	audio_default_val->aigain5 = 0x09;
	audio_default_val->aigain6 = 0x09;
	audio_default_val->aigain7 = 0x09;
	audio_default_val->aigain8 = 0x09;
	audio_default_val->aogain  = 0x08;
	audio_default_val->mux_setting = 0x0A;
	audio_default_val->delay_setting = 0x01;
	audio_default_val->live_mute = 0x88;
	audio_default_val->filter_en = 0x00;
	audio_default_val->dc_level = 0x00;
	audio_default_val->sys_clk = 0x40;

	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0xFF, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x94, audio_default_val->clk_sel);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x07, audio_default_val->bitrate);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x01, audio_default_val->aigain1);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x02, audio_default_val->aigain2);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x03, audio_default_val->aigain3);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x04, audio_default_val->aigain4);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x05, audio_default_val->migain1);

	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x22, audio_default_val->aogain);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x31, audio_default_val->mux_setting);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x47, audio_default_val->delay_setting);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x49, audio_default_val->live_mute);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x44, audio_default_val->filter_en);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x32, audio_default_val->dc_level);

	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x00, 0x02);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x06, 0x1B);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x46, 0x10);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x48, 0xD0);
	gpio_i2c_write(raptor3_i2c_addr[audio_default_val->devnum], 0x94, audio_default_val->sys_clk);
}

void audio_in_type_set(int type)
{
	if(type < NC_AD_MAX)
	{
		printk("[%s] Change audio input type %d > %d\r\n", __func__, g_ai_type, type);
		g_ai_type = type;
	}
	else
	{
		printk("[%s] Invalid argument %d\r\n", __func__, type);
	}
}

int audio_in_type_get(void)
{
	return g_ai_type;
}

void audio_sample_rate_set(int sample)
{
	if(sample < NC_AD_SAMPLE_RATE_MAX)
	{
		printk("[%s] Change audio sampling rate %d > %d\r\n", __func__, g_aud_sample, sample);
		g_aud_sample = sample;
	}
	else
	{
		printk("[%s] Invalid argument %d\r\n", __func__, sample);
	}
}

int audio_sample_rate_get(void)
{
	return g_aud_sample;
}

void audio_re_initialize(int devnum)
{
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x01);

	// Set audio sampling rate
	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x07, 0x80);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x07, 0x88);
	}
	else
	{
		printk("[%s] Not supported yet [%d] \r\n", __func__, g_aud_sample);
	}

	// Set audio input type
	if(g_ai_type == NC_AD_AOC)
	{
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x00, 0x00);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x31, 0x08);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x46, 0x00);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x58, 0x00);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x62, 0xFF);
	}
	else if(g_ai_type == NC_AD_AI)
	{
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x00, 0x02);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x31, 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x46, 0x10);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x58, 0x02);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x62, 0x00);
	}
}

void set_aoc_720_25p_ex_b(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x11);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0F);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x17);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x0E);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x11);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x1E);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x18);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_720_30p_ex_b(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x12);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0F);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x17);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x0E);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x12);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x1E);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x18);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_720_50p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x28);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x17);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x11);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_720_60p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x28);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x17);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x11);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_1080_25p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x12);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x12);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_1080_30p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x12);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x12);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_3m_25p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x06);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x6A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x06);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x6A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_3m_30p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x06);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x6A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x06);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x6A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_4m_25p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xD4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x17);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xD4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_4m_30p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xD4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x50);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x17);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xD4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_4m_15p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xD4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x11);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xD4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x40);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_5m_12_5p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x07);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xB6);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x07);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xB6);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x40);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x05);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_5m_20p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x07);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xB6);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x64);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x07);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xB6);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xC8);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_5_3m_20p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x07);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x4D);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x07);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0x4D);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xC8);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x0B);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_8m_12_5p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x08);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xC4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x10);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x08);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xC4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x40);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void set_aoc_8m_15p(decoder_dev_ch_info_s *decoder_info)
{
	int ch = decoder_info->ch;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x12);

	if(g_aud_sample == NC_AD_SAMPLE_RATE_8000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x08);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xC4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x0A);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0xA0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x13);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x08);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
	else if(g_aud_sample == NC_AD_SAMPLE_RATE_16000)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01 + (ch*0x40), 0x03);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x02 + (ch*0x40), 0x10);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x18 + (ch*0x40), 0x11);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x04 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x05 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x06 + (ch*0x40), 0x00);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x07 + (ch*0x40), 0x08);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x08 + (ch*0x40), 0xC4);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x09 + (ch*0x40), 0x03);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0A + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0B + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0C + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0D + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0E + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0F + (ch*0x40), 0x40);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + (ch*0x40), 0x04);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x11 + (ch*0x40), 0x14);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x12 + (ch*0x40), 0x01);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x13 + (ch*0x40), 0x40);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x14 + (ch*0x40), 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x15 + (ch*0x40), 0x12);

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x17 + (ch*0x40), 0x00);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x19 + (ch*0x40), 0xA0);
	}
}

void audio_set_aoc_format(decoder_dev_ch_info_s *decoder_info)
{
	switch(decoder_info->fmt_def)
	{
		// 1M
		case AHD20_720P_25P_EX_Btype :
			set_aoc_720_25p_ex_b(decoder_info);
			break;
		case AHD20_720P_30P_EX_Btype :
			set_aoc_720_30p_ex_b(decoder_info);
			break;

		case AHD20_720P_50P :
			set_aoc_720_50p(decoder_info);
		case AHD20_720P_60P :
			set_aoc_720_60p(decoder_info);
			printk("[%s] Not supported yet. [0x%X] \r\n", __func__, decoder_info->fmt_def);
			break;

			// 2M
		case AHD20_1080P_25P :
			set_aoc_1080_25p(decoder_info);
			break;
		case AHD20_1080P_30P :
			set_aoc_1080_30p(decoder_info);
			break;

			// 3M
		case AHD30_3M_25P :
			set_aoc_3m_25p(decoder_info);
		case AHD30_3M_30P :
			set_aoc_3m_30p(decoder_info);
			printk("[%s] Not supported yet. [0x%X] \r\n", __func__, decoder_info->fmt_def);
			break;

			// 4M
		case AHD30_4M_25P :
			set_aoc_4m_25p(decoder_info);
		case AHD30_4M_30P :
			set_aoc_4m_30p(decoder_info);
		case AHD30_4M_15P :
			set_aoc_4m_15p(decoder_info);
			printk("[%s] Not supported yet. [0x%X] \r\n", __func__, decoder_info->fmt_def);
			break;

			// 5M
		case AHD30_5M_12_5P :
			set_aoc_5m_12_5p(decoder_info);
		case AHD30_5M_20P :
			set_aoc_5m_20p(decoder_info);
			printk("[%s] Not supported yet. [0x%X] \r\n", __func__, decoder_info->fmt_def);
			break;

			// 5.3M
		case AHD30_5_3M_20P :
			set_aoc_5_3m_20p(decoder_info);
			printk("[%s] Not supported yet. [0x%X] \r\n", __func__, decoder_info->fmt_def);
			break;

			// 8M
		case AHD30_8M_12_5P :
			set_aoc_8m_12_5p(decoder_info);
		case AHD30_8M_15P :
			set_aoc_8m_15p(decoder_info);
			printk("[%s] Not supported yet. [0x%X] \r\n", __func__, decoder_info->fmt_def);
			break;

		default :
			printk("[%s] Not supported format [0x%X] \r\n", __func__, decoder_info->fmt_def);
			break;
	}
}

