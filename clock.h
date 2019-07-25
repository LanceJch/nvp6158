/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: Raptor3 Device Driver
*  Description	: clock.h
*  Author		:
*  Date         :
*  Version		: Version 1.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#ifndef _RAPTOR3_CLOCK_
#define _RAPTOR3_CLOCK_

#include "common.h"

typedef struct _clock{
	unsigned char ch;
	unsigned char devnum;
	unsigned char vlaue;
}clock;

typedef struct _clock_video_output{
    unsigned char port;
    unsigned char devnum;
    unsigned char clk_sel;
}clock_video_output;

typedef struct _clock_set_s{
 unsigned char clk_adc;
 unsigned char clk_pre;
 unsigned char clk_vo;			// Default 1Mux
}clock_set_s;

void adc_clock_set(clock *adc_clk);
void pre_clock_set(clock *dec_clk);

void clock_set(decoder_dev_ch_info_s *dev_ch_info);

void video_output_clock_set(clock_video_output *vout_clk);
void external_fsc_enable(unsigned char enable);

// 170208 Temp TEST Auto Vclk Set
void video_out_auto_vclk_set(clock_video_output *clk_vout);

#endif
