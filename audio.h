/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: Raptor3 Device Driver
*  Description	: audio.h
*  Author		:
*  Date         :
*  Version		: Version 1.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#ifndef _RAPTOR3_AUDIO_H_
#define _RAPTOR3_AUDIO_H_

#include "common.h"

typedef struct _afe_audio_set
{
	unsigned char b0_0x02;
}afe_audio_set;

typedef struct _audio_set
{
	unsigned char ch;
	unsigned char devnum;

	afe_audio_set afe_set;
	unsigned char clk_sel;
	unsigned char bitrate;
	unsigned char aigain1;
	unsigned char aigain2;
	unsigned char aigain3;
	unsigned char aigain4;
	unsigned char migain1;
	unsigned char aigain5;
	unsigned char aigain6;
	unsigned char aigain7;
	unsigned char aigain8;
	unsigned char aogain;
	unsigned char mix_outsel;
	unsigned char mux_setting;
	unsigned char delay_setting;
	unsigned char live_mute;

	unsigned char filter_en;
	unsigned char dc_level;
	unsigned char sys_clk;
}audio_set;

void audio_default_set(audio_set *audio_default_val);

// Add for Raptor4
void nvp6168_audio_default_set(audio_set *audio_default_val);
void audio_in_type_set(int type);
int audio_in_type_get(void);
void audio_sample_rate_set(int sample);
int audio_sample_rate_get(void);
void audio_re_initialize(int devnum);
void audio_set_aoc_format(decoder_dev_ch_info_s *decoder_info);


#endif /* _RAPTOR3_AUDIO_H_ */
