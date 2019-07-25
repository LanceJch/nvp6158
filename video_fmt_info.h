/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: The decoder's video format module
*  Description	: Video Format Information
*  Author		:
*  Date         :
*  Version		: Version 1.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#ifndef __NC_VIVO_FMT_H__
#define __NC_VIVO_FMT_H__

//#include <raptor3_fmt.h>
#include "common.h"


typedef struct _NC_VI_CH_FMT_S
{
	const char *name;

	// for SoC
	int width; // pixel
	int height; // pixel
	NC_FORMAT_FPS format_fps;
	NC_FORMAT_STANDARD format_standard;
	NC_FORMAT_RESOLUTION format_resolution;

	//For Decoder
	unsigned char sw_reset;
	unsigned char each_set;
	unsigned char no_video;
	unsigned char video_format;
	unsigned char sd_ahd_mode;
	unsigned char spl_mode;
	unsigned char pal_cm_off;
	unsigned char s_point;				
	unsigned char fsc_lock_mode;
	unsigned char hue;
	unsigned char comb_mode;
	unsigned char burst_delay;
	unsigned char sync_rs;
	unsigned char h_delay_lsb;
	unsigned char h_mask_on;
	unsigned char h_maks_sel;
	unsigned char mem_rdp;
	unsigned char h_down_scaler;
	unsigned char h_scaler_mode;
	unsigned char ref_base_lsb;
	unsigned char ref_base_msb;
	unsigned char line_mem_mode;
	unsigned char hpll_mask_on;
	unsigned char op_md;
	unsigned char hzoom_on;
	unsigned char zoom_dto;
	unsigned char agc;
	unsigned char comb_th_a;
	unsigned char y_lpf;
	unsigned char sync_en_lsb;
	unsigned char sync_en_msb;
	unsigned char vblk_end_lsb;
	unsigned char vblk_end_msb;

	unsigned char df_ydelay;
	unsigned char db_ydelay;
	unsigned char df_cdelay;
	unsigned char db_cdelay;

	unsigned char clk_adc;
	unsigned char clk_pre;
	unsigned char clk_post;
} NC_VI_CH_FMT_S;


typedef struct _NC_VO_PORT_FMT_S
{

	const char *name;

	//For SoC
	int width;
	int height;

	unsigned char vo_clk;
	unsigned char merge;
	unsigned char mux_mode;
	unsigned char seq_ch01;
	unsigned char seq_ch23;
	unsigned char chid_vin01;
	unsigned char chid_vin23;

	unsigned char devnum;

}NC_VO_PORT_FMT_S;


#endif
