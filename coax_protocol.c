/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: Raptor3 Device Driver
*  Description	: coax_protocol.c
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
#include <linux/unistd.h>
#include "common.h"
#include "coax_table.h"
#include "coax_protocol.h"
#include "gpio_i2c.h"
#include "RSAD.h"

#define SD_BIT 			0
#define AHD8_BIT 		1
#define AHD16_BIT 		2
#define AHD4_5M_BIT 	3
#define CVI_BIT 		4
#define CVI_NEW_BIT	5
#define TVI_BIT1_0 	6
#define TVI_BIT2_0 	7

#define	ONE_PACKET_MAX_SIZE 	139
#define 	COAX_FW_TIMEOUT 			20

extern unsigned char RSch_mode_status[16];
extern unsigned char ch_mode_status[16];
extern unsigned int raptor3_i2c_addr[4];
extern unsigned int cp_mode;
extern NC_VIVO_CH_FORMATDEF RS_VI_FindFormatDef( NC_FORMAT_STANDARD format_standard,NC_FORMAT_RESOLUTION format_resolution, NC_FORMAT_FPS format_fps  );
extern int chip_id[4];
extern unsigned char UTC_AUTHOR;

unsigned char ACP_RX_D0 = 0x78;
extern unsigned int pir_bk[16];
unsigned char lcnt_bak=0x00, lcntm_bak=0x00;
extern unsigned char UTC_AUTHOR;

void Delay(volatile int usec)
{
	volatile int i,j;	
    for(i = 0; i< usec*2;i++)
    {
		for(j=0;j<10;j++)
		{;}
    }
}

int valueconvert(char type,unsigned char pel_ch,int *Src,NC_COAX_CMD_DEF cmd,unsigned char udata,unsigned char data)			//数据不需重新赋值时  直接退出
{
	int i,j;
	unsigned char tmp_data[8];
	if(type == AHD4_5M_BIT)
	{
		//printk("\033[1;31m	valueconvert---ahd_4_5m--->cmd:0x%x  udata:0x%x  \033[0;39m\n",cmd,udata);
		switch(cmd)
		{
			case  COAX_CMD_PTZ_UP:		
			case  COAX_CMD_OSD_UP:	
				Src[0] = 0x00;Src[1] = 0x08;Src[2] = 0x00;Src[3] = udata;
			break;
			case  COAX_CMD_PTZ_DOWN:
			case  COAX_CMD_OSD_DOWN:	
				Src[0] = 0x00;Src[1] = 0x10;Src[2] = 0x00;Src[3] = udata;
			break;
			case  COAX_CMD_PTZ_LEFT:
			case  COAX_CMD_OSD_LEFT:	
				Src[0] = 0x00;Src[1] = 0x04;Src[2] = udata;Src[3] = 0x00;
			break;
			case  COAX_CMD_PTZ_RIGHT:
			case  COAX_CMD_OSD_RIGHT:	
				Src[0] = 0x00;Src[1] = 0x02;Src[2] = udata;Src[3] = 0x00;
			break;
			case COAX_CMD_LEFT_UP:
				Src[0] = 0x00;Src[1] = 0x0c;Src[2] = udata;Src[3] = udata;
			break;	
			case COAX_CMD_LEFT_DOWN:
				Src[0] = 0x00;Src[1] = 0x14;Src[2] = udata;Src[3] = udata;
			break;	
			case COAX_CMD_RIGHT_UP:
				Src[0] = 0x00;Src[1] = 0x0a;Src[2] = udata;Src[3] = udata;
			break;	
			case COAX_CMD_RIGHT_DOWN:
				Src[0] = 0x00;Src[1] = 0x12;Src[2] = udata;Src[3] = udata;
			break;	
			case  COAX_CMD_IRIS_INC:
				Src[0] = 0x02;Src[1] = 0x00;Src[2] = 0x00;Src[3] = 0x00;
			break;
			case  COAX_CMD_IRIS_DEC:	
				Src[0] = 0x04;Src[1] = 0x00;Src[2] = 0x00;Src[3] = 0x00;
			break;
			case COAX_CMD_SET_POINT:
				Src[0] = 0x00;Src[1] = 0x03;Src[2] = 0x00;Src[3] = udata;	
			break;
			case COAX_CMD_CLEAR_POINT:
				Src[0] = 0x00;Src[1] = 0x05;Src[2] = 0x00;Src[3] = udata;	
			break;
			case COAX_CMD_GOTO_POINT:
				Src[0] = 0x00;Src[1] = 0x07;Src[2] = 0x00;Src[3] = udata;	
			break;
			case COAX_CMD_AUTO:
				Src[0] = 0x00;Src[1] = 0x07;Src[2] = 0x00;Src[3] = 0x63;	
			break;
			case COAX_CMD_AUTO_STOP:
				Src[0] = 0x00;Src[1] = 0x07;Src[2] = 0x00;Src[3] = 0x60;	
			break;
			case COAX_CMD_SET_WHITE_LED:
				Src[0] = 0xA0;Src[1] = 0xB0;Src[2] = udata;Src[3] = data;
			break;
			case COAX_CMD_SET_WHITE_LED_MODE:
				Src[0] = 0xA1;Src[1] = 0xB1;Src[2] = udata;Src[3] = data;
			break;
			/*		// 6124
			case PELCO_CMD_ALL_0xFF:
				Src[0] = 0xff;Src[1] = 0xff;Src[2] = 0xff;Src[3] = 0xff;	
			break;
			*/
			default : return 0; //unexpected command
		}
	}
	else if (type == AHD8_BIT)
	{
		switch(cmd)
		{
			case  COAX_CMD_PTZ_UP:		
			case  COAX_CMD_OSD_UP:	
				Src[4] = 0x00;Src[5] = 0x08;Src[6] = 0x00;Src[7] = udata;
			break;
			case  COAX_CMD_PTZ_DOWN:
			case  COAX_CMD_OSD_DOWN:	
				Src[4] = 0x00;Src[5] = 0x10;Src[6] = 0x00;Src[7] = udata;
			break;
			case  COAX_CMD_PTZ_LEFT:
			case  COAX_CMD_OSD_LEFT:	
				Src[4] = 0x00;Src[5] = 0x04;Src[6] = udata;Src[7] = 0x00;
			break;
			case  COAX_CMD_PTZ_RIGHT:
			case  COAX_CMD_OSD_RIGHT:	
				Src[4] = 0x00;Src[5] = 0x02;Src[6] = udata;Src[7] = 0x00;
			break;
			case COAX_CMD_LEFT_UP:
				Src[4] = 0x00;Src[5] = 0x0c;Src[6] = udata;Src[7] = udata;
			break;	
			case COAX_CMD_LEFT_DOWN:
				Src[4] = 0x00;Src[5] = 0x14;Src[6] = udata;Src[7] = udata;
			break;	
			case COAX_CMD_RIGHT_UP:
				Src[4] = 0x00;Src[5] = 0x0a;Src[6] = udata;Src[7] = udata;
			break;	
			case COAX_CMD_RIGHT_DOWN:
				Src[4] = 0x00;Src[5] = 0x12;Src[6] = udata;Src[7] = udata;
			break;	
			case  COAX_CMD_IRIS_INC:
				Src[4] = 0x02;Src[5] = 0x00;Src[6] = 0x00;Src[7] = 0x00;
			break;
			case  COAX_CMD_IRIS_DEC:	
				Src[4] = 0x04;Src[5] = 0x00;Src[6] = 0x00;Src[7] = 0x00;
			break;
			case COAX_CMD_SET_POINT:
				Src[4] = 0x00;Src[5] = 0x03;Src[6] = 0x00;Src[7] = udata;	
			break;
			case COAX_CMD_CLEAR_POINT:
				Src[4] = 0x00;Src[5] = 0x05;Src[6] = 0x00;Src[7] = udata;	
			break;
			case COAX_CMD_GOTO_POINT:
				Src[4] = 0x00;Src[5] = 0x07;Src[6] = 0x00;Src[7] = udata;	
			break;
			case COAX_CMD_AUTO:
				Src[4] = 0x00;Src[5] = 0x07;Src[6] = 0x00;Src[7] = 0x63;	
			break;
			case COAX_CMD_AUTO_STOP:
				Src[4] = 0x00;Src[5] = 0x07;Src[6] = 0x00;Src[7] = 0x60;	
			break;
			case COAX_CMD_SET_WHITE_LED:
				Src[4] = 0xA0;Src[5] = 0xB0;Src[6] = udata;Src[7] = data;
			break;
			case COAX_CMD_SET_WHITE_LED_MODE:
				Src[4] = 0xA1;Src[5] = 0xB1;Src[6] = udata;Src[7] = data;
			break;
			default : return 0; //unexpected command
		}
	}	
	else if (type == AHD16_BIT)
	{
		switch(cmd)
		{
			case  COAX_CMD_SCAN_SR: 		
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0xE0;Src[3] = 0x46;
			break;
			case  COAX_CMD_SCAN_ST: 		
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0xE0;Src[3] = 0x00;
			break;
			case  COAX_CMD_PRESET1: 		
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0xE0;Src[3] = 0x80;
			break;
			case  COAX_CMD_PRESET2: 	
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0xE0;Src[3] = 0x40;
			break;
			case  COAX_CMD_PRESET3: 		
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0xE0;Src[3] = 0xC0;
			break;
			case  COAX_CMD_PTN1_SR: 		
				Src[0] = 0x00;Src[1] = 0xF8;Src[2] = 0xF8;Src[3] = 0x01;
			break;
			case  COAX_CMD_PTN1_ST: 		
				Src[0] = 0x00;Src[1] = 0x84;Src[2] = 0x84;Src[3] = 0x01;
			break;
			case  COAX_CMD_PTN2_SR: 		
				Src[0] = 0x00;Src[1] = 0xF8;Src[2] = 0xF8;Src[3] = 0x02;
			break;
			case  COAX_CMD_PTN2_ST: 		
				Src[0] = 0x00;Src[1] = 0x84;Src[2] = 0x84;Src[3] = 0x02;
			break;
			case  COAX_CMD_PTN3_SR: 		
				Src[0] = 0x00;Src[1] = 0xF8;Src[2] = 0xF8;Src[3] = 0x03;
			break;
			case  COAX_CMD_PTN3_ST: 		
				Src[0] = 0x00;Src[1] = 0x84;Src[2] = 0x84;Src[3] = 0x03;
			break;
			case  COAX_CMD_RUN: 			
				Src[0] = 0x00;Src[1] = 0xC4;Src[2] = 0xC4;Src[3] = 0x00;
			break;
			case COAX_CMD_SET_WHITE_LED:
				Src[0] = 0xA0;Src[1] = 0xB0;Src[2] = udata;Src[3] = data;
			break;
			case COAX_CMD_SET_WHITE_LED_MODE:
				Src[0] = 0xA1;Src[1] = 0xB1;Src[2] = udata;Src[3] = data;
			break;
			//case COAX_CMD_ALL_0xFF:
			//	Src[0] = 0xff;Src[1] = 0xff;Src[2] = 0xff;Src[3] = 0xff;	
			//break;

			default : return 0; //unexpected command
		}
	}
	else if(type == TVI_BIT1_0)
	{
		//printk("\033[1;31m	valueconvert---tvi_v1_0--->cmd:0x%x  udata:0x%x  \033[0;39m\n",cmd,udata);
		switch(cmd)
		{
			case COAX_CMD_PTZ_UP:
			case COAX_CMD_OSD_UP:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x06;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=0x0;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_PTZ_DOWN:
			case COAX_CMD_OSD_DOWN:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x07;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=0x0;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_PTZ_RIGHT:
			case COAX_CMD_OSD_RIGHT:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x08;
				Src[3]=0x0;
				Src[4]=0x80;
				Src[5]=udata;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_PTZ_LEFT:
			case COAX_CMD_OSD_LEFT:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x09;
				Src[3]=0x0;
				Src[4]=0x80;
				Src[5]=udata;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_LEFT_UP:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x0A;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=udata;
				Src[6]=0x0;
				Src[7]=0x0;
				break;	
			case COAX_CMD_LEFT_DOWN:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x0B;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=udata;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_RIGHT_UP:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x0C;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=udata;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_RIGHT_DOWN:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x0D;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=udata;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_IRIS_INC:
				Src[0]=0xb5;
				Src[1]=0x01;
				Src[2]=0x0F;
				Src[3]=0x0;
				Src[4]=0x80;
				Src[5]=0x0;
				Src[6]=0x0;
				Src[7]=0x0;
				//printk("\033[1;31m	valueconvert---COAX_CMD_IRIS_INC  \033[0;39m\n");
				break;
			case COAX_CMD_SET_POINT:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x15;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=0x0;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_CLEAR_POINT:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x16;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=0x0;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_AUTO:
			case COAX_CMD_GOTO_POINT:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x17;
				Src[3]=udata;
				Src[4]=0x80;
				Src[5]=0x0;
				Src[6]=0x0;
				Src[7]=0x0;
				break;
			case COAX_CMD_SET_CAMERA:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x87;
				Src[3]=0x0;
				Src[4]=0x80;
				Src[5]=0x0;
				Src[6]=0x0;
				Src[7]=0x0;
				break;	
			case COAX_CMD_SET_WHITE_LED:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x88;
				Src[3]=udata;    //LED time
				Src[4]=0x80;   
				Src[5]=data;//buzzer time
				Src[6]=0x0;
				Src[7]=0x0;
				break;	
			case COAX_CMD_SET_WHITE_LED_MODE:
				Src[0]=0xb5;
				Src[1]=0x0;
				Src[2]=0x89;
				Src[3]=udata;    //LED_mode：0代表长亮，1代表快闪（50ms亮,50ms灭），2代表中闪（150ms亮,150ms灭），3代表慢闪（250ms亮,250ms灭）
				Src[4]=0x80;   
				Src[5]=data; //default: 0
				Src[6]=0x0;
				Src[7]=0x0;
				break;	
			default : return 0;
		}
		Src[8]=0x0;
		for(i=0;i<8;i++)
		{
			if(i != 4)
			{
				Src[8] = Src[8] + Src[i];
			}
		}
		Src[8]=Src[8] & 0xff;
		Src[9]=0x80;
	}
	else if ((type == CVI_BIT) || (type == CVI_NEW_BIT))
	{
		switch(cmd)
		{
			case COAX_CMD_SET_POINT:
				tmp_data[0]=0xa5;
				tmp_data[1]=0x01;
				tmp_data[2]=0x81;
				tmp_data[3]=0x00;
				tmp_data[4]=udata;
				tmp_data[5]=0x00;
				break;
			case COAX_CMD_CLEAR_POINT:
				tmp_data[0]=0x3f;
				tmp_data[1]=0x01;
				tmp_data[2]=0x0b;
				tmp_data[3]=0x06;
				tmp_data[4]=udata;
				break;
			case COAX_CMD_AUTO:
			case COAX_CMD_GOTO_POINT:
				tmp_data[0]=0xa5;
				tmp_data[1]=0x01;
				tmp_data[2]=0x83;
				tmp_data[3]=0x00;
				tmp_data[4]=udata;
				tmp_data[5]=0x00;
				break;
			default : return 0;
		}
		memset(Src,0x00,sizeof(int)*7);
		for(i=0;i<6;i++)  //change high to low
		{
			for(j=0;j<8;j++)
			{
				Src[i] += ((tmp_data[i] >>(7-j))&0x01) << j;
			}
		}

		//计算校验和
		if(cmd == COAX_CMD_CLEAR_POINT)
		{
			tmp_data[5] = (tmp_data[0] + tmp_data[1] + tmp_data[2] + tmp_data[3] + tmp_data[4])&0xff;
			for(j=0;j<8;j++)
			{
				Src[5] += ((tmp_data[5] >>(7-j))&0x01) << j;
			}
		}
		else
		{
			tmp_data[6] = (tmp_data[0] + tmp_data[1] + tmp_data[2] + tmp_data[3] + tmp_data[4] + tmp_data[5])&0xff;
			for(j=0;j<8;j++)
			{
				Src[6] += ((tmp_data[6] >>(7-j))&0x01) << j;
			}
		}
	}
	
	else if (type == SD_BIT)
	{
		//printk("\033[1;31m	valueconvert---sd--->cmd:0x%x  udata:0x%x  \033[0;39m\n",cmd,udata);
		switch(cmd)
		{
			case  COAX_CMD_PTZ_UP:	
			case  COAX_CMD_OSD_UP:
				Src[0] = 0x00;Src[1] = 0x10;Src[2] = 0x00;Src[3] = 0x4C;		//{ 0x00, 0x10, 0x00, 0x00, EOD }		1
				break;
			case  COAX_CMD_PTZ_DOWN:	
			case  COAX_CMD_OSD_DOWN:
				Src[0] = 0x00;Src[1] = 0x08;Src[2] = 0x00;Src[3] = 0x4C;
				break;
			case  COAX_CMD_SCAN_SR: 	
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0x00;Src[3] = 0x46;
				break;
			case  COAX_CMD_SCAN_ST: 	
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0x00;Src[3] = 0x00;
				break;
			case  COAX_CMD_PRESET1: 	
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0x00;Src[3] = 0x80;
				break;
			case  COAX_CMD_PRESET2: 	
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0x00;Src[3] = 0x40;
				break;
			case  COAX_CMD_PRESET3: 	
				Src[0] = 0x00;Src[1] = 0xE0;Src[2] = 0x00;Src[3] = 0xC0;
				break;
			case  COAX_CMD_PTN1_SR: 	
				Src[0] = 0x00;Src[1] = 0xF8;Src[2] = 0x00;Src[3] = 0x01;
				break;
			case  COAX_CMD_PTN1_ST: 	
				Src[0] = 0x00;Src[1] = 0x84;Src[2] = 0x00;Src[3] = 0x01;
				break;
			case  COAX_CMD_PTN2_SR: 	
				Src[0] = 0x00;Src[1] = 0xF8;Src[2] = 0x00;Src[3] = 0x02;
				break;
			case  COAX_CMD_PTN2_ST: 	
				Src[0] = 0x00;Src[1] = 0x84;Src[2] = 0x00;Src[3] = 0x02;
				break;
			case  COAX_CMD_PTN3_SR: 	
				Src[0] = 0x00;Src[1] = 0xF8;Src[2] = 0x00;Src[3] = 0x03;
				break;
			case  COAX_CMD_PTN3_ST: 	
				Src[0] = 0x00;Src[1] = 0x84;Src[2] = 0x00;Src[3] = 0x03;
				break;
			case  COAX_CMD_RUN: 		
				Src[0] = 0x00;Src[1] = 0xC4;Src[2] = 0x00;Src[3] = 0x00;
				break;

			default : return 0; 
		}
	}
	else
	{
		switch(cmd)
		{
			case COAX_CMD_SET_WHITE_LED:
				Src[0] = 0xA0;Src[1] = 0xB0;Src[2] = udata;Src[3] = data;
			break;
			case COAX_CMD_SET_WHITE_LED_MODE:
				Src[0] = 0xA1;Src[1] = 0xB1;Src[2] = udata;Src[3] = data;
			break;
			default : return 0;
		}
	}

	//printk("\n=============		RSch_mode_status:0x%x	pel_ch:%d============\n",RSch_mode_status[pel_ch],pel_ch);
	return 0;
}

