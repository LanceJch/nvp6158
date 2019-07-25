/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: raptor3_drv.c
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
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <mach/io.h>
//#include <asm/system.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/list.h>
#include <asm/delay.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/poll.h>
#include <asm/bitops.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <linux/moduleparam.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "common.h"
#include "video_output.h"
#include "video_input.h"
#include "video_auto_detect.h"
#include "clock.h"
#include "coax_protocol.h"
#include "motion.h"
#include "audio.h"
#include "video_eq.h"

#include "RSAD.h"

#include <raptor3_ioctl.h>
#include "video_fmt_output.h"
#include "video_fmt_info.h"
#include "video_fmt_input.h"
#include "video_output.h"
#include "coax_protocol.h"

#include "gpio_i2c.h"

#include <linux/time.h>

#define MAX_DEBOUNCE_CNT	  5
#define AIG_DEF   0x05
#define AOG_DEF   0x08
#define DRIVER_VER_6158 "19.01.08.01"		//nextchip更新驱动日期

int chip_id[4];
int rev_id[4];
unsigned int VideoLoss[16];
//unsigned int AHD_VIDEOLOSS[4] = {0, 1, 2, 3}; //D3108NR
unsigned int AHD_VIDEOLOSS[4] = {3, 2, 0, 1}; //D3104NR/D3116NR
unsigned char VO_PORT[4]={0, 1, 2, 3};

unsigned int raptor3_i2c_addr[4] = {0x60, 0x62, 0x64, 0x66};
unsigned char outmodechip[16];
unsigned char app_curvideofmt[16]={[0 ... 15]=0xf0};
unsigned char ch_mode_status[16]={[0 ... 15]=0xff};			//接收由app的 转换后  值对应驱动6158自带的枚举
unsigned char RSch_mode_status[16]={[0 ... 15]=0xff};		//app传下来  为转换的
unsigned char ch_vfmt_status[16];

unsigned char debounceidx[16]={[0 ... 15]=0};
unsigned char	debounce[16][MAX_DEBOUNCE_CNT]={{0,0}};

unsigned int nvp6158_cnt = 0;
unsigned int boardid = 1;
unsigned int mainboardid = 0;
unsigned int vdec_mode = PAL;  //0:ntsc, 1: pal
module_param(vdec_mode, uint, S_IRUGO);
unsigned char oMux;	//portmode
unsigned char UTC_AUTHOR=0;

rsad_info info;
decoder_get_information_str decoder_inform;
unsigned int cp_mode;
unsigned int pir_bk[16];
static unsigned char novideo = 0;
char vdec;

static DEFINE_SEMAPHORE(RSAD_sem);

int RS_NoVIdeoSetFormat( unsigned char ch, unsigned char mode_status);
NC_VIVO_CH_FORMATDEF RS_VI_FindFormatDef( NC_FORMAT_STANDARD format_standard,NC_FORMAT_RESOLUTION format_resolution, NC_FORMAT_FPS format_fps  );

NC_VI_CH_FMT_S *RS_HI_VI_Get_ChannelFormat( NC_VIVO_CH_FORMATDEF def )
{

	NC_VI_CH_FMT_S *pRet = NULL;
	pRet = &VD_VI_ChannelFormatDefs[ def ];
	if(pRet->width==0 || pRet->height==0)
	{
		printk("Not Supported format Yet!!!(%d)\n",def);
		pRet = &VD_VI_ChannelFormatDefs[ AHD30_4M_25P ];
	}
	return  pRet;
}

video_output_port_fmt_s *RS_HI_VO_Get_PortFormat( NC_VIVO_CH_FORMATDEF def )
{
 	video_output_port_fmt_s *pRet=&VD_VO_PortFormatDefs[ def ];
	if(pRet->width==0 || pRet->height==0)
	{
		printk("Not Supported format Yet!!!(%d)\n",def);		// NC_VIVO_CH_FORMATDEF_UNKNOWN
		pRet = &VD_VO_PortFormatDefs[ CVI_HD_30P_EX ];
		//pRet = &VD_VO_PortFormatDefs[ AHD30_4M_25P ];
	}
	return  pRet;
}

NC_VIVO_CH_FORMATDEF RS_VI_FindFormatDef( NC_FORMAT_STANDARD format_standard,
		NC_FORMAT_RESOLUTION format_resolution, NC_FORMAT_FPS format_fps  )
{
	int ii;
	NC_VI_CH_FMT_S *pFmt = NULL;

	if(format_standard == FMT_AUTO)
		return NC_VIVO_CH_FORMATDEF_AUTO;

	for(ii=0;ii<NC_VIVO_CH_FORMATDEF_MAX;ii++)
	{
		pFmt = &VD_VI_ChannelFormatDefs[ ii ];

		if( pFmt->format_standard == format_standard )
		if( pFmt->format_resolution == format_resolution )
		if( pFmt->format_fps == format_fps )
			return ii;
	}

	printk("UNKNOWN format!!!\n");

	return NC_VIVO_CH_FORMATDEF_UNKNOWN;
}

/*****		将RS同轴命令转换为6158下枚举		******/
NC_COAX_CMD_DEF nvp6158_coaxcommand_convert(unsigned char chn,unsigned char command,unsigned char udata)
{
	NC_COAX_CMD_DEF tmp_cmd = COAX_CMD_UNKNOWN;
	#if 1
	switch(command)
	{
		case MENU_PROTOCOL:	tmp_cmd = COAX_CMD_OSD_ENTER;			break;
		
		case DOWN_PROTOCOL:
		case KEY_TILT_DOWN:	tmp_cmd = COAX_CMD_OSD_DOWN;			break;
		case UP_PROTOCOL:
		case KEY_TILT_UP:		tmp_cmd = COAX_CMD_OSD_UP;				break;
		case LEFT_PROTOCOL:
		case KEY_PAN_LEFT:		tmp_cmd = COAX_CMD_OSD_LEFT;			break;
		case RIGHT_PROTOCOL:
		case KEY_PAN_RIGHT:	tmp_cmd = COAX_CMD_OSD_RIGHT;			break;
		
		case KEY_LEFT_UP:		tmp_cmd = COAX_CMD_LEFT_UP;			break;
		case KEY_LEFT_DOWN:	tmp_cmd = COAX_CMD_LEFT_DOWN;			break;	
		case KEY_RIGTH_UP:		tmp_cmd = COAX_CMD_RIGHT_UP;			break;	
		case KEY_RIGTH_DOWN:	tmp_cmd = COAX_CMD_RIGHT_DOWN;			break;	
		
		case KEY_IRIS_CLOSE:	tmp_cmd = COAX_CMD_IRIS_DEC;			break;		///
		case KEY_IRIS_OPEN:	tmp_cmd = COAX_CMD_IRIS_INC;			break;		///
		case KEY_FOCUS_NEAR:	tmp_cmd = COAX_CMD_FOCUS_DEC;			break;
		case KEY_FOCUS_FAR:	tmp_cmd = COAX_CMD_FOCUS_INC;			break;	
		case KEY_ZOOM_WIDE:	tmp_cmd = COAX_CMD_ZOOM_DEC;			break;	
		case KEY_ZOOM_TELE:	tmp_cmd = COAX_CMD_ZOOM_INC;			break;
		
		case KEY_PRESET_SET:	tmp_cmd = COAX_CMD_SET_POINT;			break;
		case KEY_PRESET_CLR:	tmp_cmd = COAX_CMD_CLEAR_POINT;		break;
		case KEY_PRESET_CALL:	
			if(udata == 0x63)	tmp_cmd = COAX_CMD_AUTO;						//auto
			else 					tmp_cmd = COAX_CMD_GOTO_POINT;		break;
		case KEY_MOTOR_STOP:	tmp_cmd = COAX_CMD_STOP;				break;		///未使用的命令先暂时赋为 COAX_CMD_AUTO_STOP
		case KEY_CMD_OSD:		tmp_cmd = COAX_CMD_OSD_ON;				break;
		case KEY_AUTO_STOP:	tmp_cmd = COAX_CMD_AUTO_STOP;				break;		///
		case KEY_SET_CAMERA:	tmp_cmd = COAX_CMD_SET_CAMERA;			break;
		case KEY_SET_WHITE_LED:	tmp_cmd = COAX_CMD_SET_WHITE_LED;		break;
		case KEY_SET_WHITE_LED_MODE: tmp_cmd = COAX_CMD_SET_WHITE_LED_MODE;	break;
		default:
			break;
	}
	#endif
	return tmp_cmd;
}

/**		将app传下来的通道模式 转换为6158定义的枚举类型	**/
int nvp6158_chnmode_convert(const unsigned char ch, const unsigned char vfmt, const unsigned char chnmode)
{  
	unsigned char ret = 0;
	
	if(ch >= (nvp6158_cnt*4))
	{
		printk("func[nvp6158_chnmode_convert] Channel %d is out of range!!!\n", ch);
		return -1;
	}
	if(vfmt > PAL)
	{
		printk("func[nvp6158_chnmode_convert] vfmt %d is out of range!!!\n", vfmt);
		return -1;
	}

	/* set video format each format */
	if(chnmode < NVP6134_VI_BUTT) 
	{			
		switch(chnmode)	
		{
			case NVP6134_VI_720H:
			case NVP6134_VI_960H:
			case NVP6134_VI_1280H:
			case NVP6134_VI_1440H:	
			case NVP6134_VI_1920H:	
			case NVP6134_VI_960H2EX:	
				{
					if(vfmt == NTSC)	ret = AHD20_SD_H960_2EX_Btype_NT;
					else				ret = AHD20_SD_H960_2EX_Btype_PAL;
				}
				break;
			case NVP6134_VI_720P_2530:
			case NVP6134_VI_HDEX:
				{
					if(vfmt == NTSC)	ret = AHD20_720P_30P_EX_Btype;
					else				ret = AHD20_720P_25P_EX_Btype;
				}
				break;	
			case NVP6134_VI_EXC_720P:
			case NVP6134_VI_EXC_HDEX:
				{
					if(vfmt == NTSC)	ret = CVI_HD_30P_EX;
					else				ret = CVI_HD_25P_EX;	
				}
				break;
			case NVP6134_VI_EXT_720PA:
			case NVP6134_VI_EXT_HDAEX:
				{
					if(vfmt == NTSC)	ret = TVI_HD_30P_EX;
					else				ret = TVI_HD_25P_EX;
				}
				break;
			case NVP6134_VI_EXT_720PB:
			case NVP6134_VI_EXT_HDBEX:	
				{
					if(vfmt == NTSC)	ret = TVI_HD_B_30P_EX;
					else				ret = TVI_HD_B_25P_EX;
				}
				break;
			case NVP6134_VI_720P_5060:
				{
					if(vfmt == NTSC)	ret = AHD20_720P_60P;
					else				ret = AHD20_720P_50P;
				}
				break;
			case NVP6134_VI_EXC_720PRT:
				{
					if(vfmt == NTSC)	ret = CVI_HD_60P;
					else				ret = CVI_HD_50P;
				}
				break;
			case NVP6134_VI_EXT_720PRT:
				{
					if(vfmt == NTSC)	ret = TVI_HD_60P;
					else				ret = TVI_HD_50P;
				}
				break;
			case NVP6134_VI_1080P_NRT:
				{
						ret = AHD20_1080P_15P_EX;
				}
				break;
			case NVP6134_VI_1080P_2530: 
				{
					if(vfmt == NTSC)	ret = AHD20_1080P_30P;
					else				ret = AHD20_1080P_25P;
				}
				break;
			case NVP6134_VI_EXC_1080P:	
				{
					if(vfmt == NTSC)	ret = CVI_FHD_30P;
					else				ret = CVI_FHD_25P;
				}
				break;
			case NVP6134_VI_EXT_1080P:	
				{
					if(vfmt == NTSC)	ret = TVI_FHD_30P;
					else				ret = TVI_FHD_25P;
				}
				break;
			case NVP6134_VI_3M_NRT: 		ret = AHD30_3M_18P;			break;
			case NVP6134_VI_EXT_3M_NRT:	ret = TVI_3M_18P;			break;	
			case NVP6134_VI_3M:
				{
					if(vfmt == NTSC)	ret = AHD30_3M_30P;
					else				ret = AHD30_3M_25P;
				}
				break;
			case NVP6134_VI_4M_NRT: 	ret = AHD30_4M_15P;				break;
			case NVP6134_VI_4M:
				{
					if(vfmt == NTSC)	ret = AHD30_4M_30P;
					else				ret = AHD30_4M_25P;
				}
				break;
			case NVP6134_VI_EXT_4M_NRT: 	ret = TVI_4M_15P;				break;
			case NVP6134_VI_EXT_4M:
				{
					if(vfmt == NTSC)	ret = TVI_4M_30P;
					else				ret = TVI_4M_25P;
				}
				break;
			case NVP6134_VI_EXC_4M:
				{
					if(vfmt == NTSC)	ret = CVI_4M_30P;
					else				ret = CVI_4M_25P;
				}
				break;
			case NVP6134_VI_5M_NRT:		ret = AHD30_5M_12_5P;		break;
			case NVP6134_VI_5M_20P:		ret = AHD30_5M_20P;			break;
			
			case NVP6134_VI_8M:			ret = AHD30_8M_15P;			break;
			case NVP6134_VI_8M_NRT:		ret = AHD30_8M_12_5P;		break;		
			
			case NVP6134_VI_EXT_5M_NRT:	ret = TVI_5M_12_5P;			break;
			case NVP6134_VI_EXT_5M:		ret = TVI_5M_20P;			break;
			
			case NVP6134_VI_EXT_8M:		ret = TVI_8M_15P;			break;
			case NVP6134_VI_EXT_8M_NRT:	ret = TVI_8M_12_5P;			break;
			
			case NVP6134_VI_EXC_8M:		ret = CVI_8M_15P;			break;
			case NVP6134_VI_EXC_8M_NRT:	ret = CVI_8M_12_5P;			break;
			
			case NVP6134_VI_1080P_NOVIDEO:	
			default:
				novideo = 1;
				ret = CVI_HD_30P_EX;
				//ret = AHD20_1080P_30P;
				//RS_NoVIdeoSetFormat(ch,ret);
				printk("\033[1;31m CH[%d] mode[%d] Default Set to CVI_HD_30P_EX novideo mode. \033[0;39m \n",ch,ret);
				break;
		}						
		ch_mode_status[ch] = ret;

		//if (chnmode != NVP6134_VI_1080P_NOVIDEO)
			//printk("\033[1;31m[%d]=======chnmode :%x	CH[%d]-EnumValue:%d	 \033[0;39m \n", __LINE__,chnmode,ch,ret);
	}	

	return 0;
}

