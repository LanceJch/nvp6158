/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: video_input_table.c
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
#ifndef _VIDEO_INPUT_TABLE_H_
#define _VIDEO_INPUT_TABLE_H_

video_input_vafe_init_s decoder_afe_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{
		[ AHD20_SD_SH720_NT ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_SD_SH720_PAL ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_SD_H960_NT ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_SD_H960_PAL ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_1080P_15P_EX ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},
		[ AHD20_1080P_12_5P_EX ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,
		},
		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_1080P_30P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},
		[ AHD20_1080P_25P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},
		[ AHD20_720P_60P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_50P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_30P_EX_Btype ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_25P_EX_Btype ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_4M_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass =0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ AHD30_4M_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ AHD30_4M_15P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ AHD30_3M_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_3M_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_3M_18P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_5M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_5M_20P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},

		[ AHD30_5_3M_20P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_6M_18P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_6M_20P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_X_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_X_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_7_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_15P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},

		[ TVI_FHD_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ TVI_FHD_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ TVI_HD_60P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_50P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_3M_18P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_5M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},

		[ TVI_5M_20P ] = {
				.powerdown = 0,
				.gain =  1,
				.spd = 0xD,
				.ctrlreg= 1,
				.ctrlibs= 2,
				.adcspd = 0,
				.clplevel = 2,
				.eq_band = 0,
				.lpf_front_band = 7,
				.clpmode = 0,
				.f_lpf_bypass =0,
				.clproff = 0,
				.b_lpf_bypass = 0,
				.duty = 4,
				.ref_vol = 1,
				.lpf_back_band = 7,
				.clk_sel = 1,
				.eq_gainsel = 0,

		},



		[ TVI_4M_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass =0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ TVI_4M_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,
		},
		[ TVI_4M_15P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_FHD_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_FHD_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_HD_60P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_50P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_4M_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_4M_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_5M_20P ] = {
				.powerdown = 0,
				.gain =  1,
				.spd = 0xD,
				.ctrlreg= 1,
				.ctrlibs= 2,
				.adcspd = 0,
				.clplevel = 2,
				.eq_band = 0,
				.lpf_front_band = 7,
				.clpmode = 0,
				.f_lpf_bypass =0,
				.clproff = 0,
				.b_lpf_bypass = 0,
				.duty = 4,
				.ref_vol = 1,
				.lpf_back_band = 7,
				.clk_sel = 1,
				.eq_gainsel = 0,

		},
		[ CVI_8M_15P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_8M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_8M_15P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_8M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},

};