/*=======================================================================================================
 ********************************************************************************************************
 **************************** Coaxial protocol up stream function ***************************************
 ********************************************************************************************************
 * Coaxial protocol up stream Flow
 * 1. Up stream initialize       -  coax_tx_init
 * 2. Fill upstream data & Send  -  coax_tx_cmd_send
 *
 * Coaxial protocol up stream register(example: channel 0)
 * (3x00) tx_baud               : 1 bit duty
 * (3x02) tx_pel_baud           : 1 bit duty of pelco(SD)
 * (3x03) tx_line_pos0          : up stream line position(low)
 * (3x04) tx_line_pos1          : up stream line position(high)
 * (3x05) tx_line_count         : up stream output line number in 1 frame
 * (3x07) tx_pel_line_pos0      : up stream line position of pelco(low)
 * (3x08) tx_pel_line_pos1      : up stream line position of pelco(high)
 * (3x0A) tx_line_count_max     : up stream output total line
 * (3x0B) tx_mode               : up stream Mode set (ACP, CCP, TCP)
 * (3x0D) tx_sync_pos0          : up stream sync start position(low)
 * (3x0E) tx_sync_pos1          : up stream sync start position(high)
 * (3x2F) tx_even               : up stream SD..Interlace
 * (3x0C) tx_zero_length        : Only CVI 4M
 ========================================================================================================*/
/**************************************************************************************
* @desc
* 	RAPTOR3's This function initializes the register associated with the UP Stream..
*
* @param_in		(NC_VD_COAX_Tx_Init_STR *)coax_tx_mode			UP Stream Initialize structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_TX_INIT
***************************************************************************************/
NC_VD_ACP_CMDDEF_STR *__NC_VD_ACP_Get_CommandFormat_Get( NC_COAX_CMD_DEF def )
{
	NC_VD_ACP_CMDDEF_STR *pRet = &coax_cmd_lists[def];
	if( pRet == NULL )
	{
		printk("Not Supported format Yet!!!(%d)\n",def);
	}
	return  pRet;
}

NC_VD_COAX_Init_STR *__NC_VD_COAX_InitFormat_Get( NC_VIVO_CH_FORMATDEF def )
{
	NC_VD_COAX_Init_STR *pRet = &coax_init_lists[def];
	if( pRet == NULL )
	{
		printk("Not Supported format Yet!!!(%d)\n",def);
	}
	return  pRet;
}

NC_VD_COAX_Init_STR *__NC_VD_COAX_16bit_InitFormat_Get( NC_VIVO_CH_FORMATDEF def )
{
	NC_VD_COAX_Init_STR *pRet = &coax_acp_16bit_init_lists[def];
	if( pRet == NULL )
	{
		printk("Not Supported format Yet!!!(%d)\n",def);
	}
	return  pRet;
}

int __NC_VD_COAX_Command_Each_Copy( unsigned char *Dst, int *Src )
{
	int items = 0;

	while( Src[items] != EOD )
	{
		Dst[items] = Src[items];
		items++;
	}

	return items;
}

//////////		已将__NC_VD_COAX_16bit_Command_Copy合并进
int __NC_VD_COAX_Command_Copy( NC_FORMAT_STANDARD format, NC_VIVO_CH_FORMATDEF vivofmt, unsigned char *Dst, 
			NC_VD_ACP_CMDDEF_STR *pCMD ,unsigned char ch,NC_COAX_CMD_DEF cmd,unsigned char udata,unsigned char data)
{
	int cmd_cnt = 0;
	char bit=AHD8_BIT;

	if( format == FMT_SD )
	{
		//printk("\033[1;32m SD_BIT	\033[0;39m \n");
		bit=SD_BIT;
		valueconvert(bit,ch,pCMD->sd,cmd,udata,data);
		cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->sd );
	}
	else if( (format == FMT_AHD20) || (format == FMT_AHD30) )
	{
		if( 	vivofmt == AHD30_3M_18P 		|| vivofmt == AHD30_3M_25P 		|| vivofmt == AHD30_3M_30P		||
				vivofmt == AHD30_4M_30P 		|| vivofmt == AHD30_4M_25P 		|| vivofmt == AHD30_4M_15P		||
				vivofmt == AHD30_5M_20P 		|| vivofmt == AHD30_5M_12_5P 		|| vivofmt == AHD30_5_3M_20P   	|| 
				vivofmt == AHD30_8M_12_5P || vivofmt == AHD30_8M_15P )
		{
			//printk("\033[1;32m AHD4_5M_BIT	\033[0;39m \n");
			bit=AHD4_5M_BIT;
			valueconvert(bit,ch,pCMD->ahd_4_5m,cmd,udata,data);
			cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->ahd_4_5m );
		}
		else if( 	(vivofmt == AHD20_720P_25P) 			|| (vivofmt == AHD20_720P_30P) ||\
					(vivofmt == AHD20_720P_25P_EX) 		|| (vivofmt == AHD20_720P_30P_EX) ||\
					(vivofmt == AHD20_720P_25P_EX_Btype) || (vivofmt == AHD20_720P_30P_EX_Btype) )
		{
			bit=AHD16_BIT;
			valueconvert(bit,ch,pCMD->ahd_16bit,cmd,udata,data);
			cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->ahd_16bit );
		}
		else
		{
			//printk("\033[1;32m AHD8_BIT	\033[0;39m \n");
			valueconvert(bit,ch,pCMD->ahd_8bit,cmd,udata,data);
			cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->ahd_8bit );
		}
	}
	else if( format == FMT_CVI )
	{
		if( (vivofmt == CVI_4M_25P) || (vivofmt == CVI_4M_30P))
		{
			bit = CVI_NEW_BIT;
			valueconvert(bit,ch,pCMD->cvi_new_cmd,cmd,udata,data);
			cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->cvi_new_cmd );
		}
		else//CVI 800W
		{
			bit = CVI_BIT;
			valueconvert(bit,ch,pCMD->cvi_cmd,cmd,udata,data);
			cmd_cnt= __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->cvi_cmd );
		}
	}
	else if( format == FMT_TVI )
	{
		// 2018.11.30 修改为TVI 720P走2.0，其余走1.0
		if((vivofmt == TVI_HD_B_25P_EX) || (vivofmt == TVI_HD_B_30P_EX))
		{
			bit = TVI_BIT2_0;
			valueconvert(bit,ch,pCMD->tvi_v2_0,cmd,udata,data);
			cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->tvi_v2_0 );
		}
		else
		{
			bit = TVI_BIT1_0;
			valueconvert(bit,ch,pCMD->tvi_v1_0,cmd,udata,data);
			cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->tvi_v1_0 );
		}
	}
	else
		printk("NC_VD_COAX_Tx_Command_Send::Command Copy Error!!\n");


	return cmd_cnt;
}

int __NC_VD_COAX_16bit_Command_Copy( NC_FORMAT_STANDARD format, NC_VIVO_CH_FORMATDEF vivofmt, unsigned char *Dst, 
			NC_VD_ACP_CMDDEF_STR *pCMD,unsigned char ch,NC_COAX_CMD_DEF cmd,unsigned char udata,unsigned char data )
{
	int cmd_cnt = 0;
	char bit=AHD8_BIT;

	if( (vivofmt == AHD20_720P_25P) || (vivofmt == AHD20_720P_30P) ||\
		(vivofmt == AHD20_720P_25P_EX) || (vivofmt == AHD20_720P_30P_EX) ||\
		(vivofmt == AHD20_720P_25P_EX_Btype) || (vivofmt == AHD20_720P_30P_EX_Btype) )
	{
		bit=AHD16_BIT;
		valueconvert(bit,ch,pCMD->ahd_16bit,cmd,udata,data);
		cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->ahd_16bit );
	}
	else if( (vivofmt == CVI_4M_25P) || (vivofmt == CVI_4M_30P) ||\
			 (vivofmt == CVI_5M_20P) ||(vivofmt == CVI_8M_15P) || (vivofmt == CVI_8M_12_5P) )
	{
		cmd_cnt = __NC_VD_COAX_Command_Each_Copy( Dst, pCMD->cvi_new_cmd );
	}
	else
	{
		printk("[drv_coax] Can not send commands!! Unsupported format!!\n" );
		return 0;
	}

	return cmd_cnt;
}

/**************************************************************************************
* @desc
* 	RAPTOR3's This function initializes the register associated with the UP Stream..
*
* @param_in		(NC_VD_COAX_Tx_Init_STR *)coax_tx_mode			UP Stream Initialize structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_TX_INIT
***************************************************************************************/
void coax_tx_init( void *p_param )
{
	unsigned char achn;
	NC_VD_COAX_STR *coax_tx = (NC_VD_COAX_STR*)p_param;

	unsigned char ch = coax_tx->ch;
	unsigned char distance = 0;

	NC_VD_COAX_Init_STR *CoaxVal = __NC_VD_COAX_InitFormat_Get( coax_tx->vivo_fmt);

	achn = (ch%4) + (coax_tx->vd_dev)*4;
	printk("\n[drv_coax] Ch: %d Format >>>>> %s\n", achn, CoaxVal->name );

#if 0
	// Cable distance check
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->devnum], 0xFF, 0x13);          // BANK 13
	distance = gpio_i2c_read(raptor3_i2c_addr[coax_tx->devnum], (0xA0+ch)); // 0:short, 1:100m, 2:200m, 3:300m, 4:400m, 5:500m, 0x0F:Unknown

	distance = distance&0x0F;
	if(distance == 0x0F)
	{
		printk("DRV::Cable distance Unknown!!\n");
		distance = 0;
	}
	else
		printk("DRV::Cable distance(%x)\n", distance);