/***		将 6158定义的枚举 转换为 RS定义的 上传给app	***/
void RS_AUTO_VFCtoFMTDEF(unsigned char ch,unsigned char VFC)		
{
	switch(VFC)
	{
		case AHD20_SD_H960_2EX_Btype_NT:  	app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_SD_NTSC;			break;  //cvbs ntsc
		case AHD20_SD_H960_2EX_Btype_PAL:  app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_SD_PAL; 			break;	//cvbs pal
		case AHD20_720P_30P_EX_Btype:	  	app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_720P_30FPS; 		break;	//720p ntsc
		case AHD20_720P_25P_EX_Btype:  	app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_720P_25FPS; 		break;	//720p pal
		case AHD20_720P_60P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_720P_60FPS; 		break;	//720P@RT ntsc
		case AHD20_720P_50P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_720P_50FPS; 		break;	//720P@RT pal
		case AHD20_1080P_15P_EX:  			app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_1080P_NRT;		break;	//1080p 15p ntsc
		case AHD20_1080P_12_5P_EX:	  		app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_1080P_12_5FPS;	break;	//1080p 12.5p pal
		case AHD20_1080P_30P:  			app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_1080P_30FPS;		break;	//1080p ntsc
		case AHD20_1080P_25P:	  			app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_1080P_25FPS;		break;	//1080p pal
		case CVI_HD_30P_EX:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXC_720P_30FPS; 	break;  //HD exc  @ 30P
		case CVI_HD_25P_EX:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXC_720P_25FPS; 	break;  //HD EXC  @ 25P
		case TVI_HD_30P_EX:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXTA_720P_30FPS; break;  //HD EXT  @ 30A
		case TVI_HD_25P_EX:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXTA_720P_25FPS; break;  //HD EXT  @ 24A
		case TVI_HD_B_30P_EX:  			app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXTB_720P_30FPS; break;  //HD EXT  @ 30B
		case TVI_HD_B_25P_EX:  			app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXTB_720P_25FPS; break;  //HD EXT  @ 25B
		case CVI_HD_60P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXC_720P_60FPS; 	break;  //HD EXC  @ 60P
		case CVI_HD_50P:  					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXC_720P_50FPS; 	break;  //HD EXC  @ 50P
		case TVI_HD_60P:  					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXT_720P_60FPS; 	break;  //HD EXT  @ 60
		case TVI_HD_50P:  					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXT_720P_50FPS; 	break;  //HD EXT  @ 50
		case CVI_FHD_30P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXC_1080P_30FPS; break;  //FHD EXC @ 30P
		case CVI_FHD_25P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXC_1080P_25FPS; break;  //FHD EXC @ 25P
		case TVI_FHD_30P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXT_1080P_30FPS; break;  //FHD EXT @ 30P
		case TVI_FHD_25P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_EXT_1080P_25FPS; break;  //FHD EXT @ 25P
		//case 0x3F:  ret = AT_A_INPUT_VIDEOFMT_1080P_NRT; break;  //FHD NRT @ 30P 
		case AHD30_3M_18P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_3M_NRT;		break;	//AHD @ 3M NRT-18p
		case AHD30_3M_25P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_3M_25FPS;	break;//AHD @ 3M RT-25P		
		case AHD30_3M_30P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_3M_30FPS;	break;//AHD @ 3M RT-30P
		case AHD30_4M_15P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_4M_NRT;	 	break;  //QHD AHD @ NRT(15P)
		case AHD30_4M_25P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_4M_25FPS; 	break;  //QHD AHD @ 25P
		case AHD30_4M_30P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_4M_30FPS; 	break;  //QHD AHD @ 30P
		case CVI_4M_30P:  					app_curvideofmt[ch] = AT_C_INPUT_VIDEOFMT_4M_30FPS; 	break;  //QHD CVI @ 30P
		case CVI_4M_25P:  					app_curvideofmt[ch] = AT_C_INPUT_VIDEOFMT_4M_25FPS; 	break;  //QHD CVI @ 25P
		case TVI_4M_30P:  					app_curvideofmt[ch] = AT_T_INPUT_VIDEOFMT_4M_30FPS; 	break;  //QHD TVI @ 30P
		case TVI_4M_25P:  					app_curvideofmt[ch] = AT_T_INPUT_VIDEOFMT_4M_25FPS; 	break;  //QHD TVI @ 25P
		case TVI_4M_15P:  					app_curvideofmt[ch] = AT_T_INPUT_VIDEOFMT_4M15; 		break;  //QHD TVI @ 15P
		case AHD30_8M_X_30P:
		case AHD30_8M_X_25P:		break;
		case AHD30_5M_12_5P:  				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_5M_NRT; 		break;  //5M AHD @ 12.5P
		case AHD30_5M_20P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_5M_20FPS;	break;	//5M 20P
		case AHD30_5_3M_20P:		break;
		case TVI_5M_12_5P:					app_curvideofmt[ch] = AT_T_INPUT_VIDEOFMT_5M_12_5FPS;	break;	//EXT @ 5M @ 12.5p
		case TVI_5M_20P:					app_curvideofmt[ch] = AT_T_INPUT_VIDEOFMT_5M20;		break;	//EXT @ 5M @ 20p
		case TVI_3M_18P:					app_curvideofmt[ch] = AT_T_INPUT_VIDEOFMT_3M_NRT;		break;	//EXT @ 3M NRT-18p
		case TVI_8M_15P:					app_curvideofmt[ch] = AT_T_INPUT_VIDEOFMT_8M15;		break;	//EXT @ 8M @ 15p
		case AHD30_8M_15P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_8M_15P;		break;	//	8M AHD @ 15P
		case AHD30_8M_7_5P:				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_8M_7_5P;		break;	//	8M AHD @ 7.5P
		case AHD30_8M_12_5P:				app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_8M_12_5P;	break;	//	8M AHD @ 12.5P
		case CVI_8M_15P:					app_curvideofmt[ch] = AT_C_INPUT_VIDEOFMT_8M_15FPS;	break;	//	8M CVI @ 12.5P
		case CVI_8M_12_5P:					app_curvideofmt[ch] = AT_C_INPUT_VIDEOFMT_8M_12_5FPS;	break;	//	8M CVI @ 12.5Pbreak;
		case AHD30_6M_18P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_6M_18P;		break;	//	6M AHD @ 18P
		case AHD30_6M_20P:					app_curvideofmt[ch] = AT_A_INPUT_VIDEOFMT_6M_20P;		break;	//	6M AHD @ 20P
		default: 
		case NC_VIVO_CH_FORMATDEF_UNKNOWN:	app_curvideofmt[ch] = AHD_INPUT_VIDEOFMT_NOVIDEO;		break;	//not detects
	}
	
	//printk("\033[1;31m Function:[%s][%d]===============CH[%d]:0x%x	 \033[0;39m \n", __func__, __LINE__,ch,app_curvideofmt[ch]);
}

/*******************************************************************************
*	Description		: check Auto Debouce
*	Argurments		: ch:channel, pInformation(raptor3 information), videomode(0:novideo, 1:Onvideo)
*	Return value	: 0(not checked video format), -1(checked video format)
*	Modify			: N/A
*	warning			:
*******************************************************************************/
int RS_SAL_AutoDebouceCheck( unsigned char ch, unsigned char mode_status)
{
	int ret = 0;
	int i;
	unsigned char		oDebncIdx = 0;
	unsigned char 		oVfc = 0;
	NC_VIVO_CH_FORMATDEF oFmtB5Def=0;
	video_input_vfc	sVFC;

	sVFC.ch= ch % 4;
	sVFC.devnum= ch / 4;
	video_input_onvideo_check_data(&sVFC);

	oDebncIdx = debounceidx[ch];
	debounce[ch][oDebncIdx%MAX_DEBOUNCE_CNT] = sVFC.vfc;
	debounceidx[ch]++;
	debounceidx[ch] = ( (debounceidx[ch] % MAX_DEBOUNCE_CNT) == 0 ) ? 0 : debounceidx[ch];

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
		oFmtB5Def = RS_VD_AUTO_VFCtoFMTDEF(oVfc);

		if( ( oFmtB5Def != AHD30_5M_20P ) && ( oFmtB5Def != mode_status ) )
		{
			printk("\n\n\n>>>>>>WATCH OUT<<<<<<ch[%d] oFmtB5Def[%2x] != pInformation->prevideofmt[%2x]\n\n\n", ch, oFmtB5Def , mode_status);
			ret = -1;
		}
	}

	return ret;
}

/*******************************************************************************
*	Description		: set video format each channel
*	Argurments		: ch:channel, pInformation(raptor3 information), videomode(0:novideo, 1:Onvideo)
*	Return value	: NC_VIVO_CH_FORMATDEF_UNKNOWN(NO video), retfmt(get video format)
*	Modify			: N/A
*	warning			:
*******************************************************************************/
int RS_NoVIdeoSetFormat( unsigned char ch, unsigned char mode_status)
{
	video_output_port_fmt_s *pPortFmt;
	video_input_novid_set vin_novid_set;
	decoder_dev_ch_info_s DEV_CH_INFO;
	
	unsigned char oChannel;
	unsigned char devnum;
	unsigned char iPort;
	iPort = ch % 4;	
	
	oChannel = ch % 4;
	devnum = ch / 4;
	vin_novid_set.ch = ch % 4;
	vin_novid_set.devnum = ch / 4;

	DEV_CH_INFO.ch = oChannel;
	DEV_CH_INFO.devnum = devnum;
	DEV_CH_INFO.fmt_def = mode_status;
	
	if((chip_id[devnum] == RAPTOR4_4PORT_R0_ID) || (chip_id[devnum] == RAPTOR4_2PORT_R0_ID))//6168/6168C
	{
		/* This Part is enough EQ Setting */
		//NC_VD_VI_H_Timing_Set(&DEV_CH_INFO);
		video_input_h_timing_set(&DEV_CH_INFO);
		//NC_VD_VI_COLOR_Set(&DEV_CH_INFO);
		//video_input_color_set(&DEV_CH_INFO);
		//NC_VD_VI_VAFE_Init(&DEV_CH_INFO);
		video_input_vafe_init(&DEV_CH_INFO);

		//NC_VD_AUTO_NoVideo_Set(oChannel, devnum);
		nvp6168_video_input_no_video_set(&vin_novid_set);
	}
	else //6158/6158C
	{
		video_input_no_video_set(&vin_novid_set);	//自动无视频设置
		//NC_VD_VI_Format_Set(&DEV_CH_INFO);
		video_input_format_set(&DEV_CH_INFO);
		//NC_VD_CLK_SET(&DEV_CH_INFO);
		clock_set(&DEV_CH_INFO);
	}
	
	pPortFmt = (video_output_port_fmt_s *)RS_HI_VO_Get_PortFormat( mode_status );		//获取输出端口格式
	RS_VD_VO_Mode_Set_New( oChannel, devnum, iPort, pPortFmt, ch%4, ch%4, ch%4, ch%4 );		//设置新的视频输出模式

	return 0;
}