video_input_color_init_s decoder_color_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{
		[ AHD20_1080P_30P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x86,
			    .black_level = 0x80,
			    .hue = 0,
			    .u_gain = 0,
			    .v_gain = 0,
			    .u_offset = 0xF8,
			    .v_offset = 0xF8,
			    .saturation_a = 0x80,
			    .saturation_b = 0xA8,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 30,
		},
		[ AHD20_1080P_25P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x86,
			    .black_level = 0x80,
			    .hue = 0,
			    .u_gain = 0,
			    .v_gain = 0,
			    .u_offset = 0xF8,
			    .v_offset = 0xF8,
			    .saturation_a = 0x80,
			    .saturation_b = 0xA8,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x30,
		},

		[ AHD20_1080P_15P_EX ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x86,
			    .black_level = 0x80,
			    .hue = 0,
			    .u_gain = 0,
			    .v_gain = 0,
			    .u_offset = 0xF8,
			    .v_offset = 0xF8,
			    .saturation_a = 0x80,
			    .saturation_b = 0xA8,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 30,
		},
		[ AHD20_1080P_12_5P_EX ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x86,
			    .black_level = 0x80,
			    .hue = 0,
			    .u_gain = 0,
			    .v_gain = 0,
			    .u_offset = 0xF8,
			    .v_offset = 0xF8,
			    .saturation_a = 0x80,
			    .saturation_b = 0xA8,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x30,
		},

		[ AHD20_1080P_60P ] = {
				    .new_wpd_sel = 0,
				    .brightnees = 0,
				    .contrast= 0x86,
				    .black_level = 0x80,
				    .hue = 0,
				    .u_gain = 0,
				    .v_gain = 0,
				    .u_offset = 0xF8,
				    .v_offset = 0xF8,
				    .saturation_a = 0x80,
				    .saturation_b = 0xA8,
				    .burst_dec_a = 0x2A,
				    .burst_dec_b = 0,
				    .burst_dec_c = 30,
		},
		[ AHD20_1080P_50P ] = {
				.new_wpd_sel = 0,
				.brightnees = 0,
				.contrast= 0x86,
				.black_level = 0x80,
				.hue = 0,
				.u_gain = 0,
				.v_gain = 0,
				.u_offset = 0xF8,
				.v_offset = 0xF8,
				.saturation_a = 0x80,
				.saturation_b = 0xA8,
				.burst_dec_a = 0x2A,
				.burst_dec_b = 0,
				.burst_dec_c = 0x30,
		},
		[ AHD30_4M_30P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x82,
			    .black_level = 0x80,
			    .hue = 0x1,
			    .u_gain = 0x10,
			    .v_gain = 0x0,
			    .u_offset = 0xFE,
			    .v_offset = 0xFC,
			    .saturation_a = 0x80,
			    .saturation_b = 0xB0,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x40,


		},
		[ AHD30_4M_25P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x82,
			    .black_level = 0x80,
			    .hue = 0x1,
			    .u_gain = 0x10,
			    .v_gain = 0,
			    .u_offset = 0xFE,
			    .v_offset = 0xFC,
			    .saturation_a = 0x80,
			    .saturation_b = 0xB0,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x40,


		},
		[ AHD30_4M_15P ] = {
			    .new_wpd_sel = 0x0,
			    .brightnees = 0x0,
			    .contrast= 0x82,
			    .black_level = 0x80,
			    .hue = 0x1,
			    .u_gain = 0x10,
			    .v_gain = 0,
			    .u_offset = 0xFE,
			    .v_offset = 0xFC,
			    .saturation_a = 0x80,
			    .saturation_b = 0xB0,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x40,
		},

		[ TVI_FHD_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x76,
		.black_level = 0x84,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},

		[ TVI_FHD_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x75,
		.black_level = 0x84,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},

		[ TVI_5M_20P ] = {
			.new_wpd_sel = 0x0,
			.brightnees = 0x0,
			.contrast= 0x75,
			.black_level = 0x87,
			.hue = 0x0a,
			.u_gain = 0x30,
			.v_gain = 0x32,
			.u_offset = 0x02,
			.v_offset = 0xF8,
			.saturation_a = 0x80,
			.saturation_b = 0xC0,
			.burst_dec_a = 0x2A,
			.burst_dec_b = 0,
			.burst_dec_c = 0x30,

		},
		
		[ TVI_8M_15P ] = {
			.new_wpd_sel = 0x00,
			.brightnees = 0x08,
			.contrast= 0x88,
			.black_level = 0x85,
			.hue = 0x05,
			.u_gain = 0x50,
			.v_gain = 0xe0,
			.u_offset = 0xFb,
			.v_offset = 0xFc,
			.saturation_a = 0x80,
			.saturation_b = 0xd0,
			.burst_dec_a = 0x2A,
			.burst_dec_b = 0x00,
			.burst_dec_c = 0x30,
		},

		[ TVI_8M_12_5P ] = {
			.new_wpd_sel = 0x00,
			.brightnees = 0x08,
			.contrast= 0x88,
			.black_level = 0x85,
			.hue = 0x05,
			.u_gain = 0x50,
			.v_gain = 0xe0,
			.u_offset = 0xFb,
			.v_offset = 0xFc,
			.saturation_a = 0x80,
			.saturation_b = 0xd0,
			.burst_dec_a = 0x2A,
			.burst_dec_b = 0x00,
			.burst_dec_c = 0x30,
		},

		[ TVI_4M_30P ] = {
		.new_wpd_sel = 0x0,
		.brightnees = 0x0,
		.contrast= 0x75,
		.black_level = 0x87,
		.hue = 0x0,
		.u_gain = 0x30,
		.v_gain = 0x32,
		.u_offset = 0x02,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xC0,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},

		[ TVI_4M_25P ] = {
		.new_wpd_sel = 0x0,
		.brightnees = 0x0,
		.contrast= 0x75,
		.black_level = 0x87,
		.hue = 0x0,
		.u_gain = 0x30,
		.v_gain = 0x32,
		.u_offset = 0x02,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xC0,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},
		[ TVI_4M_15P ] = {
		.new_wpd_sel = 0x0,
		.brightnees = 0x0,
		.contrast= 0x75,
		.black_level = 0x87,
		.hue = 0x0,
		.u_gain = 0x30,
		.v_gain = 0x32,
		.u_offset = 0x02,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xC0,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},
		[ CVI_FHD_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x98,
		.black_level = 0x86,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xa8,
		.burst_dec_a = 0x2a,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,


		},
		[ CVI_FHD_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x98,
		.black_level = 0x86,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xa8,
		.burst_dec_a = 0x2a,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,


		},
		[ CVI_4M_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x7D,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0x00,
		.v_offset = 0x00,
		.saturation_a = 0x80,
		.saturation_b = 0x98,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0x30,
		.burst_dec_c = 0x30,


		},

		[ CVI_4M_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x7D,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0x00,
		.v_offset = 0x00,
		.saturation_a = 0x80,
		.saturation_b = 0x98,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0x30,
		.burst_dec_c = 0x30,


		},
		[ CVI_5M_20P ] = {
			.new_wpd_sel = 0x0,
			.brightnees = 0x0,
			.contrast= 0x75,
			.black_level = 0x87,
			.hue = 0x0a,
			.u_gain = 0x30,
			.v_gain = 0x32,
			.u_offset = 0x02,
			.v_offset = 0xF8,
			.saturation_a = 0x80,
			.saturation_b = 0xC0,
			.burst_dec_a = 0x2A,
			.burst_dec_b = 0,
			.burst_dec_c = 0x30,

		},
};