#endif

	// MPP Coaxial mode select Ch1~4
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x01);  // BANK 1
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xA8+ch, 0x08+ch%4);  // MPP_TST_SEL1

	// Coaxial each mode set
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x05+ch%4);  // BANK 5
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x2F, 0x00);       // MPP_H_INV, MPP_V_INV, MPP_F_INV
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x30, 0xE0);       // MPP_H_S[7~4], MPP_H_E[3:0]
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x31, 0x43);       // MPP_H_S[7:0]
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x32, 0xA2);       // MPP_H_E[7:0]
 	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x7C, CoaxVal->rx_src);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x7D, CoaxVal->rx_slice_lev);

	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2));

	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x00+((ch%2)*0x80), CoaxVal->tx_baud[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x02+((ch%2)*0x80), CoaxVal->tx_pel_baud[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x03+((ch%2)*0x80), CoaxVal->tx_line_pos0[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x04+((ch%2)*0x80), CoaxVal->tx_line_pos1[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x05+((ch%2)*0x80), CoaxVal->tx_line_count);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x07+((ch%2)*0x80), CoaxVal->tx_pel_line_pos0[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x08+((ch%2)*0x80), CoaxVal->tx_pel_line_pos1[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0A+((ch%2)*0x80), CoaxVal->tx_line_count_max);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0B+((ch%2)*0x80), CoaxVal->tx_mode);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0D+((ch%2)*0x80), CoaxVal->tx_sync_pos0[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0E + ((ch%2)*0x80), CoaxVal->tx_sync_pos1[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x2F+((ch%2)*0x80), CoaxVal->tx_even);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0C+((ch%2)*0x80), CoaxVal->tx_zero_length);

#if DBG_TX_INIT_PRINT
	printk("[drv]tx_src:            5x7C>> 0x%02X\n", CoaxVal->rx_src );
	printk("[drv]tx_slice_lev:      5x7D>> 0x%02X\n", CoaxVal->rx_slice_lev );
	printk("[drv]tx_pel_baud:       3x02>> 0x%02X\n", CoaxVal->tx_baud[distance] );
	printk("[drv]tx_pel_line_pos0:  3x07>> 0x%02X\n", CoaxVal->tx_pel_line_pos0[distance] );
	printk("[drv]tx_pel_line_pos1:  3x08>> 0x%02X\n", CoaxVal->tx_pel_line_pos1[distance] );
	printk("[drv]tx_mode:           3x0B>> 0x%02X\n", CoaxVal->tx_mode );
	printk("[drv]tx_baud:           3x00>> 0x%02X\n", CoaxVal->tx_baud[distance]);
	printk("[drv]tx_line_pos0:      3x03>> 0x%02X\n", CoaxVal->tx_line_pos0[distance] );
	printk("[drv]tx_line_pos1:      3x04>> 0x%02X\n", CoaxVal->tx_line_pos1[distance] );
	printk("[drv]tx_line_count:     3x05>> 0x%02X\n", CoaxVal->tx_line_count );
	printk("[drv]tx_line_count_max: 3x0A>> 0x%02X\n", CoaxVal->tx_line_count_max );
	printk("[drv]tx_sync_pos0:      3x0D>> 0x%02X\n", CoaxVal->tx_sync_pos0[distance] );
	printk("[drv]tx_sync_pos1:      3x0E>> 0x%02X\n", CoaxVal->tx_sync_pos1[distance] );
	printk("[drv]tx_even:           3x2F>> 0x%02X\n", CoaxVal->tx_even );
	printk("[drv]tx_zero_length:    3x0C>> 0x%02X\n", CoaxVal->tx_zero_length);
#endif

}

/**************************************************************************************
* @desc
* 	RAPTOR3's This function initializes the register associated with the UP Stream..
*
* @param_in		(NC_VD_COAX_Tx_Init_STR *)coax_tx_mode			UP Stream Initialize structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_TX_INIT
***************************************************************************************/
void coax_tx_16bit_init( void *p_param )
{
	NC_VD_COAX_STR *coax_tx = (NC_VD_COAX_STR*)p_param;
	NC_VD_COAX_Init_STR *CoaxVal;

	int ch = coax_tx->ch;
	int fmt = coax_tx->vivo_fmt;
	unsigned char distance = 0;

	if( (fmt == AHD20_720P_25P) || (fmt == AHD20_720P_30P) ||\
		(fmt == AHD20_720P_25P_EX) || (fmt == AHD20_720P_30P_EX) ||\
		(fmt == AHD20_720P_25P_EX_Btype) || (fmt == AHD20_720P_30P_EX_Btype))
	{
		printk("[drv_coax]Ch: %d ACP 16bit initialize!!!\n", ch );
	}
	else if( (fmt == CVI_4M_25P) || (fmt == CVI_4M_30P) || (fmt == CVI_5M_20P))	//cvi 4mp:cvi_new_cmd  cvi 8mp:cvi_cmd,直接return，否则同轴不能调用
	{
		printk("[drv_coax]Ch: %d CVI New Protocol initialize!!!\n", ch );
	}
	else
	{
		if(fmt == NC_VIVO_CH_FORMATDEF_UNKNOWN)
			printk("[drv_coax]Ch: %d Can not initialize!! Unsupported format!!\n", ch );
		return;
	}

	CoaxVal = __NC_VD_COAX_16bit_InitFormat_Get( coax_tx->vivo_fmt );
	printk("[drv_coax]Ch: %d Format >>>>> %s\n", ch, CoaxVal->name );

#if 0
	// Cable distance check
	gpio_i2c_write(raptor3_i2c_addr[chip_num], 0xFF, 0x13);          // BANK 13
	distance = gpio_i2c_read(raptor3_i2c_addr[chip_num], (0xA0+ch)); // 0:short, 1:100m, 2:200m, 3:300m, 4:400m, 5:500m, 0x0F:Unknown

	distance = distance&0x0F;
	if(distance == 0x0F)
	{
		printk("DRV::Cable distance Unknown!!\n");
		distance = 0;
	}
	else
		printk("DRV::Cable distance(%x)\n", distance);
#endif

	// MPP Coaxial mode select Ch1~4
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x01);  // BANK 1
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xA8+ch, 0x08+ch%4);  // MPP_TST_SEL1

	// Coaxial each mode set
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x05+ch%4);  // BANK 5
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x2F, 0x00);       // MPP_H_INV, MPP_V_INV, MPP_F_INV
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x30, 0xE0);       // MPP_H_S[7~4], MPP_H_E[3:0]
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x31, 0x43);       // MPP_H_S[7:0]
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x32, 0xA2);       // MPP_H_E[7:0]
 	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x7C, CoaxVal->rx_src);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x7D, CoaxVal->rx_slice_lev);

	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2));

	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x00+((ch%2)*0x80), CoaxVal->tx_baud[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x02+((ch%2)*0x80), CoaxVal->tx_pel_baud[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x03+((ch%2)*0x80), CoaxVal->tx_line_pos0[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x04+((ch%2)*0x80), CoaxVal->tx_line_pos1[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x05+((ch%2)*0x80), CoaxVal->tx_line_count);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x07+((ch%2)*0x80), CoaxVal->tx_pel_line_pos0[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x08+((ch%2)*0x80), CoaxVal->tx_pel_line_pos1[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0A+((ch%2)*0x80), CoaxVal->tx_line_count_max);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0B+((ch%2)*0x80), CoaxVal->tx_mode);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0D+((ch%2)*0x80), CoaxVal->tx_sync_pos0[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0E + ((ch%2)*0x80), CoaxVal->tx_sync_pos1[distance]);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x2F+((ch%2)*0x80), CoaxVal->tx_even);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0C+((ch%2)*0x80), CoaxVal->tx_zero_length);

#if DBG_TX_INIT_PRINT
	printk("[drv]tx_src:            5x7C>> 0x%02X\n", CoaxVal->rx_src );
	printk("[drv]tx_slice_lev:      5x7D>> 0x%02X\n", CoaxVal->rx_slice_lev );
	printk("[drv]tx_pel_baud:       3x02>> 0x%02X\n", CoaxVal->tx_baud[distance] );
	printk("[drv]tx_pel_line_pos0:  3x07>> 0x%02X\n", CoaxVal->tx_pel_line_pos0[distance] );
	printk("[drv]tx_pel_line_pos1:  3x08>> 0x%02X\n", CoaxVal->tx_pel_line_pos1[distance] );
	printk("[drv]tx_mode:           3x0B>> 0x%02X\n", CoaxVal->tx_mode );
	printk("[drv]tx_baud:           3x00>> 0x%02X\n", CoaxVal->tx_baud[distance]);
	printk("[drv]tx_line_pos0:      3x03>> 0x%02X\n", CoaxVal->tx_line_pos0[distance] );
	printk("[drv]tx_line_pos1:      3x04>> 0x%02X\n", CoaxVal->tx_line_pos1[distance] );
	printk("[drv]tx_line_count:     3x05>> 0x%02X\n", CoaxVal->tx_line_count );
	printk("[drv]tx_line_count_max: 3x0A>> 0x%02X\n", CoaxVal->tx_line_count_max );
	printk("[drv]tx_sync_pos0:      3x0D>> 0x%02X\n", CoaxVal->tx_sync_pos0[distance] );
	printk("[drv]tx_sync_pos1:      3x0E>> 0x%02X\n", CoaxVal->tx_sync_pos1[distance] );
	printk("[drv]tx_even:           3x2F>> 0x%02X\n", CoaxVal->tx_even );
	printk("[drv]tx_zero_length:    3x0C>> 0x%02X\n", CoaxVal->tx_zero_length);
#endif

}

/**************************************************************************************
* @desc
* 	RAPTOR3's Send UP Stream command.
*
* @param_in		(NC_VD_COAX_SET_STR *)coax_tx_mode			    UP Stream Command structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_TX_CMD_SEND
***************************************************************************************/
void coax_tx_cmd_send( void *p_param ,unsigned char udata,unsigned char data)
{
	NC_VD_COAX_STR *coax_tx = (NC_VD_COAX_STR*)p_param;
	int i;
	int cmd_cnt = 0;
	unsigned char ch              = coax_tx->ch;
	NC_COAX_CMD_DEF cmd           = coax_tx->cmd;
	NC_FORMAT_STANDARD format     = coax_tx->format_standard;
	NC_VIVO_CH_FORMATDEF vivofmt  = coax_tx->vivo_fmt;

	unsigned char achn = (coax_tx->vd_dev)*4 + ch;
	unsigned char tx_bank          = 0x00;
	unsigned char tx_cmd_addr      = 0x00;
	unsigned char tx_shot_addr     = 0x00;
	unsigned char command[32]      = {0,};
	//unsigned char TCP_CMD_Stop_v10[10] = { 0xb5, 0x00, 0x14, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc9, 0x80 };
	//unsigned char TCP_CMD_Stop_v20[10] = { 0xb5, 0x01, 0x14, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc5, 0x80 };

	// UP Stream get from coax table
	NC_VD_COAX_Init_STR *CoaxVal = __NC_VD_COAX_InitFormat_Get(vivofmt);    // Get from Coax_Tx_Init Table
	NC_VD_ACP_CMDDEF_STR *pCMD   = __NC_VD_ACP_Get_CommandFormat_Get(cmd);  // Get From Coax_Tx_Command Table
	printk("[drv_coax]Ch: %d   Command >>>>> %s >>> autostop = %d\n", achn, pCMD->name, pCMD->autostop);

	tx_bank      = CoaxVal->tx_bank;
	tx_cmd_addr  = CoaxVal->tx_cmd_addr;
	tx_shot_addr = CoaxVal->tx_shot_addr;

/**		将16bit的合并在一起	**/	
	// UP Stream command copy in coax command table
	cmd_cnt = __NC_VD_COAX_Command_Copy( format, vivofmt, command, pCMD ,achn,cmd,udata,data);

/////RS	2017.11.02  
	if( 	(vivofmt == AHD20_720P_25P) 			|| (vivofmt == AHD20_720P_30P) ||\
			(vivofmt == AHD20_720P_25P_EX) 		|| (vivofmt == AHD20_720P_30P_EX) ||\
			(vivofmt == AHD20_720P_25P_EX_Btype) 	|| (vivofmt == AHD20_720P_30P_EX_Btype) ||\
 			(vivofmt == CVI_4M_25P) 				|| (vivofmt == CVI_4M_30P))
	{
		if(format == FMT_AHD20)
		{
			// Adjust Bank
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );

			// fill Reset
			for(i=0;i<cmd_cnt;i++)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x20+((ch%2)*0x80)+i, 0);
			}

			// Command Shot
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x01);
			msleep(30);
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x00);


			// fill command
			for(i=0;i<cmd_cnt;i++)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x20+((ch%2)*0x80)+i, command[i]);
			}

			// Command Shot
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x01);
			msleep(30);
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x00);
		}
		else if(format == FMT_CVI)
		{
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+(ch%4));
			for(i=0;i<cmd_cnt;i++)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_cmd_addr+i, command[i]);
			}
		
			// Shot
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
		}
		else
			return;
	}
	else
	{
		if( format == FMT_SD)
		{
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+((ch%4)/2) );
			for(i=0;i<cmd_cnt;i++)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, 0);
			}
			// Shot
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
			msleep(CoaxVal->shot_delay);
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);

			msleep(CoaxVal->reset_delay);

			for(i=0;i<cmd_cnt;i++)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i]);
			}
			// Shot
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
			msleep(CoaxVal->shot_delay);
			//if(cmd == COAX_CMD_STOP)
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
		}
		else if(format == FMT_CVI)
		{
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+(ch%4));
			for(i=0;i<cmd_cnt;i++)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_cmd_addr+i, command[i]);
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x10+i, 0xff);
				//printk(" \r Line:%d  str[%d] :: 0x%x \n",__LINE__, i, command[i]);
			}

			// Shot
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
			if((cmd == COAX_CMD_STOP) ||(pCMD->autostop==1))
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
		}
		else if(format == FMT_TVI)
		{
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+((ch%4)/2) );
			for(i=0;i<cmd_cnt;i++)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i]);
				printk(" \r Line:%d  str[%d] :: 0x%x \n",__LINE__, i, command[i]);
			}

			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x08);			//解决TVI 2MP白光摄像机enable后再disable，图像仍为彩色的问题
			msleep(30);
			if(cmd != COAX_CMD_SET_CAMERA)
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);

			//if((cmd == COAX_CMD_STOP) ||(pCMD->autostop==1))
			//gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);

			/*if(pCMD->autostop==1)  //stop command 
			{
				if(vivofmt == TVI_4M_15P)
					msleep(70);
				else
					msleep(30);
			
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+((ch%4)/2));
				for(i=0;i<10;i++)
				{
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_cmd_addr+((ch%2)*0x80)+i, TCP_CMD_Stop_v10[i]);
				}

				// shot
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
			}*/
		}
		else
		{
					//原程序
					
			/*
			if(	vivofmt == AHD20_1080P_30P 	|| vivofmt == AHD20_1080P_25P 	|| 
				vivofmt == AHD30_3M_30P		|| vivofmt == AHD30_3M_25P		||
				vivofmt == AHD30_3M_18P 	)
			*/
			if(vivofmt == AHD20_1080P_30P || vivofmt == AHD20_1080P_25P || vivofmt == AHD20_1080P_15P_EX)
			{
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+((ch%4)/2) );
				if((UTC_AUTHOR&0x10)== 0x10)
				{	
					//gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0A+((ch%2)*0x80), 0x03);
					for(i=0;i<4;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i+4]);
					}
					
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
					msleep( 25 );
					if((UTC_AUTHOR&0x01)== 1)
					{						
					}
					else
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
					}

					command[0]=0xaa;
					command[1]=0x3c;
					command[2]=0xff;
					command[3]=0xff;
					for(i=0;i<4;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev],(tx_cmd_addr+((ch%2)*0x80))+i, command[i]);
					}
					
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
					msleep( 25 );
					if((UTC_AUTHOR&0x01)== 1)
					{
					}
					else
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
					}

					command[0]=0xaa;
					command[1]=0x1b;
					command[2]=0x00;
					command[3]=0x00;
					for(i=0;i<4;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i]);
					}
					
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
					msleep( 25 );
					if((UTC_AUTHOR&0x01)== 1)
					{
					}
					else
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
					}

					command[0]=0xaa;
					command[1]=0x3b;
					command[2]=0x00;
					command[3]=0x00;
					for(i=0;i<4;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i]);
					}
					
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
					msleep( 25 );
					if((UTC_AUTHOR&0x01)== 1)
					{
					}
					else
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
					}
				}
				else if((UTC_AUTHOR&0x02)== 0x02)
				{
					//gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0A+((ch%2)*0x80), 0x03);
					for(i=0;i<4;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i+4]);
					}
					
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
					if((UTC_AUTHOR&0x01)== 1)
					{
					}
					else
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
					}
					
					for(i=0;i<4;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i+4]);
					}
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
					if((UTC_AUTHOR&0x01)== 1)
					{
					}
					else
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
					}
				}
				else
				{
					//gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0A+((ch%2)*0x80), CoaxVal->tx_line_count_max);
					/*
					for(i=0;i<cmd_cnt;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, 0x00);
					}

					nvp6158_presend_comm(ch);
					*/
					for(i=0;i<4;i++)
					{
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i+4]);
						printk(" \r Line:%d  str[%d] :: 0x%x \n",__LINE__, i, command[i+4]);
					}

					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
					if((UTC_AUTHOR&0x01)== 1)
					{
					}
					else
					{
						if(vivofmt == AHD20_1080P_15P_EX)
						{
							msleep(35);
						}
						gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
					}			
				}
			}
			else
			{
				#if 1
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+((ch%4)/2) );
				for(i=0;i<cmd_cnt;i++)
				{
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((ch%2)*0x80))+i, command[i]);
					printk(" \r Line:%d  str[%d] :: 0x%x \n",__LINE__, i, command[i]);
				}

				// Shot
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
				/*if((UTC_AUTHOR&0x01)== 1)
				{
				}
				else*/
				{
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
				}
				#else		//添加同轴2响应
				gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+((achn%4)/2) );

				for(i=0;i<cmd_cnt;i++)
				{
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((achn%2)*0x80))+i, 0x00);
				}
				nvp6158_presend_comm(achn);
				for(i=0;i<cmd_cnt;i++)
				{
					gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], (tx_cmd_addr+((achn%2)*0x80))+i, command[i]);		// AHD 4M 25P--->0x10
					printk(" \r Line:%d  str[%d] :: 0x%x \n",__LINE__, i, command[i]);
				}

				if((UTC_AUTHOR&0x01)== 1)
				{
					nvp6158_send_comm(achn,cmd, 0);
				}
				else
				{
					//printk("---------------------\n");
					nvp6158_send_comm(achn,cmd, 1);
				}
				
				#endif
			}
		}

		if((cmd == COAX_CMD_STOP) && (format != FMT_CVI)) //stop command sends twice in case of AF camera losses response...
		{
			msleep(35);
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
			gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
		}
	}
}

