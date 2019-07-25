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
#include <linux/string.h>
#include <linux/delay.h>
#include "common.h"
#include "video_input.h"
#include "video_input_table.h"
#include "gpio_i2c.h"

extern unsigned int raptor3_i2c_addr[4];

void video_input_format_set(decoder_dev_ch_info_s *pDevChInfo)
{
	unsigned char val_5678x69;
	video_input_basic_vfmt_init_s vfmt = (video_input_basic_vfmt_init_s) decoder_basic_vfmt_fmtdef [pDevChInfo->fmt_def];

	if(pDevChInfo->ch>3)
	{
		printk("[DRV] %s CHID Error\n", __func__);
		return;
	}



	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x08 + pDevChInfo->ch, vfmt.video_format);		//Video Format
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x85 + pDevChInfo->ch, vfmt.spl_mode);	//Special Mode
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x81 + pDevChInfo->ch, vfmt.sd_ahd_mode); 	//SD_MODE[7:4] AHD_MODE[3:0]

	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x05 + pDevChInfo->ch);
	val_5678x69 = gpio_i2c_read(raptor3_i2c_addr[pDevChInfo->devnum], 0x69);
	val_5678x69 &= (~0x1);
	val_5678x69 |= (vfmt.sd_freq_sel & 0x1);
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x69, val_5678x69);
}

void video_input_chroma_set(decoder_dev_ch_info_s *pDevChInfo)
{
	video_input_basic_chroma_init_s chroma = (video_input_basic_chroma_init_s) decoder_basic_chroma_fmtdef[pDevChInfo->fmt_def];

	if(pDevChInfo->ch>3)
	{
		printk("[DRV] %s CHID Error\n", __func__);
		return;
	}


	//B0
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x00);
	//PALK_CM_OFF B0 0x21/5/9/d
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x21 + (pDevChInfo->ch*4), chroma.pal_cm_off);
	//B5/6/7/8
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x05 + pDevChInfo->ch);
	//S_POINT 		B5/6/7/8 0x28
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x28, chroma.s_point);			// 170213 Fixed 0x25 -> 0x28
	//FSC_LOCK_MODE B5/6/7/8 0x25
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x25, chroma.fsc_lock_mode);
	//COMB_MODE B5/6/7/8 0x90
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x90, chroma.comb_mode);
}

void video_input_h_timing_set(decoder_dev_ch_info_s *pDevChInfo)
{
	unsigned char val_0x54;
	video_input_basic_timing_init_s h_timing = (video_input_basic_timing_init_s)decoder_basic_timing_fmtdef[ pDevChInfo->fmt_def ];

	if(pDevChInfo->ch>3)
	{
		printk("[DRV] %s CHID Error\n", __func__);
		return;
	}


	//B0
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x00);
	//H_DELAY_LSB B0 0x58/9/a/b
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x58 + pDevChInfo->ch, h_timing.h_delay_lsb);
	//H_MASK_OB B0 0x89/a/b/c
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x89 + pDevChInfo->ch, h_timing.h_mask_on);
	//H_MASK_SEL B0 0x8E/F/90/91
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x8e + pDevChInfo->ch, h_timing.h_mask_sel);

	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xA0 + pDevChInfo->ch, h_timing.v_blk_end_b);

	val_0x54 = gpio_i2c_read(raptor3_i2c_addr[pDevChInfo->devnum], 0x54);
	val_0x54 &= ~((0x1) << (pDevChInfo->ch + 4));
	val_0x54 |= ((h_timing.fld_inv & 0x1) << (pDevChInfo->ch + 4));

	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x54, val_0x54);

	//B5/6/7/8
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x05 + pDevChInfo->ch);
	//SYNC_RS B5/6/7/8 0x47
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x47, h_timing.sync_rs);
	//MEM_RDP B5/6/7/8 0x64
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x64, h_timing.mem_rdp);

	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xA9, h_timing.v_blk_end_b);
}

