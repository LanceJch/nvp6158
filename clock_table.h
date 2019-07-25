/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: Raptor3 Device Driver
*  Description	: clock_table.h
*  Author		:
*  Date         :
*  Version		: Version 1.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#ifndef _CLOCK_TABLE_H_
#define _CLOCK_TABLE_H_

clock_set_s decoder_clk_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{
		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_SD_H960_NT ] = {
		.clk_adc = 0x6,
		.clk_pre = 0xa6,
		.clk_vo  = 0xa0,
	},

	[ AHD20_SD_H960_PAL ] = {
		.clk_adc = 0x6,
		.clk_pre = 0xa6,
		.clk_vo  = 0xa0,
	},

	[ AHD20_SD_H1280_NT ] = {
		.clk_adc = 0x6,
		.clk_pre = 0x06,
		.clk_vo  = 0x00,
	},

	[ AHD20_SD_H1280_PAL ] = {
		.clk_adc = 0x6,
		.clk_pre = 0x06,
		.clk_vo  = 0x00,
	},

	[ AHD20_SD_H1440_NT ] = {
		.clk_adc = 0x6,
		.clk_pre = 0x06,
		.clk_vo  = 0x00,
	},

	[ AHD20_SD_H1440_PAL ] = {
		.clk_adc = 0x6,
		.clk_pre = 0x06,
		.clk_vo  = 0x00,
	},

	[ AHD20_SD_H960_EX_NT ] = {
		.clk_adc = 0x6,
		.clk_pre = 0xa6,
		.clk_vo  = 0x00,
	},

	[ AHD20_SD_H960_EX_PAL ] = {
		.clk_adc = 0x6,
		.clk_pre = 0xa6,
		.clk_vo  = 0x00,
	},

	[ AHD20_SD_H960_2EX_NT ] = {
		.clk_adc = 0x6,
		.clk_pre = 0x46,
		.clk_vo  = 0x58,
	},

	[ AHD20_SD_H960_2EX_PAL ] = {
		.clk_adc = 0x6,
		.clk_pre = 0x46,
		.clk_vo  = 0x58,
	},

	[ AHD20_1080P_30P ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_1080P_25P ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_720P_60P ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_720P_50P ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_720P_30P ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x00,
	},

	[ AHD20_720P_25P ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x00,
	},

	[ AHD20_720P_30P_EX ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_720P_25P_EX ] = {
		.clk_adc = 0x0,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_720P_30P_EX_Btype ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD20_720P_25P_EX_Btype ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD30_3M_30P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo  = 0x58,
	},

	[ AHD30_3M_25P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo  = 0x58,
	},

	[ AHD30_3M_18P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo  = 0x58,
	},

	[ AHD30_4M_30P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo  = 0x58,
	},

	[ AHD30_4M_25P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo  = 0x58,
	},

	[ AHD30_4M_15P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x58,
	},


	[ AHD30_5M_20P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ AHD30_5M_12_5P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x58,
	},

	[ AHD30_5_3M_20P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ AHD30_6M_18P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ AHD30_6M_20P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ AHD30_8M_X_30P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ AHD30_8M_X_25P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ AHD30_8M_7_5P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x58,
	},

	[ AHD30_8M_12_5P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ AHD30_8M_15P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ TVI_FHD_30P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ TVI_FHD_25P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ TVI_HD_60P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ TVI_HD_50P ] = {
		.clk_adc = 0x4,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ TVI_HD_30P ] = {
		.clk_adc = 0x05,
		.clk_pre = 0x04,
		.clk_vo = 0x00,
	},

	[ TVI_HD_25P ] = {
		.clk_adc = 0x05,
		.clk_pre = 0x04,
		.clk_vo = 0x00,
	},

	[ TVI_HD_30P_EX ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ TVI_HD_25P_EX ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ TVI_HD_B_30P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x00,

	},

	[ TVI_HD_B_25P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x00,

	},

	[ TVI_HD_B_30P_EX ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x58,

	},

	[ TVI_HD_B_25P_EX ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x58,

	},

	[ TVI_3M_18P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ TVI_5M_12_5P  ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ TVI_4M_30P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ TVI_4M_25P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ TVI_4M_15P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ CVI_FHD_30P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ CVI_FHD_25P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ CVI_HD_60P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ CVI_HD_50P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ CVI_HD_30P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x00,

	},

	[ CVI_HD_25P ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x00,

	},

	[ CVI_HD_30P_EX ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x58,

	},

	[ CVI_HD_25P_EX ] = {
		.clk_adc = 0x2,
		.clk_pre = 0x40,
		.clk_vo = 0x58,

	},

	[ CVI_4M_30P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,
	},

	[ CVI_4M_25P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ CVI_8M_12_5P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},

	[ CVI_8M_15P ] = {
		.clk_adc = 0x5,
		.clk_pre = 0x44,
		.clk_vo = 0x58,

	},
};

#endif /* VIDEO_DECODER_RAPTOR3_DRV_CLOCK_TABLE_H_ */