/**************************************************************************************
* @desc
* 	RAPTOR3's Send UP Stream command.
*
* @param_in		(NC_VD_COAX_SET_STR *)coax_tx_mode			    UP Stream Command structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_TX_CMD_SEND
***************************************************************************************/
void coax_tx_16bit_cmd_send( void *p_param ,unsigned char udata,unsigned char data)
{
	NC_VD_COAX_STR *coax_tx = (NC_VD_COAX_STR*)p_param;
	int i;
	int cmd_cnt = 0;
	unsigned char ch              = coax_tx->ch;
	NC_COAX_CMD_DEF cmd           = coax_tx->cmd;
	NC_FORMAT_STANDARD format     = coax_tx->format_standard;
	NC_VIVO_CH_FORMATDEF vivofmt  = coax_tx->vivo_fmt;

	unsigned char tx_bank          = 0x00;
	unsigned char tx_cmd_addr      = 0x00;
	unsigned char tx_shot_addr     = 0x00;
	unsigned char command[32]      ={0,};

	// UP Stream get from coax table
	NC_VD_COAX_Init_STR *CoaxVal = __NC_VD_COAX_InitFormat_Get(vivofmt);    // Get from Coax_Tx_Init Table
	NC_VD_ACP_CMDDEF_STR *pCMD   = __NC_VD_ACP_Get_CommandFormat_Get(cmd);  // Get From Coax_Tx_Command Table
	printk("[drv_coax]Ch: %d Command >>>>> %s\n", ch, pCMD->name );

	tx_bank      = CoaxVal->tx_bank;
	tx_cmd_addr  = CoaxVal->tx_cmd_addr;
	tx_shot_addr = CoaxVal->tx_shot_addr;

	// UP Stream command copy in coax command table
	cmd_cnt = __NC_VD_COAX_16bit_Command_Copy( format, vivofmt, command, pCMD,ch,cmd,udata,data);

	// Adjust Bank
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );

	// fill Reset
	for(i=0;i<cmd_cnt;i++)
	{
		gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x20+((ch%2)*0x80)+i, 0);
	}

	// Command Shot
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x01);
	msleep(30);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x00);


	// fill command
	for(i=0;i<cmd_cnt;i++)
	{
		gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x20+((ch%2)*0x80)+i, command[i]);
	}

	// Command Shot
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x01);
	msleep(30);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0x0c+((ch%2)*0x80), 0x00);

}

void coax_tx_cvi_new_cmd_send( void *p_param,unsigned char udata,unsigned char data)
{
	NC_VD_COAX_STR *coax_tx = (NC_VD_COAX_STR*)p_param;
	int i;
	int cmd_cnt = 0;
//	unsigned char vd_dev          = coax_tx->vd_dev;
	unsigned char ch              = coax_tx->ch;
	NC_COAX_CMD_DEF cmd           = coax_tx->cmd;
	NC_FORMAT_STANDARD format     = coax_tx->format_standard;
	NC_VIVO_CH_FORMATDEF vivofmt  = coax_tx->vivo_fmt;

	unsigned char tx_bank          = 0x00;
	unsigned char tx_cmd_addr      = 0x00;
	unsigned char tx_shot_addr     = 0x00;
	unsigned char command[32]      ={0,};

	// UP Stream get from coax table
	NC_VD_COAX_Init_STR *CoaxVal = __NC_VD_COAX_InitFormat_Get(vivofmt);    // Get from Coax_Tx_Init Table
	NC_VD_ACP_CMDDEF_STR *pCMD   = __NC_VD_ACP_Get_CommandFormat_Get(cmd);  // Get From Coax_Tx_Command Table
	printk("[drv_coax]Ch: %d Command >>>>> %s\n", ch, pCMD->name );

	tx_bank      = CoaxVal->tx_bank;
	tx_cmd_addr  = CoaxVal->tx_cmd_addr;
	tx_shot_addr = CoaxVal->tx_shot_addr;

	// UP Stream command copy in coax command table
	cmd_cnt = __NC_VD_COAX_16bit_Command_Copy( format, vivofmt, command, pCMD ,ch,cmd,udata,data);

	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, tx_bank+(ch%4));
	for(i=0;i<cmd_cnt;i++)
	{
		gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_cmd_addr+i, command[i]);
	}

	// Shot
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], 0xFF, 0x03+((ch%4)/2) );
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x01);
	gpio_i2c_write(raptor3_i2c_addr[coax_tx->vd_dev], tx_shot_addr+((ch%2)*0x80), 0x00);
}

/*=======================================================================================================
********************************************************************************************************
**************************** Coaxial protocol down stream function *************************************
********************************************************************************************************
 *
 * Coaxial protocol down stream Flow
 * 1. Down stream initialize   -  coax_rx_init
 * 2. Down stream data read    -  coax_rx_data_get
 *
 * Coaxial protocol down stream register(example: channel 0)
 * (3x63) rx_comm_on         : Coaxial Down Stream Mode ON/OFF ( 0: OFF / 1: ON )
 * (3x62) rx_area            : Down Stream Read Line Number
 * (3x66) rx_signal_enhance  : Signal Enhance ON/OFF ( 0: OFF / 1: ON )
 * (3x69) rx_manual_duty     : 1 Bit Duty Setting ( HD@25, 30P 0x32  /  HD@50, 60P, FHD@25, 30P 0x64 )
 * (3x60) rx_head_matching   : Same Header Read (EX. 0x48)
 * (3x61) rx_data_rz         : The lower 2 bits set Coax Mode.. ( 0 : A-CP ), ( 1 : C-CP ), ( 2 : T-CP )
 * (3x68) rx_sz              : Down stream size setting
 * (3x3A)                    : Down stream buffer clear
 ========================================================================================================*/
/**************************************************************************************
* @desc
* 	RAPTOR3's   This function initializes the register associated with the Down Stream.
*
* @param_in		(NC_VD_COAX_SET_STR *)coax_tx_mode			    Down Stream Initialize structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_RX_INIT
***************************************************************************************/
void coax_rx_init(void *p_param)
{
	NC_VD_COAX_STR *coax_rx = (NC_VD_COAX_STR*)p_param;
	unsigned char ch             = coax_rx->ch;
	NC_VIVO_CH_FORMATDEF vivofmt = coax_rx->vivo_fmt;

	NC_VD_COAX_Init_STR *coax_rx_val = __NC_VD_COAX_InitFormat_Get(vivofmt);

	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0xFF, BANK3+((ch%4)/2));

	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0x63+((ch%2)*0x80), coax_rx_val->rx_comm_on);
	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0x62+((ch%2)*0x80), coax_rx_val->rx_area);
	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0x66+((ch%2)*0x80), coax_rx_val->rx_signal_enhance);
	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0x69+((ch%2)*0x80), coax_rx_val->rx_manual_duty);
	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0x60+((ch%2)*0x80), coax_rx_val->rx_head_matching);
	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0x61+((ch%2)*0x80), coax_rx_val->rx_data_rz);
	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0x68+((ch%2)*0x80), coax_rx_val->rx_sz);
#if	DBG_RX_INIT_PRINT
	printk("[drv]Channel %d Format >>>>> %s\n", ch, coax_rx_val->name );
	printk("[drv]rx_head_matching:  0x60 >> 0x%02X\n", coax_rx_val->rx_head_matching);
	printk("[drv]rx_data_rz:        0x61 >> 0x%02X\n", coax_rx_val->rx_data_rz);
	printk("[drv]rx_area:           0x62 >> 0x%02X\n", coax_rx_val->rx_area);
	printk("[drv]rx_comm_on:        0x63 >> 0x%02X\n", coax_rx_val->rx_comm_on );
	printk("[drv]rx_signal_enhance: 0x66 >> 0x%02X\n", coax_rx_val->rx_signal_enhance);
	printk("[drv]rx_sz:             0x68 >> 0x%02X\n", coax_rx_val->rx_sz);
	printk("[drv]rx_manual_duty:    0x69 >> 0x%02X\n", coax_rx_val->rx_manual_duty);
#endif

}

/**************************************************************************************
* @desc
* 	RAPTOR3's   Read down stream data.
*
* @param_in		(NC_VD_COAX_SET_STR *)coax_tx_mode			    Down Stream read structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_RX_DATA_READ
***************************************************************************************/
void coax_rx_data_get(void *p_param)
{
	NC_VD_COAX_STR *coax_rx = (NC_VD_COAX_STR*)p_param;

	int ii = 0;
	int ch = coax_rx->ch;
	int format = coax_rx->format_standard;

	gpio_i2c_write(raptor3_i2c_addr[coax_rx->vd_dev], 0xFF, BANK3+((ch%4)/2));

	if( (format == FMT_CVI) )
	{
		for(ii=0;ii<5;ii++)
		{
			//coax_rx->rx_data1[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x40+((ch%2)*0x80))+ii);   // ChX_Rx_Line_1 : 0x40 ~ 0x44 5byte
			coax_rx->rx_data1[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x50+((ch%2)*0x80))+ii);
			coax_rx->rx_data2[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x45+((ch%2)*0x80))+ii);   // ChX_Rx_Line_2 : 0x45 ~ 0x49 5byte
			coax_rx->rx_data3[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x4A+((ch%2)*0x80))+ii);   // ChX_Rx_Line_3 : 0x4A ~ 0x4E 5byte
			coax_rx->rx_data4[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x6C+((ch%2)*0x80))+ii);   // ChX_Rx_Line_4 : 0x6C ~ 0x70 5byte
			coax_rx->rx_data5[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x71+((ch%2)*0x80))+ii);   // ChX_Rx_Line_5 : 0x71 ~ 0x75 5byte
			coax_rx->rx_data6[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x76+((ch%2)*0x80))+ii);   // ChX_Rx_Line_6 : 0x76 ~ 0x7A 5byte
		}
	}
	else if(format == FMT_TVI)
	{
		coax_rx->rx_data1[1] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], 0x46+((ch%2)*0x80));
		coax_rx->rx_data1[2] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], 0x47+((ch%2)*0x80));
	}
	else  // AHD
	{
		for(ii=0;ii<8;ii++)
		{
			coax_rx->rx_pelco_data[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_rx->vd_dev], (0x50+((ch%2)*0x80))+ii);   // ChX_PELCO_Rx_Line_1 ~ 8 : 0x50 ~ 0x57 8byte
		}
	}
}

/**************************************************************************************
* @desc
* 	RAPTOR3's   Down stream buffer clear.
*
* @param_in		(NC_VD_COAX_SET_STR *)coax_tx_mode			    UP Stream Command structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_RX_BUF_CLEAR
***************************************************************************************/
void rs_coax_rx_buffer_clear(unsigned char ch)
{
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));

	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x3A+((ch%2)*0x80), 0x01);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x3A+((ch%2)*0x80), 0x00);
}

/**************************************************************************************
* @desc
* 	RAPTOR3's   Down stream mode off.
*
* @param_in		(NC_VD_COAX_SET_STR *)coax_tx_mode			    UP Stream Command structure
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_RX_DEINIT
***************************************************************************************/
void coax_rx_deinit(void *p_param)
{
	NC_VD_COAX_STR *coax_val = (NC_VD_COAX_STR*)p_param;

	unsigned char ch = coax_val->ch;

	gpio_i2c_write(raptor3_i2c_addr[coax_val->vd_dev], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[coax_val->vd_dev], 0x63+((ch%2)*0x80), 0);
}

/*=======================================================================================================
********************************************************************************************************
************************** Coaxial protocol firmware upgrade function **********************************
********************************************************************************************************
 *
 * Coaxial protocol firmware upgrade Flow
 * 1. ACP Check - Down Stream Header 0x55  - coax_fw_ready_header_check_from_isp_recv
 * 2.1 FW ready send                       - coax_fw_ready_cmd_to_isp_send
 * 2.2 FW ready ACK receive                - coax_fw_ready_cmd_ack_from_isp_recv
 * 3.1 FW start send                       - coax_fw_start_cmd_to_isp_send
 * 3.2 FW start ACK receive                - coax_fw_start_cmd_ack_from_isp_recv
 * 4.1 FW data send - 139byte         	   - coax_fw_one_packet_data_to_isp_send
 * 4.2 FW data ACK receive - offset        - coax_fw_one_packet_data_ack_from_isp_recv
 * 5.1 FW end send                         - coax_fw_end_cmd_to_isp_send
 * 5.2 FW end ACK receive                  - coax_fw_end_cmd_ack_from_isp_recv
 ========================================================================================================*/

/**************************************************************************************
* @desc
* 	RAPTOR3's   Down stream check header value.(AHD : 0x55)
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel       FW Update channel
* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result        Header check result
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_FW_ACP_HEADER_GET
***************************************************************************************/
void coax_fw_ready_header_check_from_isp_recv(void *p_param)
{
	int ret = FW_FAILURE;
	int ch = 0;
	int devnum = 0;
	unsigned char readval = 0;
	int timeout = 20;
	unsigned char achn;
	
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;
	ch = pstFileInfo->channel;
	devnum = pstFileInfo->channel/4;
	achn = (ch%4)+(devnum)*4;
	
	/* set register */
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x50+((ch%2)*0x80), 0x05 );  // PELCO Down Stream Read 1st Line
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x60+((ch%2)*0x80), 0x55 );  // Header Matching

	while( timeout != 0 )
	{
		/* If the header is (0x50=>0x55) and chip information is (0x51=>0x3X, 0x4X, 0x5X ), it can update firmware */
		if( gpio_i2c_read( raptor3_i2c_addr[devnum], 0x50+((ch%2)*0x80) ) == 0x55 )
		{
			printk(">>>>> DRV[%s:%d] CH:%d, this camera can update, please, wait! = 0x%x  timeout:%d\n", __func__, __LINE__, achn, gpio_i2c_read( raptor3_i2c_addr[ch/4], 0x51+((ch%2)*0x80) ) ,timeout);
			ret = FW_SUCCESS;
			break;
		}
		else
		{
			readval= gpio_i2c_read( raptor3_i2c_addr[devnum], 0x50+((ch%2)*0x80) );
			printk(">>>>> DRV[%s:%d] check ACP_STATUS_MODE::0x%x\n", __func__, __LINE__, readval );
			msleep(40);
			ret = FW_FAILURE;
		}		
		timeout--;
	}
	if( timeout == 0 )
	{
		ret = FW_FAILURE;
	}

	msleep(1000);
	pstFileInfo->result = ret;
}

