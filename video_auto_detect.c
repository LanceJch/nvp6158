/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: video_auto_detect.c
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
#include <asm/delay.h>
#include <linux/timer.h>
#include <linux/delay.h>

#include "common.h"
#include "video_auto_detect.h"
#include "RSAD.h"
#include "video_eq.h"
#include "gpio_i2c.h"
#include "video_fmt_info.h"

#define MAX_DEBOUNCE_CNT	  5

#define ACC_GAIN_NORMAL 0
#define ACC_GAIN_DEBUG  1

extern unsigned int raptor3_i2c_addr[4];
unsigned char videofmt_vfc[16]={[0 ... 15]=NC_VIVO_CH_FORMATDEF_UNKNOWN};
extern NC_VI_CH_FMT_S *RS_HI_VI_Get_ChannelFormat( NC_VIVO_CH_FORMATDEF def );
extern int RS_NoVIdeoSetFormat( unsigned char ch, unsigned char mode_status);

extern unsigned char app_curvideofmt[16];
//static int CVI_720P30[16]={0,};

typedef enum _RS_VIDEO_ONOFF
{
	VIDEO_LOSS_ON = 0,
	VIDEO_LOSS_OFF = 1,

} RS_VIDEO_ONOFF;

extern int chip_id[4];
extern rsad_info info;
extern char vdec;

static unsigned int pre_val_1;
static unsigned int pre_val_2;

NC_VIVO_CH_FORMATDEF arrVfcType[0x100] = {
	/*  0x00 */	AHD20_SD_H960_2EX_Btype_NT,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x10 */ 	AHD20_SD_H960_2EX_Btype_PAL,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x20 */	AHD20_720P_30P_EX_Btype, AHD20_720P_25P_EX_Btype, AHD20_720P_60P, AHD20_720P_50P,0,
	/*  0x25 */ 	TVI_HD_30P_EX, TVI_HD_25P_EX, TVI_HD_60P, TVI_HD_50P, TVI_HD_B_30P_EX, TVI_HD_B_25P_EX,
	/*  0x2B */	CVI_HD_30P_EX, CVI_HD_25P_EX, CVI_HD_60P, CVI_HD_50P,0,
	/*  0x30 */	AHD20_1080P_30P, AHD20_1080P_25P, 0,TVI_FHD_30P, TVI_FHD_25P,CVI_FHD_30P, CVI_FHD_25P, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x40 */	AHD30_3M_30P, AHD30_3M_25P, AHD30_3M_18P, 0,TVI_3M_18P, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TVI_4M_15P,
	/*  0x50 */	AHD30_4M_30P, AHD30_4M_25P, AHD30_4M_15P, 0,CVI_4M_30P, CVI_4M_25P, 0,TVI_4M_30P, TVI_4M_25P, TVI_4M_15P, 0, 0, 0, 0, 0, 0,
	/*  0x60 */	AHD30_8M_X_30P, AHD30_8M_X_25P, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x70 */	AHD30_5M_20P, AHD30_5M_12_5P, AHD30_5_3M_20P, TVI_5M_12_5P, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x80 */	AHD30_8M_15P, AHD30_8M_7_5P, AHD30_8M_12_5P, CVI_8M_15P, CVI_8M_12_5P, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x90 */	AHD30_6M_18P, AHD30_6M_20P, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0xA0 */
};
NC_VIVO_CH_FORMATDEF arrVfcType_raptor4[0x100] = {
	/*  0x00 */	AHD20_SD_H960_2EX_Btype_NT,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x10 */ AHD20_SD_H960_2EX_Btype_PAL,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x20 */	AHD20_720P_30P_EX_Btype, AHD20_720P_25P_EX_Btype, AHD20_720P_60P, AHD20_720P_50P,
				0,
	/*  0x25 */ TVI_HD_30P_EX, TVI_HD_25P_EX, TVI_HD_60P, TVI_HD_50P, TVI_HD_B_30P_EX, TVI_HD_B_25P_EX,
	/*  0x2B */	CVI_HD_30P_EX, CVI_HD_25P_EX, CVI_HD_60P, CVI_HD_50P,
				0,
	/*  0x30 */	AHD20_1080P_30P, AHD20_1080P_25P,
				0,
	/*	0x33 */ TVI_FHD_30P, TVI_FHD_25P,
	/*  0x35 */	CVI_FHD_30P, CVI_FHD_25P,
				0,
	/*  0x38 */ AHD20_1080P_60P, AHD20_1080P_50P,
	/*  0x3A */ TVI_FHD_60P, TVI_FHD_50P,
	/*  0x3C */ AHD20_1080P_15P, AHD20_1080P_12_5P,
				0, 0,
	/*  0x40 */	AHD30_3M_30P, AHD30_3M_25P, AHD30_3M_18P,
				0,
	/*  0x44 */ TVI_3M_18P,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x50 */	AHD30_4M_30P, AHD30_4M_25P, AHD30_4M_15P,
				0,
	/*  0x54 */	CVI_4M_30P, CVI_4M_25P,
				0,
	/*  0x57 */ TVI_4M_30P, TVI_4M_25P, TVI_4M_15P,
				0, 0, 0, 0, 0, 0,
	/*  0x60 */	AHD30_8M_X_30P, AHD30_8M_X_25P, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x70 */ AHD30_5M_20P, AHD30_5M_12_5P, AHD30_5_3M_20P,
	/*  0x73 */ TVI_5M_12_5P, TVI_5M_20P,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x80 */	AHD30_8M_15P, AHD30_8M_7_5P, AHD30_8M_12_5P, CVI_8M_15P, CVI_8M_12_5P, TVI_8M_15P, TVI_8M_12_5P,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x90 */	AHD30_6M_18P, AHD30_6M_20P,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0xA0 */ AHD20_960P_30P, AHD20_960P_25P, AHD20_960P_60P, AHD20_960P_50P,
	/*  0xA4 */ TVI_960P_30P, TVI_960P_25P, TVI_960P_60P, TVI_960P_50P
};

unsigned char *arrVfcName_raptor4[0x100] = {
	/*  0x00 */	"NTSC",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x10 */ "PAL",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x20 */	"AHD 720P 30P", "AHD 720P 25P", "AHD 720P 60P", "AHD 720P 50P",
				0,
	/*  0x25 */ "TVI HD 30P EX", "TVI HD 25P EX", "TVI HD 60P", "TVI HD 50P", "TVI HD 30P B", "TVI HD 25P B",
	/*  0x2B */	"CVI HD 30P EX", "CVI HD 25P EX", "CVI HD 60P", "CVI HD 50P",
				0,
	/*  0x30 */	"AHD 1080P 30P", "AHD 1080P 25P",
				0,
	/*	0x33 */ "TVI FHD 30P", "TVI FHD 25P",
	/*  0x35 */	"CVI FHD 30P", "CVI FHD 25P",
                0,
    /*  0x38 */ "AHD 1080P 60P", "AHD 1080P 50P",
    /*  0x3A */ "TVI FHD 60P", "TVI FHD 50P",
    /*  0x3C */ "AHD 1080P 15P NRT", "AHD 1080P 12.5P NRT",
                0, 0,
	/*  0x40 */	"AHD 3M 30P", "AHD 3M 25P", "AHD 3M 18P",
				0,
	/*  0x44 */ "TVI 3M 18P",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x50 */	"AHD 4M 30P", "AHD 4M 25P", "AHD 4M 15P",
				0,
	/*  0x54 */	"CVI 4M 30P", "CVI 4M 25P",
				0,
	/*  0x57 */	"TVI 4M 30P", "TVI 4M 25P", "TVI 4M 15P",
				0, 0, 0, 0, 0, 0,
	/*  0x60 */	"AHD 8M 30P X", "AHD 8M 25P X", 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*  0x70 */ "AHD 5M 20P", "AHD 5M 12.5P", "AHD 5.3M 20P",
    /*  0x73 */ "TVI 5M 12.5P" "TVI 5M 20P",
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x80 */	"AHD 8M 15P", "AHD 8M 7.5P", "AHD 8M 12.5P", "CVI 8M 15P", "CVI 8M 12.5P", "TVI 8M 15P", "TVI 8M 12.5P",
				0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*  0x90 */	"AHD 6M 18P", "AHD30 6M 20P",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*  0xA0 */ "AHD 960P 30P", "AHD 960P 25P", "AHD 960P 60P", "AHD 960P 50P",
    /*  0xA4 */ "TVI 960P 30P", "TVI 960P 25P", "TVI 960P 60P", "TVI 960P 50P"
};

//extern int current_fmt[RAPTOR3_MAX_CH_PER_CHIP * 4];
NC_VIVO_CH_FORMATDEF RS_VD_AUTO_VFCtoFMTDEF(unsigned char VFC)
{
	if(info.author == AHD_NVP6168 || info.author == AHD_NVP6168C)
	{
		return arrVfcType_raptor4[VFC];
	}
	//if(current_fmt[0] == FMT_AUTO)
	return arrVfcType[VFC];
	#if 0
	else if(current_fmt[0] == FMT_CVI)
		return arrVfcType_cvi[VFC];
	else if(current_fmt[0] == FMT_TVI)
		return arrVfcType_tvi[VFC];
	else 
		return arrVfcType_ahd[VFC];
	#endif
}

void _video_input_auto_detect_vafe_set(video_input_auto_detect *vin_auto_det)
{
	unsigned char val_1x7A;
	unsigned char val_5678x00;
	unsigned char val_5678x01;
	unsigned char val_5678x58;
	unsigned char val_5678x59;
	unsigned char val_5678x5B;
	unsigned char val_5678x5C;

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x01);
	val_1x7A = gpio_i2c_read(raptor3_i2c_addr[vin_auto_det->devnum], 0x7A);
	val_1x7A |= (1 << vin_auto_det->ch);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x7A, val_1x7A);

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x00);
	//B0 0x00/1/2/3 gain[4], powerdown[0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x00 + vin_auto_det->ch, ((vin_auto_det->vafe.gain & 0x01) << 4) |
												  (vin_auto_det->vafe.powerdown & 0x01));

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x84 + vin_auto_det->ch, 0x00);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//B5/6/7/8
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x05 + vin_auto_det->ch);

	//B5/6/7/8 0x01 spd[2], lpf_back_band[1:0]
	val_5678x00 = gpio_i2c_read(raptor3_i2c_addr[vin_auto_det->devnum], 0x00);
	val_5678x00 &= ~(0xF << 4);
	val_5678x00 |= vin_auto_det->vafe.spd << 4;

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x00, val_5678x00);

	val_5678x01 = ((vin_auto_det->vafe.ctrlreg << 6) | (vin_auto_det->vafe.ctrlibs << 4) | (vin_auto_det->vafe.adcspd << 2) | (vin_auto_det->vafe.clplevel));
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x01, val_5678x01 );

	//B5/6/7/8 0x58 eq_band[7:4], lpf_front_band[1:0]
	val_5678x58 = ((vin_auto_det->vafe.eq_band << 4) | (vin_auto_det->vafe.lpf_front_band));
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x58, val_5678x58);

	//B5/6/7/8 0x5B ref_vol[1:0]
	val_5678x59 = ((vin_auto_det->vafe.clpmode << 7) | (vin_auto_det->vafe.f_lpf_bypass << 4) | (vin_auto_det->vafe.clproff << 3) | (vin_auto_det->vafe.b_lpf_bypass));
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x59, val_5678x59);

	val_5678x5B = ((vin_auto_det->vafe.duty << 4) | (vin_auto_det->vafe.ref_vol));
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x5B, val_5678x5B);

	val_5678x5C = ((vin_auto_det->vafe.lpf_back_band << 4) | (vin_auto_det->vafe.clk_sel << 3) | (vin_auto_det->vafe.eq_gainsel));
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x5C, val_5678x5C);
}

void video_input_manual_mode_set(video_input_manual_mode *vin_manual_det)
{
	unsigned char val_0x30;
	unsigned char val_0x31;
	unsigned char val_0x32;

	unsigned char val_1x7A;

	unsigned char val_9x44;
	//B13 0x30 AUTO_FMT_SET_EN_2[3:0], AUTO_FMT_SET_EN    [3:0]
	//B13 0x31 AUTO_FMT_SET_EN_4[3:0], AUTO_FMT_SET_EN_3  [3:0]
	//B13 0x32 [	  RESERVED  	], NOVIDEO_VFC_INIT_EN[3:0]

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x01);
	val_1x7A = gpio_i2c_read(raptor3_i2c_addr[vin_manual_det->dev_num], 0x7A);
	val_1x7A &= ~(1 << vin_manual_det->ch);
	val_1x7A |= (1 << vin_manual_det->ch);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x7A, val_1x7A);

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x23 + (vin_manual_det->ch*4), 0x41);

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x13);
	val_0x30 = gpio_i2c_read(raptor3_i2c_addr[vin_manual_det->dev_num], 0x30);
	val_0x31 = gpio_i2c_read(raptor3_i2c_addr[vin_manual_det->dev_num], 0x31);
	val_0x32 = gpio_i2c_read(raptor3_i2c_addr[vin_manual_det->dev_num], 0x32);

	val_0x30 &= (~(1 << (vin_manual_det->ch + 4)) & (~(1 << vin_manual_det->ch)));
	val_0x31 &= (~(1 << (vin_manual_det->ch + 4)) & (~(1 << vin_manual_det->ch)));
	val_0x32 &= (~(1 << vin_manual_det->ch));

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x30, val_0x30);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x31, val_0x31);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x32, val_0x32);

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x05 + vin_manual_det->ch);
	//B5/6/7/8 0xB9 HAFC_LPF_SEL[7:6] GAIN1[5:4] GAIN2[3:0]
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xB9, 0xB2);


	// EXT PN VALUE Disable
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF,0x09);
	val_9x44 = gpio_i2c_read(raptor3_i2c_addr[vin_manual_det->dev_num], 0x44);
	val_9x44 &= ~(1 << vin_manual_det->ch);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x44, val_9x44);
}

