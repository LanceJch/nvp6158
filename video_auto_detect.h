/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: video_auto_detect.h
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
#ifndef _RAPTOR3_VIDEO_AUTO_DETECT_H_
#define _RAPTOR3_VIDEO_AUTO_DETECT_H_

#include "common.h"
#include "RSAD.h"


///----------------------------------------------
typedef struct _RS_VD_AUTO_VFC_STR{
 unsigned char Ch;
 unsigned char VFC;				//B5/6/7/8 0xf0
 unsigned char Dev_Num;		// Device Address
}RS_VD_AUTO_VFC_STR;

typedef enum DISTANCE
{
	SHORT_2M,
	LONG_100M,
	LONG_200M,
	LONG_300M,
	LONG_400M,
	LONG_500M,
}CABLE_DISTANCE;

typedef struct _RS_VD_AUTO_HSYNC_STR{ // 170207 Hsync Accumulation
 unsigned char Ch;
 unsigned char dev_addr;
 unsigned char h_lock;				// Bank 0 0xE2 [3:0] [Ch3:Ch0]
 unsigned int Hsync_Accum_Val1;		// Value 1  			// 170210 Add
 unsigned int Hsync_Accum_Val2;		// Value 2				// 170210 Add
 unsigned int Hsync_Accum_Result;	// Value 1 - Value 2	// 170210 Fix
}RS_VD_AUTO_HSYNC_STR;

typedef struct _RS_VD_AUTO_SAM_STR{ // 170207 SAM Value 항목 추가
 unsigned char Ch;
 unsigned char dev_addr;
 /*
 unsigned char SAMval_CD;			// B13 0xCD [7:0]
 unsigned char SAMval_CC;			// B13 0xCC [9:8]
 */
 unsigned int SAMval;
}RS_VD_AUTO_SAM_STR;

typedef struct _RS_VD_AUTO_AGC_STR{ // 170207 AGC Value 항목 추가
 unsigned char Ch;
 unsigned char devnum;
 unsigned char agc_lock;			// Bank 0 0xE0 [3:0] [Ch3:Ch0]
 unsigned char AGCval;				// B13 0xB8
}RS_VD_AUTO_AGC_STR;

typedef struct _RS_VD_AUTO_DIST_STR{ // 170207 Cable Distance 항목 추가
 unsigned char Ch;
 unsigned char devnum;
 unsigned char Dist;					// B13 0xA0
}RS_VD_AUTO_CABLE_DIST_STR;

typedef struct _RS_VD_MANUAL_DIST_STR{
 unsigned char Ch;
 unsigned char dev_addr;
 unsigned char Dist;
 unsigned char FmtDef;
 unsigned char cabletype;				// 0:coax, 1:utp, 2:reserved1, 3:reserved2
}RS_VD_MANUAL_CABLE_DIST_STR;

typedef enum ACC_DEBUG
{
	ACC_GAIN_NORMAL,
	ACC_GAIN_DEBUG,

}ACC_DEBUG;

typedef struct _RS_VD_AUTO_ACC_GAIN_STR{	// 170215 acc gain value read
	unsigned char Ch;
	unsigned char devnum;
	unsigned int AccGain;
        // DEBUG
	unsigned char FuncSel;
}RS_VD_AUTO_ACC_GAIN_STR;

///----------------------------------------------

typedef enum CH_NUM
{
	CH1 = 0,
	CH2,
	CH3,
	CH4
}CH_NUM;

typedef struct _video_input_vafe{
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

}video_input_vafe;

typedef struct _video_input_auto_detect{
	unsigned char ch;
	unsigned char devnum;

	unsigned char d_cmp;				//B5/6/7/8 0x03
	unsigned char slice_level;		//B5/6/7/8 0x08
	unsigned char control_mode;		//B5/6/7/8 0x47
	unsigned char gdf_fix_coeff;		//B5/6/7/8 0x50
	unsigned char dfe_ref_sel;		//B5/6/7/8 0x76
	unsigned char wpd_77;				//B5/6/7/8 0x77
	unsigned char wpd_78;				//B5/6/7/8 0x78
	unsigned char wpd_79;				//B5/6/7/8 0x79
	unsigned char auto_gnos_mode;		//B5/6/7/8 0x82
	unsigned char auto_sync_mode;		//B5/6/7/8 0x83
	unsigned char hafc_bypass;			//B5/6/7/8 0xB8

	unsigned char novid_vfc_init;	//B13		0x31
	unsigned char stable_mode_1;	//B13		0x0
	unsigned char stable_mode_2;	//B13		0x1

	unsigned char novid_det;		//B0		0x23/0x27/0x2B/0x2F
	video_input_vafe vafe;
}video_input_auto_detect;