/**************************************************************************************
* @desc
* 	RAPTOR3's   FW Ready command send to camera ( Mode change to FHD@25P )
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel       FW Update channel
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->cp_mode       Camera Format
* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result        Function execution result
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_FW_READY_CMD_SET
***************************************************************************************/
void coax_fw_ready_cmd_to_isp_send(void *p_param) // FW Ready
{
	int ch = 0;
	int devnum = 0;
	int ret = FW_FAILURE;
	//int cp_mode = 0;
	unsigned char achn;

	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;
	ch = pstFileInfo->channel;
	//cp_mode = pstFileInfo->cp_mode;
	devnum = pstFileInfo->channel/4;
	achn = (ch%4)+(devnum)*4;
	
	/* Adjust Tx */
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x0A+((ch%2)*0x80), 0x04);  // Tx Line count max

	/* change video mode FHD@25P Command Send */
	if( (cp_mode == FMT_AHD20) || (cp_mode == FMT_AHD30) )
	{
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x10+((ch%2)*0x80), 0x60);	// Register Write Control 				 - 17th line
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x11+((ch%2)*0x80), 0xB0);	// table(Mode Change Command) 			 - 18th line
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x12+((ch%2)*0x80), 0x02);	// Flash Update Mode(big data)			 - 19th line
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x13+((ch%2)*0x80), 0x02);	// Init Value(FW Information Check Mode) - 20th line

		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x08);	// trigger on
		msleep(400);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x10);	// reset
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x00);	// trigger Off
		printk(">>>>> DRV[%s:%d] CH:%d, coax_fw_ready_cmd_to_isp_send!!- AHD\n", __func__, __LINE__, achn );
		ret = FW_SUCCESS;
	}
	else if( (cp_mode == FMT_CVI) || (cp_mode == FMT_TVI) )
	{
		/* change video mode FHD@25P Command Send */
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2) );
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x10+((ch%2)*0x80), 0x55);	// 0x55(header)          				 - 16th line
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x11+((ch%2)*0x80), 0x60);	// Register Write Control 				 - 17th line
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x12+((ch%2)*0x80), 0xB0);	// table(Mode Change Command) 			 - 18th line
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x13+((ch%2)*0x80), 0x02);	// Flash Update Mode         			 - 19th line
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x14+((ch%2)*0x80), 0x00);	// Init Value(FW Information Check Mode) - 20th line

		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x08);	// trigger on
		msleep(1000);
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x10);	// reset
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x00);	// trigger Off
		printk(">>>>> DRV[%s:%d] CH:%d, coax_fw_ready_cmd_to_isp_send!!- CVI/TVI\n", __func__, __LINE__, achn );
		ret = FW_SUCCESS;
	}
	else
	{
		printk(">>>> DRV[%s:%d] CH:%d, FMT:%d > Unknown Format!!! \n", __func__, __LINE__, achn, cp_mode );
		ret = FW_FAILURE;
	}

	pstFileInfo->result = ret;
}

/**************************************************************************************
* @desc
* 	RAPTOR3's   FW Ready ACK receive from camera
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel       FW Update channel

* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result        Function execution result
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_FW_READY_ACK_GET
***************************************************************************************/
void coax_fw_ready_cmd_ack_from_isp_recv(void *p_param)
{
	int ret = FW_FAILURE;
	int ch = 0;
	int devnum = 0;
	unsigned char retval = 0x00;
	unsigned char retval2 = 0x00;
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;
	int timeout_cnt = 0;
	unsigned char achn;
	
	ch = pstFileInfo->channel;
	devnum = pstFileInfo->channel/4;
	achn = (ch%4)+(devnum)*4;
	
	/* Adjust Rx FHD@25P */
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x63+((ch%2)*0x80), 0x01 );	// Ch_X Rx ON
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x62+((ch%2)*0x80), 0x05 );	// Ch_X Rx Area
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x66+((ch%2)*0x80), 0x81 );	// Ch_X Rx Signal enhance
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x69+((ch%2)*0x80), 0x2D );	// Ch_X Rx Manual duty
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x60+((ch%2)*0x80), 0x55 );	// Ch_X Rx Header matching
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x61+((ch%2)*0x80), 0x00 );	// Ch_X Rx data_rz
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x68+((ch%2)*0x80), 0x80 );	// Ch_X Rx SZ

	timeout_cnt = 0;
	while( timeout_cnt++ < 20 )
	{

		if( gpio_i2c_read( raptor3_i2c_addr[devnum], 0x57+((ch%2)*0x80) ) == 0x02 )
		{
			/* get status, If the status is 0x00(Camera information), 0x01(Firmware version */
			if( gpio_i2c_read( raptor3_i2c_addr[devnum], 0x56+((ch%2)*0x80) ) == 0x00 )
			{
				printk(">>>>> DRV[%s:%d]CH:%d Receive ISP status : [READY]\n", __func__, __LINE__, achn );
				printk(">>>>> DRV[%s:%d]CH:%d Receive ISP status : [READY]\n", __func__, __LINE__, achn );
				printk(">>>>> DRV[%s:%d]CH:%d Receive ISP status : [READY]\n", __func__, __LINE__, achn );
				printk(">>>>> DRV[%s:%d]CH:%d Receive ISP status : [READY]\n", __func__, __LINE__, achn );
				printk(">>>>> DRV[%s:%d]CH:%d Receive ISP status : [READY]\n", __func__, __LINE__, achn);
				ret = FW_SUCCESS;
				break;
			}
		}
		else
		{
			retval	= gpio_i2c_read( raptor3_i2c_addr[devnum], 0x56+((ch%2)*0x80) );
			retval2 = gpio_i2c_read( raptor3_i2c_addr[devnum], 0x57+((ch%2)*0x80) );
			printk(">>>>> DRV[%s:%d]CH:%d retry : Receive ISP status[READY], [0x56-true[0x00]:0x%x], [0x57-true[0x02]:0x%x]\n", __func__, __LINE__, achn, retval, retval2 );
			if( timeout_cnt == 20 )
			{
				ret = FW_FAILURE;
				break;
			}
			msleep(1000);
		}
	}
	/* Rx Buffer clear */
#if 1
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x3A+((ch%2)*0x80), 0x01);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x3A+((ch%2)*0x80), 0x00);
#endif
	pstFileInfo->result = ret;
}

/**************************************************************************************
* @desc
* 	RAPTOR3's   FW start command send to camera ( change to black pattern )
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel       FW Update channel
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->cp_mode       Camera Format
* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result        Function execution result
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_FW_START_CMD_SET
***************************************************************************************/
void coax_fw_start_cmd_to_isp_send(void *p_param)
{
	int ch = 0;
	int devnum = 0;
	unsigned char achn;

	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;

	ch = pstFileInfo->channel;
	devnum = pstFileInfo->channel/4;
	achn = (ch%4)+(devnum)*4;

	/* Adjust Tx */
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2) );
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x00+((ch%2)*0x80), 0x2D);   // Duty
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x03+((ch%2)*0x80), 0x0D);   // line
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x05+((ch%2)*0x80), 0x03);   // tx_line_count
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x0A+((ch%2)*0x80), 0x04);   // tx_line_count_max

	// Tx Command set
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x10+((ch%2)*0x80), 0x60);	 // Register Write Control 				 - 17th line
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x11+((ch%2)*0x80), 0xB0);	 // table(Mode Change Command) 			 - 18th line
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x12+((ch%2)*0x80), 0x02);	 // Flash Update Mode(big data)			 - 19th line
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x13+((ch%2)*0x80), 0x40);	 // Start firmware update                - 20th line

	// Tx Command Shot
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x08);	 // trigger on
	msleep(200);
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x10);	 // reset
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x00);	 // trigger Off

	printk(">>>>> DRV[%s:%d]CH:%d >> Send command[START]\n", __func__, __LINE__, achn );

}

/**************************************************************************************
* @desc
* 	RAPTOR3's    FW Start ACK receive from camera
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel       FW Update channel
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->cp_mode       Camera Format
* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result        Function execution result
*
* @return   	void  		       								None
*
* ioctl : IOC_VDEC_COAX_FW_START_ACK_GET
***************************************************************************************/
//void coax_fw_start_cmd_ack_from_isp_recv( void *p_param )
int coax_fw_start_cmd_ack_from_isp_recv( int ch,int devnum)
{
	int ret = FW_FAILURE;
	unsigned char retval56 = 0x00,retval57 = 0x00;

	/* Adjust Rx FHD@25P */
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x63+((ch%2)*0x80), 0x01 ); // Ch_X Rx ON
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x62+((ch%2)*0x80), 0x05 ); // Ch_X Rx Area
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x66+((ch%2)*0x80), 0x81 ); // Ch_X Rx Signal enhance
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x69+((ch%2)*0x80), 0x2D ); // Ch_X Rx Manual duty
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x60+((ch%2)*0x80), 0x55 ); // Ch_X Rx Header matching
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x61+((ch%2)*0x80), 0x00 ); // Ch_X Rx data_rz
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x68+((ch%2)*0x80), 0x80 ); // Ch_X Rx SZ

	retval57 = gpio_i2c_read( raptor3_i2c_addr[devnum], 0x57+((ch%2)*0x80) );
	retval56 = gpio_i2c_read( raptor3_i2c_addr[devnum], 0x56+((ch%2)*0x80) );
	if( retval57 == 0x02 )
	{
		if( retval56 == 0x00 )
		{
			printk(">>>>> DRV[%s:%d]CH:%d Receive ISP status : [START]\n", __func__, __LINE__, (ch%4 + devnum*4));
			ret = FW_SUCCESS;
		}
		else
		{
			unsigned char retval1;
			unsigned char retval2;
			gpio_i2c_write( raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
			retval1 = gpio_i2c_read( raptor3_i2c_addr[devnum], 0x56+((ch%2)*0x80) );
			retval2 = gpio_i2c_read( raptor3_i2c_addr[devnum], 0x57+((ch%2)*0x80) );
			ret = FW_FAILURE;
			printk(">>>>> DRV[%s:%d]CH:%d retry : Receive ISP status[START], [0x56-true[0x02]:0x%x], [0x57-true[0x02]:0x%x]\n",	__func__, __LINE__, (ch%4 + devnum*4), retval1, retval2 );
		}
	}

	/* Rx Buffer clear */
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x3A+((ch%2)*0x80), 0x01);
	gpio_i2c_write(raptor3_i2c_addr[devnum], 0x3A+((ch%2)*0x80), 0x00);

	return ret;
}

/**************************************************************************************
* @desc
* 	RAPTOR3's    FW Data send to camera(One packet data size 139byte)
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel                  FW Update channel
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->readsize                 One packet data size
* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->currentFileOffset        File offset
* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result                   Function execution result
*
* @return   	void  		       								           None
*
* ioctl : IOC_VDEC_COAX_FW_SEND_DATA_SET
***************************************************************************************/
void coax_fw_one_packet_data_to_isp_send( void *p_param )
{
	int ch = 0;
	int devnum = 0;
	int ii = 0;
	unsigned int low = 0x00;
	unsigned int mid = 0x00;
	unsigned int high = 0x00;
	unsigned int readsize = 0;
	int byteNumOfPacket = 0;
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;

	/* file information */
	ch        = pstFileInfo->channel;
	readsize  = pstFileInfo->readsize;
	devnum 	  = pstFileInfo->channel/4;

	/* fill packet(139bytes), end packet is filled with 0xff */
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0xff, 0x0c+(ch%4) );
	for( ii = 0; ii < 139; ii++ )
	{
		if( byteNumOfPacket < readsize)
		{
			gpio_i2c_write( raptor3_i2c_addr[devnum], 0x00+ii, pstFileInfo->onepacketbuf[ii] );
			byteNumOfPacket++;
		}
		else if( byteNumOfPacket >= readsize ) // end packet : fill 0xff
		{
			gpio_i2c_write( raptor3_i2c_addr[devnum], 0x00+ii, 0xff );
			byteNumOfPacket++;
		}

		if( ii == 0 )
			low = pstFileInfo->onepacketbuf[ii];
		else if( ii == 1 )
			mid = pstFileInfo->onepacketbuf[ii];
		else if( ii == 2 )
			high = pstFileInfo->onepacketbuf[ii];
	}

	/* offset */
	pstFileInfo->currentFileOffset = (unsigned int)((high << 16 )&(0xFF0000))| (unsigned int)((mid << 8 )&(0xFF00)) | (unsigned char)(low);

	/* Tx Change mode to use Big data */
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2) );
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x0B+((ch%2)*0x80), 0x30);
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x05+((ch%2)*0x80), 0x8A);

	/* Tx Shot */
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2) );
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x08);	// trigger on
}