void nvp6168_video_input_manual_mode_set(video_input_manual_mode *vin_manual_det)
{
	unsigned char val_1x7A;
	unsigned char val_9x44;

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x01);
	val_1x7A = gpio_i2c_read(raptor3_i2c_addr[vin_manual_det->dev_num], 0x7A);
	val_1x7A &= ~(1 << vin_manual_det->ch);
	val_1x7A |= (1 << vin_manual_det->ch);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x7A, val_1x7A);

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x30, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x70, 0x00);

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x05 + vin_manual_det->ch);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xB9, 0x72);

	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0xFF, 0x09);
	val_9x44 = gpio_i2c_read(raptor3_i2c_addr[vin_manual_det->dev_num], 0x44);
	val_9x44 &= ~(1 << vin_manual_det->ch);
	gpio_i2c_write(raptor3_i2c_addr[vin_manual_det->dev_num], 0x44, val_9x44);
}

void video_input_auto_detect_set(video_input_auto_detect *vin_auto_det)
{
	unsigned char val_0x30;
	unsigned char val_0x31;
	unsigned char val_0x32;

	vin_auto_det->vafe.powerdown 		= 0x00;
	vin_auto_det->vafe.gain		 		= 0x01;
	vin_auto_det->vafe.spd		 		= 0x0d;
	vin_auto_det->vafe.ctrlreg 	 		= 0x01;
	vin_auto_det->vafe.ctrlibs	 		= 0x02;
	vin_auto_det->vafe.adcspd	 		= 0x00;
	vin_auto_det->vafe.clplevel  		= 0x02;
	vin_auto_det->vafe.eq_band	 		= 0x00;
	vin_auto_det->vafe.lpf_front_band 	= 0x07;
	vin_auto_det->vafe.clpmode   		= 0x00;
	vin_auto_det->vafe.f_lpf_bypass 	= 0x01;
	vin_auto_det->vafe.clproff 			= 0x00;
	vin_auto_det->vafe.b_lpf_bypass 	= 0x00;
	vin_auto_det->vafe.duty				= 0x04;
	vin_auto_det->vafe.ref_vol			= 0x03;
	vin_auto_det->vafe.lpf_back_band	= 0x07;
	vin_auto_det->vafe.clk_sel			= 0x01;
	vin_auto_det->vafe.eq_gainsel		= 0x07;

	vin_auto_det->d_cmp					= 0x3f;
	vin_auto_det->slice_level			= 0x5a;
	vin_auto_det->stable_mode_1			= 0x04;
	vin_auto_det->stable_mode_2			= 0x00;
	vin_auto_det->novid_det				= 0x41;


	_video_input_auto_detect_vafe_set(vin_auto_det);

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x05 + vin_auto_det->ch);

	//B5/6/7/8 0x03 Digital Clamp
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x03, vin_auto_det->d_cmp);
	//B5/6/7/8 0x08 Slice Level
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x08, vin_auto_det->slice_level);
	//B5/6/7/8 0xB9 HAFC_LPF_SEL[7:6] GAIN1[5:4] GAIN2[3:0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xB9, 0x72);

	//B5/6/7/8 0xCA ADV_V_DELAY_AD[4] ADV_V_DELAY_ON[0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xCA, 0x10);

	//B13 0x30 AUTO_FMT_SET_EN_2[3:0], AUTO_FMT_SET_EN    [3:0]
	//B13 0x31 AUTO_FMT_SET_EN_4[3:0], AUTO_FMT_SET_EN_3  [3:0]
	//B13 0x32 [	  RESERVED  	], NOVIDEO_VFC_INIT_EN[3:0]

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x13);
	val_0x30 = gpio_i2c_read(raptor3_i2c_addr[vin_auto_det->devnum], 0x30);
	val_0x31 = gpio_i2c_read(raptor3_i2c_addr[vin_auto_det->devnum], 0x31);
	val_0x32 = gpio_i2c_read(raptor3_i2c_addr[vin_auto_det->devnum], 0x32);
	val_0x30 |= ((1 << (vin_auto_det->ch + 4)) | (1 << vin_auto_det->ch));
	val_0x31 |= ((1 << (vin_auto_det->ch + 4)) | (1 << vin_auto_det->ch));
	val_0x32 |= ((1 << vin_auto_det->ch) & 0xF);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x30, val_0x30);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x31, val_0x31);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x32, val_0x32);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x36, 0x0A);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x37, 0x82);

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x81+vin_auto_det->ch, 0x0A);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x85+vin_auto_det->ch, 0x02);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//B13
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x13);
	//B13 0x00  Stable Mode set
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x00, vin_auto_det->stable_mode_1);
	//B13 0x01  Stable Mode Set
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x01, ((vin_auto_det->stable_mode_2) & 0x3));
	//B13 0x40 VFC_EQ_BAND_SEL[7:4] VFC_LPF_F_SEL[1:0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x40, 0x07);
	//B13 0x41 VFC_REF_VTG
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x41, 0x01);
	//B13 0x42 VFC_D_CMP_SET
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x42, 0x3F);
	//B13 0x43 VFC_SLICE_VALUE
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x43, 0x5A);
	//B13 0x44 VFC_SLICE_MD2
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x44, 0x30);
	//B13 0x45 VFC_CONTROL_MODES
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x45, 0xEE);
	//B13 0x46 VFC_GDF_FIX_COEFF
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x46, 0xC6);
	//B13 0x47 VFC_DFE_REF_SEL_OLD[4] VFC_DFE_REF_SEL_NEW[0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x47, 0x00);
	//B13 0x48 VFC_D_BLK_CNT_NEW[[7:4] VFC_HAFC_BYPASS_NEW[1] VFC_UPDN_SEL[0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x48, 0x80);
	//B13 0x49 VFC_OLD_WPD_ON[4] VFC_NEW_WPD_ON[0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x49, 0x00);
	//B13 0x4A VFC_D_CMP_FZ_OLD[4] VFC_D_CMP_FZ_NEW[1]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x4A, 0x11);
	//B13 0x4B VFC_AUTO_GNOS_MODE
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x4B, 0x7F);
	//B13 0x4C VFC_AUTO_SYNC_MODE
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x4C, 0x00);
	//B13 0x4D VFC_HAFC_BYPASS[7] ??? [6:0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x4D, 0xB9);
	//B13 0x4E VFC_VAFE_B_LPF_SEL[6:4] VFC_VAFE_CKSEL[3] VFC_VAFE_EQ_GAIN_SEL[2:0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x4E, 0x78);
	//B13 0x4F VFC_VAFE_CTRL_RES[7:6] VFC_VAFE_IBS_CTRL[5:4] VFC_VAFE_SPD[2] VFC_VAFE_CLP_LEVEL[1:0]
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x4F, 0x62);

	//B0  0x23/0x27/0x2B/0x2F No Video Detect
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x0);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x23 + ((vin_auto_det->ch) * 4), vin_auto_det->novid_det);

	/* clock set */
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x1);
    	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x84 + vin_auto_det->ch, 0x00);
    	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x8c + vin_auto_det->ch, 0x55);

}

void nvp6168_video_input_auto_detect_set(video_input_auto_detect *vin_auto_det)
{
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x13);

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x12, 0x04);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x2E, 0x10);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x30, 0x7f);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x31, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x32, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x33, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x77, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x3a, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x3b, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x3c, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x3d, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x3e, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x3f, 0xff);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x70, 0xf0);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x72, 0x05);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x7A, 0x10);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x61, 0x0A);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x62, 0x02);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x60, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x60, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x07, 0x47);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x59, 0x24);

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x01, 0x0c);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x2f, 0xc8);

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x73, 0x23);

	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xff, 0x09 );
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x96, 0x03);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xB6, 0x03);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xD6, 0x03);
	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xF6, 0x03);
}

void video_input_vfc_read(video_input_vfc *vin_vfc)
{
	gpio_i2c_write(raptor3_i2c_addr[vin_vfc->devnum], 0xFF, 0x13);
	vin_vfc->vfc = gpio_i2c_read(raptor3_i2c_addr[vin_vfc->devnum], 0xF0 + vin_vfc->ch);
}

void nvp6168_video_input_vfc_read(video_input_vfc *vin_vfc)
{
	gpio_i2c_write(raptor3_i2c_addr[vin_vfc->devnum], 0xFF, 0x05 + vin_vfc->ch);
	vin_vfc->vfc = gpio_i2c_read(raptor3_i2c_addr[vin_vfc->devnum], 0xF0);
}

void video_input_novid_read(video_input_novid *vin_novid)
{
	unsigned char val_0xA8;

	gpio_i2c_write(raptor3_i2c_addr[vin_novid->devnum], 0xFF, 0x00);
	val_0xA8 = gpio_i2c_read(raptor3_i2c_addr[vin_novid->devnum], 0xA8);

	vin_novid->novid = (((val_0xA8 >> vin_novid->ch) & 0x1)) ;
}


void video_input_no_video_set(video_input_novid_set *auto_novid)
{
	unsigned char val_13x30;
	unsigned char val_13x31;
	unsigned char val_13x32;
	unsigned char val_9x44;
	unsigned char val_1x7A;

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x21 + (auto_novid->ch * 4), 0x82);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x23 + (auto_novid->ch * 4), 0x41);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x09);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x80 + (auto_novid->ch * 0x20), 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x81 + (auto_novid->ch * 0x20), 0x00);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x0A+auto_novid->ch/2);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x3D + ((auto_novid->ch%2) * 0x80), 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x3C + ((auto_novid->ch%2) * 0x80), 0x00);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x05 + auto_novid->ch);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x2C, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x01, 0x62);

	/* Before 08/28 */
	//gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x58, 0x07);
	//gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x5C, 0x78);
	/* After 08/28 */
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x50, 0xC6);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x58, 0x47);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x5C, 0x7f);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x6E, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x6F, 0x00);

        /* Low-Poass Filter (LPF) Bypass Enable  Bank5/6/7/8 0x59 */
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x59, 0x10);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xB8, 0xB8);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xB9, 0xB2);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x43, 0x5a);

	val_13x30 = gpio_i2c_read(raptor3_i2c_addr[auto_novid->devnum], 0x30);
	val_13x31 = gpio_i2c_read(raptor3_i2c_addr[auto_novid->devnum], 0x31);
	val_13x32 = gpio_i2c_read(raptor3_i2c_addr[auto_novid->devnum], 0x32);
	val_13x30 |= ((1 << (auto_novid->ch + 4)) | (1 << auto_novid->ch));
	val_13x31 |= ((1 << (auto_novid->ch + 4)) | (1 << auto_novid->ch));
	val_13x32 |= ((1 << auto_novid->ch) & 0xF);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x30, val_13x30);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x31, val_13x31);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x32, val_13x32);

	/* disable Bank11 0x00, if before setting format TVI 5M 20P when onvideo */
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x11);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x00 + ( auto_novid->ch * 0x20 ), 0x00);
	
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x09);
	val_9x44 = gpio_i2c_read(raptor3_i2c_addr[auto_novid->devnum], 0x44);
	val_9x44 |= (1 << auto_novid->ch);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x50 + (auto_novid->ch*4) , 0x30);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x51 + (auto_novid->ch*4) , 0x6F);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x52 + (auto_novid->ch*4) , 0x67);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x53 + (auto_novid->ch*4) , 0x48);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x44 , val_9x44);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x01);
	val_1x7A = gpio_i2c_read(raptor3_i2c_addr[auto_novid->devnum], 0x7A);
//	val_1x7A &= ~(1 << auto_novid->ch);
	val_1x7A |= (1 << auto_novid->ch);

}

void nvp6168_video_input_no_video_set(video_input_novid_set *auto_novid)
{
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x21 + (auto_novid->ch * 4), 0x82);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x23 + (auto_novid->ch * 4), 0x41);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x09);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x80 + (auto_novid->ch * 0x20), 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x81 + (auto_novid->ch * 0x20), 0x00);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xff, (auto_novid->ch < 2 ? 0x0a : 0x0b) );
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x3d + (auto_novid->ch%2 * 0x80), 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x3c + (auto_novid->ch%2 * 0x80), 0x00);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x05 + auto_novid->ch);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x01, 0x62);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x2C, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x50, 0xc6);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x58, 0x47);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x59, 0x10);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x5C, 0x7f);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xB8, 0xB8);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xB9, 0x72);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x6E, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x6F, 0x00);

	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0xFF, 0x11);
	gpio_i2c_write(raptor3_i2c_addr[auto_novid->devnum], 0x00 + ( auto_novid->ch * 0x20 ), 0x00);
}

void video_input_cable_dist_read(video_input_cable_dist *vin_cable_dist)
{
	gpio_i2c_write(raptor3_i2c_addr[vin_cable_dist->devnum], 0xFF, 0x13);

	//B13 0xA0 [3:0] Cable Distance Value
	vin_cable_dist->dist = gpio_i2c_read(raptor3_i2c_addr[vin_cable_dist->devnum], 0xA0 + vin_cable_dist->ch ) & 0xF;
}