/*******************************************************************************
*	Description		: set video format each channel
*	Argurments		: ch:channel, pInformation(raptor3 information), videomode(0:novideo, 1:Onvideo)
*	Return value	: NC_VIVO_CH_FORMATDEF_UNKNOWN(NO video), retfmt(get video format)
*	Modify			:
*	warning			:
*******************************************************************************/
int RS_OnVIdeoSetFormat( unsigned char ch)
{
	int iPort = 0;
	unsigned char oChannel = 0x00;
	unsigned char oDevNum = 0x00;

	video_output_port_fmt_s *pPortFmt;	
	decoder_dev_ch_info_s DEV_CH_INFO;

	NC_VIVO_CH_FORMATDEF FmtDef = ch_mode_status[ch];		//当前视频格式
	iPort = ch%4;
	oChannel = ch%4;
	oDevNum = ch/4;
	
	pPortFmt = (video_output_port_fmt_s *)RS_HI_VO_Get_PortFormat( FmtDef ); // output 	获取端口模式

	DEV_CH_INFO.ch = oChannel;
	DEV_CH_INFO.devnum = oDevNum;
	DEV_CH_INFO.fmt_def= FmtDef;

	if((chip_id[oDevNum] == RAPTOR4_4PORT_R0_ID) || (chip_id[oDevNum] == RAPTOR4_2PORT_R0_ID))
	{
		nvp6168_video_input_onvideo_set(&DEV_CH_INFO);
	}
	else
	{
		video_input_onvideo_set(&DEV_CH_INFO);			//视频状态确认
	}
	
      /* This Part is enough EQ Setting */
	video_input_h_timing_set(&DEV_CH_INFO);		//行消隐设置
	video_input_color_set(&DEV_CH_INFO);			//颜色设置
    video_input_vafe_init(&DEV_CH_INFO);			//AFE初始化

	if((chip_id[oDevNum] == RAPTOR4_4PORT_R0_ID) || (chip_id[oDevNum] == RAPTOR4_2PORT_R0_ID))
	{
		if((pPortFmt->width==0 || pPortFmt->height==0))
		{
			printk(" Not Support This Format .. Fmt:[%d]\n", FmtDef);
			return 0;
		}
	}
	else
	{
    	video_input_new_format_set(&DEV_CH_INFO);		// 添加支持TVI_5M_20P
    }
	
    RS_VD_VO_Mode_Set_New( oChannel, oDevNum, iPort, pPortFmt, ch%4, ch%4, ch%4, ch%4 );		//设置端口(port)模式

	return 0;
}

void rs_set_portmode(int chn)
{
	video_output_port_enable_s sPortEnable;
	unsigned char Port_enable;
	
	if(chip_id[chn/4] == NVP6158C_R0_ID)
	{
		if((boardid == 5) || (boardid == 9)|| (boardid == 17))	//D4004NR/D4008NR/D4016NR/
		{
			//nvp6158_set_portmode(chn/4, 1, NVP6158_OUTMODE_4MUX_MIX, 0);
			//nvp6158_set_portmode(chn/4, 2, NVP6158_OUTMODE_4MUX_MIX, 0);
		}
		else
		{
			nvp6158_set_portmode(chn/4, 1, NVP6158_OUTMODE_2MUX_FHD, VO_PORT[0]);
			nvp6158_set_portmode(chn/4, 2, NVP6158_OUTMODE_2MUX_FHD, VO_PORT[1]);
		}
	}
	else if(chip_id[chn/4] == NVP6158_R0_ID)//open data output
	{
		sPortEnable.devnum =chn/4;
		gpio_i2c_write(raptor3_i2c_addr[sPortEnable.devnum], 0xff, 0x01);
		Port_enable=gpio_i2c_read(raptor3_i2c_addr[sPortEnable.devnum], 0xca);
		
		sPortEnable.enable = Port_enable|(1<<(chn%4));
		video_out_port_enable(&sPortEnable);		//端口打开
		printk("======ch:%d,sPortEnable.enable:0x%x\n",chn,sPortEnable.enable);
	}

}

void rs_coax_init(int chn)
{
	NC_VIVO_CH_FORMATDEF oFmtDef;
	NC_VI_CH_FMT_S 		*pChFmt=NULL; 

	oFmtDef = ch_mode_status[chn];
	//printk("\033[1;32m rs_coax_init===>oFmtDef:[ch:%d]:%d \033[0;39m \n",chn,oFmtDef);
	pChFmt = (NC_VI_CH_FMT_S *)RS_HI_VI_Get_ChannelFormat( oFmtDef );
	RS_APP_VD_COAX_Tx_Init( chn/4, chn%4, pChFmt->format_standard, pChFmt->format_resolution, pChFmt->format_fps );
	RS_APP_VD_COAX_Rx_Init( chn/4, chn%4, pChFmt->format_standard, pChFmt->format_resolution, pChFmt->format_fps );
}