/**************************************************************************************
* @desc
* 	RAPTOR3's    FW Data ACK receive from camera
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel                  FW Update channel
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->currentFileOffset        File offset

* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result                   Function execution result
*
* @return   	void  		       								           None
*
* ioctl : IOC_VDEC_COAX_FW_SEND_ACK_GET
***************************************************************************************/
int coax_fw_one_packet_data_ack_from_isp_recv( void *p_param )
{
	int ret = FW_FAILURE;
	int ch = 0;
	int devnum = 0;
	unsigned int onepacketaddr = 0;
	unsigned int receive_addr = 0;

	int timeoutcnt = 1200;
	int ii=0;
	int retrycnt=0;
	
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;
	ch = pstFileInfo->channel;
	onepacketaddr = pstFileInfo->currentFileOffset;
	devnum = pstFileInfo->channel/4;
	
	for( ii=0; ii<timeoutcnt; ii++ )
	{
		/* Adjust Rx FHD@25P */
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x63+((ch%2)*0x80), 0x01 ); // Ch_X Rx ON
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x62+((ch%2)*0x80), 0x05 ); // Ch_X Rx Area
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x66+((ch%2)*0x80), 0x81 ); // Ch_X Rx Signal enhance
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x69+((ch%2)*0x80), 0x2D ); // Ch_X Rx Manual duty
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x60+((ch%2)*0x80), 0x55 ); // Ch_X Rx Header matching
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x61+((ch%2)*0x80), 0x00 ); // Ch_X Rx data_rz
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x68+((ch%2)*0x80), 0x80 ); // Ch_X Rx SZ

		if( gpio_i2c_read( raptor3_i2c_addr[devnum], 0x57+((ch%2)*0x80) ) == 0x02 )
		{
			/* check ISP status - only check first packet */
			if( pstFileInfo->currentpacketnum == 0 )
			{
				if( gpio_i2c_read( raptor3_i2c_addr[devnum], 0x56+((ch%2)*0x80) ) == 0x03 )
				{
					pstFileInfo->result = FW_FAILURE;
					printk(">>>>> DRV[%s:%d] CH:%d, Failed, error status, code=3..................\n", __func__, __LINE__, ch );
					return FW_FAILURE;
				}
			}

			/* check offset */
			receive_addr = (( gpio_i2c_read( raptor3_i2c_addr[devnum], 0x53+((ch%2)*0x80))<<16) + \
					(gpio_i2c_read( raptor3_i2c_addr[devnum], 0x54+((ch%2)*0x80))<<8) +
					gpio_i2c_read( raptor3_i2c_addr[devnum], 0x55+((ch%2)*0x80)));
			if( onepacketaddr == receive_addr )
			{
				gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x10);	// Reset
				gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x00);	// trigger off
				printk("Firmware Update[%d/%d]  \t offset[0x%06X/%d] : \tRetry_times[%d] \n",
						pstFileInfo->currentpacketnum+1,
						pstFileInfo->filepacketnum,
						pstFileInfo->currentFileOffset,
						pstFileInfo->currentFileOffset,
						retrycnt);
				ret = FW_SUCCESS;
				//pstFileInfo->receive_addr = receive_addr;
				pstFileInfo->result = ret;
				//printk(">>>>> DRV[%s:%d] CH:%d, write FW_SUCCESS,retrycnt:%d, offset of file:0x%06X\n", __func__, __LINE__, ch, retrycnt, onepacketaddr );
				break;
			}
			else
			{
				msleep(30);
				retrycnt++;
			}
		}
		else
		{
			//msleep(10);
			msleep(30);
		}
	}

	/* time out */
	if( ii == timeoutcnt )
	{
		#if 0
		/* debug message */
		for( ii = 0; ii < ONE_PACKET_MAX_SIZE; ii++ )
		{
			if( (ii!=0) && ((ii%16)==0) )
				printk("\n");
			printk("%02x ", pstFileInfo->onepacketbuf[ii] );
		}
		printk("\n");
		#endif

		printk(">>>>> DRV[%s:%d] CH:%d, write timeout:%d, offset of file:0x%06X\n", __func__, __LINE__, ch, timeoutcnt, onepacketaddr );
		ret = FW_FAILURE;
		pstFileInfo->result = ret;
	}
	
	return ret;
}

/**************************************************************************************
* @desc
* 	RAPTOR3's    FW End command send to camera
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel                  FW Update channel
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->result                   FW Data send result
*
* @return   	void  		       								           None
*
* ioctl : IOC_VDEC_COAX_FW_END_CMD_SET
***************************************************************************************/
void coax_fw_end_cmd_to_isp_send(void *p_param)
{
	int ch = 0;
	int devnum = 0;
	int send_success = 0;

	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;

	ch = pstFileInfo->channel;
	send_success = pstFileInfo->result;
	devnum = pstFileInfo->channel/4;

	/* adjust Tx line */
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2) );
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x00+((ch%2)*0x80), 0x2D);   // Duty
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x0B+((ch%2)*0x80), 0x10);   // Mode
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x03+((ch%2)*0x80), 0x0D);   // line
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x05+((ch%2)*0x80), 0x03);	// Tx_Line Count       3 line number
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x0A+((ch%2)*0x80), 0x03);	// Tx Total Line Count 3 line number

	/* Fill end command */
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x10+((ch%2)*0x80), 0x60);
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x11+((ch%2)*0x80), 0xb0);
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x12+((ch%2)*0x80), 0x02);
	if( send_success == FW_FAILURE )
	{
		gpio_i2c_write( raptor3_i2c_addr[devnum], 0x13+((ch%2)*0x80), 0xE0/*0xC0*/);
		printk(">>>>> DRV[%s:%d] CH:%d, Camera UPDATE error signal. send Abnormal ending!\n", __func__, __LINE__, ch );
	}
	else
	{
		gpio_i2c_write( raptor3_i2c_addr[devnum], 0x13+((ch%2)*0x80), 0x80/*0x60*/);
		printk(">>>>> DVR[%s:%d] CH:%d, Camera UPDATE ending signal. wait please!\n", __func__, __LINE__, ch );
	}

	/* Shot */
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x08);
	msleep(400);
	gpio_i2c_write( raptor3_i2c_addr[devnum], 0x09+((ch%2)*0x80), 0x00);

	if( send_success == FW_SUCCESS )
	{
		printk(">>>>> DVR[%s:%d] CH:%d, Camera UPDATE mode finish!\n", __func__, __LINE__, ch );
		printk(">>>>> DVR[%s:%d] CH:%d, Camera UPDATE mode finish!\n", __func__, __LINE__, ch );
		printk(">>>>> DVR[%s:%d] CH:%d, Camera UPDATE mode finish!\n", __func__, __LINE__, ch );
		printk(">>>>> DVR[%s:%d] CH:%d, Camera UPDATE mode finish!\n", __func__, __LINE__, ch );
		printk(">>>>> DVR[%s:%d] CH:%d, Camera UPDATE mode finish!\n", __func__, __LINE__, ch );
	}

}

/**************************************************************************************
* @desc
* 	RAPTOR3's    FW End command ACK receive from camera
*
* @param_in		(FIRMWARE_UP_FILE_INFO *)p_param->channel                  FW Update channel
*
* @param_out	(FIRMWARE_UP_FILE_INFO *)p_param->result                   Function execution result
*
* @return   	void  		       								           None
*
* ioctl : IOC_VDEC_COAX_FW_END_ACK_GET
***************************************************************************************/
void coax_fw_end_cmd_ack_from_isp_recv(void *p_param)
{
	int ch = 0;
	int devnum = 0;
	//int timeout_cnt = 0;
	//int MAX_TIMER_CNT = 30;

	unsigned char videofm = 0x00;
	unsigned char ack_return = 0x00;
	unsigned char isp_status = 0x00;
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;

	ch = pstFileInfo->channel;
	devnum = pstFileInfo->channel/4;

	//timeout_cnt = 0;
	//while( timeout_cnt++ < MAX_TIMER_CNT )
	{

		/* check video format(video loss), 0:videoloss, 1:video on */
		gpio_i2c_write( raptor3_i2c_addr[devnum], 0xFF, 0x05+(ch%4));
		videofm = gpio_i2c_read( raptor3_i2c_addr[devnum], 0xF0);

		if( videofm == 0xFF )
		{
			printk(">>>>> DRV[%s:%d] Final[CH:%d], No video[END]!\n", __func__, __LINE__, ch );
			pstFileInfo->result = FW_FAILURE;
			return;
		}

		/* Adjust Rx FHD@25P */
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x63+((ch%2)*0x80), 0x01 );   // Ch_X Rx ON
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x62+((ch%2)*0x80), 0x05 );   // Ch_X Rx Area
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x66+((ch%2)*0x80), 0x81 );   // Ch_X Rx Signal enhance
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x69+((ch%2)*0x80), 0x2D );   // Ch_X Rx Manual duty
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x60+((ch%2)*0x80), 0x55 );   // Ch_X Rx Header matching
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x61+((ch%2)*0x80), 0x00 );   // Ch_X Rx data_rz
		gpio_i2c_write(raptor3_i2c_addr[devnum], 0x68+((ch%2)*0x80), 0x80 );   // Ch_X Rx SZ

		/* get status, If the ack_return(0x56) is 0x05(completed writing f/w file to isp's flash) */
		gpio_i2c_write( raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
		ack_return = gpio_i2c_read( raptor3_i2c_addr[devnum], 0x56+((ch%2)*0x80) );
		isp_status = gpio_i2c_read( raptor3_i2c_addr[devnum], 0x57+((ch%2)*0x80) );
		if( ( isp_status == 0x02 ) && ( ack_return == 0x05 ) )
		{
			printk(">>>>> DRV[%s:%d]CH:%d Receive ISP status : [END]\n", __func__, __LINE__, ch );
			pstFileInfo->result = FW_SUCCESS;
			return;
		}
		else
		{
			printk(">>>>> DRV[%s:%d]CH:%d retry : Receive ISP status[END], [0x56-true[0x05]:0x%x], [0x57-true[0x02]:0x%x]\n", __func__, __LINE__, ch, ack_return, isp_status );
			pstFileInfo->result = FW_FAILURE;
			return;
		}
	}
}


/*=======================================================================================================
 *  Coaxial protocol Support option function
 *
 ========================================================================================================*/
/**************************************************************************************
* @desc
* 	RAPTOR3's    RT/NRT Mode change
*
* @param_in		(NC_VD_COAX_Tx_Init_STR *)p_param->channel                 Coax read channel
*
* @return   	void  		       								           None
*
* ioctl : IOC_VDEC_COAX_TEST_TX_INIT_DATA_READ
***************************************************************************************/
void coax_option_rt_nrt_mode_change_set(void *p_param)
{
	NC_VD_COAX_STR *coax_val = (NC_VD_COAX_STR*)p_param;

	unsigned char ch    = coax_val->ch;
	unsigned char param = coax_val->param;
	unsigned char fmtdef = coax_val->vivo_fmt;
	unsigned char tx_line = 0;
	unsigned char tx_line_max = 0;
	//
	gpio_i2c_write(raptor3_i2c_addr[coax_val->vd_dev], 0xFF, 0x03+((ch%4)/2));

	tx_line     = gpio_i2c_read( raptor3_i2c_addr[coax_val->vd_dev], 0x05+((ch%2)*0x80) );
	tx_line_max = gpio_i2c_read( raptor3_i2c_addr[coax_val->vd_dev], 0x0A+((ch%2)*0x80) );

	// Adjust Tx
	if( fmtdef == AHD30_3M_30P || fmtdef == AHD30_3M_25P || fmtdef == AHD30_3M_18P  ||
		fmtdef == AHD30_4M_30P || fmtdef == AHD30_4M_25P || fmtdef ==  AHD30_4M_15P ||
	    fmtdef == AHD30_5M_12_5P || fmtdef == AHD30_5M_20P
		)
	{  	// 3M Upper Format
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x05+((ch%2)*0x80), 0x07);       // Tx line set
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x0A+((ch%2)*0x80), 0x08);       // Tx max line set
	}
	else // 3M Under Format
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x05+((ch%2)*0x80), 0x03);       // Tx line set
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x0A+((ch%2)*0x80), 0x04);       // Tx max line set
	}

	if( param == 0 ) // RT Mode
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x10+((ch%2)*0x80), 0x60);   // Register write
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x11+((ch%2)*0x80), 0xb1);   // Output command
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x12+((ch%2)*0x80), 0x00);   // RT Mode
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x13+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x14+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x15+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x16+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x17+((ch%2)*0x80), 0x00);
	}
	else if( param == 1 )// NRT Mode
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x10+((ch%2)*0x80), 0x60);   // Register write
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x11+((ch%2)*0x80), 0xb1);   // Output command
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x12+((ch%2)*0x80), 0x01);   // NRT Mode
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x13+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x14+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x15+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x16+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x17+((ch%2)*0x80), 0x00);
	}
	else if( param == 2 )// AHD 5M 20P
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x10+((ch%2)*0x80), 0x60);   // Register write
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x11+((ch%2)*0x80), 0xb1);   // Output command
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x12+((ch%2)*0x80), 0x02);   // Change Format
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x13+((ch%2)*0x80), 0x00);   // AHD 5M 20P
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x14+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x15+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x16+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x17+((ch%2)*0x80), 0x00);
	}
	else if( param == 3 )//  AHD 5M 12.5P
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x10+((ch%2)*0x80), 0x60);   // Register write
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x11+((ch%2)*0x80), 0xb1);   // Output command
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x12+((ch%2)*0x80), 0x02);   // Change Format
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x13+((ch%2)*0x80), 0x01);	 // AHD 5M 12.5P
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x14+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x15+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x16+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x17+((ch%2)*0x80), 0x00);
	}
	else if( param == 4 )// AHD 4M 30P
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x10+((ch%2)*0x80), 0x60);   // Register write
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x11+((ch%2)*0x80), 0xb1);   // Output command
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x12+((ch%2)*0x80), 0x02);   // Change Format
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x13+((ch%2)*0x80), 0x02);   // AHD 4M 30P
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x14+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x15+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x16+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x17+((ch%2)*0x80), 0x00);
	}
	else if( param == 5 )//  AHD 4M 25P
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x10+((ch%2)*0x80), 0x60);   // Register write
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x11+((ch%2)*0x80), 0xb1);   // Output command
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x12+((ch%2)*0x80), 0x02);   // Change Format
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x13+((ch%2)*0x80), 0x03);   // AHD 4M 25P
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x14+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x15+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x16+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x17+((ch%2)*0x80), 0x00);
	}
	else if( param == 6 )//  AHD 4M 15P
	{
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x10+((ch%2)*0x80), 0x60);   // Register write
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x11+((ch%2)*0x80), 0xb1);   // Output command
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x12+((ch%2)*0x80), 0x02);   // Change Format
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x13+((ch%2)*0x80), 0x04);   // AHD 4M 15P
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x14+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x15+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x16+((ch%2)*0x80), 0x00);
		gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x17+((ch%2)*0x80), 0x00);
	}

	// Tx Command Shot
	gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x09+((ch%2)*0x80), 0x08);	 // trigger on
	msleep(300);
	gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x09+((ch%2)*0x80), 0x10);	 // reset
	gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x09+((ch%2)*0x80), 0x00);	 // trigger Off

	gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x05+((ch%2)*0x80), tx_line);           // Tx line set
	gpio_i2c_write( raptor3_i2c_addr[coax_val->vd_dev], 0x0A+((ch%2)*0x80), tx_line_max);       // Tx max line set

}

/*=======================================================================================================
 *  Coaxial protocol test function
 *
 ========================================================================================================*/
/**************************************************************************************
* @desc
* 	RAPTOR3's    Test function. Read coax Tx initialize value
*
* @param_in		(NC_VD_COAX_Tx_Init_STR *)p_param->channel                 Coax read channel
*
* @return   	void  		       								           None
*
* ioctl : IOC_VDEC_COAX_TEST_TX_INIT_DATA_READ
***************************************************************************************/
void coax_test_tx_init_read(NC_VD_COAX_TEST_STR *coax_tx_mode)
{
	//int ch = coax_tx_mode->ch;
	//int devnum = coax_tx_mode->chip_num;

	int ch = 0;
	int devnum = 0;

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x05+ch%4);
	coax_tx_mode->rx_src = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x7C);
	coax_tx_mode->rx_slice_lev = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x7D);

	gpio_i2c_write(raptor3_i2c_addr[devnum], 0xFF, 0x03+((ch%4)/2));
	coax_tx_mode->tx_baud           = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x00+((ch%2)*0x80));
	coax_tx_mode->tx_pel_baud       = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x02+((ch%2)*0x80));
	coax_tx_mode->tx_line_pos0      = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x03+((ch%2)*0x80));
	coax_tx_mode->tx_line_pos1      = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x04+((ch%2)*0x80));
	coax_tx_mode->tx_line_count     = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x05+((ch%2)*0x80));
	coax_tx_mode->tx_pel_line_pos0  = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x07+((ch%2)*0x80));
	coax_tx_mode->tx_pel_line_pos1  = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x08+((ch%2)*0x80));
	coax_tx_mode->tx_line_count_max = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x0A+((ch%2)*0x80));
	coax_tx_mode->tx_mode           = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x0B+((ch%2)*0x80));
	coax_tx_mode->tx_sync_pos0      = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x0D+((ch%2)*0x80));
	coax_tx_mode->tx_sync_pos1      = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x0E +((ch%2)*0x80));
	coax_tx_mode->tx_even           = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x2F+((ch%2)*0x80));
	coax_tx_mode->tx_zero_length    = gpio_i2c_read(raptor3_i2c_addr[devnum], 0x0C+((ch%2)*0x80));
}