void video_input_sam_val_read(video_input_sam_val *vin_sam_val ) 
{
	unsigned char val1, val2;

	// Channel Change Sequence
	gpio_i2c_write(raptor3_i2c_addr[vin_sam_val->devnum], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[vin_sam_val->devnum], 0x2B, vin_sam_val->ch);

	gpio_i2c_write(raptor3_i2c_addr[vin_sam_val->devnum], 0xFF, 0x13); /* + vin_sam_val->ch ); */
	//B13 0xC9 [7:0] SAM Value
	val1 = gpio_i2c_read(raptor3_i2c_addr[vin_sam_val->devnum], 0xC9) ;
	//B13 0xC8 [9:8] SAM Value
	val2 = gpio_i2c_read(raptor3_i2c_addr[vin_sam_val->devnum], 0xC8) & 0x3;

	vin_sam_val->sam_val = ((val2 << 8) | val1);
}

void video_input_hsync_accum_read(video_input_hsync_accum *vin_hsync_accum )
{
	unsigned char val01, val02, val03, val04;
	unsigned char val11, val12, val13, val14;

	unsigned char h_lock;
	unsigned int val_1;
	unsigned int val_2;
	unsigned int val_result;

	gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xFF, 0x00);
	h_lock = (gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xE2) >> vin_hsync_accum->ch) & 0x1;

	vin_hsync_accum->h_lock = h_lock;

	gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0x2B, vin_hsync_accum->ch);

	gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xFF, 0x13); 	/* + vin_sam_val->ch  */

	//B13 0xB4 [ 7:0] Hsync Accumulation Value
	val01 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD0);	// 170214 0xB4 -> 0xD0 Fix
	//B13 0xB5 [15:8] Hsync Accumulation Value
	val02 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD1);	// 170214 0xB5 -> 0xD1 Fix
	//B13 0xB6 [23:16] Hsync Accumulation Value
	val03 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD2);	// 170214 0xB6 -> 0xD2 Fix
	//B13 0xB7 [31:24] Hsync Accumulation Value
	val04 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD3);	// 170214 0xB7 -> 0xD3 Fix

	//B13 0xB4 [ 7:0] Hsync Accumulation Value
	val11 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD4);	// 170214 0xB8 -> 0xD4 Fix
	//B13 0xB5 [15:8] Hsync Accumulation Value
	val12 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD5);	// 170214 0xB9 -> 0xD5 Fix
	//B13 0xB6 [23:16] Hsync Accumulation Value
	val13 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD6);	// 170214 0xBA -> 0xD6 Fix
	//B13 0xB7 [31:24] Hsync Accumulation Value
	val14 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD7);	// 170214 0xBB -> 0xD7 Fix

	val_1 = ((val04 << 24) | (val03 << 16) | (val02 << 8) | val01);
	val_2 = ((val14 << 24) | (val13 << 16) | (val12 << 8) | val11);

	val_result = val_1 - val_2;

	vin_hsync_accum->hsync_accum_val1 = val_1;
	vin_hsync_accum->hsync_accum_val2 = val_2;
	vin_hsync_accum->hsync_accum_result = val_result;
}

static int nvp6168_get_eq_read_cnt(unsigned char devnum, unsigned char ch)
{
	unsigned char vfc;
	int ret = 50;

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x05 + ch);
	vfc = gpio_i2c_read(raptor3_i2c_addr[devnum], 0xF0);

	switch(vfc)
	{
		// 25fps, 3frame=120ms
		case 0x10 :
		case 0x21 :
		case 0x26 :
		case 0x2A :
		case 0x2C :
		case 0x31 :
		case 0x34 :
		case 0x36 :
		case 0x41 :
		case 0x51 :
		case 0x55 :
		case 0x58 :
		case 0x61 :
		case 0xA1 :
		case 0xA5 :
			ret = 24;
			break;

		// 30fps, 3frame=100ms
		case 0x00 :
		case 0x20 :
		case 0x25 :
		case 0x29 :
		case 0x2B :
		case 0x30 :
		case 0x33 :
		case 0x35 :
		case 0x40 :
		case 0x50 :
		case 0x54 :
		case 0x57 :
		case 0x60 :
		case 0xA0 :
		case 0xA4 :
			ret = 20;
			break;

		// 50fps, 3frame=60ms
		case 0x23 :
		case 0x28 :
		case 0x2E :
		case 0x39 :
		case 0x3B :
		case 0xA3 :
		case 0xA7 :
			ret = 12;
			break;

		// 60fps, 3frame=50ms
		case 0x22 :
		case 0x27 :
		case 0x2D :
		case 0x38 :
		case 0x3A :
		case 0xA2 :
		case 0xA6 :
			ret = 10;
			break;

		// 20fps, 3frame=150ms
		case 0x70 :
		case 0x72 :
		case 0x74 :
			ret = 30;
			break;

		// 18fps, 3frame=167ms
		case 0x42 :
		case 0x44 :
		case 0x90 :
			ret = 34;
			break;

		// 15fps, 3frame=200ms
		case 0x3C :
		case 0x52 :
		case 0x59 :
		case 0x80 :
		case 0x83 :
		case 0x85 :
			ret = 40;
			break;

		// 12.5fps, 3frame=240ms
		case 0x3D :
		case 0x71 :
		case 0x73 :
		case 0x82 :
		case 0x84 :
		case 0x86 :
			ret = 48;
			break;

		// 7.5fps, 3frame=400ms
		case 0x81 :
			ret = 80;
			break;

		default :
			break;
	}

	return ret;
}

void nvp6168_video_input_hsync_accum_read(video_input_hsync_accum *vin_hsync_accum )
{
	unsigned char val01, val02, val03, val04;
	unsigned char val11, val12, val13, val14;

	unsigned int val_1 = 0;
	unsigned int val_2 = 0;
	unsigned int val_result;

	unsigned char rst_reg = 1<<vin_hsync_accum->ch;
	unsigned char vfc, video_loss;
	int read_cnt=0, total_cnt;
	video_input_novid_set s_auto_novid;

	total_cnt = nvp6168_get_eq_read_cnt(vin_hsync_accum->devnum, vin_hsync_accum->ch);

	gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0x2B, vin_hsync_accum->ch);

	while(read_cnt < total_cnt)
	{
		gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xFF, 0x00);
		video_loss = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xA8);
		video_loss = (((video_loss >> vin_hsync_accum->ch) & 0x1)) ;

		gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xFF, 0x05 + vin_hsync_accum->ch);
		vfc = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xF0);

		if((video_loss == 1) && (vfc == 0xFF))
		{
			printk("[%s] CH:%d, video_loss:%02X, vfc:0x%X \r\n", __func__, vin_hsync_accum->ch, video_loss, vfc);
			vin_hsync_accum->hsync_accum_val1 = 0;
			vin_hsync_accum->hsync_accum_val2 = 0;
			vin_hsync_accum->hsync_accum_result = 0xffffffff;
			s_auto_novid.ch = vin_hsync_accum->ch;
			nvp6168_video_input_no_video_set(&s_auto_novid);
			return;
		}

		gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xFF, 0x13);
		//B13 0xB4 [ 7:0] Hsync Accumulation Value
		val01 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD0);	// 170214 0xB4 -> 0xD0 Fix
		//B13 0xB5 [15:8] Hsync Accumulation Value
		val02 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD1);	// 170214 0xB5 -> 0xD1 Fix
		//B13 0xB6 [23:16] Hsync Accumulation Value
		val03 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD2);	// 170214 0xB6 -> 0xD2 Fix
		//B13 0xB7 [31:24] Hsync Accumulation Value
		val04 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD3);	// 170214 0xB7 -> 0xD3 Fix

		//B13 0xB4 [ 7:0] Hsync Accumulation Value
		val11 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD4);	// 170214 0xB8 -> 0xD4 Fix
		//B13 0xB5 [15:8] Hsync Accumulation Value
		val12 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD5);	// 170214 0xB9 -> 0xD5 Fix
		//B13 0xB6 [23:16] Hsync Accumulation Value
		val13 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD6);	// 170214 0xBA -> 0xD6 Fix
		//B13 0xB7 [31:24] Hsync Accumulation Value
		val14 = gpio_i2c_read(raptor3_i2c_addr[vin_hsync_accum->devnum], 0xD7);	// 170214 0xBB -> 0xD7 Fix

		val_1 = ((val04 << 24) | (val03 << 16) | (val02 << 8) | val01);
		val_2 = ((val14 << 24) | (val13 << 16) | (val12 << 8) | val11);

		//printk("[%s] CH:%d, video_loss:%02X, vfc:0x%X val1:%08X / val2:%08X \r\n", __func__, vin_hsync_accum->ch, video_loss, vfc, val_1, val_2);

		if((val_1 != 0) && (val_2 != 0))
		{
			if((pre_val_1 != val_1) || (pre_val_2 != val_2))
			{
				gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0x7A, rst_reg);
				gpio_i2c_write(raptor3_i2c_addr[vin_hsync_accum->devnum], 0x7A, 0x10);
				pre_val_1 = val_1;
				pre_val_2 = val_2;
				break;
			}
		}
		msleep(10);
		read_cnt++;
	}
	val_result = val_1 - val_2;

	vin_hsync_accum->hsync_accum_val1 = val_1;
	vin_hsync_accum->hsync_accum_val2 = val_2;
	vin_hsync_accum->hsync_accum_result = val_result;
}

void video_input_agc_val_read(video_input_agc_val *vin_agc_val) 
{
	unsigned char agc_lock;

	gpio_i2c_write(raptor3_i2c_addr[vin_agc_val->devnum], 0xFF, 0x00);
	agc_lock = (gpio_i2c_read(raptor3_i2c_addr[vin_agc_val->devnum], 0xE0) >> vin_agc_val->ch) & 0x1;

	 vin_agc_val->agc_lock = agc_lock;

	gpio_i2c_write(raptor3_i2c_addr[vin_agc_val->devnum], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[vin_agc_val->devnum], 0x2B, vin_agc_val->ch);

	gpio_i2c_write(raptor3_i2c_addr[vin_agc_val->devnum], 0xFF, 0x13); /* + vin_sam_val->ch ); */

	//B13 0xB8 [ 7:0] Hsync Accumulation Value
	vin_agc_val->agc_val = gpio_i2c_read(raptor3_i2c_addr[vin_agc_val->devnum], 0xC4); // 170213 0xA9 -> 0xC5 // 170310 0xC5 -> 0xC4
}

void video_input_fsc_val_read(video_input_fsc_val *vin_fsc_val)
{
	unsigned char val01, val02, val03, val04;
	unsigned char val11, val12, val13, val14;
	unsigned char val21, val22, val23, val24;

	unsigned int val_1, val_2, val_final;

	// Channel Change Sequence
	gpio_i2c_write(raptor3_i2c_addr[vin_fsc_val->devnum], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[vin_fsc_val->devnum], 0x2B, vin_fsc_val->ch);

	gpio_i2c_write(raptor3_i2c_addr[vin_fsc_val->devnum], 0xFF, 0x13);

	//B13 0xB4 [ 7:0] r_fsc_line_diff_sts
	val01 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xB4);
	//B13 0xB5 [15:8] r_fsc_line_diff_sts
	val02 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xB5);
	//B13 0xB6 [23:16] r_fsc_line_diff_sts
	val03 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xB6);
	//B13 0xB7 [31:24] r_fsc_line_diff_sts
	val04 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xB7);

	//B13 0xB4 [ 7:0] r_fsc_line2_diff_sts
	val11 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xB8);
	//B13 0xB5 [15:8] r_fsc_line2_diff_sts
	val12 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xB9);
	//B13 0xB6 [23:16] r_fsc_line2_diff_sts
	val13 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xBA);
	//B13 0xB7 [31:24] r_fsc_line2_diff_sts
	val14 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xBB);

	//B13 0xB4 [ 7:0] r_fsc_line_diff_final
	val21 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xBC);
	//B13 0xB5 [15:8] r_fsc_line_diff_final
	val22 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xBD);
	//B13 0xB6 [23:16] r_fsc_line_diff_final
	val23 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xBE);
	//B13 0xB7 [31:24] r_fsc_line_diff_final
	val24 = gpio_i2c_read(raptor3_i2c_addr[vin_fsc_val->devnum], 0xBF);


	val_1 = ((val04 << 24) | (val03 << 16) | (val02 << 8) | val01);
	val_2 = ((val14 << 24) | (val13 << 16) | (val12 << 8) | val11);
	val_final = ((val24 << 24) | (val23 << 16) | (val22 << 8) | val21);

	vin_fsc_val->fsc_val1 = val_1;
	vin_fsc_val->fsc_val2 = val_2;
	vin_fsc_val->fsc_final = val_final;
}

//  170420 RAPTOR3 DR2 DEMO ONLY
void video_input_aeq_val_set(video_input_aeq_set *vin_aeq_val) // 170214 aeq value set
{
//	if(vin_aeq_val->aeq_val == 0x00)
//	{
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0xFF, 0x05 + vin_aeq_val->ch);
//
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x58, 0x03);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x59, 0x00);
//	}
//
//	else if(vin_aeq_val->aeq_val == 0x02)
//	{
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0xFF, 0x05 + vin_aeq_val->ch);
//
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x58, 0xD3);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x59, 0x11);
//	}

}