void video_input_h_scaler_mode_set(decoder_dev_ch_info_s *pDevChInfo)
{
	video_input_basic_hscaler_mode_init_s h_scaler_mode = (video_input_basic_hscaler_mode_init_s) decoder_basic_hscaler_fmtdef[ pDevChInfo->fmt_def ];
	if(pDevChInfo->ch>3)
	{
		printk("[DRV] %s CHID Error\n", __func__);
		return;
	}


	//B0
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x00);
	//LINE_MEM_MODE B0 0x34/5/6/7
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x34 + pDevChInfo->ch, h_scaler_mode.line_mem_mode);
	//B9
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x09);
	//H_DOWN_SCALER	B9 0x96/b6/d6/f6
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x96 + (pDevChInfo->ch * 0x20), h_scaler_mode.h_down_scaler);
	//H_SCALER_MODE	B9 0x97/b7/d7/f7
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x97 + (pDevChInfo->ch * 0x20), h_scaler_mode.h_scaler_mode);
	//REF_BASE_LSB	B9 0x98/b8/d8/f8
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x98 + (pDevChInfo->ch * 0x20), h_scaler_mode.ref_base_lsb);
	//REF_BASE_MSB	B9 0x99/b9/d9/f9
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x99 + (pDevChInfo->ch * 0x20), h_scaler_mode.ref_base_msb);
}

void video_input_hpll_set(decoder_dev_ch_info_s *pDevChInfo)
{
	video_input_basic_hpll_init_s hpll = (video_input_basic_hpll_init_s) decoder_basic_hpll_fmtdef[ pDevChInfo->fmt_def ];
	if(pDevChInfo->ch>3)
	{
		printk("[DRV] %s CHID Error\n", __func__);
		return;
	}


	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xFF, 0x05 + pDevChInfo->ch);

	//B5/6/7/8 0x50 DECI_BYPASS, HPLL_MASK_ON
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0x50, hpll.hpll_mask_on);
	// unsigned char op_md;   					//B5/6/7/8 0xB8
	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xB8, hpll.hafc_op_md);

	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xBB, hpll.hafc_byp_th_e);

	gpio_i2c_write(raptor3_i2c_addr[pDevChInfo->devnum], 0xB7, hpll.hafc_byp_th_s);
}

void video_input_vafe_init(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char val_5678x00;
	unsigned char val_5678x01;
	unsigned char val_5678x58;
	unsigned char val_5678x59;
	unsigned char val_5678x5B;
	unsigned char val_5678x5C;

	video_input_vafe_init_s afe = (video_input_vafe_init_s) decoder_afe_fmtdef [decoder_info->fmt_def];

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x00);

	//B0 0x00/1/2/3 gain[4], powerdown[0]
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00 + decoder_info->ch, ((afe.gain & 0x01) << 4) | (afe.powerdown & 0x01));

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x84 + decoder_info->ch, 0x00);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//B5/6/7/8
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x05 + decoder_info->ch);

	//B5/6/7/8 0x01 spd[2], lpf_back_band[1:0]
	val_5678x00 = gpio_i2c_read(raptor3_i2c_addr[decoder_info->devnum], 0x00);
	val_5678x00 |= (afe.spd << 4);

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x00, val_5678x00);

	val_5678x01 = ((afe.ctrlreg << 6) | (afe.ctrlibs << 4) | (afe.adcspd << 2) | (afe.clplevel));
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x01, val_5678x01 );

	//B5/6/7/8 0x58 eq_band[7:4], lpf_front_band[1:0]
	val_5678x58 = ((afe.eq_band << 4) | (afe.lpf_front_band));
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x58, val_5678x58);

		//B5/6/7/8 0x5B ref_vol[1:0]
	val_5678x59 = ((afe.clpmode << 7) | (afe.f_lpf_bypass << 4) | (afe.clproff << 3) | (afe.b_lpf_bypass));
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x59, val_5678x59);

	val_5678x5B = ((afe.duty << 4) | (afe.ref_vol));
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x5B, val_5678x5B);

	val_5678x5C = ((afe.lpf_back_band << 4) | (afe.clk_sel << 3) | (afe.eq_gainsel));
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x5C, val_5678x5C);
}

