/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: video_input.c
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
#ifndef _RAPTOR3_VIDEO_INPUT_
#define _RAPTOR3_VIDEO_INPUT_

#include "common.h"

typedef struct _video_input_format{
	unsigned char ch;
	unsigned char format;
	unsigned char special_mode;
	unsigned char sd_ahd_mode;
}video_input_format;

typedef struct _video_input_chroma{
	unsigned char ch;
	unsigned char pal_cm_off;
	unsigned char s_point;
	unsigned char fsc_lock_mode;
	unsigned char hue;
	unsigned char comb_mode;
	unsigned char burst_delay;
}video_input_chroma;

typedef struct _video_input_h_timing{
	unsigned char ch;
	unsigned char devnum;
	unsigned char sync_rs;
	unsigned char h_delay_lsb;
	unsigned char h_mask_on;
	unsigned char h_mask_sel;
	unsigned char mem_rdp;
}video_input_h_timing;

typedef struct _video_input_h_sclaer{
	unsigned char ch;
	unsigned char h_down_scaler;
	unsigned char h_scaler_mode;
	unsigned char ref_base_lsb;
	unsigned char ref_base_msb;
	unsigned char line_mem_mode;
}video_input_h_scaler;

typedef struct _video_input_chid{
	unsigned char ch01;				//B0       0x55
	unsigned char ch23;				//B0       0x56
}video_input_chid;

typedef struct _video_input_vafe_init_s{
	unsigned char powerdown;		//B0       0x00/1/2/3 [0]
	unsigned char gain;			//B0       0x00/1/2/3 [4]
	unsigned char spd;				//B5/6/7/8 0x00       [5:4]

	unsigned char ctrlreg;			//B5/6/7/8 0x01       [6]
	unsigned char ctrlibs;			//B5/6/7/8 0x01       [5:4]
	unsigned char adcspd;			//B5/6/7/8 0x01       [2]
	unsigned char clplevel;		//B5/6/7/8 0x01       [1:0]


	unsigned char eq_band;			//B5/6/7/8 0x58       [6:4]
	unsigned char lpf_front_band;	//B5/6/7/8 0x58       [1:0]

	unsigned char clpmode;			//B5/6/7/8 0x59       [7]
	unsigned char f_lpf_bypass;	//B5/6/7/8 0x59       [4]
	unsigned char clproff;			//B5/6/7/8 0x59       [3]
	unsigned char b_lpf_bypass;	//B5/6/7/8 0x59       [0]

	unsigned char duty;		   	//B5/6/7/8 0x5B    	  [6:4]
	unsigned char ref_vol;			//B5/6/7/8 0x5B       [1:0]

	unsigned char lpf_back_band;	//B5/6/7/8 0x5C       [6:4]
	unsigned char clk_sel;			//B5/6/7/8 0x5C       [3]
	unsigned char eq_gainsel;		//B5/6/7/8 0x5C       [2:0]

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;
}video_input_vafe_init_s;