/**************************************************************************************
* @desc
* 	RAPTOR3's    Test function. bank, address, value setting.  get from application
*
* @param_in		(NC_VD_COAX_TEST_STR *)coax_data                 Coax Tx setting value
*
* @return   	void  		       								 None
*
* ioctl : IOC_VDEC_COAX_TEST_DATA_SET
***************************************************************************************/
void coax_test_data_set(NC_VD_COAX_TEST_STR *coax_data)
{
	unsigned char temp_reg;
	printk("[DRV_Set]bank(0x%02X)/addr(0x%02X)/param(0x%02X)\n", coax_data->bank, coax_data->data_addr, coax_data->param );

	gpio_i2c_write(raptor3_i2c_addr[coax_data->chip_num], 0xFF, coax_data->bank);

	if(coax_data->bank == 0x01 && coax_data->data_addr == 0xED)
	{
		temp_reg = gpio_i2c_read(raptor3_i2c_addr[coax_data->chip_num], coax_data->data_addr);
		temp_reg = ((temp_reg & ~(0x01 << coax_data->param)) | (0x01 << coax_data->param));
	}
	else if(coax_data->bank == 0x01 && coax_data->data_addr == 0x7A)
	{
		temp_reg = gpio_i2c_read(raptor3_i2c_addr[coax_data->chip_num], coax_data->data_addr);
		temp_reg = (temp_reg & ~(0x01 << coax_data->param));
	}
	else if(coax_data->bank == 0x09 && coax_data->data_addr == 0x44)
	{
		temp_reg = gpio_i2c_read(raptor3_i2c_addr[coax_data->chip_num], coax_data->data_addr);
		temp_reg = ((temp_reg & ~(0x01 << coax_data->param)) | (0x01 << coax_data->param));
	}
	else
		temp_reg = coax_data->param ;

	gpio_i2c_write(raptor3_i2c_addr[coax_data->chip_num], coax_data->data_addr, temp_reg );
}


/**************************************************************************************
* @desc
* 	RAPTOR3's    Test function. Read value bank, address, value. To application
*
* @param_in		(NC_VD_COAX_TEST_STR *)coax_data                 Coax read channel
*
* @return   	void  		       								 None
*
* ioctl : IOC_VDEC_COAX_TEST_DATA_READ
***************************************************************************************/
void coax_test_data_get(NC_VD_COAX_TEST_STR *coax_data)
{
	gpio_i2c_write(raptor3_i2c_addr[coax_data->chip_num], 0xFF, coax_data->bank);
	coax_data->param = gpio_i2c_read(raptor3_i2c_addr[coax_data->chip_num], coax_data->data_addr);
	printk("[DRV_Get]bank(0x%02X), addr(0x%02X), param(0x%02X)\n", coax_data->bank, coax_data->data_addr, coax_data->param );
}

/**************************************************************************************
* @desc
* 	RAPTOR3's    Test function. Bank Dump To application
*
* @param_in		(NC_VD_COAX_BANK_DUMP_STR *)coax_data            Coax read channel
*
* @return   	void  		       								 None
*
* ioctl : IOC_VDEC_COAX_TEST_DATA_READ
***************************************************************************************/
void coax_test_Bank_dump_get(NC_VD_COAX_BANK_DUMP_STR *coax_data)
{
	int ii = 0;

	gpio_i2c_write(raptor3_i2c_addr[coax_data->vd_dev], 0xFF, coax_data->bank);

	for(ii=0; ii<256; ii++)
	{
		coax_data->rx_pelco_data[ii] = gpio_i2c_read(raptor3_i2c_addr[coax_data->vd_dev], 0x00+ii);
	}
}


/*******************************************************************************
*	Description		: read acp data of ISP
*	Argurments		: ch(channel ID), reg_addr(high[1byte]:bank, low[1byte]:register)
*	Return value	: void
*	Modify			:
*	warning			:
*******************************************************************************/
unsigned char coax_acp_isp_read(unsigned char ch, unsigned int reg_addr)
{
	unsigned char data_3x50[8];
	unsigned char lcnt_bak, lcntm_bak,crc_bak;
	unsigned char bank;
	unsigned char addr;
	int i;

	bank = (reg_addr>>8)&0xFF;
	addr = reg_addr&0xFF;

	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	lcnt_bak = gpio_i2c_read(raptor3_i2c_addr[ch/4], 0x05+((ch%2)*0x80));
	lcntm_bak = gpio_i2c_read(raptor3_i2c_addr[ch/4], 0x0A+((ch%2)*0x80));
	crc_bak = gpio_i2c_read(raptor3_i2c_addr[ch/4], 0x60+((ch%2)*0x80));
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x05+((ch%2)*0x80), 0x07);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x0A+((ch%2)*0x80), 0x08);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x60+((ch%2)*0x80), 0x61);

	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+(ch%2)*0x80, 0x61);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+1+(ch%2)*0x80, bank);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+2+(ch%2)*0x80, addr);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+3+(ch%2)*0x80, 0x00);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x09+(ch%2)*0x80, 0x08);
	msleep(100);
	for(i=0;i<8;i++)
	{
		data_3x50[i] = gpio_i2c_read(raptor3_i2c_addr[ch/4],0x50+i+((ch%2)*0x80));
		printk("acp_isp_read ch = %d, reg_addr = %x, reg_data = %x\n", ch,reg_addr, data_3x50[i]);
	}
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x05+((ch%2)*0x80), lcnt_bak);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x0A+((ch%2)*0x80), lcntm_bak);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x60+((ch%2)*0x80), crc_bak);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x09+((ch%2)*0x80), 0x10);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x09+((ch%2)*0x80), 0x00);
	msleep(100);
	//gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	//gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x63+((ch%2)*0x80), 0);	

	return data_3x50[3];
}

/*******************************************************************************
*  description    : firmware update( fill, send, verification )
*  argurments     : p_param( file information)
*  return value   : 0(send/receive OK ), -1(send/receive failed )
*  modify         :
*  warning        :
 *******************************************************************************/
int  acp_dvr_firmware_update( void *p_param )
{
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;
	int ret = -1;
	
	/* make protocol(FILL) */
	coax_fw_one_packet_data_to_isp_send( pstFileInfo );

	/* send and verification */
	ret = coax_fw_one_packet_data_ack_from_isp_recv( pstFileInfo );
	return ret;
}

/*******************************************************************************
*  description    : start F/W
*  argurments     : p_param( file information)
*  return value   : 0(OK ), -1(failed )
*  modify         :
*  warning        :
 *******************************************************************************/
void acp_dvr_start_command( void *p_param )
{
	int ret = -1;
	int ch = 0;
	int s_cnt = 0;
	int devnum = 0;
	
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;
	ch = pstFileInfo->channel;
	devnum = pstFileInfo->channel/4;

	msleep(2000);
	/* start F/W  */
	coax_fw_start_cmd_to_isp_send( pstFileInfo );

	/* CHECK : is it possible to start F/W */
	while( s_cnt++ < COAX_FW_TIMEOUT )
	{
		ret = coax_fw_start_cmd_ack_from_isp_recv(ch,devnum);
		if( ret == FW_SUCCESS )
		{
			printk(">>>>> DRV[%s:%d] stage2[CH:%d], Receive ISP status[START], cnt:%d\n", __func__, __LINE__, ch, s_cnt );
			printk(">>>>> DRV[%s:%d] stage2[CH:%d], Receive ISP status[START], cnt:%d\n", __func__, __LINE__, ch, s_cnt );
			printk(">>>>> DRV[%s:%d] stage2[CH:%d], Receive ISP status[START], cnt:%d\n", __func__, __LINE__, ch, s_cnt );
			printk(">>>>> DRV[%s:%d] stage2[CH:%d], Receive ISP status[START], cnt:%d\n", __func__, __LINE__, ch, s_cnt );
			printk(">>>>> DRV[%s:%d] stage2[CH:%d], Receive ISP status[START], cnt:%d\n", __func__, __LINE__, ch, s_cnt );
			break;
		}
		else
		{
			unsigned char retval1;
			unsigned char retval2;
			gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
			retval1 = gpio_i2c_read( raptor3_i2c_addr[ch/4], 0x56+((ch%2)*0x80) );
			retval2 = gpio_i2c_read( raptor3_i2c_addr[ch/4], 0x57+((ch%2)*0x80) );
			printk(">>>>> DRV[%s:%d] stage2[CH:%d], retry : Receive ISP status[START], [0x56-true[0x02]:0x%x], [0x57-true[0x02]:0x%x], cnt:%d\n", \
					__func__, __LINE__, ch, retval1, retval2, s_cnt );
			if( s_cnt == COAX_FW_TIMEOUT )
			{
				printk("\033[1;32m [Start_ACK]ACP FIRMUP Start ACK Recv FAIL - ACK Recv Time out!!	\033[0;39m \n");
				ret = FW_FAILURE;
				break;
			}
		}
		msleep(1000);
	}

	pstFileInfo->result = ret;
}

/*******************************************************************************
*  Description    : END command : Success or Fail
*  Argurments     : send_success(0:success, -1:failed), p_param( file information)
*  Return value   : void
*  Modify         :
*  warning        :
 *******************************************************************************/
int acp_dvr_end_command( int send_success, void *p_param )
{
	//int ret = 0;
	int timeout_cnt = 0;
	int MAX_TIMER_CNT = 90;		//test:升级后写flash时间长，导致最后步判断值出错
	int ch = 0;
	FIRMWARE_UP_FILE_INFO *pstFileInfo = (FIRMWARE_UP_FILE_INFO*)p_param;
	ch = pstFileInfo->channel;

	msleep(2000);
	coax_fw_end_cmd_to_isp_send( pstFileInfo );

	/* receive ACK signal of END */
	timeout_cnt = 0;
	if( send_success != FW_FAILURE )	//解决界面取消升级后，仍会等while循环90次后才停止的问题
	{
		#if 1
		while( timeout_cnt++ < MAX_TIMER_CNT )
		{
			coax_fw_end_cmd_ack_from_isp_recv( pstFileInfo );
			if( pstFileInfo->result == FW_SUCCESS )
			{
				break;
			}
			else
			{
				if( timeout_cnt == MAX_TIMER_CNT )
				{
				    pstFileInfo->result = FW_FAILURE;
				    msleep(1000);
					break;
				}
				msleep(1000);
			}
		}
		#endif
	}
	return pstFileInfo->result;
}

/*========================================================================================================================
 * Coaxial UP stream function
 *
 ========================================================================================================================*/
void RS_APP_VD_COAX_Tx_Init( int vd_dev, int vd_ch, NC_FORMAT_STANDARD format_standard, NC_FORMAT_RESOLUTION format_resolution, NC_FORMAT_FPS format_fps )
{
	NC_VIVO_CH_FORMATDEF vivo_fmt = RS_VI_FindFormatDef( format_standard, format_resolution, format_fps );
	NC_VD_COAX_STR CoaxTx_Init;

	CoaxTx_Init.vd_dev             = vd_dev;
	CoaxTx_Init.ch                 = vd_ch%4;
	CoaxTx_Init.format_standard    = format_standard;
	CoaxTx_Init.format_resolution  = format_resolution;
	CoaxTx_Init.format_fps         = format_fps;
	CoaxTx_Init.vivo_fmt           = vivo_fmt;

	coax_tx_init(&CoaxTx_Init);			//TX初始化
	coax_tx_16bit_init(&CoaxTx_Init);
}

/*========================================================================================================================
 * Coaxial Down stream function
 ========================================================================================================================*/
void RS_APP_VD_COAX_Rx_Init( int vd_dev, int vd_ch, NC_FORMAT_STANDARD format_standard, NC_FORMAT_RESOLUTION format_resolution, NC_FORMAT_FPS format_fps )
{
	NC_VIVO_CH_FORMATDEF vivo_fmt = RS_VI_FindFormatDef( format_standard, format_resolution, format_fps );
	NC_VD_COAX_STR CoaxRx_Init;

	CoaxRx_Init.vd_dev          = vd_dev;
	CoaxRx_Init.ch              = vd_ch%4;
	CoaxRx_Init.format_standard = format_standard;
	CoaxRx_Init.vivo_fmt        = vivo_fmt;
	coax_rx_init(&CoaxRx_Init);			//RX初始化
}

void RS_APP_VD_COAX_Tx_Command_Send_Set( int vd_dev, int vd_ch, NC_FORMAT_STANDARD format_standard, 
			NC_FORMAT_RESOLUTION format_resolution, NC_FORMAT_FPS format_fps, NC_COAX_CMD_DEF cmd,unsigned char udata,unsigned char data)
{
	NC_VIVO_CH_FORMATDEF vivo_fmt = RS_VI_FindFormatDef( format_standard, format_resolution, format_fps );
	NC_VD_COAX_STR CoaxTx_CMD;

	CoaxTx_CMD.vd_dev          = vd_dev;
	CoaxTx_CMD.ch              = vd_ch%4;
	CoaxTx_CMD.format_standard = format_standard;
	CoaxTx_CMD.vivo_fmt        = vivo_fmt;
	CoaxTx_CMD.cmd             = cmd;
	coax_tx_cmd_send(&CoaxTx_CMD,udata,data);
}

void RS_APP_VD_COAX_Tx_16Bit_Command_Send_Set( int vd_dev, int vd_ch, NC_FORMAT_STANDARD format_standard, 
			NC_FORMAT_RESOLUTION format_resolution, NC_FORMAT_FPS format_fps, NC_COAX_CMD_DEF cmd,unsigned char udata ,unsigned char data)
{
	NC_VIVO_CH_FORMATDEF vivo_fmt = RS_VI_FindFormatDef( format_standard, format_resolution, format_fps );
	NC_VD_COAX_STR CoaxTx_CMD;

	CoaxTx_CMD.vd_dev          = vd_dev;
	CoaxTx_CMD.ch              = vd_ch%4;
	CoaxTx_CMD.format_standard = format_standard;
	CoaxTx_CMD.vivo_fmt        = vivo_fmt;
	CoaxTx_CMD.cmd             = cmd;
	
	if( format_standard == FMT_AHD20)
    {
		coax_tx_16bit_cmd_send(&CoaxTx_CMD,udata,data);
    }
	else if( format_standard == FMT_CVI)
	{
		coax_tx_cvi_new_cmd_send(&CoaxTx_CMD,udata,data);
	}
	else

	printk("RS_APP_VD_COAX_Tx_16Bit_Command_Send_Set::Not Supported::%d\n", format_standard);
}