void video_input_color_set(decoder_dev_ch_info_s *decoder_info)
{

	//unsigned char val_9x44; // This IF sentense
	if(decoder_info->fmt_def == AHD20_1080P_30P || decoder_info->fmt_def == AHD20_1080P_25P ||
		decoder_info->fmt_def == CVI_FHD_30P || decoder_info->fmt_def == CVI_FHD_25P ||
		decoder_info->fmt_def == TVI_FHD_30P || decoder_info->fmt_def == TVI_FHD_25P ||
	   decoder_info->fmt_def == AHD30_4M_30P 	|| decoder_info->fmt_def == AHD30_4M_25P 	|| 
	   decoder_info->fmt_def == AHD30_4M_15P ||    decoder_info->fmt_def == CVI_5M_20P 	|| 
	   decoder_info->fmt_def == CVI_4M_30P 		|| decoder_info->fmt_def == CVI_4M_25P 	||
	   decoder_info->fmt_def == TVI_4M_30P 		|| decoder_info->fmt_def == TVI_4M_25P		||
	   decoder_info->fmt_def == TVI_4M_15P	|| decoder_info->fmt_def == TVI_5M_20P		|| 
	   decoder_info->fmt_def == TVI_8M_15P  || decoder_info->fmt_def == TVI_8M_12_5P
	)
	{
		video_input_color_init_s color_init = (video_input_color_init_s)decoder_color_fmtdef[decoder_info->fmt_def];
#if 0
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xff, 0x00 );
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x0c + decoder_info->ch, color_init.brightnees);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + decoder_info->ch, color_init.contrast );
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x22 + (decoder_info->ch*4), 0x0B );				// FIxed Value
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x3c + decoder_info->ch, color_init.saturation_a );
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x40 + decoder_info->ch, color_init.hue      );
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x44 + decoder_info->ch, color_init.u_gain   );
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x48 + decoder_info->ch, color_init.v_gain   );
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x4c + decoder_info->ch, color_init.u_offset );
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x50 + decoder_info->ch, color_init.v_offset );
#endif
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xff, 0x05 + decoder_info->ch);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x2b, color_init.saturation_b);
//		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x20, color_init.black_level);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x24, color_init.burst_dec_a);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x5f, color_init.burst_dec_b);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xd1, color_init.burst_dec_c);
	}
	else
	{
		printk("NOT_YET_SUPPORT_COLOR_SET_FORMAT:[%d]",decoder_info->fmt_def);
	}


	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xff, 0x05 + decoder_info->ch);

	if(decoder_info->fmt_def == TVI_5M_12_5P)
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x26,0x20);
	else
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x26,0x40);


	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x05 + decoder_info->ch);

	if(decoder_info->fmt_def >= AHD20_SD_H960_NT && decoder_info->fmt_def <= AHD20_SD_H960_2EX_Btype_PAL)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xB8, 0xB8);	// SD Rees Only
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x40 + decoder_info->ch, 0x60);
	}
	else
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xB8, 0x39); // Other Format
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x09);
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x40 + decoder_info->ch, 0x00);
	}
}

void video_input_hafc_gain_ctrl(decoder_dev_ch_info_s *decoder_info)
{
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x05 + decoder_info->ch);

	if(decoder_info->fmt_def == NC_VIVO_CH_FORMATDEF_UNKNOWN)
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xB9, 0xB2);
	}
	else
	{
		gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xB9, 0x72);
	}
}

void video_input_contrast_off(decoder_dev_ch_info_s *decoder_info)
{
	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0xFF, 0x00);

	gpio_i2c_write(raptor3_i2c_addr[decoder_info->devnum], 0x10 + decoder_info->ch, 0x00);
}

void video_input_new_format_set(decoder_dev_ch_info_s *decoder_info)
{
	unsigned char ch = decoder_info->ch % 4;
	unsigned char devnum = decoder_info->devnum;
	//unsigned char fmtdef = decoder_info->fmt_def;
	unsigned char val_9x44;

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF,0x09);
	val_9x44 = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x44);
	val_9x44 &= ~(1 << ch);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x44, val_9x44);

	/* CVI HD 30P PN Value Set */
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x50 + ( ch * 4 ) , 0x30);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x51 + ( ch * 4 ) , 0x6F);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x52 + ( ch * 4 ) , 0x67);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x53 + ( ch * 4 ) , 0x48);

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x11);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x00 + ( ch * 0x20 ), 0x00);
}