video_input_basic_vfmt_init_s decoder_basic_vfmt_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{
		[ NC_VIVO_CH_FORMATDEF_UNKNOWN ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xA,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},
		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		    .video_format = 0xA0,
		    .sd_ahd_mode = 0xE0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		    .video_format = 0xDD,
		    .sd_ahd_mode = 0xF0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},
		[ AHD20_SD_SH720_NT ] = {
		    .video_format = 0xA0,
		    .sd_ahd_mode = 0x0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_SH720_PAL ] = {
		    .video_format = 0xDD,
		    .sd_ahd_mode = 0x10,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},
		[ AHD20_SD_H960_NT ] = {
		    .video_format = 0xA0,
		    .sd_ahd_mode = 0x0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H960_PAL ] = {
		    .video_format = 0xDD,
		    .sd_ahd_mode = 0x10,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H1280_NT ] = {
		    .video_format = 0xA0,
		    .sd_ahd_mode = 0x20,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H1280_PAL ] = {
		    .video_format = 0xDD,
		    .sd_ahd_mode = 0x30,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H1440_NT ] = {
		    .video_format = 0xA0,
		    .sd_ahd_mode = 0x40,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H1440_PAL ] = {
		    .video_format = 0xDD,
		    .sd_ahd_mode = 0x50,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H960_EX_NT ] = {
		    .video_format = 0xA0,
		    .sd_ahd_mode = 0xA0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H960_EX_PAL ] = {
		    .video_format = 0xDD,
		    .sd_ahd_mode = 0xB0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H960_2EX_NT ] = {
		    .video_format = 0xA0,
		    .sd_ahd_mode = 0xC0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_SD_H960_2EX_PAL ] = {
		    .video_format = 0xDD,
		    .sd_ahd_mode = 0xD0,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x1,
		},

		[ AHD20_1080P_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_1080P_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x3,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		
		[ AHD20_1080P_15P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},
		[ AHD20_1080P_12_5P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x3,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_1080P_60P ] = {
			.video_format = 0x0,
			.sd_ahd_mode = 0x2,
			.spl_mode = 0x0,
			.sd_freq_sel = 0x0,
		},

		[ AHD20_1080P_50P ] = {
			.video_format = 0x0,
			.sd_ahd_mode = 0x3,
			.spl_mode = 0x0,
			.sd_freq_sel = 0x0,
		},

		[ AHD20_720P_60P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x4,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_720P_50P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x5,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_720P_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x6,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_720P_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x7,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_720P_30P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xA,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_720P_25P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xB,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_720P_30P_EX_Btype ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xC,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD20_720P_25P_EX_Btype ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xD,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_3M_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0x4,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_3M_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x3,
		    .spl_mode = 0x4,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_3M_18P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x4,
		    .spl_mode = 0x4,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_4M_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xE,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_4M_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xF,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_4M_15P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xA,
		    .spl_mode = 0x4,
		    .sd_freq_sel = 0x0,
		},

	
		[ AHD30_5M_20P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x1,
		    .spl_mode = 0x5,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_5M_12_5P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x0,
		    .spl_mode = 0x5,
		    .sd_freq_sel = 0x0,
		},

	        [ AHD30_8M_X_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xC,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_8M_X_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xD,
		    .spl_mode = 0x0,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_5_3M_20P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x1,
		    .spl_mode = 0x6,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_6M_18P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0x6,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_6M_20P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x3,
		    .spl_mode = 0x6,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_8M_7_5P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x0,
		    .spl_mode = 0x8,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_8M_12_5P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x1,
		    .spl_mode = 0x8,
		    .sd_freq_sel = 0x0,
		},

		[ AHD30_8M_15P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0x8,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_FHD_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_FHD_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x3,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_60P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x4,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_50P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x5,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x6,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x7,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_30P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xA,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_25P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xB,
		    .spl_mode = 0x1,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_B_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x6,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_B_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x7,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_B_30P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xA,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_HD_B_25P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xB,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_3M_18P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x8,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_5M_12_5P  ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x9,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_5M_20P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xE,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},


		[ TVI_4M_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xE,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_4M_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xF,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},
		[ TVI_4M_15P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x9,
		    .spl_mode = 0x3,
		    .sd_freq_sel = 0x0,
		},

		[ TVI_8M_15P ] = {
			.video_format = 0x0,
			.sd_ahd_mode = 0x2,
			.spl_mode = 0xA,
			.sd_freq_sel = 0x0,
		},
		[ TVI_8M_12_5P ] = {
			.video_format = 0x0,
			.sd_ahd_mode = 0x2,
			.spl_mode = 0xA,
			.sd_freq_sel = 0x0,
		},		
		[ CVI_FHD_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_FHD_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x3,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_HD_60P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x4,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_HD_50P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x5,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_HD_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x6,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_HD_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x7,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_HD_30P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xA,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_HD_25P_EX ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xB,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_4M_30P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xE,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_4M_25P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xF,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},
		[ CVI_5M_20P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0xE,
		    .spl_mode = 0x2,
		    .sd_freq_sel = 0x0,
		},
		[ CVI_8M_12_5P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x1,
		    .spl_mode = 0xA,
		    .sd_freq_sel = 0x0,
		},

		[ CVI_8M_15P ] = {
		    .video_format = 0x0,
		    .sd_ahd_mode = 0x2,
		    .spl_mode = 0xA,
		    .sd_freq_sel = 0x0,
		},

};