//  170420 RAPTOR3 DR2 DEMO ONLY
void video_input_deq_val_set(video_input_deq_set *vin_deq_val) // 170214 deq value set
{
	// B9 0x80/0xA0/0xC0/0xE0 [3:0]
//	if(vin_deq_val->deq_val == 0x00)
//	{
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0xFF, 0x09);
//
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x80 + ((vin_deq_val->ch)*0x20), 0x00);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x84 + ((vin_deq_val->ch)*0x20), 0x21);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x85 + ((vin_deq_val->ch)*0x20), 0x60);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x86 + ((vin_deq_val->ch)*0x20), 0xF6);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x87 + ((vin_deq_val->ch)*0x20), 0x20);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x88 + ((vin_deq_val->ch)*0x20), 0x00);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x89 + ((vin_deq_val->ch)*0x20), 0xDC);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x8a + ((vin_deq_val->ch)*0x20), 0x02);
//
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0xFF, 0x00);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x30, 0x18);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x3C, 0x90);
//	}
//	else if(vin_deq_val->deq_val == 0x02)
//	{
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0xFF, 0x09);
//
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x80 + ((vin_deq_val->ch)*0x20), 0xA7);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x84 + ((vin_deq_val->ch)*0x20), 0x21);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x85 + ((vin_deq_val->ch)*0x20), 0x60);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x86 + ((vin_deq_val->ch)*0x20), 0xF6);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x87 + ((vin_deq_val->ch)*0x20), 0x20);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x88 + ((vin_deq_val->ch)*0x20), 0x00);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x89 + ((vin_deq_val->ch)*0x20), 0xDC);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x8a + ((vin_deq_val->ch)*0x20), 0x02);
//
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0xFF, 0x00);
//		gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x30, 0x16);
//	}

//	val = gpio_i2c_read(raptor3_i2c_addr[chip_num], 0x80 + ((vin_deq_val->ch)*0x20));
//	val = (vin_deq_val->deq_val & 0xF) | val;
//
//	gpio_i2c_write(raptor3_i2c_addr[chip_num], 0x80 + ((vin_deq_val->ch)*0x20), val);
}

void video_input_acc_gain_val_read(video_input_acc_gain_val *vin_acc_gain) // 170215 acc gain read
{
	unsigned char val1, val2;

	if(vin_acc_gain->func_sel == ACC_GAIN_NORMAL) {

		gpio_i2c_write(raptor3_i2c_addr[vin_acc_gain->devnum], 0xFF, 0x05 + vin_acc_gain->ch);

		val1 = gpio_i2c_read(raptor3_i2c_addr[vin_acc_gain->devnum],0xE2) & 0x7; // B5 0xE2 acc gain [10:8]
		val2 = gpio_i2c_read(raptor3_i2c_addr[vin_acc_gain->devnum],0xE3); 		 // B5 0xE3 acc gain [7:0]
	}
	else if(vin_acc_gain->func_sel == ACC_GAIN_DEBUG) { 	// DEBUG
		gpio_i2c_write(raptor3_i2c_addr[vin_acc_gain->devnum], 0xFF, 0x00);
		val1 = 0;
		val2 = gpio_i2c_read(raptor3_i2c_addr[vin_acc_gain->devnum],0xD8 + vin_acc_gain->ch); // B13 0xC6 acc gain [9:8]
	}
	else
	{
		gpio_i2c_write(raptor3_i2c_addr[vin_acc_gain->devnum], 0xFF, 0x05);

		val1 = gpio_i2c_read(raptor3_i2c_addr[vin_acc_gain->devnum],0xE2) & 0x7; // B5 0xE2 acc gain [10:8]
		val2 = gpio_i2c_read(raptor3_i2c_addr[vin_acc_gain->devnum],0xE3); 		 // B5 0xE3 acc gain [7:0]
	}

	vin_acc_gain->acc_gain_val = val1 << 8 | val2;
}

void video_output_data_out_mode_set(video_output_data_out_mode *vo_data_out_mode)
{
	unsigned char temp_val = 0x0;

	//  Show/Hide mode is using register Bank 0 0x7A, 7B
	// 		   CH2	  CH1		    CH4    CH3
	//	0x7A [7 : 4][3 : 0]  0x7B [7 : 4][3 : 0]
	gpio_i2c_write(raptor3_i2c_addr[vo_data_out_mode->devnum], 0xFF, 0x00);

	switch(vo_data_out_mode -> ch)
	{
		case CH1 :
		case CH2 : temp_val = gpio_i2c_read(raptor3_i2c_addr[vo_data_out_mode->devnum], 0x7A);
					break;
		case CH3 :
		case CH4 : temp_val = gpio_i2c_read(raptor3_i2c_addr[vo_data_out_mode->devnum], 0x7B);
					break;
	}

	switch(vo_data_out_mode -> ch)
	{
		case CH1 :
		case CH3 :	temp_val = ((temp_val & 0xF0) | (vo_data_out_mode -> set_val & 0xF));
					break;
		case CH2 :
		case CH4 :  temp_val = ((temp_val & 0x0F) | ((vo_data_out_mode -> set_val & 0xF) << 4));
					break;
	}

	// printk("[%s:%s] : %s >>>> temp_val [ %x ]\n", __FILE__, __LINE__, __FUNCTION__,temp_val);
	switch(vo_data_out_mode -> ch)
	{
		case CH1 :
		case CH2 : gpio_i2c_write(raptor3_i2c_addr[vo_data_out_mode->devnum], 0x7A, temp_val);
				   break;
		case CH3 :
		case CH4 : gpio_i2c_write(raptor3_i2c_addr[vo_data_out_mode->devnum], 0x7B, temp_val);
				   break;
	}
}


unsigned char __IsOver3MRTVideoFormat( decoder_dev_ch_info_s *decoder_info )
{
	unsigned char ret = 0; //

	if(
	   (decoder_info->fmt_def == AHD30_3M_30P) ||
	   (decoder_info->fmt_def == AHD30_3M_25P) ||
	   (decoder_info->fmt_def == AHD30_4M_30P) ||
	   (decoder_info->fmt_def == AHD30_4M_25P) ||
	   (decoder_info->fmt_def == AHD30_5M_20P) ||
	   (decoder_info->fmt_def == AHD30_5_3M_20P) ||
	   (decoder_info->fmt_def == AHD30_6M_18P) ||
	   (decoder_info->fmt_def == AHD30_6M_20P) ||
	   (decoder_info->fmt_def == AHD30_8M_12_5P) ||
	   (decoder_info->fmt_def == AHD30_8M_15P) ||
	   (decoder_info->fmt_def == TVI_4M_30P) ||
	   (decoder_info->fmt_def == TVI_4M_25P) ||
	   (decoder_info->fmt_def == TVI_5M_20P) ||	   
	   (decoder_info->fmt_def == CVI_5M_20P) ||
	   (decoder_info->fmt_def == CVI_4M_25P) ||
	   (decoder_info->fmt_def == CVI_4M_30P) ||
	   (decoder_info->fmt_def == CVI_8M_15P) ||
	   (decoder_info->fmt_def == CVI_8M_12_5P) ||
	   (decoder_info->fmt_def == TVI_8M_15P) ||
	   (decoder_info->fmt_def == TVI_8M_12_5P)

	   )
	{
		ret = 1;
	}
	return ret; // 0:Over 3M RT, 1:other formation
}

unsigned char RS__IsOver3MRTVideoFormat( const char *poFmtName )
{
	unsigned char ret = 1; //

	if((strcmp(poFmtName, "AHD30_3M_30P") == 0) ||
	   (strcmp(poFmtName, "AHD30_3M_25P") == 0) ||
	   (strcmp(poFmtName, "AHD30_4M_30P") == 0) ||
	   (strcmp(poFmtName, "AHD30_4M_25P") == 0) ||
	   (strcmp(poFmtName, "AHD30_5M_20P") == 0) ||
	   (strcmp(poFmtName, "AHD30_5_3M_20P") == 0) ||
	   (strcmp(poFmtName, "AHD30_6M_18P") == 0) ||
	   (strcmp(poFmtName, "AHD30_6M_20P") == 0) ||
	   (strcmp(poFmtName, "AHD30_8M_12_5P") == 0) ||
	   (strcmp(poFmtName, "AHD30_8M_15P") == 0) ||
	   (strcmp(poFmtName, "TVI_4M_30P") == 0) ||
	   (strcmp(poFmtName, "TVI_4M_25P") == 0) ||
	   (strcmp(poFmtName, "TVI_5M_20P") == 0) ||
	   (strcmp(poFmtName, "CVI_4M_25P") == 0) ||
	   (strcmp(poFmtName, "CVI_4M_30P") == 0) ||
	   (strcmp(poFmtName, "CVI_8M_15P") == 0) ||
	   (strcmp(poFmtName, "CVI_8M_12_5P") == 0) ||
	   (strcmp(poFmtName, "TVI_8M_15P") == 0) ||
	   (strcmp(poFmtName, "TVI_8M_12_5P") == 0))
	{
		ret = 0;
	}
	return ret; // 0:Over 3M RT, 1:other formation
}

unsigned char s_only_onetime_run[32] = {0, };
void video_input_onvideo_set(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char format_3M_RT;
	unsigned char achn;

	achn = (decoder_info->ch)%4 + (decoder_info->devnum)*4;

	printk("Onvideo_set ch_num[%x] fmt_def[%d]\n", achn, decoder_info->fmt_def);

	/* before 09/12 */
// unsigned char val_9x44;
//	if(decoder_info->fmt_def == TVI_4M_30P) // if TVI 4M 30P ---> PN Value Set
//	{
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF,0x09);
//		val_9x44 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x44);
//		val_9x44 |= (1 << decoder_info->ch);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x44, val_9x44);
//
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x09);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x50 + (decoder_info->ch*4) , 0x9E);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x51 + (decoder_info->ch*4) , 0x48);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x52 + (decoder_info->ch*4) , 0x58);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x53 + (decoder_info->ch*4) , 0x74);
//	}
//	else // Else EXT_PN_VALUE Disable
//	{
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF,0x09);
//		val_9x44 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x44);
//		val_9x44 &= ~(1 << decoder_info->ch);
//
//		/* CVI HD 30P PN Value Set */
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x09);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x50 + (decoder_info->ch*4) , 0x30);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x51 + (decoder_info->ch*4) , 0x6F);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x52 + (decoder_info->ch*4) , 0x67);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x53 + (decoder_info->ch*4) , 0x48);
//
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x44, val_9x44);
//
//		if(	decoder_info->fmt_def == CVI_HD_30P 		||
//			decoder_info->fmt_def == CVI_HD_30P_EX		||
//			decoder_info->fmt_def == AHD20_720P_30P		||
//			decoder_info->fmt_def == AHD20_720P_30P_EX	||
//			decoder_info->fmt_def == AHD20_720P_30P_EX_Btype)
//		{
//			//meant to remove pre-connection issue. 07.31
//			if( s_only_onetime_run[decoder_info->ch * decoder_info->devnum] == 0)
//			{
//			video_input_vafe_reset(decoder_info);
//				s_only_onetime_run[decoder_info->ch * decoder_info->devnum] = 1;
//			}
//		}
//		else
//		{
//			if( s_only_onetime_run[decoder_info->ch * decoder_info->devnum] == 0)
//			{
//				s_only_onetime_run[decoder_info->ch * decoder_info->devnum] = 1;
//			}
//		}
//	}

	/* after 09/12 */
	format_3M_RT = __IsOver3MRTVideoFormat(decoder_info);

	if(format_3M_RT)
	{
		/* DECI_FILTER_ON */
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x05 + decoder_info->ch);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x50, 0x76);
	}
	else
	{
		/* DECI_FILTER_OFF */
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x05 + decoder_info->ch);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x50, 0xc6);
	}


		if(	decoder_info->fmt_def == CVI_HD_30P 		||
			decoder_info->fmt_def == CVI_HD_30P_EX		||
			decoder_info->fmt_def == AHD20_720P_30P		||
			decoder_info->fmt_def == AHD20_720P_30P_EX	||
			decoder_info->fmt_def == AHD20_720P_30P_EX_Btype)
		{
			//meant to remove pre-connection issue. 07.31
			if( s_only_onetime_run[decoder_info->ch + 4 * decoder_info->devnum] == 0)
			{
				video_input_vafe_reset(decoder_info);
				s_only_onetime_run[decoder_info->ch + 4 * decoder_info->devnum] = 1;
			}
		}
		else
		{
			if( s_only_onetime_run[decoder_info->ch + 4 * decoder_info->devnum] == 0)
			{
				s_only_onetime_run[decoder_info->ch + 4 * decoder_info->devnum] = 1;
			}
		}

}

void video_input_onvideo_check_data_bank5(video_input_vfc *vin_vfc)
{
	gpio_i2c_write(raptor3_i2c_addr[vin_vfc->devnum], 0xFF, 0x05 + vin_vfc->ch);
	vin_vfc->vfc = gpio_i2c_read(raptor3_i2c_addr[vin_vfc->devnum], 0xF0);
}