typedef struct _video_input_novid{
	unsigned char ch;
	unsigned char novid; 				//B0 0xa8 [3:0]  MSB 1Ch ~ LSB 4Ch
	unsigned char devnum;
}video_input_novid;

typedef struct _video_input_vfc{
	unsigned char ch;
	unsigned char vfc;				//B5/6/7/8 0xf0
	unsigned char devnum;
}video_input_vfc;

typedef struct _video_input_onvid_set{
	unsigned char ch;
	unsigned char auto_gnos_mode;		//B5/6/7/8 0x82
	unsigned char auto_sync_mode;		//B5/6/7/8 0x83
	unsigned char op_md;				//B5/6/7/8 0xB8
}video_input_onvid_set;

typedef struct _video_input_onvid_set_2{
	unsigned char ch;
	unsigned char dfe_ref_sel;			//B5/6/7/8 0x76
	unsigned char wpd_77;				//B5/6/7/8 0x77
	unsigned char wpd_78;				//B5/6/7/8 0x78
	unsigned char wpd_79;				//B5/6/7/8 0x79
	unsigned char slice_mode;			//B5/6/7/8 0x0E
}video_input_onvid_set_2;

typedef struct _video_input_novid_set{
	unsigned char ch;
	unsigned char devnum;
	unsigned char control_mode;
	unsigned char gdf_fix_coeff;
	unsigned char auto_gnos_mode;
	unsigned char auto_sync_mode;
	unsigned char hafc_bypass;
	unsigned char dfe_ref_sel;			//B5/6/7/8 0x76
	unsigned char wpd_77;				//B5/6/7/8 0x77
	unsigned char wpd_78;				//B5/6/7/8 0x78
	unsigned char wpd_79;				//B5/6/7/8 0x79
	unsigned char slice_mode;			//B5/6/7/8 0x0E
}video_input_novid_set;

typedef struct _video_input_cable_dist{	
	unsigned char ch;
	unsigned char devnum;
	unsigned char dist;				// B13 0xA0
	unsigned char FmtDef;
	unsigned char cabletype;			// 0:coax, 1:utp, 2:reserved1, 3:reserved2
}video_input_cable_dist;

typedef struct _video_input_sam_val{
	unsigned char ch;
	unsigned char devnum;
	/*
	unsigned char sam_val_1;		// B13 0xCD [7:0]
	unsigned char sam_val_2;		// B13 0xCC [9:8]
	*/
	unsigned int  sam_val;
}video_input_sam_val;

typedef struct _video_input_hsync_accum{
	unsigned char ch;
	unsigned char devnum;
	unsigned char h_lock;				// Bank 0 0xE2 [3:0] [Ch3:Ch0]
	unsigned int  hsync_accum_val1;		// Value 1  			// 170210 Add
	unsigned int  hsync_accum_val2;		// Value 2				// 170210 Add
	unsigned int  hsync_accum_result;	// Value 1 - Value 2	// 170210 Fix
}video_input_hsync_accum;

typedef struct _video_input_agc_val{
	unsigned char ch;
	unsigned char devnum;
	unsigned char agc_lock;
	unsigned char agc_val;			// B13 0xB8
}video_input_agc_val;

typedef struct _video_input_format_set_done { // [add] 170209 format set done
	unsigned char ch;
	unsigned char set_val;		// B13 0x70 [3:0] each channel
}video_input_format_set_done;

typedef struct _video_input_fsc_val {
	unsigned char ch;
	unsigned char devnum;
	unsigned int fsc_val1;
	unsigned int fsc_val2;
	unsigned int fsc_final;
}video_input_fsc_val;

typedef struct _video_input_aeq_set{ // 170214 AEQ Set
	unsigned char ch;
	unsigned char aeq_val;				//B5/6/7/8 0x58       [7:4]
}video_input_aeq_set;

typedef struct _video_input_deq_set{ // 170214 DEQ Set
	unsigned char ch;
	unsigned char deq_val;				// B9 0x80/0xA0/0xC0/0xE0 [3:0]
}video_input_deq_set;

typedef struct _video_input_vfc_set{	// 170215 VFC Setting Enable  (temp)
	unsigned char ch;
	unsigned char set_val;
}video_input_vfc_set;


typedef struct _video_input_acc_gain_val{	// 170215 acc gain value read
	unsigned char ch;
	unsigned char devnum;
	unsigned int acc_gain_val;
	unsigned char func_sel;
}video_input_acc_gain_val;

typedef struct _video_input_sleep_time_val{	// 170215 acc gain value read
	unsigned char sleep_val;
}video_input_sleep_time_val;

typedef struct _video_input_agc_reset_val{	// 170221 agc init
	unsigned char ch;
	unsigned char reset_val;
}video_input_agc_reset_val;

typedef struct _video_output_data_out_mode{
	unsigned char ch;
	unsigned char devnum;
	unsigned char set_val;
}video_output_data_out_mode;