video_input_basic_chroma_init_s decoder_basic_chroma_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{

		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		    .pal_cm_off = 0x2,
		    .s_point = 0xD0,
		    .fsc_lock_mode = 0xCC,
		    .comb_mode = 0x1,
		},
		[ AHD20_SD_SH720_NT ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_SH720_PAL ] = {
		    .pal_cm_off = 0x2,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xCC,
		    .comb_mode = 0x1,
		},
		[ AHD20_SD_H960_NT ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H960_PAL ] = {
		    .pal_cm_off = 0x2,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xCC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H1280_NT ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H1280_PAL ] = {
		    .pal_cm_off = 0x2,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xCC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H1440_NT ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H1440_PAL ] = {
		    .pal_cm_off = 0x2,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xCC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H960_EX_NT ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H960_EX_PAL ] = {
		    .pal_cm_off = 0x2,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xCC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H960_2EX_NT ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_SD_H960_2EX_PAL ] = {
		    .pal_cm_off = 0x2,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xCC,
		    .comb_mode = 0x1,
		},

		[ AHD20_1080P_30P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_1080P_25P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_1080P_15P_EX ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_1080P_12_5P_EX ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_1080P_60P ] = {
			.pal_cm_off = 0x82,
			.s_point = 0x90,
			.fsc_lock_mode = 0xDC,
			.comb_mode = 0x1,
		},

		[ AHD20_1080P_50P ] = {
			.pal_cm_off = 0x82,
			.s_point = 0x90,
			.fsc_lock_mode = 0xDC,
			.comb_mode = 0x1,
		},

		[ AHD20_720P_60P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_720P_50P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_720P_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_720P_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_720P_30P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_720P_25P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_720P_30P_EX_Btype ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD20_720P_25P_EX_Btype ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_3M_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_3M_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_3M_18P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_4M_30P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_4M_25P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_4M_15P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

                [ AHD30_5M_20P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_5M_12_5P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_8M_X_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_8M_X_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_5_3M_20P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ AHD30_6M_18P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_6M_20P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_8M_7_5P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ AHD30_8M_12_5P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ AHD30_8M_15P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x1,
		},

		[ TVI_FHD_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_FHD_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_60P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_50P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_30P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_25P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_B_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_B_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_B_30P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_HD_B_25P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_3M_18P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_5M_20P ] = {
			.pal_cm_off = 0x82,
			.s_point = 0x90,
			.fsc_lock_mode = 0xDC,
			.comb_mode = 0x5,
		},

		[ TVI_5M_12_5P  ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_4M_30P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ TVI_4M_25P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},
		[ TVI_4M_15P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},
		[ TVI_8M_15P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},
		[ TVI_8M_12_5P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},
		[ CVI_FHD_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_FHD_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_HD_60P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_HD_50P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_HD_30P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_HD_25P ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_HD_30P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_HD_25P_EX ] = {
		    .pal_cm_off = 0x92,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_4M_30P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_4M_25P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},
		[ CVI_5M_20P ] = {
			.pal_cm_off = 0x92,
			.s_point = 0x90,
			.fsc_lock_mode = 0xDC,
			.comb_mode = 0x5,
		},

		[ CVI_8M_12_5P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},

		[ CVI_8M_15P ] = {
		    .pal_cm_off = 0x82,
		    .s_point = 0x90,
		    .fsc_lock_mode = 0xDC,
		    .comb_mode = 0x5,
		},


};