void nvp6168_video_input_onvideo_set(decoder_dev_ch_info_s *decoder_info)
{
	//unsigned char format_3M_RT;
	unsigned char ch = decoder_info->ch % 4;
	unsigned char devnum = decoder_info->devnum;
	unsigned char val_9x44;
	unsigned char set_done=0xF0;

	printk("onvideo_set dev_num[%x] ch_num[%x] fmt_def[%d]", decoder_info->devnum, decoder_info->ch, decoder_info->fmt_def);

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x09);
	val_9x44 = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x44);
	val_9x44 &= ~(1 << ch);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x44, val_9x44);

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x50 + (ch*4) , 0x30);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x51 + (ch*4) , 0x6F);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x52 + (ch*4) , 0x67);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x53 + (ch*4) , 0x48);

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x11);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x00 + (ch*0x20), 0x00);

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x13);
	set_done |= gpio_i2c_read(raptor3_i2c_addr[devnum], 0x70);
	set_done |= (1<<ch);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x70, set_done);

	set_done = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x71);
	set_done |= (1<<ch);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x71, set_done);
}

void video_input_onvideo_check_data(video_input_vfc *vin_vfc)
{
	#if 0		// 6158/6158C bank 5
	gpio_i2c_write(raptor3_i2c_addr[vin_vfc->devnum], 0xFF, 0x05 + vin_vfc->ch);
	vin_vfc->vfc = gpio_i2c_read(raptor3_i2c_addr[vin_vfc->devnum], 0xF0);
	#else		// 6158/6158C bank 13
	if(info.author == AHD_NVP6168 || info.author == AHD_NVP6168C)
	{
		gpio_i2c_write(raptor3_i2c_addr[vin_vfc->devnum], 0xFF, 0x05 + vin_vfc->ch);
		vin_vfc->vfc = gpio_i2c_read(raptor3_i2c_addr[vin_vfc->devnum], 0xF0);
	}
	else
	{
		gpio_i2c_write(raptor3_i2c_addr[vin_vfc->devnum], 0xFF, 0x13);
		vin_vfc->vfc = gpio_i2c_read(raptor3_i2c_addr[vin_vfc->devnum], 0xF0 + vin_vfc->ch);
	}
	#endif
}

void video_input_auto_ch_sw_rst(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char val_1x97;
	 //Software Reset
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF,0x01);
	val_1x97 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x97);
	val_1x97 &= ~(1 << decoder_info->ch);
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x97, val_1x97);
	msleep(10);
	val_1x97 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x97);
	val_1x97 |= (1 << decoder_info->ch);
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x97, val_1x97);

	printk("[DRV] Decoder CH[%d] Software Reset done\n",decoder_info->ch);
}

void video_input_vafe_reset(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char val_0x00;
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x00);
	val_0x00 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch);
	_SET_BIT(val_0x00, 0);
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch, val_0x00);
	msleep(10);
	_CLE_BIT(val_0x00, 0);
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch, val_0x00);
	printk("[DRV] AFE CH:[%d] Reset done\n", decoder_info->ch);
}

void video_input_manual_agc_stable_endi(decoder_dev_ch_info_s *decoder_info, int endi)
{
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x05+decoder_info->ch);
	if( endi == 1 )
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x82, 0xff);
		//printk("[DRV] MANUAL AGC STABLE ENABLE CH:[%d]\n", decoder_info->ch);
	}
	else
	{

		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x82, 0x00);
		//printk("[DRV] MANUAL AGC STABLE ENABLE CH:[%d]\n", decoder_info->ch);
	}
}

void video_input_vafe_control(decoder_dev_ch_info_s *decoder_info, int cmd)
{
	unsigned char val_0x00;

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x00);

	if(cmd == 0)
	{
		val_0x00 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch);
		_SET_BIT(val_0x00, 0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch, val_0x00);

		printk("[DRV] [Ch:%d] AFE Power Down ... \n", decoder_info->ch);

		msleep(10);
	}
	else if(cmd == 1)
	{
		val_0x00 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch);
		_CLE_BIT(val_0x00, 0);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch, val_0x00);

		printk("[DRV] [Ch:%d] AFE Power Up ... \n", decoder_info->ch);

		msleep(10);
	}
}

unsigned int __s_max_min_exclude_avg_func(unsigned int* input_arry, int cnt)
{
	unsigned int max, min, sum = 0, result = 0;
	unsigned int ii;

	max = input_arry[0];
	min = input_arry[0];

	for(ii = 0; ii < cnt; ii++)
	{
		max = max > input_arry[ii] ? max : input_arry[ii];
		min = min > input_arry[ii] ? input_arry[ii] : min;

		sum += input_arry[ii];
	}

	result = sum - (max + min);

	if(result == 0)
	{
		return 0;
	}
	else
	{
		result /= ( cnt - 2 );
	}

	return result;
}

unsigned int __s_distinguish_5M_ahd_tvi_func(unsigned int* input_arry, int cnt)
{
	unsigned int chk1, chk2;
	unsigned int max, max_idx = 0;
	unsigned int calc_array[10][10] = { {0, 0},  };
	unsigned int need_update = 0;
	unsigned int find_idx = 0;
	unsigned int ii, ij;
	unsigned int inner_idx = 0;

	chk1 = input_arry[0];

	for(ii = 0; ii < cnt; ii++)
	{
		chk2 = input_arry[ii];

		if( chk1 == chk2)
		{
			calc_array[0][inner_idx] += 1;
			calc_array[1][inner_idx] = chk1;
		}
		else if( chk1 != chk2 )
		{
			for(ij = 0; ij < ii; ij++)
			{
				if( calc_array[1][ij] == chk2 )
				{
					find_idx = ij;
					calc_array[0][find_idx] += 1;
					calc_array[1][find_idx] = chk2;
					need_update = 0;
					break;
				}
				need_update = 1;
			}

			if(need_update)
			{
				inner_idx += 1;
				calc_array[0][inner_idx] += 1;
				calc_array[1][inner_idx] = chk2;
			}
		}

		chk1 = chk2;
	}

	max = calc_array[0][0];

	for(ii = 0; ii < cnt; ii++)
	{
		if( max < calc_array[0][ii] )
		{
			max_idx = ii;
			max = calc_array[0][ii];
		}
	}


	//for(ii = 0; ii < cnt; ii++)
	//{
		//printk("[DRV] [ idx %d ] [ num %d ] [ val %x ]\n", ii, calc_array[0][ii], calc_array[1][ii]);
	//}

	//printk("[DRV] [ max_idx : %d ]\n", max_idx);
	//printk("[DRV] [ inner_idx : %d ]\n", inner_idx);

	return calc_array[1][max_idx];
}

void video_input_ahd_tvi_distinguish(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char ch = decoder_info->ch;
	unsigned char devnum = decoder_info->devnum;
	unsigned char fmtdef = decoder_info->fmt_def;
	unsigned char ii;
	unsigned int check_point;

	unsigned char check_time = 10;


#if 1
	unsigned int B5xF5_F4[10];

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x05 + ch);

	for(ii = 0; ii < check_time; ii++)
	{
		msleep(10);
		B5xF5_F4[ii] = ( gpio_i2c_read(raptor3_i2c_addr[devnum], 0xF5) << 8 ) | gpio_i2c_read(raptor3_i2c_addr[devnum], 0xF4);
		//printk("[DRV] [Ch:%d] %d time B5xF3_F4 : %x \n", ch, ii, B5xF5_F4[ii]);
	}

	check_point = __s_distinguish_5M_ahd_tvi_func( B5xF5_F4, check_time );

	if( fmtdef == AHD30_5M_20P )
	{
		if( ( check_point & 0xfff ) == 0x7c2)
		{
			decoder_info->fmt_def = TVI_5M_20P;
			//printk("[DRV] [Ch:%d] Get Format : AHD 5M 20P, Change Format : TVI 5M 20P\n", decoder_info->ch);
		}
		else if( ( check_point & 0xfff ) == 0x7c4)
		{
			decoder_info->fmt_def = CVI_5M_20P;
			printk("[DRV] [Ch:%d] Get Format : AHD 5M 20P, Change Format : TVI 5M 20P\n", decoder_info->ch);
		}
		else
		{
			;//printk("[DRV] [Ch:%d] Get Format : AHD 5M 20P, Not Change Format\n", decoder_info->ch);
		}
	}/*
	else if( fmtdef == CVI_8M_15P)
	{
		if( ( check_point & 0xfff ) == 0x8d0)
		{
			decoder_info->fmt_def = TVI_8M_15P;
			//printk("[DRV] [Ch:%d] Get Format : TVI 8M 15P, Change Format : TVI 8M 15P\n", decoder_info->ch);
		}
		else
		{
			;//printk("[DRV] [Ch:%d] Get Format : CVI 8M 15P, Not Change Format\n", decoder_info->ch);
		}
	}*/
	else if( fmtdef == 0x2B) 
	{
		if( ( check_point & 0xfff ) >= 0x673)
		{
			decoder_info->fmt_def = TVI_4M_15P;
			//printk("[DRV] [Ch:%d] Get Format : AHD 4M15P #0P, Change Format : TVI 4M 15P\n", decoder_info->ch);
		}
	}
	else
	{
		decoder_info->fmt_def = fmtdef;
	}


#else
	unsigned int B5xE8_E9[10] = {0, };
	unsigned int B5xEA_EB[10] = {0, };

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x05 + ch);


	for(ii = 0; ii < check_time; ii++)
	{
	msleep(10);
		B5xE8_E9[ii] = ( gpio_i2c_read(raptor3_i2c_addr[devnum], 0xE8) << 8 ) | gpio_i2c_read(raptor3_i2c_addr[devnum], 0xE9);
		B5xEA_EB[ii] = ( gpio_i2c_read(raptor3_i2c_addr[devnum], 0xEA) << 8 ) | gpio_i2c_read(raptor3_i2c_addr[devnum], 0xEB);
		printk("[DRV] [Ch:%d] %d time 0xE8_0xE9 : %x \n", decoder_info->ch, ii, B5xE8_E9[ii]);
		printk("[DRV] [Ch:%d] %d time 0xEA_0xEB : %x \n", decoder_info->ch, ii, B5xEA_EB[ii]);
	}

	check_point1 = __s_max_min_exclude_avg_func( B5xE8_E9, check_time );
	check_point2 = __s_max_min_exclude_avg_func( B5xEA_EB, check_time );

	printk("[DRV] [Ch:%d] AVG 0xE8_0xE9 : %x \n", decoder_info->ch, check_point1);
	printk("[DRV] [Ch:%d] AVG 0xEA_0xEB : %x \n", decoder_info->ch, check_point2);

	if( ( check_point1 < 0x30 ) && ( check_point2 < 0x30 ) )
	{
		if( fmtdef == AHD30_5M_20P )
		{
			decoder_info->fmt_def = TVI_5M_20P;

			printk("[DRV] [Ch:%d] Get Format : AHD 5M 20P, Change Format : TVI 5M 20P\n", decoder_info->ch);
		}
		else if( fmtdef == AHD30_3M_30P ) /* Not Yet Support , only add item */
		{
			decoder_info->fmt_def = TVI_4M_15P;

			printk("[DRV] [Ch:%d] Get Format : AHD 3M #0P, Change Format : TVI 4M 15P\n", decoder_info->ch);
		}
		else
		{
			decoder_info->fmt_def = fmtdef;
		}
	}
	else
	{
		decoder_info->fmt_def = fmtdef;
	}
#endif
}


void nvp6168_video_input_cvi_tvi_5Mdistinguish(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char ch = decoder_info->ch;
	unsigned char devnum = decoder_info->devnum;
	unsigned char ii;
	unsigned int check_point;

	unsigned char check_time = 10;

	unsigned int B5xF5_F4[10];

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x05 + ch);

	for(ii = 0; ii < check_time; ii++)
	{
		msleep(30);
		B5xF5_F4[ii] = ( gpio_i2c_read(raptor3_i2c_addr[devnum], 0xF5) << 8 ) | gpio_i2c_read(raptor3_i2c_addr[devnum], 0xF4);
		printk("[DRV] [Ch:%d] %d time B5xF3_F4 : %x \n", ch, ii, B5xF5_F4[ii]);
	}

	check_point = __s_distinguish_5M_ahd_tvi_func( B5xF5_F4, check_time );

	if( ( check_point & 0xfff ) == 0x7c4)
	{
		decoder_info->fmt_def = CVI_5M_20P;
		printk("[DRV] [Ch:%d] Get Format : AHD 5M 20P, Change Format : CVI 5M 20P\n", decoder_info->ch);
	}
	else
	{
		decoder_info->fmt_def = TVI_5M_20P;
		printk("[DRV] [Ch:%d] Get Format : AHD 5M 20P, Change Format : TVI 5M 20P\n", decoder_info->ch);

	}
}