void rs_manual_video_eq_set(video_equalizer_info_s *vin_eq_set)
{
	if((info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
	{
		nvp6168_video_input_eq_val_set(vin_eq_set);
	}
	else
	{
		video_input_eq_val_set(vin_eq_set);				//通道号  设备号	线长	视频格式
	}
}

void video_fmt_det(vdec_input_videofmt *pvideofmt)
{
	int i;
	if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
		(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
	{
		//printk("\033[1;31m video_fmt_det------- \033[0;39m \n");
		for(i=0; i<nvp6158_cnt*4; i++)
		{
			RS_GetFormat_Bank5_EachCh(i);
		}
		
		for(i=0; i<nvp6158_cnt*4; i++)
		{
			pvideofmt->getvideofmt[i] = app_curvideofmt[(i/4)*4+AHD_VIDEOLOSS[i%4]];
		
			//if (pvideofmt->getvideofmt[i] != 0xf0)
			//{
			//	printk("\033[1;31m pvideofmt->getvideofmt[%d]:0x%x------- \033[0;39m \n",i,pvideofmt->getvideofmt[i]);
			//}
		}
	}
}

/*******************************************************************************
*	Description		: Get Device ID
*	Argurments		: dec(slave address)
*	Return value	: Device ID
*	Modify			:
*	warning			:
*******************************************************************************/
int check_id(unsigned int dec)
{
	int ret;
	gpio_i2c_write(dec, 0xFF, 0x01);
	ret = gpio_i2c_read(dec, 0xf4);
	if(ret == 0x83)
	{
		return ret;
	}
	else
	{
		gpio_i2c_write(dec, 0xFF, 0x00);
		ret = gpio_i2c_read(dec, 0xf4);
		return ret;
	}
}

/*******************************************************************************
*	Description		: Get rev ID
*	Argurments		: dec(slave address)
*	Return value	: rev ID
*	Modify			:
*	warning			:
*******************************************************************************/
int check_rev(unsigned int dec)
{
	int ret;
	gpio_i2c_write(dec, 0xFF, 0x00);
	ret = gpio_i2c_read(dec, 0xf5);
	return ret;
}

int RSAD_open(struct inode * inode, struct file * file)
{
	printk("[DRV] Raprot3 Driver Open\n");
	return 0;
} 

int RSAD_close(struct inode * inode, struct file * file)
{
	return 0;
}

long RSAD_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	unsigned int __user *argp = (unsigned int __user *)arg;	

	//RS-------------------------------------//
	int tmp=0,tmp1=0,tmp0=0;
	unsigned int chn=0;
	int i2c_addr=0;
	int oDevNum=0,i=0;
	CABLE_DISTANCE CableDistance = 0;
	unsigned char pel_ch;

	NC_COAX_CMD_DEF coax_cmd;
	RSAD_PROTOCOL_S rsad_protocol;
	rsad_work_mode  work_mode;
	rsad_video_loss video_loss;
	rsad_image_adjust analog_cfg;
	rsad_audio_playback audio_playback;
	rsad_audio_da_volume audio_da_volume;
	rsad_audio_da_mute audio_da_mute;

	NC_FORMAT_STANDARD   eFmtStd;
	vdec_input_videofmt vidiofmt;
	video_equalizer_info_s vin_eq_set;
	NC_VI_CH_FMT_S 		*pChFmt=NULL; 
	NC_VIVO_CH_FORMATDEF oFmtDef;
	decoder_dev_ch_info_s sDevChInfo;
	
	//decoder_dev_ch_info_s decoder_info;
	//video_output_data_out_mode vo_data_out_mode;
	rsad_audio_samplerate_width samplerate_width;
	rsad_audio_set_i2s SetI2s;
	FIRMWARE_UP_FILE_INFO sfirmup_info;
	rsad_eq_stage   eq_stage;
	rsad_acp_rw_data acpdata;
	rsad_acp_rw_data_ex acpdata_ex;
	rsad_common_data common_data;
	nvp6124_input_videofmt input_videofmt;

	NC_VIVO_CH_FORMATDEF vivo_fmt;
	NC_VD_COAX_STR CoaxTx_Init;
	video_output_port_enable_s sPortEnable;
	unsigned char Port_enable;
	static unsigned char data[2];
	
	audio_da_mute.chn = 0;
	audio_da_mute.chip= 0;
	
	
	//----------------------------------------//
	
	if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
		(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
	{
		switch (_IOC_NR(cmd))
		{
			case _IOC_NR(RSAD_SET_VIDEO_NORM):
				break;
			case _IOC_NR(RSAD_SET_PROTOCOL):
				{
					if(copy_from_user(&rsad_protocol,argp,sizeof(RSAD_PROTOCOL_S)))
					{
						printk("set protocol failed\n");
						return -1;
					}

					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						tmp0 = (rsad_protocol.chn/4)*4 + AHD_VIDEOLOSS[rsad_protocol.chn%4];
						oDevNum = tmp0/4;

						oFmtDef = ch_mode_status[tmp0];			// 使用设置完模式后的枚举

						pChFmt = (NC_VI_CH_FMT_S *)RS_HI_VI_Get_ChannelFormat( oFmtDef );
						eFmtStd = pChFmt->format_standard;
						coax_cmd = nvp6158_coaxcommand_convert(tmp0,rsad_protocol.command,rsad_protocol.udata);	

						RS_APP_VD_COAX_Tx_Command_Send_Set( oDevNum, tmp0, eFmtStd, pChFmt->format_resolution, pChFmt->format_fps, coax_cmd,rsad_protocol.udata,rsad_protocol.status);
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_SET_WORK_MODE):
				{
					tmp1 = down_interruptible(&RSAD_sem);

					if (copy_from_user(&work_mode, argp, sizeof(work_mode)))
					{
						up(&RSAD_sem);
						return -1;
					}
					
					chn = AHD_VIDEOLOSS[work_mode.chn%4]+(work_mode.chn/4)*4;
					//work_mode.chn = chn;
					outmodechip[work_mode.chn] = work_mode.mode;
					RSch_mode_status[chn] =  work_mode.mode;
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp0 = nvp6158_chnmode_convert(chn, work_mode.vformat[work_mode.chn], work_mode.mode);
						if(tmp0 != 0)
						{
							printk("nvp6158_chnmode_convert error!\n");
							up(&RSAD_sem);
						}
						if(novideo == 0)
						{
							RS_OnVIdeoSetFormat(chn);
						}
						else
						{
							novideo = 0;
							RS_NoVIdeoSetFormat(chn,ch_mode_status[chn]);
							if(chip_id[chn/4] == NVP6158_R0_ID) //close data output
							{
								sPortEnable.devnum =chn/4;
								//gpio_i2c_write(raptor3_i2c_addr[chn/4],0xff,0x00);
								//Port_enable=gpio_i2c_read(raptor3_i2c_addr[chn/4],0xa8);
								gpio_i2c_write(raptor3_i2c_addr[sPortEnable.devnum], 0xff, 0x01);
								Port_enable=gpio_i2c_read(raptor3_i2c_addr[sPortEnable.devnum], 0xca);
								
								sPortEnable.enable = Port_enable&(~(1<<(chn%4)));
								video_out_port_enable(&sPortEnable);		//端口关闭
								printk("======ch:%d,sPortEnable.enable:0x%x\n",chn,sPortEnable.enable);
							}
							/*else//6158C
							{
								gpio_i2c_write(raptor3_i2c_addr[chn/4], 0xff, 0x01);
								Port_enable=gpio_i2c_read(raptor3_i2c_addr[chn/4], 0x96);
								
								sPortEnable.enable = Port_enable|(1<<(chn%4));
								gpio_i2c_write(raptor3_i2c_addr[chn/4], 0x96, sPortEnable.enable);		//端口关闭
								printk("======ch:%d,6158C sPortEnable.enable:0x%x",chn,sPortEnable.enable);
							}*/
							
							//解决AHD 8MP 界面切5MP模式再切回auto模式后，出现颜色变绿现象
							gpio_i2c_write(raptor3_i2c_addr[chn/4], 0xff, 0x00);  //afe reset
							gpio_i2c_write(raptor3_i2c_addr[chn/4], chn%4, 0x11);
							msleep(30);
							gpio_i2c_write(raptor3_i2c_addr[chn/4], chn%4, 0x10);
							rs_coax_rx_buffer_clear(chn);	//清buffer，解决pir枪机 切 普通枪机后误报问题
						}
					}

					up(&RSAD_sem);
				}
				break;
			case _IOC_NR(RSAD_SET_STABLE_WORKMODE):
				{
					#if 0
					tmp1 = down_interruptible(&RSAD_sem);
					if (copy_from_user(&work_mode, argp, sizeof(work_mode)))
					{
						up(&RSAD_sem);
						return -1;
					}
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C))
					{
						work_mode.chip = 0;		//根据chip的值的变化 判断视频格式是否发生变化
						tmp0=AHD_VIDEOLOSS[work_mode.chn%4]+(work_mode.chn/4)*4;

						RSch_mode_status[tmp0] =  work_mode.mode;
						ret = nvp6158_chnmode_convert(tmp0, work_mode.vformat[work_mode.chn], work_mode.mode);
						if(ret != 0)
						{
							printk("nvp6158_chnmode_convert error!\n");
							up(&RSAD_sem);
						}
						
						/* check debouce video format(-1:changed, 0:not checked) when you changed video format(Dahua-NVP2450). */
						ret = RS_SAL_AutoDebouceCheck( tmp0, ch_mode_status[tmp0]);
						if( ret == -1 )
						{
							decoder_info.ch = tmp0%4;
							decoder_info.devnum = tmp0/4;
							decoder_info.fmt_def = ch_mode_status[tmp0];

							/* hide decoder */
							//NC_VD_AUTO_CONTRAST_OFF(&sDevChInfo);
							//video_input_contrast_off(&decoder_info);		//不使用
							
							//vo_data_out_mode.ch = tmp0%4;
							//vo_data_out_mode.devnum = tmp0/4;
							//vo_data_out_mode.set_val = 0xF;			//	0xF is OUT_MODE_OFF
							
							//video_output_data_out_mode_set(&vo_data_out_mode);			//不使用

							/* decoder afe power down */
							video_input_vafe_control(&decoder_info, 0);
							
							/* set no video- first(i:channel, raptor3_vfmts:information */
							RS_NoVIdeoSetFormat( tmp0, ch_mode_status[tmp0] );
							/* decoder afe power up */
							video_input_vafe_control(&decoder_info, 1);

							/* for forced agc stable */
							video_input_manual_agc_stable_endi(&decoder_info, 1);
							msleep(500);

							/* save onvideo to prevideofmt */
							//s_raptor3_vfmts.prevideofmt[oLogicalChannel] = NC_VIVO_CH_FORMATDEF_UNKNOWN;

							work_mode.chip = 1 ;
							printk(">>>>> CH[%d], Auto, Reset, Set No video : 0x%02X====%d\n", tmp0, ch_mode_status[tmp0] ,work_mode.chip);
							
						}

						if (copy_to_user(argp, &work_mode, sizeof(work_mode)))
						{
							printk("======copy_to_user error!\n");
							up(&RSAD_sem);
							return -1;   
						}
					}
					up(&RSAD_sem);
					#endif
				}
				break;
			case _IOC_NR(RSAD_GET_VIDEO_LOSS):
				{
					if(copy_from_user(&video_loss, argp, sizeof(rsad_video_loss)))
						printk("RSAD_GET_VIDEO_LOSS error\n");
					tmp1 = down_interruptible(&RSAD_sem);

					i2c_addr = raptor3_i2c_addr[video_loss.chip/4];
					video_loss.ch=AHD_VIDEOLOSS[video_loss.ch%4];

					gpio_i2c_write(i2c_addr,0xff,0x00);
					//if(info.author == AHD_NVP6158 )
					{
						tmp=gpio_i2c_read(i2c_addr,0xa8);

						video_loss.is_lost=((~tmp) >> video_loss.ch)&0x01;
					}
					/*else //6158C
					{
						tmp=gpio_i2c_read(i2c_addr,0xa8);//0:on  1:no
						video_loss.is_lost=((~tmp) >> video_loss.ch)&0x01;
						if(app_curvideofmt[(video_loss.chip/4)*4+video_loss.ch] == AHD_INPUT_VIDEOFMT_NOVIDEO)
						{
							video_loss.is_lost=0;
						}
					}*/
					VideoLoss[video_loss.chip]=video_loss.is_lost;			// 值为1时有视频
					
					if (copy_to_user(argp, &video_loss, sizeof(rsad_video_loss)))
					{
						up(&RSAD_sem);
						return -1;   
					}
					up(&RSAD_sem);
				}
				break;
			case _IOC_NR(RSAD_SET_IMAGE_ADJUST):
				{
					if(copy_from_user(&analog_cfg, (const void *)arg, sizeof(rsad_image_adjust)))
					{
						return -1;
					}
					tmp=outmodechip[analog_cfg.chn];
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);	
						i2c_addr = raptor3_i2c_addr[analog_cfg.chip/4];
						analog_cfg.chn=AHD_VIDEOLOSS[analog_cfg.chn%4];
						gpio_i2c_write(i2c_addr,0xff,0x00);	
						if(analog_cfg.item_sel & RSAD_SET_BRIGHT) //brightness
						{
							analog_cfg.brightness=analog_cfg.brightness-128;	
							gpio_i2c_write(i2c_addr, 0x0c+analog_cfg.chn, analog_cfg.brightness);
						}
						if(analog_cfg.item_sel & RSAD_SET_CONTRAST) //contrast
						{				
							gpio_i2c_write(i2c_addr, 0x10+analog_cfg.chn, analog_cfg.contrast);
						}
						if (analog_cfg.item_sel & RSAD_SET_SATURATION)//saturation
						{
							gpio_i2c_write(i2c_addr, 0x3c+analog_cfg.chn, analog_cfg.saturation);
						}
						if (analog_cfg.item_sel & RSAD_SET_HUE)//hue
						{
							analog_cfg.hue=analog_cfg.hue-128;
							gpio_i2c_write(i2c_addr, 0x40+analog_cfg.chn, analog_cfg.hue);
						}
						if (analog_cfg.item_sel & RSAD_SET_SHARPNESS)//sharpness
						{	
							gpio_i2c_write(i2c_addr, 0x14+analog_cfg.chn, analog_cfg.sharpness);
						}
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_GET_IMAGE_ADJUST):
				{
					if(copy_from_user(&analog_cfg, (const void *)arg, sizeof(rsad_image_adjust)))
					{
						return -1;
					}
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);	
						i2c_addr = raptor3_i2c_addr[analog_cfg.chip/4];
						analog_cfg.chn=AHD_VIDEOLOSS[analog_cfg.chn%4];
						gpio_i2c_write(i2c_addr,0xff,0x00);	
						if(analog_cfg.item_sel & RSAD_SET_BRIGHT) //brightness
						{
							tmp = gpio_i2c_read(i2c_addr, 0x0c+analog_cfg.chn);
							analog_cfg.brightness = tmp + 128;//UI value
						}
						if(analog_cfg.item_sel & RSAD_SET_CONTRAST) //contrast
						{				
							analog_cfg.contrast = gpio_i2c_read(i2c_addr, 0x10+analog_cfg.chn);
						}
						if (analog_cfg.item_sel & RSAD_SET_SATURATION)//saturation
						{
							 analog_cfg.saturation = gpio_i2c_read(i2c_addr, 0x3c+analog_cfg.chn);
						}
						if (analog_cfg.item_sel & RSAD_SET_HUE)//hue
						{
							tmp = gpio_i2c_read(i2c_addr, 0x40+analog_cfg.chn);
							analog_cfg.hue = tmp + 128;//UI value
						}
						if (analog_cfg.item_sel & RSAD_SET_SHARPNESS)//sharpness
						{	
							analog_cfg.sharpness = gpio_i2c_read(i2c_addr, 0x14+analog_cfg.chn);
						}
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_SET_AUDIO_PLAYBACK):
				{
					if (copy_from_user(&audio_playback, argp, sizeof(rsad_audio_playback)))
					{
						return -1;
					}

					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						i2c_addr = raptor3_i2c_addr[audio_playback.chip];
						gpio_i2c_write(i2c_addr,0xff,0x01);			
						tmp = gpio_i2c_read(i2c_addr, 0x23);
						tmp &= 0xe0;
						tmp |= 0x10; //playback
						gpio_i2c_write(i2c_addr,0x23,tmp);
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_SET_AUDIO_DA_VOLUME):
			{
				if (copy_from_user(&audio_da_volume, argp, sizeof(rsad_audio_da_volume)))
				{
					return -1;
				}

				if(audio_da_volume.volume > 63 || audio_da_volume.volume < 0)
				{
				   return -1;
				}

				if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
					(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
				{
					tmp0 = down_interruptible(&RSAD_sem);
					i2c_addr = raptor3_i2c_addr[audio_da_volume.chip];
					gpio_i2c_write(i2c_addr,0xff,0x01);
			
					tmp = (audio_da_volume.volume/4);
					gpio_i2c_write(i2c_addr, 0x22, tmp);
					up(&RSAD_sem);
				}
				break;
			}
			case _IOC_NR(RSAD_SET_AUDIO_DA_MUTE):
				{
					if (copy_from_user(&audio_da_mute, argp, sizeof(rsad_audio_da_mute)))
					{
						return -1;
					}
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						i2c_addr = raptor3_i2c_addr[audio_da_mute.chip];	
						gpio_i2c_write(i2c_addr,0xff,0x01);
						tmp = gpio_i2c_read(i2c_addr, 0x23);
						tmp &=0xe0;
						tmp |=0x19;/*静音*/
						gpio_i2c_write(i2c_addr, 0x23, tmp);
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_DIS_AUDIO_DA_MUTE):
				{
					if (copy_from_user(&audio_da_mute, argp, sizeof(rsad_audio_da_mute)))
					{
						return -1;
					}
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						i2c_addr = raptor3_i2c_addr[audio_da_mute.chip];
						gpio_i2c_write(i2c_addr,0xff,0x01);
						tmp = gpio_i2c_read(i2c_addr, 0x23);
						tmp &= 0xe0;
						tmp |= audio_da_mute.chn;
						gpio_i2c_write(i2c_addr,0x23,tmp);

						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_GET_VIDEO_NORM):
				{
					tmp1 = down_interruptible(&RSAD_sem);
					memset(&vidiofmt,0xff,sizeof(vidiofmt));
					video_fmt_det(&vidiofmt);

					if (copy_to_user(argp, &vidiofmt, sizeof(vidiofmt)))
					{
						up(&RSAD_sem);
						return -1; 
					}
					up(&RSAD_sem);
					break;	
				}
				break;
			case _IOC_NR(IOC_VDEC_SET_EQUALIZER):
				{		
					if (copy_from_user(&tmp, argp, sizeof(unsigned char)))		//通道号
					{
						return -1;
					}
					tmp1 = down_interruptible(&RSAD_sem);
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp0=(tmp/4)*4+AHD_VIDEOLOSS[tmp%4];
						
						CableDistance = RS_APP_VD_MANUAL_CABLE_DISTANCE_Get( tmp0, ch_mode_status[tmp0] );		//获取光缆长度

						vin_eq_set.Ch = tmp0%4;
						vin_eq_set.devnum = tmp0/4;
						vin_eq_set.distance = CableDistance;
						vin_eq_set.FmtDef = ch_mode_status[tmp0];		//使用不转换的视频格式(6158的枚举)

						//video_input_eq_val_set(&vin_eq_set);				//通道号  设备号	线长	视频格式
						rs_manual_video_eq_set(&vin_eq_set);

						rs_coax_init(tmp0);
						rs_set_portmode(tmp0);
						if(ch_mode_status[tmp0] == AHD20_1080P_12_5P_EX || ch_mode_status[tmp0] == AHD20_1080P_15P_EX)
						{
							sDevChInfo.ch = tmp0%4;
							sDevChInfo.devnum = tmp0/4;
							sDevChInfo.fmt_def = ch_mode_status[tmp0];
							video_input_manual_agc_stable_endi(&sDevChInfo,0);		//disable agc stable	
						}
					}
					up(&RSAD_sem);
				}
				break;
			case _IOC_NR(RSAD_GET_TVI_VERSION):
				{

				}
				break;
			case _IOC_NR(RSAD_SET_AD_SAMPLE_RATE):
				{
					if (copy_from_user(&samplerate_width, argp, sizeof(rsad_audio_samplerate_width)))
						return -1;
					
					tmp0 = down_interruptible(&RSAD_sem);
					for(i=0;i<nvp6158_cnt;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[i],0xff,0x01);
						if(samplerate_width.samplerate == RSAD_SAMPLE_RATE_8000)
						{
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x07);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x07, tmp &(~(1<<3)));
							printk("Set AD samplerate is 8K\n");
						}
						else if(samplerate_width.samplerate == RSAD_SAMPLE_RATE_16000)
						{
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x07);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x07, tmp |(1<<3));
							printk("Set AD samplerate is 16K\n");
						}
						else
						{
							printk("Set AD samplerate is error,default 8K\n");
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x07);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x07, tmp &(~(1<<3)));
						}
						
						
						if(samplerate_width.width == RSAD_SAMPLE_WIDTH_8BIT)
						{
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x07);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x07, tmp |(1<<2));
							printk("Set AD width is 8bit\n");
						}
						else if(samplerate_width.width == RSAD_SAMPLE_WIDTH_16BIT)
						{
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x07);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x07, tmp &(~(1<<2)));
							printk("Set AD width is 16bit\n");
						}
						else
						{
							printk("Set AD width is error,default 16bit\n");
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x07);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x07, tmp &(~(1<<2)));
						}
					up(&RSAD_sem);
				}

				break;
			}
			case _IOC_NR(RSAD_SET_DA_SAMPLE_RATE):
			{
					if (copy_from_user(&samplerate_width, argp, sizeof(rsad_audio_samplerate_width)))
						return -1;

					tmp0 = down_interruptible(&RSAD_sem);
					for(i=0;i<nvp6158_cnt;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[i],0xff,0x01);
						if(samplerate_width.samplerate == RSAD_SAMPLE_RATE_8000)
						{
						 	
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x13);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x13, tmp &(~(1<<3)));
							printk("Set DA samplerate is 8K\n");
						}
						else if(samplerate_width.samplerate == RSAD_SAMPLE_RATE_16000)
						{
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x13);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x13, tmp |(1<<3));
							printk("Set DA samplerate is 16K\n");
						}
						else
						{
							printk("Set DA samplerate is error,default 8K\n");
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x13);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x13, tmp &(~(1<<3)));
						}
						
						
						if(samplerate_width.width == RSAD_SAMPLE_WIDTH_8BIT)
						{
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x13);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x13, tmp |(1<<2));
							printk("Set DA width is 8bit\n");
						}
						else if(samplerate_width.width == RSAD_SAMPLE_WIDTH_16BIT)
						{
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x13);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x13, tmp &(~(1<<2)));
							printk("Set DA width is 16bit\n");
						}
						else
						{
							printk("Set DA width is error,default 16bit\n");
							tmp=gpio_i2c_read(raptor3_i2c_addr[i], 0x13);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x13, tmp &(~(1<<2)));
						}
					up(&RSAD_sem);
				}
				break;
			}
			case _IOC_NR(RSAD_SET_AUDIO_I2S):
			{
				if (copy_from_user(&SetI2s, argp, sizeof(rsad_audio_set_i2s)))
						return -1;

				if(SetI2s.vender == 0)//AHD
				{
					tmp0 = down_interruptible(&RSAD_sem);
					gpio_i2c_write(raptor3_i2c_addr[0],0xff,0x01);
					if(SetI2s.type == 0)//maser
					{
						tmp=gpio_i2c_read(raptor3_i2c_addr[0], 0x07);
						tmp |=0x80;
						gpio_i2c_write(raptor3_i2c_addr[0], 0x07, tmp);
						printk("====set AHD record i2s is maser\n");
					}
					else if(SetI2s.type == 1)//slave
					{
						tmp=gpio_i2c_read(raptor3_i2c_addr[0], 0x07);
						tmp &=0x7f;
						gpio_i2c_write(raptor3_i2c_addr[0], 0x07, tmp);
						printk("====set AHD record i2s is slave\n");
					}
					else
					{
						printk("====set AHD record i2s is error SetI2s.type=%d\n",SetI2s.type);
					}
					up(&RSAD_sem);
					
				}
				
				else
				{
					printk("====set record i2s is error SetI2s.vender=%d\n",SetI2s.vender);
				}
				
				break;
			}
			case _IOC_NR(RSAD_GET_AD_TYPE):
				{					
					if((info.author == TVI_TP2802_AHD_NVP6124) || (info.author == AHD_NVP6124))
					{
						tmp0=0;//AHD
						printk("\nthe AD is AHD\n");
					}
					else if(info.author == AHD_NVP6134)
					{
						tmp0=3;//AHD
						printk("\nthe AD is AHD\n");
					}
					else if(info.author == AHD_NVP6158 || info.author == AHD_NVP6168)		//test
					{
						tmp0=4;//6158
						printk("\nthe AD is AHD-6158\n");
					}
					else if(info.author == AHD_NVP6158C || info.author == AHD_NVP6168C)		//test
					{
						tmp0=5;//6158C
						printk("\nthe AD is AHD-6158C\n");
					}/*
					else if(info.author == AHD_NVP6168)
					{
						tmp0=6;//6168
						printk("\nthe AD is AHD-6168\n");
					}
					else if(info.author == AHD_NVP6168C)
					{
						tmp0=7;//6168C
						printk("\nthe AD is AHD-6168C\n");
					}*/
					else
					{
						tmp0=1;//TVI
						printk("\nthe AD is TVI\n");
					}
					if(copy_to_user(argp, &tmp0, sizeof(unsigned char)))
					{
						return -1;
					}
					break;
				}
				break;
			case _IOC_NR(RSAD_ACP_INIT):
				{
					if (copy_from_user(&acpdata, argp, sizeof(rsad_acp_rw_data)))	
						return -1;
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						acpdata.ch =AHD_VIDEOLOSS[acpdata.ch%4] + (acpdata.ch/4)*4;
						pir_bk[acpdata.ch]=acpdata.addr;

						if(ch_mode_status[acpdata.ch] == TVI_HD_30P_EX	||	ch_mode_status[acpdata.ch] == TVI_HD_25P_EX	||
							ch_mode_status[acpdata.ch] == TVI_HD_B_25P_EX 	||	ch_mode_status[acpdata.ch] == TVI_HD_B_30P_EX	||
							ch_mode_status[acpdata.ch] == TVI_HD_50P 		||	ch_mode_status[acpdata.ch] == TVI_HD_60P		||
							ch_mode_status[acpdata.ch] == TVI_FHD_25P	 	|| 	ch_mode_status[acpdata.ch] == TVI_FHD_30P		|| 
							ch_mode_status[acpdata.ch] == TVI_3M_18P 		|| 	ch_mode_status[acpdata.ch] == TVI_5M_12_5P ||
							ch_mode_status[acpdata.ch] == TVI_5M_20P        || ch_mode_status[acpdata.ch] == TVI_8M_15P )
						{
							nvp6158_acp_command(acpdata.ch);
						}
						else if(ch_mode_status[acpdata.ch] == CVI_FHD_30P   || ch_mode_status[acpdata.ch] == CVI_FHD_25P    ||
								ch_mode_status[acpdata.ch] == CVI_HD_30P    || ch_mode_status[acpdata.ch] == CVI_HD_25P     ||
								ch_mode_status[acpdata.ch] == CVI_HD_30P_EX || ch_mode_status[acpdata.ch] == CVI_HD_25P_EX  ||
								ch_mode_status[acpdata.ch] == CVI_4M_30P    || ch_mode_status[acpdata.ch] == CVI_4M_25P     ||
								ch_mode_status[acpdata.ch] == CVI_8M_15P    || ch_mode_status[acpdata.ch] == CVI_8M_12_5P)
						{
							//过滤CVI模式 pir 初始化，解决app在cvi模式下初始化pir，影响同轴反应慢，或点一下出来两下的问题
						}
						else if(ch_mode_status[acpdata.ch] == AHD20_720P_30P_EX_Btype   || ch_mode_status[acpdata.ch] == AHD20_SD_H960_2EX_Btype_NT)
						{

						}
						else
						{
							__nvp6158_set_each_coax_mode(acpdata.ch);
							msleep(20);
							acp_isp_init_rs(acpdata.ch, acpdata.addr);
						}
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_READ_ACP):
				{
					if (copy_from_user(&acpdata, argp, sizeof(rsad_acp_rw_data)))	
						return -1;
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						acpdata.ch =AHD_VIDEOLOSS[acpdata.ch%4] + (acpdata.ch/4)*4;

						if(ch_mode_status[acpdata.ch] == TVI_HD_30P_EX	||	ch_mode_status[acpdata.ch] == TVI_HD_25P_EX	||
							ch_mode_status[acpdata.ch] == TVI_HD_B_25P_EX 	||	ch_mode_status[acpdata.ch] == TVI_HD_B_30P_EX	||
							ch_mode_status[acpdata.ch] == TVI_HD_50P 		||	ch_mode_status[acpdata.ch] == TVI_HD_60P		||
							ch_mode_status[acpdata.ch] == TVI_FHD_25P	 	|| 	ch_mode_status[acpdata.ch] == TVI_FHD_30P		|| 
							ch_mode_status[acpdata.ch] == TVI_3M_18P 		|| 	ch_mode_status[acpdata.ch] == TVI_5M_12_5P 	|| 	
							ch_mode_status[acpdata.ch] == TVI_5M_20P        || ch_mode_status[acpdata.ch] == TVI_8M_15P)
						{
							if(acpdata.opt == 0) //write	
							{
								acp_isp_write(acpdata.ch, acpdata.addr, acpdata.udata);
							}
							else	//read			
							{	
								 RS_TVI_ACP_Rx_Data_Get(acpdata.ch,data);
								 acpdata.udata=data[0];
								if(copy_to_user(argp, &acpdata, sizeof(rsad_acp_rw_data)))	
								{
									printk("IOC_VDEC_ACP_WRITE error\n");
								}
							}	
						}
						else
						{
							if(acpdata.opt == 0) //write	
							{
								acp_isp_write(acpdata.ch, acpdata.addr, acpdata.udata);
							}
							else	//read			
							{				
								acpdata.udata = acp_isp_read_rs(acpdata.ch, acpdata.addr);	
								if(copy_to_user(argp, &acpdata, sizeof(rsad_acp_rw_data)))	
								{
									printk("IOC_VDEC_ACP_WRITE error\n");
								}
							}	
						}
						up(&RSAD_sem);		
					}
				}
				break;
			case _IOC_NR(RSAD_GET_PIR_AGC):
				{
					if (copy_from_user(&acpdata_ex, argp, sizeof(rsad_acp_rw_data_ex)))	
						return -1;
					
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						acpdata_ex.ch =AHD_VIDEOLOSS[acpdata_ex.ch%4] + (acpdata_ex.ch/4)*4;

						if(ch_mode_status[acpdata_ex.ch] == TVI_HD_30P_EX	||	ch_mode_status[acpdata_ex.ch] == TVI_HD_25P_EX	||
							ch_mode_status[acpdata_ex.ch] == TVI_HD_B_25P_EX 	||	ch_mode_status[acpdata_ex.ch] == TVI_HD_B_30P_EX	||
							ch_mode_status[acpdata_ex.ch] == TVI_HD_50P 		||	ch_mode_status[acpdata_ex.ch] == TVI_HD_60P		||
							ch_mode_status[acpdata_ex.ch] == TVI_FHD_25P	 	|| 	ch_mode_status[acpdata_ex.ch] == TVI_FHD_30P		|| 
							ch_mode_status[acpdata_ex.ch] == TVI_3M_18P 		|| 	ch_mode_status[acpdata_ex.ch] == TVI_5M_12_5P 	|| 	
							ch_mode_status[acpdata_ex.ch] == TVI_5M_20P        || ch_mode_status[acpdata_ex.ch] == TVI_8M_15P)
						{
							if(acpdata_ex.opt == 0) //write	
							{
								acp_isp_write(acpdata_ex.ch, acpdata_ex.addr, acpdata_ex.udata[0]);
							}
							else	//read			
							{	
								RS_TVI_ACP_Rx_Data_Get(acpdata_ex.ch,acpdata_ex.udata );
								if(copy_to_user(argp, &acpdata_ex, sizeof(rsad_acp_rw_data_ex)))	
								{
									printk("RSAD_GET_PIR_AGC error(%d)\n",__LINE__);
								}
							}	
						}
						else
						{
							if(acpdata_ex.opt == 0) //write	
							{
								acp_isp_write(acpdata_ex.ch, acpdata_ex.addr, acpdata_ex.udata[0]);
							}
							else	//read			
							{				
								acp_isp_read_rs_ex(acpdata_ex.ch, acpdata_ex.udata);	
								if(copy_to_user(argp, &acpdata_ex, sizeof(rsad_acp_rw_data_ex)))	
								{
									printk("RSAD_GET_PIR_AGC error(%d)\n",__LINE__);
								}
							}	
						}
						up(&RSAD_sem);		
					}
				}
				break;	
			case _IOC_NR(RSAD_SET_UTC_MODE):
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						if (copy_from_user(&tmp, argp, sizeof(unsigned char)))
						{
							up(&RSAD_sem);
							return -1;
						}
						UTC_AUTHOR=tmp;
						printk("\033[1;34m NVP6158 UTC set Urmet 0x%x----- \033[0;39m \n",UTC_AUTHOR);
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_SET_CUSTOM_FUNCTION):
				{

				}
				break;
			case _IOC_NR(RSAD_CLOSE_UTC_SINGLE):
				{
					#if 1
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
			        	tmp1 = down_interruptible(&RSAD_sem);
						if (copy_from_user(&tmp, argp, sizeof(unsigned char)))
						{
							up(&RSAD_sem);
							return -1;
						}
						
						pel_ch=(tmp/4)*4 + AHD_VIDEOLOSS[tmp%4];
						gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], 0xFF, 0x03+((pel_ch%4)/2));
						
			        	if((RSch_mode_status[pel_ch] < NVP6134_VI_720P_2530))
						{
							gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_PEL_OUT+(((pel_ch)%2)*0x80), 0x00);
						}	
						else if( RSch_mode_status[pel_ch] == NVP6134_VI_720P_5060)
						{
							gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_PEL_OUT+(((pel_ch)%2)*0x80), 0x00);
						}
						else if( RSch_mode_status[pel_ch] == NVP6134_VI_720P_2530 || RSch_mode_status[pel_ch] == NVP6134_VI_HDEX)
						{
							gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_PEL_OUT+(((pel_ch)%2)*0x80), 0x00);
						}
						else 
						{
							gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x00);
						}
						printk("=============================NVP6158,RSAD_CLOSE_UTC_SINGLE(chn):%d\n",tmp);
						up(&RSAD_sem);
			        }
					#endif
				}
				break;
			case _IOC_NR(RSAD_INIT_RESET_AHD_AUDIO):
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						for (i = 0; i < nvp6158_cnt; i ++)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x01);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x38, 0x18);
							msleep(20);
							gpio_i2c_write(raptor3_i2c_addr[i], 0x38, 0x08);
						}
						printk("\nRASD set AHD audio reset ok \n");
						up(&RSAD_sem);
					}
					else
					{
						return -1;
					}
				}
				break;
			case _IOC_NR(RSAD_SET_TVI_SCAN_MODE):
				{

				}
				break;
			case _IOC_NR(RSAD_SET_EQ_STAGE):
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						if (copy_from_user(&eq_stage, argp, sizeof(rsad_eq_stage)))
						{
							up(&RSAD_sem);
							return -1;
						}
						tmp0=(eq_stage.ch/4)*4+AHD_VIDEOLOSS[eq_stage.ch%4];
						
						vin_eq_set.Ch = tmp0%4;
						vin_eq_set.devnum = tmp0/4;
						//vin_eq_set.distance = 0;			//先默认
						vin_eq_set.FmtDef = ch_mode_status[tmp0];		//使用不转换的视频格式(6158的枚举)
							
						if(eq_stage.flag == 0) 		//auto
						{
							vin_eq_set.distance = 0;
							//video_input_eq_val_set(&vin_eq_set);
							rs_manual_video_eq_set(&vin_eq_set);
							
							msleep(35);
							//自动获取距离
							CableDistance = RS_APP_VD_MANUAL_CABLE_DISTANCE_Get( tmp0, ch_mode_status[tmp0] );		//获取光缆长度
							vin_eq_set.distance = CableDistance;

							//video_input_eq_val_set(&vin_eq_set);				//通道号  设备号	线长	视频格式
							rs_manual_video_eq_set(&vin_eq_set);
							printk("\n======ch[%d] set EQ auto stage is %d \n",tmp0,vin_eq_set.distance);
						}
						else
						{
							//手动设置等级
							vin_eq_set.distance = eq_stage.stage;
							//video_input_eq_val_set(&vin_eq_set);				//通道号  设备号	线长	视频格式
							rs_manual_video_eq_set(&vin_eq_set);
							printk("\n\033[1;34m======ch[%d] set EQ manual stage is %d \033[0;39m\n",tmp0,eq_stage.stage);
						}

						rs_coax_init(tmp0);
						rs_set_portmode(tmp0);
						if(ch_mode_status[tmp0] == AHD20_1080P_12_5P_EX || ch_mode_status[tmp0] == AHD20_1080P_15P_EX)
						{
							sDevChInfo.ch = tmp0%4;
							sDevChInfo.devnum = tmp0/4;
							sDevChInfo.fmt_def = ch_mode_status[tmp0];
							video_input_manual_agc_stable_endi(&sDevChInfo,0);		//disable agc stable	
						}
						
						up(&RSAD_sem);
					}
				}
				break;
			case _IOC_NR(RSAD_RT_NRT_CHANGE):
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						down_interruptible(&RSAD_sem);
						if (copy_from_user(&common_data, argp, sizeof(rsad_common_data)))
						{
							up(&RSAD_sem);
							return -1;
						}
						tmp0=(common_data.ch/4)*4+AHD_VIDEOLOSS[common_data.ch%4];
						
						if(common_data.data == 0) //nrt
						{
							nvp6158_acp_RT2NRT(tmp0, ch_vfmt_status[tmp0]);
						}
						else if(common_data.data == 1)//rt
						{
							nvp6158_acp_NRT2RT(tmp0);
						}
						else if(common_data.data == 2 )//25fps
						{
							nvp6158_acp_NTSCorPAL(tmp0, PAL,0);
						}
						else if( common_data.data == 3)//30fps
						{
							nvp6158_acp_NTSCorPAL(tmp0, NTSC,0);
						}
						else if( common_data.data == 4)//nrt PAL
						{
							nvp6158_acp_NTSCorPAL(tmp0, PAL,1);
						}
						else if( common_data.data == 5)//nrt NTSC
						{
							nvp6158_acp_NTSCorPAL(tmp0, NTSC,1);
						}
						printk("\n\033[1;34m======RSAD_RT_NRT_CHANGE[ch:%d],common_data.data:%d\033[0;39m\n",tmp0,common_data.data);
						up(&RSAD_sem);
					}
					else
					{
						return -1;
					}
				}
				break;
			case _IOC_NR(RSAD_GET_AGC):
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						tmp1 = down_interruptible(&RSAD_sem);
						if (copy_from_user(&common_data, argp, sizeof(rsad_common_data)))
						{
							up(&RSAD_sem);
							return -1;
						}
						memset(&input_videofmt,0,sizeof(input_videofmt));
						tmp0=(common_data.ch/4)*4+AHD_VIDEOLOSS[common_data.ch%4];

						gpio_i2c_write(raptor3_i2c_addr[tmp0/4], 0xFF, 0x03+((tmp0%4)/2));
						
						acp_read(&input_videofmt,tmp0);
						if(input_videofmt.getacpdata[tmp0][0]==0x55 && input_videofmt.getacpdata[tmp0][7]==0x00 && ((input_videofmt.getacpdata[tmp0][1])&0x80)>>7 == 1)
						{
							common_data.data = input_videofmt.getacpdata[tmp0][2];
						}
						else
						{
							common_data.data = 0xffff;
						}

						if(copy_to_user(argp, &common_data, sizeof(rsad_common_data)))	
						{
							printk("RSAD_GET_AGC error\n");
						}
						up(&RSAD_sem);
					}
				}
				break;
			/***************************************************************
									 ACP firmware update
			***************************************************************/
			case _IOC_NR(IOC_VDEC_ACP_POSSIBLE_FIRMUP):		// 1 检查是否能升级	
				if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
					(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
				{
					printk("\n\033[1;31m [POSSIBLE] \033[0;39m \n");
					if (copy_from_user(&sfirmup_info, argp, sizeof(FIRMWARE_UP_FILE_INFO)))
						return -1;
					tmp1 = down_interruptible(&RSAD_sem);
					sfirmup_info.channel = (sfirmup_info.channel/4)*4 + AHD_VIDEOLOSS[sfirmup_info.channel%4];

					//确定格式:FMT_AHD20,FMT_AHD30,FMT_TVI,FMT_CVI
					oFmtDef = ch_mode_status[sfirmup_info.channel];
					pChFmt = (NC_VI_CH_FMT_S *)RS_HI_VI_Get_ChannelFormat( oFmtDef );
					cp_mode = pChFmt->format_standard;

					if( (oFmtDef == AHD20_720P_25P) || (oFmtDef == AHD20_720P_30P) ||\
						(oFmtDef == AHD20_720P_25P_EX) || (oFmtDef == AHD20_720P_30P_EX) ||\
						(oFmtDef == AHD20_720P_25P_EX_Btype) || (oFmtDef == AHD20_720P_30P_EX_Btype)|| \
						(oFmtDef == CVI_4M_25P) || (oFmtDef == CVI_4M_30P) ||\
			 			(oFmtDef == CVI_8M_15P) || (oFmtDef == CVI_8M_12_5P) )
					{
						vivo_fmt = RS_VI_FindFormatDef( pChFmt->format_standard,  pChFmt->format_resolution, pChFmt->format_fps );
						CoaxTx_Init.vd_dev             = sfirmup_info.channel/4;
						CoaxTx_Init.ch                 = sfirmup_info.channel%4;
						CoaxTx_Init.format_standard    = pChFmt->format_standard;
						CoaxTx_Init.format_resolution  = pChFmt->format_resolution;
						CoaxTx_Init.format_fps         = pChFmt->format_fps;
						CoaxTx_Init.vivo_fmt           = vivo_fmt;
						
						coax_tx_init(&CoaxTx_Init);
						printk("\n[ACP_POSSIBLE_FIRMUP]:[%s] coax_tx_init!!!\n", pChFmt->name );		//1mp同轴升级使用8bit模式  同轴菜单使用16bit
					}
	
					//[FirmUP] Step: "ACP Check"
					//[FirmUP] Step: "FW Ready"
					coax_fw_ready_header_check_from_isp_recv(&sfirmup_info);
					if( sfirmup_info.result == FW_SUCCESS )
					{
						coax_fw_ready_cmd_to_isp_send(&sfirmup_info);
						if(sfirmup_info.result == FW_FAILURE)
						{
							printk(">>>>> DRV[%s:%d] CH:%d, failed to check possible!\n", __func__, __LINE__, sfirmup_info.channel );
						}
					}
					up(&RSAD_sem);
					if(copy_to_user(argp, &sfirmup_info, sizeof(FIRMWARE_UP_FILE_INFO)))
						printk("IOC_VDEC_ACP_POSSIBLE_FIRMUP error\n");
				}
				break;
			case _IOC_NR(IOC_VDEC_ACP_CHECK_ISPSTATUS):		// 2 
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						printk("\n\033[1;31m [CHECK] \033[0;39m \n");
						if (copy_from_user(&sfirmup_info, argp, sizeof(FIRMWARE_UP_FILE_INFO)))
							return -1;
						tmp1 = down_interruptible(&RSAD_sem);
						sfirmup_info.channel = (sfirmup_info.channel/4)*4 + AHD_VIDEOLOSS[sfirmup_info.channel%4];

						//[FirmUP] Step: "FW Ready"
						coax_fw_ready_cmd_ack_from_isp_recv( &sfirmup_info );		//	判断ISP接收状态----正常
						if(sfirmup_info.result == FW_FAILURE)
						{
							printk(">>>>> DRV[%s:%d] CH:%d, failed to check ispstatus!\n", __func__, __LINE__, sfirmup_info.channel );
						}
						
						up(&RSAD_sem);
						if(copy_to_user(argp, &sfirmup_info, sizeof(FIRMWARE_UP_FILE_INFO)))
							printk("IOC_VDEC_ACP_CHECK_ISPSTATUS error\n");
					}
				}
				break;
			case _IOC_NR(IOC_VDEC_ACP_START_FIRMUP):		// 3 
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						printk("\n\033[1;31m [START] \033[0;39m \n");
						if (copy_from_user(&sfirmup_info, argp, sizeof(FIRMWARE_UP_FILE_INFO)))
							return -1;
						tmp1 = down_interruptible(&RSAD_sem);
						sfirmup_info.channel = (sfirmup_info.channel/4)*4 + AHD_VIDEOLOSS[sfirmup_info.channel%4];
						//[FirmUP] Step: "FW Data Send"
						acp_dvr_start_command( &sfirmup_info );
						if(sfirmup_info.result == FW_FAILURE)
						{
							printk(">>>>> DRV[%s:%d] CH:%d, failed to start ACP-firmup!\n", __func__, __LINE__, sfirmup_info.channel );
						}
						
						up(&RSAD_sem);
						if(copy_to_user(argp, &sfirmup_info, sizeof(FIRMWARE_UP_FILE_INFO)))
							printk("IOC_VDEC_ACP_START_FIRMUP error\n");
					}
				}
				break;
			case _IOC_NR(IOC_VDEC_ACP_FIRMUP):		// 4 
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						if (copy_from_user(&sfirmup_info, argp, sizeof(FIRMWARE_UP_FILE_INFO)))
							return -1;
						tmp1 = down_interruptible(&RSAD_sem);

						//[FirmUP] Step: "FW Data Send"
						sfirmup_info.channel = (sfirmup_info.channel/4)*4 + AHD_VIDEOLOSS[sfirmup_info.channel%4];
						acp_dvr_firmware_update( &sfirmup_info );
						if(sfirmup_info.result == FW_FAILURE)
						{
							printk(">>>>> DRV[%s:%d] CH:%d, failed to ACP firmup!\n", __func__, __LINE__, sfirmup_info.channel );
						}
						
						up(&RSAD_sem);
						if(copy_to_user(argp, &sfirmup_info, sizeof(FIRMWARE_UP_FILE_INFO)))
							printk("IOC_VDEC_ACP_FIRMUP error\n");
					}
				}
				break;
			case _IOC_NR(IOC_VDEC_ACP_FIRMUP_END):		// 5 
				{
					if((info.author == AHD_NVP6158) || (info.author == AHD_NVP6158C) || \
						(info.author == AHD_NVP6168) || (info.author == AHD_NVP6168C))
					{
						printk("\n\033[1;31m [END] \033[0;39m \n");
						if (copy_from_user(&sfirmup_info, argp, sizeof(FIRMWARE_UP_FILE_INFO)))
							return -1;
						tmp1 = down_interruptible(&RSAD_sem);
						sfirmup_info.channel = (sfirmup_info.channel/4)*4 + AHD_VIDEOLOSS[sfirmup_info.channel%4];
						//[FirmUP] Step: "FW End"
						
						acp_dvr_end_command( sfirmup_info.result, &sfirmup_info );
						if(sfirmup_info.result == FW_FAILURE)
						{
							printk(">>>>> DRV[%s:%d] CH:%d, failed to end ACP-firmup!\n", __func__, __LINE__, sfirmup_info.channel );
						}
						up(&RSAD_sem);
						if(copy_to_user(argp, &sfirmup_info, sizeof(FIRMWARE_UP_FILE_INFO)))
							printk("IOC_VDEC_ACP_FIRMUP_END error\n");
					}
				}
				break;
		}
	}

	return 0;
}