void nvp6158_send_comm(unsigned char pel_ch, NC_COAX_CMD_DEF cmd,bool stop)
{
	gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], 0xFF, 0x03+((pel_ch%4)/2));

	if(RSch_mode_status[pel_ch] == NVP6134_VI_3M)
	{
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x01);
		if((UTC_AUTHOR&0x10) == 0x10)
		{
			Delay( 200000 );
		}
		else
		{
			msleep( 25 );
		}
		if(stop == 1)
		{
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x10);
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x00);
			//msleep( 25 );
		}
	}
	else if( RSch_mode_status[pel_ch] == NVP6134_VI_3M_NRT  || RSch_mode_status[pel_ch] == NVP6134_VI_5M_20P)  // by Song(2016-07-01)
	{
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x01);
		msleep( 55 );
		if(stop == 1)
		{
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x10);		// reset - by song(2016-07-01)
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x00);		// clear - by song(2016-07-01)
		}
	}
	else if( RSch_mode_status[pel_ch] == NVP6134_VI_4M_NRT )  
	{
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x08);
		msleep( 70 );
		if(stop == 1)
		{
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x10);		
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x00);		
		}
	}
	else if( RSch_mode_status[pel_ch] == NVP6134_VI_5M_NRT)
	{
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x01);
		msleep( 90 );
		if(stop == 1)
		{
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x10);		// reset - by song(2016-07-01)
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x00);		// clear - by song(2016-07-01)
		}
	}
	else 
	{
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x01);
		msleep( 25 );

		if(stop == 1)
		{
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x10);
			gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x00);
			//msleep( 25 );
		}
	}

	if(cmd == COAX_CMD_SET_CAMERA)
	{
	
	}
	else
	{
		/* change AHD mode - by song(2016-06-29) */
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], 0xFF, 0x03+((pel_ch%4)/2));
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], ACP_AHD2_FHD_MODE+((pel_ch)*0x80), 0x10);
		printk(">>>>> DRV[%s:%d] Normaly, Change mode, AHD\n", __func__, __LINE__ );
	}
}

void nvp6158_presend_comm(unsigned char pel_ch)
{
	gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], 0xFF, 0x03+((pel_ch%4)/2));
	if( RSch_mode_status[pel_ch] == NVP6134_VI_720P_5060)
	{
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_PEL_OUT+(((pel_ch)%2)*0x80), 0x01);
		msleep( 25 );
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_PEL_OUT+(((pel_ch)%2)*0x80), 0x00);
	}
	else 
	{
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x01);
		//msleep( 25 );
		gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], AHD2_FHD_OUT+(((pel_ch)%2)*0x80), 0x00);
	}
}

void get_acp_reg_rd(unsigned char ch, unsigned char bank, unsigned char addr)
{
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+(ch%2)*0x80, 0x61);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+1+(ch%2)*0x80, bank);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+2+(ch%2)*0x80, addr);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+3+(ch%2)*0x80, 0x00);//Dummy
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x09+(ch%2)*0x80, 0x08);
}
#define AHD2_FHD_LINES	0x05

void init_acp_reg_rd(unsigned char ch)
{
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));

	if(0)
	//if(chip_id[ch/4] == RAPTOR3_4PORT_R0_ID)			// 6158
	{
		if(RSch_mode_status[ch] == NVP6134_VI_4M_NRT || RSch_mode_status[ch] == NVP6134_VI_4M || \
		RSch_mode_status[ch] == NVP6134_VI_5M_NRT || RSch_mode_status[ch] == NVP6134_VI_5M_20P || \
		RSch_mode_status[ch] == NVP6134_VI_8M || RSch_mode_status[ch] == NVP6134_VI_8M_NRT)
		{
			gpio_i2c_write(raptor3_i2c_addr[ch/4], AHD2_FHD_LINES+((ch%2)*0x80), 0x07);
		}
		else
		{
			gpio_i2c_write(raptor3_i2c_addr[ch/4], AHD2_FHD_LINES+((ch%2)*0x80), 0x03);
		}
	}

	gpio_i2c_write(raptor3_i2c_addr[ch/4], ACP_MODE_ID+((ch%2)*0x80), ACP_REG_RD);
}

void acp_reg_rx_clear(unsigned char ch)
{
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x3A+((ch%2)*0x80), 0x01);
	msleep(10);
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x3A+((ch%2)*0x80), 0x00);
	msleep(200);
}

void  acp_isp_init_rs(unsigned char ch, unsigned int reg_addr)
{
	unsigned char bank;
	unsigned char addr;

	bank = (reg_addr>>8)&0xFF;
	addr = reg_addr&0xFF;

	init_acp_reg_rd(ch);
	get_acp_reg_rd(ch, bank, addr);
	acp_reg_rx_clear(ch);
}

void __nvp6158_set_each_coax_mode(unsigned char pel_ch)
{
	//unsigned char ch;
	//ch = pel_ch%4;
	NC_VD_COAX_Init_STR *CoaxVal = __NC_VD_COAX_InitFormat_Get( ch_mode_status[pel_ch] );

	gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], 0xFF, 0x03+((pel_ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[pel_ch/4], 0x0B+((pel_ch%2)*0x80), CoaxVal->tx_mode);
}

void acp_isp_write(unsigned char ch, unsigned int reg_addr, unsigned char reg_data)			//借用6134的  待验证
{
	unsigned char bankaddr = 0x00;
	unsigned char device_id = 0x00;

	/* set coax RX device ID */
	bankaddr = (reg_addr>>8)&0xFF;
	if( bankaddr >= 0xB0 && bankaddr <= 0xB4 )
	{
		device_id = 0x55;
	}
	else
	{
		device_id = ACP_REG_WR;
	}

	/* write data to isp */
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x05+((ch%2)*0x80), 0x07);// CH Active line(0x07->8Line)
	gpio_i2c_write( raptor3_i2c_addr[ch/4], ACP_MODE_ID+((ch%2)*0x80), ACP_REG_WR);
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x10+((ch%2)*0x80), ACP_REG_WR);			// data1(#define ACP_AHD2_FHD_D0	0x10)
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x11+((ch%2)*0x80), (reg_addr>>8)&0xFF);	// data2(bank)
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x12+((ch%2)*0x80), reg_addr&0xFF);			// data3(address)
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x13+((ch%2)*0x80), reg_data);				// data4(Don't care)
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x60+((ch%2)*0x80), device_id);				// data4(DEVICE ID)
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x09+((ch%2)*0x80), 0x08);					// by song - pulse on(trigger)
	msleep(140);																		// sleep to recognize NRT(15fps) signal for ISP by song(M)
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x09+((ch%2)*0x80), 0x10);					// by song(2016-07-01)-reset - pulse off
	gpio_i2c_write( raptor3_i2c_addr[ch/4], 0x09+((ch%2)*0x80), 0x00);					// by song - pulse off
}

#define DAY_NIGHT_MODE_BW_OFF	0x00
#define DAY_NIGHT_MODE_BW_ON	0x01
unsigned char s_transflag[16] = {DAY_NIGHT_MODE_BW_OFF, };

void acp_ctl_dec( unsigned char ch, void *p_param )
{
	unsigned char vidmode;
	unsigned char bwinfo;

	nvp6124_input_videofmt *pvideoacp = (nvp6124_input_videofmt*)p_param;

	vidmode = RSch_mode_status[ch];
	if( vidmode == NVP6134_VI_3M_NRT || vidmode == NVP6134_VI_3M ||
	vidmode == NVP6134_VI_4M_NRT || vidmode == NVP6134_VI_4M    ||
	vidmode == NVP6134_VI_5M_NRT || vidmode == NVP6134_VI_5M_20P )
	{
		/* control dec according to ISP information */
		bwinfo = (pvideoacp->getacpdata[ch][1]>>1)&0x01;
		if( bwinfo == DAY_NIGHT_MODE_BW_OFF && s_transflag[ch] != DAY_NIGHT_MODE_BW_OFF )
		{
			/* set flag */
			s_transflag[ch] = DAY_NIGHT_MODE_BW_OFF;
			printk(">>>>> DRV[%s:%d] CH:%d, Change mode BW OFF\n", __func__, __LINE__, ch );
		}
		else if( bwinfo == DAY_NIGHT_MODE_BW_ON && s_transflag[ch] != DAY_NIGHT_MODE_BW_ON )
		{
			/* set flag */
			s_transflag[ch] = DAY_NIGHT_MODE_BW_ON;
			printk(">>>>> DRV[%s:%d] CH:%d, Change mode BW ON\n", __func__, __LINE__, ch );
		}
	}

	return;
}

unsigned char read_acp_status(unsigned char ch)
{
	unsigned char val;

	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	gpio_i2c_write(raptor3_i2c_addr[ch/4], ACP_MODE_ID+((ch%2)*0x80), ACP_CAM_STAT);
	val = gpio_i2c_read( raptor3_i2c_addr[ch/4], 0x50+((ch%2)*0x80));

	return val;
}

void acp_read(nvp6124_input_videofmt *pvideoacp, unsigned char ch)
{
	unsigned int buf[16];
	unsigned char val, i;

	/*
	 * check status and set/get information
	 */
	val = read_acp_status(ch);
	if(val == ACP_CAM_STAT)
	{
		for(i=0;i<8;i++)
		{
			buf[i] = gpio_i2c_read(raptor3_i2c_addr[ch/4],0x50+((ch%2)*0x80)+i);
			pvideoacp->getacpdata[ch][i] = buf[i];
		}

		/* control dec according to the isp information */
		acp_ctl_dec( ch, pvideoacp );
	}
	else if(val == ACP_REG_WR)
	{
		for(i=0;i<4;i++)
		{
			buf[i] = gpio_i2c_read(raptor3_i2c_addr[ch/4],ACP_RX_D0+((ch%2)*0x80)+i);
			pvideoacp->getacpdata[ch][i] = buf[i];
		}
		gpio_i2c_write(raptor3_i2c_addr[ch/4], ACP_AHD2_FHD_OUT+((ch%2)*0x80), 0x00);
	}
	else if(val == ACP_REG_RD)
	{
		for(i=0;i<4;i++)
		{
			buf[i] = gpio_i2c_read(raptor3_i2c_addr[ch/4],ACP_RX_D0+((ch%2)*0x80)+i);
			pvideoacp->getacpdata[ch][i] = buf[i];
		}
		gpio_i2c_write(raptor3_i2c_addr[ch/4], ACP_AHD2_FHD_OUT+((ch%2)*0x80), 0x00);
	}
	else
	{
		for(i=0;i<8;i++)
		{
			pvideoacp->getacpdata[ch][i] = 0x00;
		}
		gpio_i2c_write(raptor3_i2c_addr[ch/4], ACP_AHD2_FHD_OUT+((ch%2)*0x80), 0x00);
	}
	rs_coax_rx_buffer_clear(ch);
}

unsigned char acp_isp_read_rs(unsigned char ch, unsigned int reg_addr)
{
	unsigned int data;
	unsigned int temp=0;
	unsigned char vidmode;
	
	vidmode = RSch_mode_status[ch];
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	if( vidmode == NVP6134_VI_4M_NRT || vidmode == NVP6134_VI_5M_NRT ||
		vidmode == NVP6134_VI_4M 	 || vidmode == NVP6134_VI_5M_20P )
	{
		temp = gpio_i2c_read(raptor3_i2c_addr[ch/4], ACP_MODE_ID+((ch%2)*0x80));
		if(temp != ACP_REG_RD)
		{
			acp_isp_init_rs(ch,pir_bk[ch]);//400W or 500W modify acp_isp_write_eqstage
		}
	}

	data = gpio_i2c_read(raptor3_i2c_addr[ch/4],0x50+3+((ch%2)*0x80));			//原6134接收的寄存器为0x78

	return data;
}

//get pir and agc
unsigned char acp_isp_read_rs_ex(unsigned char ch, unsigned char *data)
{
	//unsigned int data;
	//unsigned int temp=0;
	unsigned char vidmode;
	vidmode = RSch_mode_status[ch];
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xFF, 0x03+((ch%4)/2));
	data[0] = gpio_i2c_read(raptor3_i2c_addr[ch/4],0x50+3+((ch%2)*0x80));			//原6134接收的寄存器为0x78
	data[1] = gpio_i2c_read(raptor3_i2c_addr[ch/4],0x50+4+((ch%2)*0x80));
	return 0;
}


void nvp6158_acp_command(unsigned char ch)
{
	unsigned char i;
	unsigned char str_ext[10];
	
	__nvp6158_set_each_coax_mode(ch);
	mdelay(20);

	str_ext[0]=0xb5;
	str_ext[1]=0x0;
	str_ext[2]=0x87;
	str_ext[3]=0x0;
	str_ext[4]=0x80;
	str_ext[5]=0x0;
	str_ext[6]=0x0;
	str_ext[7]=0x0;
	str_ext[8]=0x0;
	for(i=0;i<8;i++)
	{
		if(i != 4)
		{
			str_ext[8] = str_ext[8] + str_ext[i];
		}
	}
	str_ext[8]=str_ext[8] & 0xff;
	str_ext[9]=0x80;
	gpio_i2c_write(raptor3_i2c_addr[ch/4], 0xff, 0x03+((ch%4)/2));

	for(i=0;i<10;i++)
	{
		gpio_i2c_write(raptor3_i2c_addr[ch/4], 0x10+i+(((ch)%2)*0x80), str_ext[i]);
	}
	gpio_i2c_write(raptor3_i2c_addr[ch/4], AHD2_FHD_OUT+(((ch)%2)*0x80), 0x08);
}

//extern unsigned char videofmt_vfc[16];
void RS_TVI_ACP_Rx_Data_Get(unsigned char ch,unsigned char *data)
{
	static unsigned char j;
	static unsigned char protocol_data[2];
	NC_VD_COAX_STR Coax_Rx_Data;

	Coax_Rx_Data.vd_dev	   			= ch/4;
	Coax_Rx_Data.ch					= ch%4;
	Coax_Rx_Data.format_standard  	= FMT_TVI;
	//Coax_Rx_Data.vivo_fmt         	= videofmt_vfc[ch];		//直接获取0xf0的值
	Coax_Rx_Data.vivo_fmt         	= ch_mode_status[ch];
	coax_rx_data_get(&Coax_Rx_Data);

	memset(protocol_data,0,sizeof(protocol_data));
	//change high to low
	
	//printk("rx_data1:%#x ====rx_data2:%#x,===========\n",Coax_Rx_Data.rx_data1[1],Coax_Rx_Data.rx_data1[2]);

	//printk("TVI PIR====pir data:0x%x\n",Coax_Rx_Data.rx_data1[1]);
	if (Coax_Rx_Data.rx_data1[1] == 0xe2)			//TVI 200W/500W普通pir
		data[0]=0xaa;
	else if (Coax_Rx_Data.rx_data1[1] == 0xe3)	//触发值
		data[0]=0xcc;
	else if (Coax_Rx_Data.rx_data1[1] == 0xe4)//TVI 200W 白光
		data[0]=0x11;
	else if (Coax_Rx_Data.rx_data1[1] == 0xe0)	// 白光摄像机 触发值
		data[0]=0x22;
	else
	{
		//change high to low
	
		for(j=0;j<8;j++)
		{
			protocol_data[0] += ((Coax_Rx_Data.rx_data1[1] >>(7-j))&0x01) << j;
		}
		data[0]=protocol_data[0];
	}
	for(j=0;j<8;j++)
	{
		protocol_data[1] += ((Coax_Rx_Data.rx_data1[2] >>(7-j))&0x01) << j;
	}
	data[1]=protocol_data[1];
	//printk("change rx_data1:%#x ====rx_data2:%#x,===========\n",data[0],data[1]);
}