unsigned int __s_distinguish_8M_cvi_tvi_func(unsigned int* input_arry, int cnt)
{
	unsigned int chk1, chk2;
	unsigned int max, max_idx = 0;
	unsigned int calc_array[10][10] = { {0, 0},  };
	unsigned int need_update = 0;
	unsigned int find_idx = 0;
	unsigned int ii, ij;
	unsigned int inner_idx = 0;

	chk1 = input_arry[0];

	for(ii = 0; ii < cnt; ii++)
	{
		chk2 = input_arry[ii];

		if( chk1 == chk2)
		{
			calc_array[0][inner_idx] += 1;
			calc_array[1][inner_idx] = chk1;
		}
		else if( chk1 != chk2 )
		{
			for(ij = 0; ij < ii; ij++)
			{
				if( calc_array[1][ij] == chk2 )
				{
					find_idx = ij;
					calc_array[0][find_idx] += 1;
					calc_array[1][find_idx] = chk2;
					need_update = 0;
					break;
				}
				need_update = 1;
			}

			if(need_update)
			{
				inner_idx += 1;
				calc_array[0][inner_idx] += 1;
				calc_array[1][inner_idx] = chk2;
			}
		}

		chk1 = chk2;
	}

	max = calc_array[0][0];

	for(ii = 0; ii < cnt; ii++)
	{
		if( max < calc_array[0][ii] )
		{
			max_idx = ii;
			max = calc_array[0][ii];
		}
	}


	//for(ii = 0; ii < cnt; ii++)
	{
		//printk("[DRV] [ idx %d ] [ num %d ] [ val %x ]\n", ii, calc_array[0][ii], calc_array[1][ii]);
	}

	//printk("[DRV] [ max_idx : %d ]\n", max_idx);
	//printk("[DRV] [ inner_idx : %d ]\n", inner_idx);

	return calc_array[1][max_idx];
}

void video_input_cvi_tvi_distinguish(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char ch = decoder_info->ch;
	unsigned char devnum = decoder_info->devnum;
	unsigned char fmtdef = decoder_info->fmt_def;
	unsigned char ii;
	unsigned int check_point;

	unsigned char check_time = 10;

	unsigned int B13xAB[10];

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x13);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x2B, ch % 4 );
	
	for(ii = 0; ii < check_time; ii++)
	{
		msleep(100);
		B13xAB[ii] = gpio_i2c_read(raptor3_i2c_addr[devnum], 0xAB);
		//printk("[DRV] [Ch:%d] %d time B13xAB : %x \n", ch, ii, B13xAB[ii]);
	}

	check_point = __s_distinguish_8M_cvi_tvi_func( B13xAB, check_time );

	if( fmtdef == CVI_8M_15P || fmtdef == CVI_8M_12_5P )
	{
		if( ( check_point & 0xff ) > 0x1A )
		{
			if( fmtdef == CVI_8M_12_5P )
			{
				decoder_info->fmt_def = TVI_8M_12_5P;
				//printk("[DRV] [Ch:%d] Get Format : CVI 8M 12_5P, Change Format : TVI 8M 12_5P\n", decoder_info->ch);
			}
			else 
			{
				decoder_info->fmt_def = TVI_8M_15P;
				//printk("[DRV] [Ch:%d] Get Format : CVI 8M 15P, Change Format : TVI 8M 15P\n", decoder_info->ch);
			}
		}
		else
		{
			//printk("[DRV] [Ch:%d] Get Format : CVI 8M, Not Change Format\n", decoder_info->ch);
		}
	}
	else
	{
		decoder_info->fmt_def = fmtdef;
	}
}

/******************************************************************************
*	Description		: Get Y plus slope
*	Argurments		: ch : channel number
*	Return value	: Y plus slope value
*	Modify			:
*	warning			:
*******************************************************************************/
unsigned int __get_LE_YPlusSlope(unsigned char ch, unsigned char devnum)
{
	unsigned int y_plus_slp_status;

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF,0x05+ch);
	y_plus_slp_status = gpio_i2c_read(raptor3_i2c_addr[devnum],0xE8)&0x07;
	y_plus_slp_status <<= 8;
	y_plus_slp_status |= gpio_i2c_read(raptor3_i2c_addr[devnum],0xE9);

	return y_plus_slp_status;
}



/******************************************************************************
 *   Description     : Get Y minus slope
 *   Argurments      : ch : channel number
 *   Return value    : Y minus slope value
 *   Modify          :
 *   warning         :
 *******************************************************************************/
unsigned int __get_LE_YMinusSlope(unsigned char ch, unsigned char devnum)
{
	unsigned int y_minus_slp_status;

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF,0x05+ch);
	y_minus_slp_status = gpio_i2c_read(raptor3_i2c_addr[devnum],0xEA)&0x07;
	y_minus_slp_status <<= 8;
	y_minus_slp_status |= gpio_i2c_read(raptor3_i2c_addr[devnum],0xEB);

	return y_minus_slp_status;
}

/******************************************************************************
 *   Description     : Get EQ pattern color gain
 *   Argurments      : ch : channel number
 *   Return value    : EQ pattern color gain value
 *   Modify          :
 *   warning         :
 *******************************************************************************/
unsigned int __get_EQ_AccGain(unsigned char ch, unsigned char devnum)
{
	unsigned int acc_gain_status;

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF,0x05+ch);
	acc_gain_status = gpio_i2c_read(raptor3_i2c_addr[devnum],0xE2) & 0x1f;
	acc_gain_status <<= 8;
	acc_gain_status |= gpio_i2c_read(raptor3_i2c_addr[devnum],0xE3);
	//printk("acc_gain_status    : 0x%x\n", acc_gain_status);
	return acc_gain_status;
}
unsigned int __s_distinguish_ahd_nrt_func(unsigned int* input_arry, int cnt)
{
	unsigned int chk1, chk2;
	unsigned int max, max_idx = 0;
	unsigned int calc_array[10][10] = { {0, 0},  };
	unsigned int need_update = 0;
	unsigned int find_idx = 0;
	unsigned int ii, ij;
	unsigned int inner_idx = 0;

	chk1 = input_arry[0];

	for(ii = 0; ii < cnt; ii++)
	{
		chk2 = input_arry[ii];

		if( chk1 == chk2)
		{
			calc_array[0][inner_idx] += 1;
			calc_array[1][inner_idx] = chk1;
		}
		else if( chk1 != chk2 )
		{
			for(ij = 0; ij < ii; ij++)
			{
				if( calc_array[1][ij] == chk2 )
				{
					find_idx = ij;
					calc_array[0][find_idx] += 1;
					calc_array[1][find_idx] = chk2;
					need_update = 0;
					break;
				}
				need_update = 1;
			}

			if(need_update)
			{
				inner_idx += 1;
				calc_array[0][inner_idx] += 1;
				calc_array[1][inner_idx] = chk2;
			}
		}

		chk1 = chk2;
	}

	max = calc_array[0][0];

	for(ii = 0; ii < cnt; ii++)
	{
		if( max < calc_array[0][ii] )
		{
			max_idx = ii;
			max = calc_array[0][ii];
		}
	}


	//for(ii = 0; ii < cnt; ii++)
	{
		//printk("[DRV] [ idx %d ] [ num %d ] [ val %x ]\n", ii, calc_array[0][ii], calc_array[1][ii]);
	}

	//printk("[DRV] [ max_idx : %d ]\n", max_idx);
	//printk("[DRV] [ inner_idx : %d ]\n", inner_idx);

	return calc_array[1][max_idx];
}


void video_input_ahd_nrt_distinguish(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char ch = decoder_info->ch;
	unsigned char devnum = decoder_info->devnum;
	unsigned char ii;
	unsigned int check_point;

	unsigned char check_time = 10;

	unsigned int B5xF3[10];

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x05 + ch);

	for(ii = 0; ii < check_time; ii++)
	{
		msleep(30);
		B5xF3[ii] = gpio_i2c_read(raptor3_i2c_addr[devnum], 0xF3);
		//printk("[DRV] [Ch:%d] %d time B5xF3 : %x \n", ch, ii, B5xF3[ii]);
	}

	check_point = __s_distinguish_ahd_nrt_func( B5xF3, check_time );

	if( ( check_point & 0xff ) == 0x14 )
	{
		decoder_info->fmt_def = AHD20_1080P_12_5P_EX;
		printk("[DRV] [Ch:%d] Get Format : AHD 1080P 12.5P\n", decoder_info->ch);
	}
	else if( ( check_point & 0xff ) == 0x11 )
	{
		decoder_info->fmt_def = AHD20_1080P_15P_EX;
		printk("[DRV] [Ch:%d] Get Format : AHD 1080P 15P\n", decoder_info->ch);
	}
	else
	{
		decoder_info->fmt_def = NC_VIVO_CH_FORMATDEF_UNKNOWN;
		printk("[DRV] [Ch:%d] Get Format : Unknown Format \n", decoder_info->ch);
	}
}



/***		ºÏ≤‚≈–∂œ «∑ÒŒ™tvi 5M 20P…„œÒÕ∑		***/
unsigned char TVI_5M20P_Detect(unsigned char ch,decoder_dev_ch_info_s *dev_ch_info)
{
	/* Read Bank13 0xA4, 0xA5 ---> integral_status_ahd_vbi[7:0], integral_status_ahd_vbi[15:8]	*/
	/* integral_vbi level is Bank13 0x14														*/
	/* If integral_status_ahd_vbi < threshold ----> TVI_5M_20P
	 * else AHD30_5M_20P Setting
	 */
	// unsigned char ch_mode;;
	//printk("[CH:%d] >> finding format:AHD 5M 20P....\n", ch);
	//printk("[CH:%d] >> finding format:AHD 5M 20P....\n", ch);
	//printk("[CH:%d] >> finding format:AHD 5M 20P....\n", ch);

	//dev_ch_info->fmt_def = ch_mode;
	//NC_VD_VI_AHD_TVI_Ditinguish(&sDevChInfo);
	video_input_ahd_tvi_distinguish(dev_ch_info);

	if( dev_ch_info->fmt_def == TVI_5M_20P )
	{
		;//printk("[CH:%d] >> changing format:TVI 5M 20P....\n", ch);
		//printk("[CH:%d] >> changing format:TVI 5M 20P....\n", ch);
		//printk("[CH:%d] >> changing format:TVI 5M 20P....\n", ch);

		//dev_ch_info->fmt_def = TVI_5M_20P;
		//ch_mode = TVI_5M_20P;
	}
	//ch_mode = dev_ch_info->fmt_def;
	return dev_ch_info->fmt_def;
}

static unsigned char debounceidx[16]={[0 ... 15]=0};
static unsigned char	debounce[16][MAX_DEBOUNCE_CNT]={{0,0}};
/*******************************************************************************
*	Description	: check Auto Debouce
*	Argurments		: ch:channel, pInformation(raptor3 information), videomode(0:novideo, 1:Onvideo)
*	Return value	: 0(not checked video format), -1(checked video format)
*	Modify			: N/A
*	warning			:
*******************************************************************************/
int RS_AutoDebouceCheck( unsigned char ch)
{
	int i,ret=0;
	unsigned char		oDebncIdx = 0;
	unsigned char		oVfc = 0;
	NC_VIVO_CH_FORMATDEF oFmtB5Def;
	video_input_vfc	sVFC;

	sVFC.ch= ch % 4;
	sVFC.devnum= ch / 4;
	video_input_onvideo_check_data_bank5(&sVFC);

	oDebncIdx = debounceidx[ch];
	debounce[ch][oDebncIdx%MAX_DEBOUNCE_CNT] = sVFC.vfc;

	debounceidx[ch]++;
	debounceidx[ch] = ((debounceidx[ch] % MAX_DEBOUNCE_CNT) == 0) ? 0 : debounceidx[ch];

	oVfc = debounce[ch][debounceidx[ch]];
	for( i = 0; i < MAX_DEBOUNCE_CNT; i++ )
	{
		if( oVfc != debounce[ch][i])
		{
			break;
		}
	}
	if( i == MAX_DEBOUNCE_CNT )
	{
		oFmtB5Def = RS_VD_AUTO_VFCtoFMTDEF(sVFC.vfc);
			
		if(((oFmtB5Def != AHD30_5M_20P) && (oFmtB5Def != CVI_8M_15P) && \
			(oFmtB5Def != CVI_8M_12_5P) && (oFmtB5Def != CVI_HD_30P_EX) /*&& \
			(oFmtB5Def != AHD20_1080P_25P) && (oFmtB5Def != AHD20_1080P_30P)*/) && (oFmtB5Def != videofmt_vfc[ch]) 
			)	// ahd 2mp 15pÊó∂Ê≥®ÊÑè
		{
			printk("\033[2;34m Fun:%s Line:%d oFmtB5Def:%d preB5Def:%#x\033[0;39m \n",__FUNCTION__,__LINE__,oFmtB5Def,videofmt_vfc[ch]);
			ret= -1;
			//videofmt_vfc[ch]= oFmtB5Def;
			//RS_AUTO_VFCtoFMTDEF(ch,videofmt_vfc[ch]);
		}
	}

	return ret;
}