void nvp6158_system_init(unsigned char chip)
{
	gpio_i2c_write(raptor3_i2c_addr[chip], 0xFF, 0x01);
	gpio_i2c_write(raptor3_i2c_addr[chip], 0x80, 0x40);
	msleep(30);
	gpio_i2c_write(raptor3_i2c_addr[chip], 0x80, 0x61);
	msleep(30);
	gpio_i2c_write(raptor3_i2c_addr[chip], 0x80, 0x60);
	msleep(30);
	printk("nvp6158_system_init done\n");
}

static struct file_operations RSAD_fops = {
	.owner      = THIS_MODULE,
    .unlocked_ioctl	= RSAD_ioctl,
	.open       = RSAD_open,
	.release    = RSAD_close
};

static struct miscdevice RSAD_dev = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "RSAD",
	.fops  		= &RSAD_fops,
};

module_param(boardid, uint, S_IRUGO);
module_param(mainboardid, uint, S_IRUGO);

static int RSAD_GET_INFO(void)
{
	if(check_id(0x60) == NVP6158_R0_ID )
	{
		info.author=AHD_NVP6158;
		printk("The board is NVP6158_R0_ID\n");
	}
	else if(check_id(0x60) == NVP6158C_R0_ID )
	{
		info.author=AHD_NVP6158C;
		printk("The board is NVP6158C_R0_ID\n");
	}
	else if(check_id(0x60) == NVP6168_R0_ID )
	{
		info.author=AHD_NVP6168;
		printk("The board is NVP6168_R0_ID\n");
	}
	else if(check_id(0x60) == NVP6168C_R0_ID )
	{
		info.author=AHD_NVP6168C;
		printk("The board is NVP6168C_R0_ID\n");
	}
	else
	{
		printk("gpio i2c is error!\n");
	}
	return 0;
}

