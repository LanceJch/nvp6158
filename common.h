/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: Raptor3 Device Driver
*  Description	: common.h
*  Author		:
*  Date         :
*  Version		: Version 1.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

//unsigned char __I2CReadByte8(unsigned char devaddress, unsigned char address);
//void __I2CWriteByte8(unsigned char devaddress, unsigned char address, unsigned char data);
//#define  gpio_i2c_read   __I2CReadByte8
//#define  gpio_i2c_write  __I2CWriteByte8

#define DRIVER_VER "17.0.xx.00"

//For Test
#define FPGA_TEST	1

#define HI_CHIPID_BASE 0x12050000
#define HI_CHIPID0 IO_ADDRESS(HI_CHIPID_BASE + 0xEEC)
#define HI_CHIPID1 IO_ADDRESS(HI_CHIPID_BASE + 0xEE8)
#define HI_CHIPID2 IO_ADDRESS(HI_CHIPID_BASE + 0xEE4)
#define HI_CHIPID3 IO_ADDRESS(HI_CHIPID_BASE + 0xEE0)
#define HW_REG(reg) *((volatile unsigned int *)(reg))

#define _SET_BIT(data,bit) ((data)|=(1<<(bit)))
#define _CLE_BIT(data,bit) ((data)&=(~(1<<(bit))))

#define PORTA		0x00
#define PORTB		0x01
#define PORTC		0x02
#define PORTD		0x03
#define PORTAB		0x04
#define PORTCD		0x05

#define FUNC_ON		0x01
#define FUNC_OFF		0x00

#define RAPTOR3_4PORT_R0_ID 0xA1  //6158
#define RAPTOR3_2PORT_R0_ID 0xA0  //6158C
#define RAPTOR3_1PORT_R0_ID 0xA2
#define AFE_NVP6134E_R0_ID 	0x80

#define RAPTOR3_4PORT_REV_ID 0x00
#define RAPTOR3_2PORT_REV_ID 0x00
#define RAPTOR3_1PORT_REV_ID 0x00

#define RAPTOR4_4PORT_R0_ID 0xC1
#define RAPTOR4_2PORT_R0_ID 0xC0

#define VDEC_RAPTOR3 RAPTOR3_2PORT_R0_ID
#define VDEC_RAPTOR4 RAPTOR4_2PORT_R0_ID


enum {
    NC_AD_SAMPLE_RATE_8000 = 8000,
    NC_AD_SAMPLE_RATE_16000 = 16000,
    NC_AD_SAMPLE_RATE_32000 = 32000,
    NC_AD_SAMPLE_RATE_44100 = 44100,

    NC_AD_SAMPLE_RATE_MAX,
};

enum {
	NC_AD_AI = 0,
	NC_AD_AOC,

	NC_AD_MAX
};

enum {
	NC_AD_BIT_WIDTH_8 = 0,
	NC_AD_BIT_WIDTH_16,
	NC_AD_BIT_WIDTH_24,

	NC_AD_BIT_WIDTH_MAX
};

#define VI_1MULTIPLEX_MODE  0
#define VI_2MULTIPLEX_MODE	1

typedef struct _decoder_get_information_str
{
	unsigned char chip_id[4];
	unsigned char chip_rev[4];
	unsigned char chip_addr[4];

	unsigned char Total_Port_Num;
	unsigned char Total_Chip_Cnt;

}decoder_get_information_str;

typedef struct _decoder_dev_ch_info_s
{
	unsigned char ch;
	unsigned char devnum;
	unsigned char fmt_def;
}decoder_dev_ch_info_s;


typedef enum NC_FORMAT_FPS
{
	FMT_FPS_UNKNOWN = 0,
	FMT_NT = 1,
	FMT_PAL,
	FMT_12_5P,
	FMT_7_5P,
	FMT_30P,
	FMT_25P,
	FMT_50P,
	FMT_60P,
	FMT_15P,
	FMT_18P,
	FMT_18_75P,
	FMT_20P,

	FMT_FPS_MAX,

} NC_FORMAT_FPS;

//#define FMT_AUTO (-1)

typedef enum NC_FORMAT_STANDARD
{
	FMT_STD_UNKNOWN = 0,
	FMT_SD,
	FMT_AHD20,
	FMT_AHD30,
	FMT_TVI,
	FMT_CVI,

	FMT_AUTO,		// FIXME

	FMT_STD_MAX,

} NC_FORMAT_STANDARD;


typedef enum NC_FORMAT_RESOLUTION
{
	FMT_RESOL_UNKNOWN = 0,
	FMT_SH720,
	FMT_H960,
	FMT_H1280,
	FMT_H1440,
	FMT_H960_EX,
	FMT_H960_2EX,
	FMT_H960_Btype_2EX,
	FMT_720P,
	FMT_720P_EX,
	FMT_720P_Btype,
	FMT_720P_Btype_EX,
	FMT_1080P,
	FMT_1080P_EX,
	FMT_3M,
	FMT_4M,
	FMT_5M,
	FMT_5_3M,
	FMT_6M,
	FMT_8M_X,
	FMT_8M,

	FMT_H960_Btype_2EX_SP,
	FMT_720P_Btype_EX_SP,

	FMT_960P,
	FMT_RESOL_MAX,

} NC_FORMAT_RESOLUTION;