typedef struct _video_input_color_init_s{
	unsigned char	brightnees;		//B0		0x0c/0x0d/0x0e/0x0f
	unsigned char	contrast;		//B0 		0x10/0x11/0x12/0x13
	unsigned char	hue;			//B0		0x40/0x41/0x42/0x43
	unsigned char	u_gain;         //B0		0x44/0x45/0x46/0x47
	unsigned char	v_gain;         //B0		0x48/0x49/0x4a/0x4b
	unsigned char	u_offset;       //B0		0x4c/0x4d/0x4e/0x4f
	unsigned char	v_offset;       //B0		0x50/0x51/0x52/0x53
	unsigned char	saturation_a;   //B0		0x3c/0x3d/0x3e/0x3f
	unsigned char	saturation_b;	//B5/6/7/8	0x2b
	unsigned char	black_level;  	 //B5/6/7/8	0x20
	unsigned char	burst_dec_a;	//B5/6/7/8	0x24
	unsigned char	burst_dec_b;    //B5/6/7/8	0x5f
	unsigned char	burst_dec_c;    //B5/6/7/8	0xd1
	unsigned char 	new_wpd_sel;	//B5/6/7/8 	0x75				[0]

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_color_init_s;


typedef struct _video_input_basic_vfmt_init_s{
	unsigned char	video_format;	//B0		0x08/0x09/0x0a/0x0b
	unsigned char	sd_ahd_mode;	//B0 		0x81/0x82/0x83/0x84
	unsigned char	spl_mode;		//B0		0x85/0x86/0x87/0x88
	unsigned char	sd_freq_sel;    //B5/6/7/8	0x69[0]

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_basic_vfmt_init_s;

typedef struct _video_input_basic_chroma_init_s{
	unsigned char	pal_cm_off;		//B0		0x21/0x25/0x29/0x2d
	unsigned char	s_point;		//B5/6/7/8 	0x28
	unsigned char	fsc_lock_mode;	//B5/6/7/8	0x25
	unsigned char	comb_mode;    	//B5/6/7/8	0x90

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_basic_chroma_init_s;

typedef struct _video_input_basic_timing_init_s{
	unsigned char	sync_rs;		//B5/6/7/8	0x47
	unsigned char	h_delay_lsb;	//B0 		0x58/0x59/0x5a/0x5b
	unsigned char	h_mask_on;		//B0		0x89/0x8a/0x8b/0x8c
	unsigned char	h_mask_sel;     //B0		0x8e/0x8f/0x90/0x91
	unsigned char 	mem_rdp;		//B5/6/7/8	0x64
	unsigned char	v_blk_end_b;	//B5/6/7/8	0xA9
	unsigned char	y_delay;		//B0		0xA0/0xA1/0xA2/0xA3
	unsigned char	fld_inv;		//B0		0x54[4]/[5]/[6]/[7]
	unsigned char	v_blk_end_a;	//B0		0x64/0x65/0x66/0x67

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_basic_timing_init_s;

typedef struct _video_input_basic_hscaler_mode_init_s{
	unsigned char	h_down_scaler;	//B9		0x96/0xb6/0xd6/0xf6
	unsigned char	h_scaler_mode;	//B9	 	0x97/0xb7/0xd7/0xf7
	unsigned char	ref_base_lsb;	//B9		0x98/0xb8/0xd8/0xf8
	unsigned char	ref_base_msb;  	//B9		0x99/0xb9/0xd9/0xf9
	unsigned char	line_mem_mode;	//B0		0x34/0x35/0x36/0x37

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_basic_hscaler_mode_init_s;

typedef struct _video_input_basic_hpll_init_s{
	unsigned char	hpll_mask_on;	//B5/6/7/8		0x50
	unsigned char	hafc_byp_th_e;	//B5/6/7/8	 	0xbb
	unsigned char	hafc_byp_th_s;	//B5/6/7/8		0xb7
	unsigned char	hafc_op_md;  	//B5/6/7/8		0xb8

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_basic_hpll_init_s;

void video_input_format_set(decoder_dev_ch_info_s *decoder_info);
void video_input_chroma_set(decoder_dev_ch_info_s *decoder_info);
void video_input_h_timing_set(decoder_dev_ch_info_s *decoder_info);
void video_input_h_scaler_mode_set(decoder_dev_ch_info_s *decoder_info);
void video_input_hpll_set(decoder_dev_ch_info_s *decoder_info);
void video_input_vafe_init(decoder_dev_ch_info_s *decoder_info);

// NEW CODE FORMAT
void video_input_color_set(decoder_dev_ch_info_s *decoder_info);
void video_input_hafc_gain_ctrl(decoder_dev_ch_info_s *decoder_info);
void video_input_contrast_off(decoder_dev_ch_info_s *decoder_info);

// For New Format (TVI 5M 20P ... and more)
void video_input_new_format_set(decoder_dev_ch_info_s *decoder_info);
#endif
/********************************************************************
 *  End of file
 ********************************************************************/