video_input_basic_timing_init_s decoder_basic_timing_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{

		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x7C,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},
		[ AHD20_SD_SH720_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_SH720_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},
		[ AHD20_SD_H960_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1280_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1280_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1440_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1440_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_EX_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_EX_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_2EX_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_2EX_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x7C,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x4,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x88,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x3,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_15P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x7C,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x4,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_12_5P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x88,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x3,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_60P ] = {
			.sync_rs = 0xEE,
			.h_delay_lsb = 0x7C,
			.h_mask_on = 0x10,
			.h_mask_sel = 0x4,
			.mem_rdp = 0x0,
			.v_blk_end_b = 0x0,
			.y_delay = 0x5,
			.fld_inv = 0x0,
			.v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_50P ] = {
			.sync_rs = 0xEE,
			.h_delay_lsb = 0x88,
			.h_mask_on = 0x10,
			.h_mask_sel = 0x3,
			.mem_rdp = 0x0,
			.v_blk_end_b = 0x0,
			.y_delay = 0x5,
			.fld_inv = 0x0,
			.v_blk_end_a = 0x80,
		},


		[ AHD20_720P_60P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_50P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_30P_EX_Btype ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_25P_EX_Btype ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x13,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_3M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x83,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x3,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x3,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_3M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x3,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x3,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_3M_18P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x4,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x4,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_4M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_4M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_4M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x72,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

	        [ AHD30_5M_20P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_5M_12_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x83,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

	        [ AHD30_8M_X_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_X_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_5_3M_20P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_6M_18P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_6M_20P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_7_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_12_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_FHD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_FHD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x88,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_60P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_50P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x24,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x20,
		    .mem_rdp = 0x24,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x70,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_3M_18P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_5M_12_5P  ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x7B,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_5M_20P ] = {
			.sync_rs = 0xEE,
			.h_delay_lsb = 0x80,
			.h_mask_on = 0x00,
			.h_mask_sel = 0x00,
			.mem_rdp = 0x0,
			.v_blk_end_b = 0x0,
			.y_delay = 0x15,
			.fld_inv = 0x0,
			.v_blk_end_a = 0x80,
		},

		[ TVI_4M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x7,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_4M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x7,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_4M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x7,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},
		
		[ CVI_FHD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x4,
		    .mem_rdp = 0x21,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_FHD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x22,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_60P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_50P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x1,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_4M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_4M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},
		[ CVI_5M_20P ] = {
			.sync_rs = 0xEE,
			.h_delay_lsb = 0x80,
			.h_mask_on = 0x00,
			.h_mask_sel = 0x00,
			.mem_rdp = 0x0,
			.v_blk_end_b = 0x0,
			.y_delay = 0x15,
			.fld_inv = 0x0,
			.v_blk_end_a = 0x80,
		},

		[ CVI_8M_12_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_8M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},
		[ TVI_8M_12_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_8M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

};


video_input_basic_hscaler_mode_init_s decoder_basic_hscaler_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{

		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		    .h_down_scaler = 0x10,
		    .h_scaler_mode = 0x10,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},

		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		    .h_down_scaler = 0x10,
		    .h_scaler_mode = 0x10,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},
		[ AHD20_SD_SH720_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_SH720_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},
		[ AHD20_SD_H960_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1280_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1280_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1440_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1440_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_EX_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_EX_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_2EX_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_2EX_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_1080P_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_1080P_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_1080P_15P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_1080P_12_5P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_1080P_60P ] = {
			.h_down_scaler = 0x0,
			.h_scaler_mode = 0x0,
			.ref_base_lsb = 0x0,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ AHD20_1080P_50P ] = {
			.h_down_scaler = 0x0,
			.h_scaler_mode = 0x0,
			.ref_base_lsb = 0x0,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ AHD20_720P_60P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_50P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_30P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_25P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_30P_EX_Btype ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},

		[ AHD20_720P_25P_EX_Btype ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},

		[ AHD30_3M_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_3M_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_3M_18P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_4M_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_4M_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_4M_15P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_5M_20P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_5M_12_5P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

	        [ AHD30_8M_X_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_X_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},
		[ AHD30_5_3M_20P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_6M_18P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_6M_20P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_7_5P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_12_5P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_15P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_FHD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_FHD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_60P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_50P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0xc0,
		    .ref_base_msb = 0x01,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_30P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_25P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_30P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_25P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_3M_18P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_5M_12_5P  ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_5M_20P ] = {
			.h_down_scaler = 0x0,
			.h_scaler_mode = 0x0,
			.ref_base_lsb = 0x0,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ TVI_4M_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_4M_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_4M_15P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},
		
		[ TVI_8M_15P ] = {
			.h_down_scaler = 0x1,
			.h_scaler_mode = 0x9,
			.ref_base_lsb = 0xA8,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ TVI_8M_12_5P ] = {
			.h_down_scaler = 0x1,
			.h_scaler_mode = 0x9,
			.ref_base_lsb = 0xA8,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ CVI_FHD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x39,
		    .ref_base_lsb = 0x78,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_FHD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x49,
		    .ref_base_lsb = 0x4f,
		    .ref_base_msb = 0x2,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_60P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x11,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_50P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x21,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x19,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x29,
		    .ref_base_lsb = 0xc0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_30P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x19,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_25P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x29,
		    .ref_base_lsb = 0xc0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_4M_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x69,
		    .ref_base_lsb = 0xF8,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ CVI_4M_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x79,
		    .ref_base_lsb = 0xC0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},
		[ CVI_5M_20P ] = {
			.h_down_scaler = 0x0,
			.h_scaler_mode = 0x0,
			.ref_base_lsb = 0x0,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},		
		[ CVI_8M_12_5P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x9,
		    .ref_base_lsb = 0x68,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_8M_15P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x9,
		    .ref_base_lsb = 0xA8,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},


};

video_input_basic_hpll_init_s decoder_basic_hpll_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{

		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_SH720_NT ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_SH720_PAL ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H960_NT ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H960_PAL ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H1280_NT ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H1280_PAL ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H1440_NT ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H1440_PAL ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H960_EX_NT ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H960_EX_PAL ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H960_2EX_NT ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_SD_H960_2EX_PAL ] = {
		    .hpll_mask_on = 0x84,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0xB9,
		},
		[ AHD20_1080P_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_1080P_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_1080P_15P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_1080P_12_5P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_1080P_60P ] = {
			.hpll_mask_on = 0xC6,
			.hafc_byp_th_e = 0xF,
			.hafc_byp_th_s = 0xFC,
			.hafc_op_md = 0x39,
		},
		[ AHD20_1080P_50P ] = {
			.hpll_mask_on = 0xC6,
			.hafc_byp_th_e = 0xF,
			.hafc_byp_th_s = 0xFC,
			.hafc_op_md = 0x39,
		},
		[ AHD20_720P_60P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_720P_50P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_720P_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_720P_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_720P_30P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_720P_25P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_720P_30P_EX_Btype ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD20_720P_25P_EX_Btype ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_3M_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_3M_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_3M_18P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_4M_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_4M_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_4M_15P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
	
		[ AHD30_5M_20P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x40 ,
		    .hafc_byp_th_s = 0xff ,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_5M_12_5P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x0F,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},

		[ AHD30_8M_X_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x7,
		    .hafc_byp_th_s = 0x2,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_8M_X_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x7,
		    .hafc_byp_th_s = 0x2,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_5_3M_20P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_6M_18P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x7,
		    .hafc_byp_th_s = 0x40,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_6M_20P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x7,
		    .hafc_byp_th_s = 0xFF,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_8M_7_5P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_8M_12_5P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ AHD30_8M_15P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},

		[ TVI_FHD_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_FHD_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_60P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_50P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_30P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_25P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_B_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_B_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_B_30P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_HD_B_25P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_3M_18P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x0F,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_5M_12_5P  ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0x0F,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},

		[ TVI_5M_20P ] = {
			.hpll_mask_on = 0xC6,
			.hafc_byp_th_e = 0xF,
			.hafc_byp_th_s = 0xFC,
			.hafc_op_md = 0x39,
		},

		[ TVI_4M_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_4M_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_4M_15P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ TVI_8M_15P ] = {
			.hpll_mask_on = 0xC6,
			.hafc_byp_th_e = 0xF,
			.hafc_byp_th_s = 0xFC,
			.hafc_op_md = 0x39,
		},
		[ TVI_8M_12_5P ] = {
			.hpll_mask_on = 0xC6,
			.hafc_byp_th_e = 0xF,
			.hafc_byp_th_s = 0xFC,
			.hafc_op_md = 0x39,
		},
		[ CVI_FHD_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_FHD_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_HD_60P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_HD_50P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_HD_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_HD_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_HD_30P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_HD_25P_EX ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_4M_30P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_4M_25P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_5M_20P ] = {
			.hpll_mask_on = 0xC6,
			.hafc_byp_th_e = 0xF,
			.hafc_byp_th_s = 0xFC,
			.hafc_op_md = 0x39,
		},
		[ CVI_8M_12_5P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},
		[ CVI_8M_15P ] = {
		    .hpll_mask_on = 0xC6,
		    .hafc_byp_th_e = 0xF,
		    .hafc_byp_th_s = 0xFC,
		    .hafc_op_md = 0x39,
		},


};





#endif /* EXTDRV_RAPTOR3_VIDEO_INPUT_TABLE_H_ */