/*******************************************************************************
*	Description		: It is called when "insmod raptor3.ko" command run
*	Argurments			: void
*	Return value		: -1(could not register raptor3 device), 0(success)
*	Modify				:
*	warning			:
*******************************************************************************/
static int __init raptor3_module_init(void)
{
	unsigned char ch;
	unsigned char port;
	int ret = 0;
	int chip;
	int i;
	unsigned char val_9x44;
	video_input_auto_detect vin_auto_det;
	audio_set audio_default_val;

	ret = misc_register(&RSAD_dev);
   	if (ret)
	{
		printk("ERROR: could not register RSAD_dev devices:%#x \n",ret);
        return -1;
	}
	
   	printk("RAPTOR3(B/C) EXT Driver %s \n", DRIVER_VER);
	printk("NVP6158(B/C) EXT Driver %s\n", DRIVER_VER_6158);

	RSAD_GET_INFO();

	if(info.author == AHD_NVP6158 || info.author == AHD_NVP6158C || \
		info.author == AHD_NVP6168 || info.author == AHD_NVP6168C)
	{
		// 	D4008NR 	D4108NR
		if((boardid == 9) || (boardid == 109))
		{
			AHD_VIDEOLOSS[0]=0;
			AHD_VIDEOLOSS[1]=1;
			AHD_VIDEOLOSS[2]=3;
			AHD_VIDEOLOSS[3]=2;
		}
		else if((boardid == 5) || (boardid == 17))		// D4004NR 	D4016NR
		{
			AHD_VIDEOLOSS[0]=3;
			AHD_VIDEOLOSS[1]=2;
			AHD_VIDEOLOSS[2]=0;
			AHD_VIDEOLOSS[3]=1;
		}
		
		for(chip=0;chip<4;chip++)
		{
			chip_id[chip] = check_id(raptor3_i2c_addr[chip]);
			rev_id[chip]  = check_rev(raptor3_i2c_addr[chip]);
			if( (chip_id[chip] != RAPTOR3_4PORT_R0_ID )  	&&
				(chip_id[chip] != RAPTOR3_2PORT_R0_ID) 		&&
				(chip_id[chip] != RAPTOR3_1PORT_R0_ID)		&&
				(chip_id[chip] != RAPTOR4_4PORT_R0_ID) 		&&
				(chip_id[chip] != RAPTOR4_2PORT_R0_ID)		&&
				(chip_id[chip] != AFE_NVP6134E_R0_ID)
			)
			{
				printk("Device ID Error... %x, Chip Count:[%d]\n", chip_id[chip], chip);
				raptor3_i2c_addr[chip] = 0xFF;
				chip_id[chip] = 0xFF;
			}
			else
			{
				printk("Device (0x%x) ID OK... %x , Chip Count:[%d]\n", raptor3_i2c_addr[chip], chip_id[chip], chip);
				printk("Device (0x%x) REV %x\n", raptor3_i2c_addr[chip], rev_id[chip]);
				raptor3_i2c_addr[nvp6158_cnt] = raptor3_i2c_addr[chip];

				if(nvp6158_cnt<chip)
				{
					raptor3_i2c_addr[chip] = 0xFF;
				}

				chip_id[nvp6158_cnt] = chip_id[chip];
				rev_id[nvp6158_cnt]  = rev_id[chip];

				nvp6158_cnt++;
			}

			if((chip == 3) && (nvp6158_cnt < chip))
			{
				for(i = nvp6158_cnt; i < 4; i++)
				{
					chip_id[i] = 0xff;
					rev_id[i]  = 0xff;
				}
			}
		}

		if((chip_id[0] == RAPTOR3_2PORT_R0_ID) || (chip_id[0] == RAPTOR3_4PORT_R0_ID))
		{
			printk("RAPTOR3(B/C) EXT Driver %s COMPILE TIME[%s %s]\n", DRIVER_VER, __DATE__,__TIME__);
			printk("RAPTOR3 Probe\n");
			vdec = chip_id[0]&VDEC_RAPTOR3;
		}
		else if((chip_id[0] == RAPTOR4_2PORT_R0_ID) || (chip_id[0] == RAPTOR4_4PORT_R0_ID))
		{
			printk("RAPTOR4(B/C) EXT Driver %s COMPILE TIME[%s %s]\n", DRIVER_VER, __DATE__,__TIME__);
			printk("RAPTOR4 Probe\n");
			vdec = chip_id[0]&VDEC_RAPTOR4;
		}
	
		printk("Chip Count = %d\n", nvp6158_cnt);
		printk("Address [0x%x][0x%x][0x%x][0x%x]\n",raptor3_i2c_addr[0],raptor3_i2c_addr[1],raptor3_i2c_addr[2],raptor3_i2c_addr[3]);
		printk("Chip Id [0x%x][0x%x][0x%x][0x%x]\n",chip_id[0],chip_id[1],chip_id[2],chip_id[3]);
		printk("Rev Id [0x%x][0x%x][0x%x][0x%x]\n",rev_id[0],rev_id[1],rev_id[2],rev_id[3]);

		for( i = 0; i < 4; i++ )
		{
			decoder_inform.chip_id[i] = chip_id[i];
			decoder_inform.chip_rev[i] = rev_id[i];
			decoder_inform.chip_addr[i] = raptor3_i2c_addr[i];
		}
		decoder_inform.Total_Chip_Cnt = nvp6158_cnt;

	    for( i = 0; i < nvp6158_cnt; i++ )
	    {
	    	if(vdec == VDEC_RAPTOR3)
			{
		    	/* set black screen */
		    	//video_output_colorbar_set(i);
		    	
				/*reset PLL*/
				nvp6158_system_init(i);
				
		    	/* set initialization value  */
		    	for(ch = 0; ch < 4; ch++)
		    	{
					gpio_i2c_write(raptor3_i2c_addr[i], 0xFF, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x22 + (ch * 4), 0x0B);	
					gpio_i2c_write(raptor3_i2c_addr[i], 0xFF, 0x05+ch);
					gpio_i2c_write(raptor3_i2c_addr[i], 0xD5, 0x80);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x00, 0xD0); //clamp speed
					gpio_i2c_write(raptor3_i2c_addr[i], 0x76, 0x00);
		    	}

		    	/* set NOVIDEO */
		    	for(ch = 0; ch < 4; ch++)
		    	{
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0xFF, 0x09);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x80 + (ch * 0x20), 0x00);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x81 + (ch * 0x20), 0x00);

		    		gpio_i2c_write(raptor3_i2c_addr[i], 0xFF, 0x05 + ch);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x2C, 0x00);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0xB8, 0xB8);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0xB9, 0xB2);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x25, 0xDC);


		    		gpio_i2c_write(raptor3_i2c_addr[i], 0xFF, 0x09);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x50 + (ch*4) , 0x30);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x51 + (ch*4) , 0x6F);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x52 + (ch*4) , 0x67);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x53 + (ch*4) , 0x48);

		    		val_9x44 = gpio_i2c_read(raptor3_i2c_addr[i], 0x44);
		    		val_9x44 &= ~(1 << ch);
		    		val_9x44 |= (1 << ch);
		    		gpio_i2c_write(raptor3_i2c_addr[i], 0x44 , val_9x44);
		    	}

		    	if(chip_id[i] == RAPTOR3_4PORT_R0_ID)
		    	{
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x01);
					/* set Port setting */
					for(port = 0; port < 4; port++)
					{
						/* port channel sequence set */
						gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + (port * 2), (port | (port << 4)));
						gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + (port * 2), (port | (port << 4)));
					}

					/* port 1mux set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc8, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc9, 0x00);

					/* all port enable */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xca, 0xf0);		//临时解决 接3MP以上枪机绿屏问题(目前nextchip没好的解决方法)

					/* mux chid set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x55, 0x10);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x56, 0x32);
		    	}
		    	else if (chip_id[i] == RAPTOR3_2PORT_R0_ID)
		    	{
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x01);
					/* set Port setting */
					for(port = 1; port < 3; port++)
					{
						/* port channel sequence set */
#ifdef	SUPPORT_3520D_6158C
						if(port == 1)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + ((port+1) * 2), 0x10);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + ((port+1) * 2), 0x10);
						}
						else if(port == 2)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + ((port-1) * 2), 0x32);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + ((port-1) * 2), 0x32);
						}