typedef enum NC_VIVO_CH_FORMATDEF
{
	NC_VIVO_CH_FORMATDEF_UNKNOWN = 0,
	NC_VIVO_CH_FORMATDEF_AUTO,

	AHD20_SD_H960_NT,					// 2
	AHD20_SD_H960_PAL,
	AHD20_SD_SH720_NT,
	AHD20_SD_SH720_PAL,
	AHD20_SD_H1280_NT,
	AHD20_SD_H1280_PAL,
	AHD20_SD_H1440_NT,
	AHD20_SD_H1440_PAL,
	AHD20_SD_H960_EX_NT,				// 10
	AHD20_SD_H960_EX_PAL,
	AHD20_SD_H960_2EX_NT,
	AHD20_SD_H960_2EX_PAL,
	AHD20_SD_H960_2EX_Btype_NT,
	AHD20_SD_H960_2EX_Btype_PAL,

	AHD20_1080P_30P,
	AHD20_1080P_25P,

	AHD20_720P_60P,
	AHD20_720P_50P,
	AHD20_720P_30P,		// 20
	AHD20_720P_25P,
	AHD20_720P_30P_EX,
	AHD20_720P_25P_EX,
	AHD20_720P_30P_EX_Btype,
	AHD20_720P_25P_EX_Btype,

	AHD30_4M_30P,
	AHD30_4M_25P,
	AHD30_4M_15P,
	AHD30_3M_30P,
	AHD30_3M_25P,		// 30
	AHD30_3M_18P,
	AHD30_5M_12_5P,
	AHD30_5M_20P,


	AHD30_5_3M_20P,
	AHD30_6M_18P,
	AHD30_6M_20P,
	AHD30_8M_X_30P,
	AHD30_8M_X_25P,
	AHD30_8M_7_5P,
	AHD30_8M_12_5P,		// 40
	AHD30_8M_15P,

	TVI_FHD_30P,
	TVI_FHD_25P,
	TVI_HD_60P,
	TVI_HD_50P,
	TVI_HD_30P,
	TVI_HD_25P,
	TVI_HD_30P_EX,
	TVI_HD_25P_EX,
	TVI_HD_B_30P,		// 50
	TVI_HD_B_25P,
	TVI_HD_B_30P_EX,
	TVI_HD_B_25P_EX,
	TVI_3M_18P,
	TVI_5M_12_5P,
	TVI_5M_20P,
	TVI_4M_30P,
	TVI_4M_25P,
	TVI_4M_15P,
	TVI_8M_15P, 		// 60
	TVI_8M_12_5P, 

	CVI_FHD_30P,
	CVI_FHD_25P,
	CVI_HD_60P,
	CVI_HD_50P,
	CVI_HD_30P,
	CVI_HD_25P,
	CVI_HD_30P_EX,
	CVI_HD_25P_EX,		// 70
	CVI_4M_30P,
	CVI_4M_25P,
	CVI_5M_20P,
	CVI_8M_15P,
	CVI_8M_12_5P,

	AHD20_1080P_60P,
	AHD20_1080P_50P,
	AHD20_1080P_15P,
	AHD20_1080P_12_5P,

	TVI_FHD_60P,		//
	TVI_FHD_50P,

	AHD20_960P_30P,
	AHD20_960P_25P,
	AHD20_960P_60P,
	AHD20_960P_50P,
	TVI_960P_30P,
	TVI_960P_25P,
	TVI_960P_60P,
	TVI_960P_50P,

	AHD20_1080P_15P_EX, // Hidden For test
	AHD20_1080P_12_5P_EX, // Hidden For test

	AHD20_720P_15P_2EX_Btype, // Hidden For test
	AHD20_720P_12_5P_2EX_Btype, // Hidden For test

	AHD20_720P_15P_EX_Btype, // Hidden For test
	AHD20_720P_12_5P_EX_Btype, // Hidden For test

	NC_VIVO_CH_FORMATDEF_MAX,

} NC_VIVO_CH_FORMATDEF;

#define UNUSED(x) ((void)(x))

#if 0
#define dbg_printk(...) _kernel_dbg_printk( __VA_ARGS__)

static void _kernel_dbg_printk(const char* s, ...)
{
	unsigned char buffer[128];
	char *pS = buffer;

	va_list args;
	va_start(args, s);
	vsprintf(buffer, s, args);
	va_end(args);


	while(*pS) { if( *pS == '\n' ) *pS= ' '; pS++; }

	printk("\033[33m\033[1m [KERENL] \033[0m:\033[32m\033[1m %s \033[0m\n", buffer);
}
#endif


#endif