/*******************************************************************************
*	Description		: Get video format bank13(each ch)
*	Argurments		: 
*	Return value	: N/A
*	Modify			:
*	warning			:
*******************************************************************************/
int RS_GetFormat_Bank5_EachCh( unsigned char ch)
{
	int ii = 0;
	int ret;
	int retry_cnt = 0;
	video_input_vfc sVFC;
	NC_VIVO_CH_FORMATDEF oCurVidFmt = NC_VIVO_CH_FORMATDEF_UNKNOWN;
	unsigned char curvideoloss[16] = {[0 ... 15]=VIDEO_LOSS_OFF};
	decoder_dev_ch_info_s decoder_info;
	video_input_novid  vin_novid;
	unsigned char vfc_tmp;
	NC_VI_CH_FMT_S		*pChFmt=NULL;
	NC_FORMAT_STANDARD	 eFmtStd;

	video_input_vfc sVFC_B13,sVFC_B5;
	decoder_dev_ch_info_s sDevChInfo;

	/* initialize vfc(B5xF0) and videoloss information(B0xA8) */
	sVFC.ch = ch%4;
	sVFC.devnum= ch/4;

	/* get vfc and videoloss */
	video_input_onvideo_check_data(&sVFC);		//VFC≈–∂œ

	vin_novid.ch = ch%4 ;
	//vin_novid.ch = (ch/4)*4+AHD_VIDEOLOSS[ch%4];
	vin_novid.devnum = ch/4;
	video_input_novid_read(&vin_novid);


	/* check vfc&videoloss and run debounce  */
	if(((((sVFC.vfc>> 4 ) & 0xF) != 0xF) && ((sVFC.vfc& 0x0F) != 0xF)) && (!vin_novid.novid)) // OnVideo
	{
		/* convert vfc to formatDefine for APP and save videoloss information */
		oCurVidFmt = RS_VD_AUTO_VFCtoFMTDEF(sVFC.vfc);
	}
	/* check novideo option */
	if(!vin_novid.novid)
	{
		curvideoloss[ch] = VIDEO_LOSS_ON;
	}

	//if(app_curvideofmt[ch] == AT_A_INPUT_VIDEOFMT_720P_30FPS )		//AHD 720P N÷∆ µ⁄2¥Œº∞“‘∫Û ∂º◊ﬂ’‚±ﬂ(app_curvideofmt[ch]Œ™µ⁄1¥Œdetect∫Û±£¥Ê)
	{
		;//printk("\033[1;34m ----------AHD 720P N--------- \033[0;39m \n ");
	}
	//else
	{
		/* check vfc&videoloss and run debounce  */
		if(curvideoloss[ch] == VIDEO_LOSS_ON)
		{
			//if(oCurVidFmt != NC_VIVO_CH_FORMATDEF_UNKNOWN)
			if((oCurVidFmt != NC_VIVO_CH_FORMATDEF_UNKNOWN) && (videofmt_vfc[ch] == NC_VIVO_CH_FORMATDEF_UNKNOWN))
			{			
				//oCurVidFmt = RS_VD_AUTO_VFCtoFMTDEF(sVFC.vfc);
				if(oCurVidFmt == AHD30_5M_20P)
				{
					decoder_info.ch = ch%4;
					decoder_info.devnum = ch/4;
					decoder_info.fmt_def = oCurVidFmt;
					oCurVidFmt =TVI_5M20P_Detect(ch,&decoder_info);
				}
				else if( oCurVidFmt == CVI_8M_15P || oCurVidFmt == CVI_8M_12_5P )
				{
					decoder_info.ch = ch%4;
					decoder_info.devnum = ch/4;
					decoder_info.fmt_def = oCurVidFmt;

					//video_input_cvi_tvi_distinguish(&decoder_info);
					if(vdec == VDEC_RAPTOR3)
					{
						video_input_cvi_tvi_distinguish(&decoder_info);
					}
					else
					{
						nvp6168_video_input_cvi_tvi_5Mdistinguish(&decoder_info);
					}
					oCurVidFmt = decoder_info.fmt_def;

					if( oCurVidFmt == TVI_8M_15P )
					{
						;//printk("[CH:%d] >> changing format:TVI 8M 15P....\n", ch);
					}
					else if( oCurVidFmt == TVI_8M_12_5P )
					{
						;//printk("[CH:%d] >> changing format:TVI 8M 12_5P....\n", ch);
					}
				}
				#if 0
				else if( oCurVidFmt == AHD20_720P_30P_EX_Btype/* || oFmtDef == CVI_HD_30P_EX*/)
				{
					if(CVI_720P30[ch] == 0)
					{
						oCurVidFmt = CVI_HD_30P_EX;
						CVI_720P30[ch] = 1;
					}
				}	
				#endif

				if( sVFC.vfc == 0x2B)
				{
					//try to distinguish TVI 4M15P 
					decoder_info.ch = ch%4;
					decoder_info.devnum = ch/4;
					decoder_info.fmt_def = oCurVidFmt;
					video_input_ahd_tvi_distinguish(&decoder_info);
					oCurVidFmt = decoder_info.fmt_def;

					if( oCurVidFmt == TVI_4M_15P )
					{
						pChFmt = (NC_VI_CH_FMT_S *)RS_HI_VI_Get_ChannelFormat( oCurVidFmt );
						eFmtStd = pChFmt->format_standard;
						if ((eFmtStd == FMT_AUTO) ||(eFmtStd == FMT_TVI))
						{
							;//printk("[CH:%d] >> changing format:TVI 4M 15P....\n", ch);
							;//printk("[CH:%d] >> changing format:TVI 4M 15P....\n", ch);
							;//printk("[CH:%d] >> changing format:TVI 4M 15P....\n", ch);
							oCurVidFmt = TVI_4M_15P;
						}
						else
							oCurVidFmt = NC_VIVO_CH_FORMATDEF_UNKNOWN;
					}
				}
			
				videofmt_vfc[ch]= oCurVidFmt;
				RS_AUTO_VFCtoFMTDEF(ch,videofmt_vfc[ch]);
				return 0;
			}
			else if((oCurVidFmt == NC_VIVO_CH_FORMATDEF_UNKNOWN) && (videofmt_vfc[ch] == NC_VIVO_CH_FORMATDEF_UNKNOWN))		// videofmt_vfc[ch]±£¥Ê…œ¥Œµƒ÷µ
			{
					/* AHD 1080P, 720P NRT Detection Part */
					/*
					1. Check Bank13 0xF0
					2. Check NoVideo Register ( Bank0 0xA8 )
					3. Set Value 0x7f to Bank5 0x82
					4. Read Bank13 0xf0
					5. Read Bank5 0xf0
					6. Check H Count
					7. AHD 1080P or 720P Set
					8. Set value 0x00 to bank5 0x82
					*/					
				sVFC_B13.ch= ch%4;
				sVFC_B13.devnum= ch/4;
				sVFC_B5.ch= ch%4;
				sVFC_B5.devnum= ch/4;

				sDevChInfo.ch= ch%4;
				sDevChInfo.devnum= ch/4;

				video_input_manual_agc_stable_endi(&sDevChInfo,1);		//enable agc stable

				for(ii = 0; ii < 20; ii++ )
				{
					if((chip_id[sVFC_B13.devnum] == RAPTOR4_4PORT_R0_ID) || \
						(chip_id[sVFC_B13.devnum] == RAPTOR4_2PORT_R0_ID))
					{
						nvp6168_video_input_vfc_read(&sVFC_B13);
					}
					else
					{
						video_input_vfc_read(&sVFC_B13);
					}
					video_input_onvideo_check_data_bank5(&sVFC_B5);

					if( ((sVFC_B5.vfc>> 4) & 0xf ) != 0x3)
					{
						msleep(50);
						//printk("[APP] CH[%d] 0xff [%d] \n", ch%4, retry_cnt );
						if(retry_cnt > 10)	//B5_0xf0 –Ë“ª∂Œ ±º‰≤≈ƒ‹ºÏ≤‚µΩ¿‡–Õ
							break;
					}

					if( sVFC_B13.vfc== 0x2b && sVFC_B5.vfc== 0x3f)
					{
						//printk("[DRV] CH[%d] Bank13 0xF0 [%02x], Bank5 0xF0[%02x]\n", ch%4, sVFC_B13.vfc, sVFC_B5.vfc);
						//printk("[DRV] CH[%d] AFHD 15P or 12.5P [%d]\n" , ch%4, retry_cnt );
						break;
					}
					else if( ( sVFC_B5.vfc!= 0x3f ) &&  sVFC_B13.vfc!= 0x2b )
					{
						;//printk("[APP] CH[%d] Bank13 0xF0 [%02x], Bank5 0xF0[%02x]\n", ch%4, sVFC_B13.vfc, sVFC_B5.vfc);
						;//printk("[APP] CH[%d] Unknown Status [%d] \n", ch%4, retry_cnt );
					}

					if(retry_cnt >= 20 )
					{
						printk("CH[%d] AHD 1080P, 720P NRT Disitinguish Finished ...\n", ch%4 );
						break;
					}

					retry_cnt++;
					msleep(33);
				}

				if( ((sVFC_B5.vfc >> 4) & 0xf ) != 0x3)
				{
					videofmt_vfc[ch] = NC_VIVO_CH_FORMATDEF_UNKNOWN;
					//return 0;
				}
				else
				{
					video_input_ahd_nrt_distinguish( &sDevChInfo );

					if( sDevChInfo.fmt_def == NC_VIVO_CH_FORMATDEF_UNKNOWN )
					{
						printk("[DRV] CH[%d] unknown format \n", ch);
					}
					else
					{
						oCurVidFmt = sDevChInfo.fmt_def;
					
						videofmt_vfc[ch]= oCurVidFmt;
						RS_AUTO_VFCtoFMTDEF(ch,videofmt_vfc[ch]);
						//printk("\033[1;34m ----------AT_A_INPUT_VIDEOFMT_1080P_NRT--------- \033[0;39m \n ");
						return 0;
					}
				}
			}
			else	//debounce
			{
									
				/* check debouce video format(-1:changed, 0:not checked) when you changed video format(Dahua-NVP2450). */
				ret = RS_AutoDebouceCheck(ch);

				if( ret == -1 )
				{
					sDevChInfo.ch= ch % 4;
					sDevChInfo.devnum= ch/4;
					sDevChInfo.fmt_def = NC_VIVO_CH_FORMATDEF_UNKNOWN;

					//NC_VD_AUTO_CONTRAST_OFF(&sDevChInfo);

					/* hide decoder */
					//NC_VD_VO_Auto_Data_Mode_Set( oLogicalChannel, oDevNum,  OUT_MODE_OFF );

					/* decoder afe power down */
					//NC_VD_AUTO_AFE_DOWN(&sDevChInfo);
					video_input_vafe_control(&sDevChInfo,0);
					
					/* set no video- first(i:channel, raptor3_vfmts:information */
					//RAPTOR3_SAL_NoVIdeoSetFormat( oLogicalChannel, &s_raptor3_vfmts );
					RS_NoVIdeoSetFormat(ch, CVI_HD_30P_EX);

					//NC_VD_AUTO_AFE_UP(&sDevChInfo);
					video_input_vafe_control(&sDevChInfo,1);

					/* for forced agc stable */
					//NC_VD_AUTO_MANUAL_AGC_STABLE_ENABLE(&sDevChInfo);
					//video_input_manual_agc_stable_endi(&sDevChInfo,1);
					msleep(500);

					/* save onvideo to prevideofmt */
					videofmt_vfc[ch] = NC_VIVO_CH_FORMATDEF_UNKNOWN;
					RS_AUTO_VFCtoFMTDEF(ch,videofmt_vfc[ch]);
					//printk(">>>>> CH[%d], Reset, Set No video : 0x%02X\n", ch, videofmt_vfc[ch]);
				}
			}
		}
	}
	/* check novideo option *///ºÏ≤ÈŒﬁ ”∆µ
	if(!vin_novid.novid)		//on video
	{
		gpio_i2c_write(raptor3_i2c_addr[sVFC.devnum], 0xFF, 0x05 + sVFC.ch);
		vfc_tmp = gpio_i2c_read(raptor3_i2c_addr[sVFC.devnum], 0xF0);
		if((((vfc_tmp >> 4 ) & 0xF) == 0xF) || ((vfc_tmp & 0x0F) == 0xF))
		{
			videofmt_vfc[ch] = NC_VIVO_CH_FORMATDEF_UNKNOWN;
			//printk("\033[1;34m ----------ch[%d]:0x%x  video:%d --------- \033[0;39m \n ",sVFC.ch,sVFC.vfc,vin_novid.novid);
			RS_AUTO_VFCtoFMTDEF(ch,videofmt_vfc[ch]);
		}
	}
	else		//no video
	{
		videofmt_vfc[ch] = NC_VIVO_CH_FORMATDEF_UNKNOWN;
		RS_AUTO_VFCtoFMTDEF(ch,videofmt_vfc[ch]);
	}
	return 0;
}



/**************************************************************************************
* @desc
* 	Function to read cable distance for EQ setting according to cable distance.(manual)
*
* @param_in		(unsigned char)Ch						Video Channel
*
* @return   	(CABLE_DISTANCE) 0				Short ( < 2M )
* @return   	1								100M
* @return   	2								200M
* @return   	3								300M
* @return   	4								400M
* @return   	5								500M
***************************************************************************************/
#define MAX_EQ_COUNT 10
#define CHANNEL_COUNT 4