typedef struct _video_input_manual_mode{
	unsigned char ch;
	unsigned char dev_num;
}video_input_manual_mode;

typedef struct _video_input_onvideo_check_s{
	unsigned char vfc;
	unsigned char sw_rst_ret;
	decoder_dev_ch_info_s info;
}video_input_onvideo_check_s;


void video_input_auto_detect_set(video_input_auto_detect *vin_auto_det);
void video_input_vfc_read(video_input_vfc *vin_vfc);
void video_input_novid_read(video_input_novid *vin_novid); // 170204 novid
void video_input_no_video_set(video_input_novid_set *auto_novid); // 170206 novideo set 
void video_input_cable_dist_read(video_input_cable_dist *vin_cable_dist);	// 170207 Cable Distance 
void video_input_sam_val_read(video_input_sam_val *vin_sam_val ); 	// 170207 SAM Value 
void video_input_hsync_accum_read(video_input_hsync_accum *vin_hsync_accum );	// 170207 Hsync Accumulation 
void video_input_agc_val_read(video_input_agc_val *vin_agc_val); 	// 170207 AGC Value 
void video_input_fsc_val_read(video_input_fsc_val *vin_fsc_val); // 170214 fsc value read
void video_input_aeq_val_set(video_input_aeq_set *vin_aeq_val); // 170214 aeq value set
void video_input_deq_val_set(video_input_deq_set *vin_deq_val); // 170214 deq value set
void video_input_acc_gain_val_read(video_input_acc_gain_val *vin_acc_gain); // 170215 acc gain value read
void video_output_data_out_mode_set(video_output_data_out_mode *vo_data_out_mode); // 170329 Data Out Mode Setting Func
void video_input_manual_mode_set(video_input_manual_mode *vin_manual_det); // 170330 Manual Mode Set
void video_input_onvideo_set(decoder_dev_ch_info_s *decoder_info);

void video_input_onvideo_check_data(video_input_vfc *vin_vfc);
void video_input_auto_ch_sw_rst(decoder_dev_ch_info_s *decoder_info);

int  video_input_cable_measure_way( unsigned char ch, unsigned char devnum );
void video_input_vafe_reset(decoder_dev_ch_info_s *decoder_info);
void video_input_vafe_control(decoder_dev_ch_info_s *decoder_info, int cmd);
void video_input_manual_agc_stable_endi(decoder_dev_ch_info_s *decoder_info, int endi);
void video_input_ahd_tvi_distinguish(decoder_dev_ch_info_s *decoder_info);
void video_input_cvi_tvi_distinguish(decoder_dev_ch_info_s *decoder_info);

unsigned char RS__IsOver3MRTVideoFormat( const char *poFmtName );
NC_VIVO_CH_FORMATDEF RS_VD_AUTO_VFCtoFMTDEF(unsigned char VFC);

unsigned char  TVI_5M20P_Detect(unsigned char ch,decoder_dev_ch_info_s *dev_ch_info);
int RS_GetFormat_Bank5_EachCh( unsigned char ch);
CABLE_DISTANCE RS_APP_VD_MANUAL_CABLE_DISTANCE_Get(unsigned char Ch, NC_VIVO_CH_FORMATDEF FmtDef );
void RS_VD_AUTO_SAM_Get (unsigned char Ch, video_input_sam_val *pSAM);
void RS_VD_AUTO_HSYNC_Get (unsigned char Ch, video_input_hsync_accum* pHsync);
void RS_VD_AUTO_AGC_Get (unsigned char Ch, video_input_agc_val* pAGC);
void RS_VD_AUTO_ACC_GAIN_Get(unsigned char Ch, ACC_DEBUG FuncSel);
CABLE_DISTANCE RS_VD_MANUAL_CABLE_DISTANCE_Get (unsigned char Ch, video_input_cable_dist *pDistance);

void video_input_ahd_nrt_distinguish(decoder_dev_ch_info_s *decoder_info);

// Add for Raptor4
void nvp6168_video_input_manual_mode_set(video_input_manual_mode *vin_manual_det);
void nvp6168_video_input_auto_detect_set(video_input_auto_detect *vin_auto_det);
void nvp6168_video_input_vfc_read(video_input_vfc *vin_vfc);
void nvp6168_video_input_no_video_set(video_input_novid_set *auto_novid);
void nvp6168_video_input_hsync_accum_read(video_input_hsync_accum *vin_hsync_accum );
void nvp6168_video_input_onvideo_set(decoder_dev_ch_info_s *decoder_info);
void nvp6168_video_input_cvi_tvi_5Mdistinguish(decoder_dev_ch_info_s *decoder_info);


#endif /* _RAPTOR3_VIDEO_AUTO_DETECT_H_ */
