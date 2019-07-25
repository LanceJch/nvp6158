/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: Raptor3 Device Driver
*  Description	: clock.c
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
#include "clock.h"
#include "common.h"
#include "clock_table.h"
#include "gpio_i2c.h"

extern unsigned int raptor3_i2c_addr[4];

void adc_clock_set(clock *clk_adc)
{
    gpio_i2c_write(raptor3_i2c_addr[clk_adc->devnum], 0xff, 0x01);
    //B1	0x84/5/6/7 ADC Clock
    gpio_i2c_write(raptor3_i2c_addr[clk_adc->devnum], 0x84 + clk_adc->ch, clk_adc->vlaue);
}

void pre_clock_set(clock *clk_pre)
{
    gpio_i2c_write(raptor3_i2c_addr[clk_pre->devnum], 0xff, 0x01);
    //B1	0x8C/D/E/F PRE Clock
    gpio_i2c_write(raptor3_i2c_addr[clk_pre->devnum], 0x8c + clk_pre->ch, clk_pre->vlaue);
}

void clock_set(decoder_dev_ch_info_s *dev_ch_info)
{
	clock_set_s clk_set = (clock_set_s)decoder_clk_fmtdef[dev_ch_info->fmt_def];

	gpio_i2c_write(raptor3_i2c_addr[dev_ch_info->devnum], 0xff, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[dev_ch_info->devnum], 0x84 + dev_ch_info->ch, clk_set.clk_adc);
	gpio_i2c_write(raptor3_i2c_addr[dev_ch_info->devnum], 0x8c + dev_ch_info->ch, clk_set.clk_pre);
}

void video_out_auto_vclk_set(clock_video_output *clk_vout)
{
	gpio_i2c_write(raptor3_i2c_addr[clk_vout->devnum], 0xff, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[clk_vout->devnum], 0xCC + clk_vout->port, clk_vout->clk_sel);
}