CABLE_DISTANCE RS_APP_VD_MANUAL_CABLE_DISTANCE_Get(unsigned char Ch, NC_VIVO_CH_FORMATDEF FmtDef )
{
	unsigned int Waiting_AGC_Stable_cnt = 0;
	unsigned char oChannel = 0;
	CABLE_DISTANCE Distance;
	unsigned char oMaxTimeCnt = 20;			// 20
	video_input_hsync_accum Hsync_Accumulation;
	video_input_sam_val SAM;
	video_input_agc_val AGC;
	RS_VD_AUTO_CABLE_DIST_STR Cable_Distance;
	video_input_cable_dist sManualDistance;
	static int a=0,b=0,c=0,d=0;
	static unsigned int sync_ref[4][MAX_EQ_COUNT]={{0,0}},sync_max[4]={0},sync_max_aver,sync_min[4]={0},sync_min_aver;

	unsigned char oDevAddr = 0x00;
	unsigned int AGC_Stable_Check = 0;
	//unsigned char vfc_count=0;
	video_input_vfc sVFC;
	unsigned char eq_videoloss=0xff;

	sVFC.ch = Ch%4;
	sVFC.devnum= Ch/4;

	oChannel = Ch % 4;
	oDevAddr = Ch / 4;

	SAM.ch = oChannel;
	SAM.devnum= oDevAddr;
	Hsync_Accumulation.ch= oChannel;
	Hsync_Accumulation.devnum= oDevAddr;
	AGC.ch = oChannel;
	AGC.devnum= oDevAddr;
	Cable_Distance.Ch = oChannel;
	Cable_Distance.devnum = oDevAddr;

	while(1)
	{
		//usleep(300*1000);
		msleep(300);
#if 1
		gpio_i2c_write(raptor3_i2c_addr[sVFC.devnum], 0xFF, 0x05 + sVFC.ch);
		sVFC.vfc = gpio_i2c_read(raptor3_i2c_addr[sVFC.devnum], 0xF0);
		gpio_i2c_write(raptor3_i2c_addr[sVFC.devnum], 0xFF, 0x00);
		eq_videoloss = gpio_i2c_read(raptor3_i2c_addr[sVFC.devnum], 0xa8);
		
		if(sVFC.vfc == 0xFF && (eq_videoloss &(1<< sVFC.ch)) != 0)
		{
			printk("\033[1;34mCH:[%d] read bank5 f0:%#x fail[%d]times!\033[0;39m \n", Ch,sVFC.vfc,eq_videoloss);
			break;
		}

#else
		gpio_i2c_write(raptor3_i2c_addr[sVFC.devnum], 0xFF, 0x05 + sVFC.ch);
		sVFC.vfc = gpio_i2c_read(raptor3_i2c_addr[sVFC.devnum], 0xF0);
		//video_input_onvideo_check_data(&sVFC);		//—≠ª∑π˝≥Ã÷–…„œÒÕ∑±ª∞Œ≥ˆ  ÷±Ω”Ã¯≥ˆ—≠ª∑
		if(sVFC.vfc == 0xFF)
		{
		
			printk("\033[1;34mCH:[%d] sVFC.devnum:%d,sVFC.ch,%d,bank5 f0:0x%x fail times!   Waiting_AGC_Stable_cnt:%d \033[0;39m \n", Ch,sVFC.devnum,sVFC.ch,sVFC.vfc ,Waiting_AGC_Stable_cnt);

			msleep(500);
			gpio_i2c_write(raptor3_i2c_addr[sVFC.devnum], 0xFF, 0x05 + sVFC.ch);
			sVFC.vfc = gpio_i2c_read(raptor3_i2c_addr[sVFC.devnum], 0xF0);
			printk("\033[1;34mCH:[%d] =======sVFC.devnum:%d,sVFC.ch,%d,bank5 f0:0x%x fail times!   Waiting_AGC_Stable_cnt:%d \033[0;39m \n", Ch,sVFC.devnum,sVFC.ch,sVFC.vfc ,Waiting_AGC_Stable_cnt);
			break;			
		}
#endif
		RS_VD_AUTO_SAM_Get(oChannel, &SAM);
		RS_VD_AUTO_HSYNC_Get(oChannel, &Hsync_Accumulation);
		RS_VD_AUTO_AGC_Get(oChannel, &AGC);
		RS_VD_AUTO_ACC_GAIN_Get(Ch, ACC_GAIN_NORMAL);

		AGC_Stable_Check = ((Hsync_Accumulation.hsync_accum_result!= 0) && (SAM.sam_val!= 0));

		if(AGC_Stable_Check || Waiting_AGC_Stable_cnt >= oMaxTimeCnt)
		{
			/* temp  by edward */
			//usleep(500*1000);
			msleep(500);
			RS_VD_AUTO_HSYNC_Get(oChannel, &Hsync_Accumulation);
			RS_VD_AUTO_AGC_Get(oChannel, &AGC);
			RS_VD_AUTO_SAM_Get(oChannel, &SAM);

			if(Waiting_AGC_Stable_cnt >= oMaxTimeCnt)
			{
				printk("CH:[%d] AGC Stable Fail\n", oChannel);
			}
			else
			{
				;//printk("CH:[%d] AGC Stable Success.\n", oChannel);
				if(Hsync_Accumulation.hsync_accum_result)
				{
					if((oChannel == 0) && (a < MAX_EQ_COUNT))
						sync_ref[oChannel][a++]=Hsync_Accumulation.hsync_accum_result;
					else if((oChannel == 1) && (b < MAX_EQ_COUNT))
						sync_ref[oChannel][b++]=Hsync_Accumulation.hsync_accum_result;
					else if((oChannel == 2) && (c < MAX_EQ_COUNT))
						sync_ref[oChannel][c++]=Hsync_Accumulation.hsync_accum_result;
					else if((oChannel == 3) && (d < MAX_EQ_COUNT))
						sync_ref[oChannel][d++]=Hsync_Accumulation.hsync_accum_result;
					
					if(((a == MAX_EQ_COUNT) && (b == MAX_EQ_COUNT) && (c == MAX_EQ_COUNT) && (d == MAX_EQ_COUNT)))
					{
						for(b=0;b<CHANNEL_COUNT;b++)
						{
							sync_min[b]=0xffffffff;
							sync_max[b]=0x00000000;
							for(a=0;a < MAX_EQ_COUNT;a++)
							{
								sync_min[b]=sync_min[b]>sync_ref[b][a]?sync_ref[b][a]:sync_min[b];
								sync_max[b]=sync_max[b]<sync_ref[b][a]?sync_ref[b][a]:sync_max[b];
							}
							printk("sync_min[%d]=%08x\n",b,sync_min[b]);
							printk("sync_max[%d]=%08x\n",b,sync_max[b]);
							sync_min_aver += sync_min[b];
							sync_max_aver += sync_max[b];
						}
						sync_min_aver = sync_min_aver/4;
						sync_max_aver = sync_max_aver/4;
						printk("sync_min_aver=%08x\n",sync_min_aver);
						printk("sync_max_aver=%08x\n",sync_max_aver);
						a=0,b=0,c=0,d=0,sync_min_aver=0,sync_max_aver=0;
						
					}
					else
					{
							printk("channel = %d\na = %d\n",oChannel,a);
							printk("b = %d\n",b);
							printk("c = %d\n",c);
					
					}		printk("d = %d\n",d);
				}
			}
			Waiting_AGC_Stable_cnt = 0;
			break;
		}

		Waiting_AGC_Stable_cnt++;
	}

	/* convert vfc to formatDefine for APP and save videoloss information */
	sManualDistance.ch= oChannel;
	sManualDistance.FmtDef= FmtDef;
	sManualDistance.devnum= oDevAddr;
	sManualDistance.cabletype= 0; 		// Now, we use coaxial cable(0:coax, 1:utp, 2:reserved1, 3:reserved2

	Distance = RS_VD_MANUAL_CABLE_DISTANCE_Get(Ch, &sManualDistance);		//ªÒ»°EQµ»º∂

	return Distance;
}

// 170207 SAM register read
void RS_VD_AUTO_SAM_Get (unsigned char Ch, video_input_sam_val *pSAM)
{
	// (Hsync Accumulation 1 - Hsync Accumulation 2) / AGC(Auto Gain Control) Value Read
	video_input_sam_val_read(pSAM);
																								
	if(pSAM->sam_val!= 0)
	{
		;//printk("[%d CH] SAM : %3x\n",Ch, pSAM->sam_val);
	}
	else
	{
		;//printk("[%d CH] SAM : Error [%d]\n",Ch, pSAM->sam_val);
	}
}

// 170207 Hsync Accumulation register read
void RS_VD_AUTO_HSYNC_Get (unsigned char Ch, video_input_hsync_accum* pHsync)
{
	if(info.author == AHD_NVP6168 || info.author == AHD_NVP6168C)
	{
		nvp6168_video_input_hsync_accum_read(pHsync);
	}
	else
	{
		video_input_hsync_accum_read(pHsync);
	}
	
	if(pHsync->hsync_accum_result!= 0 && pHsync->h_lock)
	{
		;//printk("[%d CH] Hsync 1 : %08x\n", Ch, pHsync->hsync_accum_val1);
		;//printk("[%d CH] Hsync 2 : %08x\n", Ch, pHsync->hsync_accum_val2);
		;//printk("[%d CH] Hsync Result : %08x\n", Ch, pHsync->hsync_accum_result);
	}
	else
	{
		;//printk("h_lock:%x", pHsync->h_lock);
	}

}

// 170207 AGC register read
void RS_VD_AUTO_AGC_Get (unsigned char Ch, video_input_agc_val* pAGC)
{
	video_input_agc_val_read(pAGC);						// Auto Gain Control Value Read

	if(pAGC->agc_val!= 0 && pAGC->agc_lock)
	{
		;//printk("AGC : %2x", pAGC->agc_val);
		;//printk("AGClock : %x", pAGC->agc_lock);
	}
	else
	{
		;//printk("[%d CH] AGC : %x\n",Ch, pAGC->agc_val);
	}

}

//*******************************************************************************//
//
//				Verification Code
//
//
//*******************************************************************************//
void RS_VD_AUTO_ACC_GAIN_Get(unsigned char Ch, ACC_DEBUG FuncSel)
{
	video_input_acc_gain_val ACC;

	ACC.ch= Ch % 4;
	ACC.devnum= Ch / 4;
	ACC.func_sel= FuncSel;

	// DEBUG
	video_input_acc_gain_val_read(&ACC);
	//printk("SAM ACC : %3x",ACC.acc_gain_val);

	if(FuncSel == ACC_GAIN_NORMAL)		// B5 0xE2 [10:8] 0xE3[7:0] ACC Gain Register
		;//printk("CH:[%d] ACC GAIN : %3x\n", Ch, ACC.acc_gain_val);
	else if(FuncSel == ACC_GAIN_DEBUG)	// B13 0xC6 [9:8] 0xC7[7:0] ACC Gain Debug Register
		printk("CH:[%d] SAM ACC GAIN : %3x\n", Ch, ACC.acc_gain_val);
	else
		printk("CH:[%d] ACC GAIN : %3x\n", Ch, ACC.acc_gain_val);
}

/*******************************************************************************
*	Description		: get eq stage(manual)
*	Argurments		: Ch(channel), pDistance(distance structure)
*	Return value	: distance( eq stage)
*	Modify			:
*	warning			:
*******************************************************************************/
CABLE_DISTANCE RS_VD_MANUAL_CABLE_DISTANCE_Get (unsigned char Ch, video_input_cable_dist *pDistance)
{
	unsigned char sGetDistCnt = 0;
	unsigned char sGetDist[10] = {0, };
	unsigned char sMaxGetDistVal;
	unsigned char sMaxDistVal;
	unsigned char ii;
	video_input_vfc sVFC;
	unsigned char eq_videoloss=0xff;
	int sMaxDistCnt;

	if((chip_id[Ch/4] == RAPTOR4_4PORT_R0_ID) || (chip_id[Ch/4] == RAPTOR4_2PORT_R0_ID))
	{
		sMaxDistCnt = 3;
	}
	else
	{
		sMaxDistCnt = 10;
	}
	
	sVFC.ch = Ch%4;
	sVFC.devnum= Ch/4;
	
	/* Get Distance 10 Times */
	while(sGetDistCnt < sMaxDistCnt)			// 10
	{
		//usleep(10);
		msleep(1);

		//…Ë÷√EQ ±£¨»ÙBNC∞Œ≥ˆ£¨÷±Ω”ÕÀ≥ˆ
		gpio_i2c_write(raptor3_i2c_addr[sVFC.devnum], 0xFF, 0x05 + sVFC.ch);
		sVFC.vfc = gpio_i2c_read(raptor3_i2c_addr[sVFC.devnum], 0xF0);
		gpio_i2c_write(raptor3_i2c_addr[sVFC.devnum], 0xFF, 0x00);
		eq_videoloss = gpio_i2c_read(raptor3_i2c_addr[sVFC.devnum], 0xa8);
		
		if(sVFC.vfc == 0xFF && (eq_videoloss &(1<< sVFC.ch)) != 0)
		{
			printk("\033[1;34mCH:[%d] cann't detect the video_type!bank5_f0[%#x]\033[0;39m \n", Ch,sVFC.vfc);
			return 0;
		}
		
		/*video_input_onvideo_check_data(&sVFC);
		if(sVFC.vfc == 0xFF)
		{
			break;
		}*/

		if((chip_id[Ch/4] == RAPTOR4_4PORT_R0_ID) || (chip_id[Ch/4] == RAPTOR4_2PORT_R0_ID))
		{
			nvp6168_video_input_cable_manualdist_read(pDistance);
			if(pDistance->dist == 0xFF)
			{
				return pDistance->dist;
			}
		}
		else
		{
			video_input_cable_manualdist_read(pDistance);
		}
		
		sGetDist[ pDistance->dist]++;
		sGetDistCnt++;
	}

	sMaxDistVal = sGetDist[0];
	sMaxGetDistVal = 0;

	for(ii = 1; ii < 9; ii++)
	{
		if( sMaxDistVal < sGetDist[ii] )
		{
			sMaxDistVal = sGetDist[ii];
			sMaxGetDistVal = ii;
		}
	}

	
	printk("TESTING... Get Distance Value : ");
	for(ii = 0; ii < 9; ii++)
		printk("[ stage: %d _ get_value: %d ]\n", ii, sGetDist[ii]);

	return sMaxGetDistVal;
}