#else
						if(port == 1)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + (port * 2), 0x10);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + (port * 2), 0x10);
						}
						else if(port == 2)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + (port * 2), 0x32);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + (port * 2), 0x32);
						}
#endif
					}

					/* port 1mux set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc8, 0x20);
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc9, 0x02);

					/* all port enable */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xca, 0x66);
					
					/* close 656 data output*/
					//gpio_i2c_write(raptor3_i2c_addr[i], 0x96, 0x0f);

					/* mux chid set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x55, 0x10);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x56, 0x10);
		    	}

		    	 // for image enhancement 3M RT upper format when cable distance 300M over
		    	for(ch = 0; ch < 4; ch++)
		    	{
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x05 + ch );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x50, 0xc6 );

		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x0a + (ch / 2));

		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x00 + ( 0x80 * (ch % 2)), 0x80 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x01 + ( 0x80 * (ch % 2)), 0x02 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x02 + ( 0x80 * (ch % 2)), 0x04 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x03 + ( 0x80 * (ch % 2)), 0x80 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x04 + ( 0x80 * (ch % 2)), 0x06 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x05 + ( 0x80 * (ch % 2)), 0x07 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x06 + ( 0x80 * (ch % 2)), 0x80 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x07 + ( 0x80 * (ch % 2)), 0x07 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x08 + ( 0x80 * (ch % 2)), 0x03 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x09 + ( 0x80 * (ch % 2)), 0x08 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x0a + ( 0x80 * (ch % 2)), 0x04 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x0b + ( 0x80 * (ch % 2)), 0x10 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x0c + ( 0x80 * (ch % 2)), 0x08 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x0d + ( 0x80 * (ch % 2)), 0x1f );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x0e + ( 0x80 * (ch % 2)), 0x2e );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x0f + ( 0x80 * (ch % 2)), 0x08 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x10 + ( 0x80 * (ch % 2)), 0x38 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x11 + ( 0x80 * (ch % 2)), 0x35 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x12 + ( 0x80 * (ch % 2)), 0x00 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x13 + ( 0x80 * (ch % 2)), 0x20 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x14 + ( 0x80 * (ch % 2)), 0x0d );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x15 + ( 0x80 * (ch % 2)), 0x80 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x16 + ( 0x80 * (ch % 2)), 0x54 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x17 + ( 0x80 * (ch % 2)), 0xb1 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x18 + ( 0x80 * (ch % 2)), 0x91 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x19 + ( 0x80 * (ch % 2)), 0x1c );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x1a + ( 0x80 * (ch % 2)), 0x87 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x1b + ( 0x80 * (ch % 2)), 0x92 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x1c + ( 0x80 * (ch % 2)), 0xe2 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x1d + ( 0x80 * (ch % 2)), 0x20 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x1e + ( 0x80 * (ch % 2)), 0xd0 );
		    		 gpio_i2c_write(raptor3_i2c_addr[i], 0x1f + ( 0x80 * (ch % 2)), 0xcc );
				}
			}

			// Start NVP6168/NVP6168C Initialize - For Raptor4
			else if(vdec == VDEC_RAPTOR4)
			{
				gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x01 );
				gpio_i2c_write(raptor3_i2c_addr[i], 0x97, 0x00); // CH_RST ON
				gpio_i2c_write(raptor3_i2c_addr[i], 0x97, 0x0f); // CH_RST OFF
				gpio_i2c_write(raptor3_i2c_addr[i], 0x7a, 0x0f); // Clock Auto ON
				gpio_i2c_write(raptor3_i2c_addr[i], 0xca, 0xff); // VCLK_EN, VDO_EN

				gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00 );
				gpio_i2c_write(raptor3_i2c_addr[i], 0x23, 0x41); // channel 0
				gpio_i2c_write(raptor3_i2c_addr[i], 0x27, 0x41); // channel 1
				gpio_i2c_write(raptor3_i2c_addr[i], 0x2b, 0x41); // channel 2
				gpio_i2c_write(raptor3_i2c_addr[i], 0x2f, 0x41); // channel 3

				for(ch=0; ch<4; ch++)
				{
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x05 +ch);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x00, 0xd0);

					gpio_i2c_write(raptor3_i2c_addr[i], 0x05, 0x04);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x08, 0x55);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x47, 0xEE);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x59, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x76, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x77, 0x80);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x78, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x79, 0x11);
					gpio_i2c_write(raptor3_i2c_addr[i], 0xB8, 0xB8); // H_PLL_BYPASS
					gpio_i2c_write(raptor3_i2c_addr[i], 0x7B, 0x11); // v_rst_on
					gpio_i2c_write(raptor3_i2c_addr[i], 0xb9, 0x72);
					gpio_i2c_write(raptor3_i2c_addr[i], 0xB8, 0xB8); // No Video Set

					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x00+ch, 0x10);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x22+(ch*0x04), 0x0b);
				}

				gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x13);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x12, 0x04);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x2E, 0x10);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x30, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x77, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x3a, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x3b, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x3c, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x3d, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x3e, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x3f, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x70, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x72, 0x05);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x7A, 0x10);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x61, 0x03);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x62, 0x00);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x63, 0x03);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x64, 0x00);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x65, 0x03);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x66, 0x00);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x67, 0x03);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x68, 0x00);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x60, 0x0f);
	//				gpio_i2c_write(raptor3_i2c_addr[i], 0x60, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x07, 0x47);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x59, 0x24);

				/* SAM Range */
				gpio_i2c_write(raptor3_i2c_addr[i], 0x74, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x76, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x78, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x75, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x77, 0xff);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x79, 0xff);

				gpio_i2c_write(raptor3_i2c_addr[i], 0x01, 0x0c);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x2f, 0xc8);

				// EQ Stage Get
				gpio_i2c_write(raptor3_i2c_addr[i], 0x73, 0x23);

				gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x09);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x96, 0x03);
				gpio_i2c_write(raptor3_i2c_addr[i], 0xB6, 0x03);
				gpio_i2c_write(raptor3_i2c_addr[i], 0xD6, 0x03);
				gpio_i2c_write(raptor3_i2c_addr[i], 0xF6, 0x03);

				/********************************************************
				 * Audio Default Setting
				 ********************************************************/
				gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x01);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x05, 0x09);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x07, 0x88); // Master Mode, 16Khz, 16bit_Width
				gpio_i2c_write(raptor3_i2c_addr[i], 0x22, 0x08);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x44, 0x00);

				gpio_i2c_write(raptor3_i2c_addr[i], 0x00, 0x02);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x06, 0x1B);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x31, 0x0A);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x32, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x46, 0x10);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x47, 0x01);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x48, 0xD0);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x49, 0x88);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x58, 0x02);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x59, 0x00);

				/********************************************************
				 * VI Channel ID
				 ********************************************************/
				gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x55, 0x10);
				gpio_i2c_write(raptor3_i2c_addr[i], 0x56, 0x10);

				if (chip_id[i] == RAPTOR4_4PORT_R0_ID)
				{
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x01);
					/* set Port setting */
					for(port = 0; port < 4; port++)
					{
						/* port channel sequence set */
						gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + (port * 2), (port | (port << 4)));
						gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + (port * 2), (port | (port << 4)));
					}

					/* port 1mux set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc8, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc9, 0x00);

					/* all port enable */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xca, 0xff);

					/* mux chid set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x55, 0x10);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x56, 0x32);
				}
				else if (chip_id[i] == RAPTOR4_2PORT_R0_ID)
				{
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x01);
					/* set Port setting */
					for(port = 1; port < 3; port++)
					{
						/* port channel sequence set */
#ifdef	SUPPORT_3520D_6158C
						if(port == 1)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + ((port+1) * 2), 0x10);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + ((port+1) * 2), 0x10);
						}
						else if(port == 2)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + ((port-1) * 2), 0x32);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + ((port-1) * 2), 0x32);
						}

#else
						if(port == 1)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + (port * 2), 0x10);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + (port * 2), 0x10);
						}
						else if(port == 2)
						{
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc0 + (port * 2), 0x32);
							gpio_i2c_write(raptor3_i2c_addr[i], 0xc1 + (port * 2), 0x32);
						}
#endif
					}
					/* port 1mux set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc8, 0x20);
					gpio_i2c_write(raptor3_i2c_addr[i], 0xc9, 0x02);

					/* all port enable */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xca, 0x66);

					/* mux chid set */
					gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x55, 0x10);
					gpio_i2c_write(raptor3_i2c_addr[i], 0x56, 0x10);
				}

			}
		}

		for( i = 0; i < nvp6158_cnt; i++ )
		{
			gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x00);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x00, 0x11);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x01, 0x11);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x02, 0x11);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x03, 0x11);
			msleep(100);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x00, 0x10);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x01, 0x10);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x02, 0x10);
			gpio_i2c_write(raptor3_i2c_addr[i], 0x03, 0x10);
		}
		
		for(ch=0;ch<nvp6158_cnt*4;ch++)
		{
			//nvp6158_chnmode_convert(ch, vdec_mode,NVP6134_VI_1080P_NOVIDEO);    //默认设置为1080P模式.
			//RS_OnVIdeoSetFormat(ch);
			ch_mode_status[ch] = CVI_HD_30P_EX;
			RS_NoVIdeoSetFormat(ch,ch_mode_status[ch]);
			ch_vfmt_status[ch] = vdec_mode;
		}
		
		/* set auto mode, but if you want to change mode from auto to manual mode, check this!(2017-07-30) */
		for( i = 0; i < ( nvp6158_cnt*4 ); i++ )
		{
			vin_auto_det.ch = i%4;
			vin_auto_det.devnum = i/4;
			if(vdec == VDEC_RAPTOR4)
			{
				nvp6168_video_input_auto_detect_set(&vin_auto_det);
			}
			else
			{
				video_input_auto_detect_set(&vin_auto_det);
			}
		}

		for( chip = 0; chip <  nvp6158_cnt ; chip++ )
		{
			if(chip_id[chip] == NVP6158C_R0_ID)
			{
				if((boardid == 5) || (boardid == 9)|| (boardid == 17))
				{
					nvp6158_set_portmode(chip, 1, NVP6158_OUTMODE_4MUX_MIX, 0);
					nvp6158_set_portmode(chip, 2, NVP6158_OUTMODE_4MUX_MIX, 0);
				}
				else
				{
					nvp6158_set_portmode(chip, 1, NVP6158_OUTMODE_2MUX_FHD, VO_PORT[0]);
					nvp6158_set_portmode(chip, 2, NVP6158_OUTMODE_2MUX_FHD, VO_PORT[1]);
				}
			}
		}

		if(vdec == VDEC_RAPTOR3)
		{
			gpio_i2c_write(raptor3_i2c_addr[i], 0xff, 0x13 );
    		gpio_i2c_write(raptor3_i2c_addr[i], 0x12, 0xff );
		}
		
		/* set audio(default) */
		if(vdec == VDEC_RAPTOR4)
		{
			nvp6168_audio_default_set(&audio_default_val);
		}
		else
		{
			audio_default_set(&audio_default_val);
		}
		
		/* set mux according to the CHIPID */
		for( i = 0; i < 4; i++ )
		{
			if( chip_id[i] == RAPTOR3_2PORT_R0_ID )
			{
				oMux = VI_2MULTIPLEX_MODE;
				printk(">>>>> RAPTOR3_2PORT_R0_ID\n");
				break;
			}
			else
			{
				oMux = VI_1MULTIPLEX_MODE;
				printk(">>>>> RAPTOR3_4PORT_R0_ID\n");
				break;
			}
		}
	}
	return 0;
}

/*******************************************************************************
*	Description		: It is called when "rmmod nvp61XX_ex.ko" command run
*	Argurments		: void
*	Return value	: void
*	Modify			:
*	warning			:
*******************************************************************************/
static void __exit raptor3_module_exit(void)
{
	misc_deregister(&RSAD_dev);

    printk("RAPTOR3/4 DEVICE DRIVER UNLOAD SUCCESS\n");
}

module_init(raptor3_module_init);
module_exit(raptor3_module_exit);

MODULE_LICENSE("GPL");

/*******************************************************************************
*	End of file
*******************************************************************************/
