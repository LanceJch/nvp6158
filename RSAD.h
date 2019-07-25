#ifndef __RSAD_H__
#define __RSAD_H__

//#define ONLY_720H

#define NVP6114	0x60
#define NVP6114_R0_ID 	0x83

/*====start nvp6124====*/
#define NVP6124	0x60
#define NVP6124_R0_ID 	0x84
#define NVP6114A_R0_ID 	0x85
#define NVP6124B_R0_ID 	0x86

#define NVP6134_R0_ID 	0x91
#define NVP6134B_R0_ID 	0x90
#define NVP6134B_REV_ID 	0x00
#define NVP6134C_REV_ID 	0x01
#define NVP6134E_REV_ID 	0x03	//128
#define NVP6134F_REV_ID 	0x04	//88

#define NVP6158C_R0_ID 	0xA0
#define NVP6158_R0_ID 	0xA1

#define NVP6168C_R0_ID 	0xC0
#define NVP6168_R0_ID 	0xC1

/*====end nvp6124====*/

//FIXME HI3520 Register
#define VIU_CH_CTRL					0x08
#define VIU_ANC0_START				0x9c
#define VIU_ANC0_SIZE				0xa0
#define VIU_ANC1_START				0xa4
#define VIU_ANC1_SIZE				0xa8
#define VIU_BLANK_DATA_ADDR			0xac

#define VDEC_NTSC	        0
#define VDEC_PAL	        1
#define VDEC_ERROR	        2

#define VDEC_AUTO	        3
#define VDEC_INVALID_MODE	4

/*====start nvp6124====*/
#define	VIDEO_NTSC_960_4CH	6
#define	VIDEO_PAL_960_4CH	7
#define	VIDEO_NTSC_960_720P	8 
#define	VIDEO_PAL_960_720P	9
#define	VIDEO_NTSC_720P_960	10
#define	VIDEO_PAL_720P_960	11
#define	VIDEO_NTSC_720P_2CH	36	
#define	VIDEO_PAL_720P_2CH	37
/*====end nvp6124====*/

#define NTSC   0
#define PAL    1
#define SET_ALL_CH          0xff

#define RSAD_SET_HUE             0x01
#define RSAD_SET_CONTRAST        0x02
#define RSAD_SET_BRIGHT          0x04
#define RSAD_SET_SATURATION      0x08
#define RSAD_SET_SHARPNESS       0x10

#define TVI_TP2802             0
#define AHD_NVP6114            1

/*====start nvp6124====*/
#define TVI_TP2802_AHD_NVP6124 2
#define AHD_NVP6124            3
#define TVI_TP2802_TW2964      4
#define TVI_TP2823     		   5
#define TVI_TP2824     		   6
#define AHD_NVP6124B     	   7
#define TVI_TP2834     		   8
#define TVI_TP2833     		   9
#define TVI_TP2833C     	   10
#define TVI_TP2853C     	   11
#define AHD_NVP6134     	   12
#define TVI_TP2823C     	   13
#define TVI_TP2826     	   	   14
#define TVI_TP2827     	   	   15
#define TVI_TP2827C     	   16
#define AHD_NVP6158 		17
#define AHD_NVP6158C 		18
#define AHD_NVP6168		19
#define AHD_NVP6168C		20


/*====end nvp6124====*/

#define CHIP_TYPE_4CH      0
#define CHIP_TYPE_8CH      1

#define CHIP_CHN_4CH      0
#define CHIP_CHN_8CH      1
#define CHIP_CHN_16CH     2
#define CHIP_CHN_9CH      3

/* common EQ define */
#define EQ_COMMON_ON	0x00
#define EQ_COMMON_OFF	0x01

typedef struct _rsad_info
{
    unsigned char author;
    unsigned char chiptype;
	unsigned char chipchn;
}rsad_info;

typedef struct _rsad_video_norm
{
    unsigned int chip;
    unsigned int mode;
} rsad_video_norm;

typedef struct _rsad_work_mode
{
	unsigned char chn;
    unsigned char chip;
    unsigned int mode;
	unsigned char vformat[16];
} rsad_work_mode;

typedef struct _rsad_video_loss
{
    unsigned int chip;
    unsigned int ch;
    unsigned int is_lost;
} rsad_video_loss;

typedef struct _rsad_image_adjust
{
    unsigned char chip;
    unsigned char chn;
    unsigned char hue;
    unsigned char contrast;
    unsigned int brightness;
    unsigned char saturation;
    unsigned char sharpness;
    unsigned long item_sel;/* use such as "CX26828_SET_HUE|CX26828_SET_CONTRAST" */
} rsad_image_adjust;

typedef struct _rsad_audio_format
{
    unsigned char format;   /* 0:i2s; 1:dsp */
} rsad_audio_format;

typedef struct _rsad_audio_output
{
    unsigned char PlaybackOrLoop;   /*0:playback; 1:loop*/
    unsigned char channel;          /*[0, 15]*/
    unsigned char reserve[6];
} rsad_audio_output;

typedef struct _rsad_audio_playback
{
    unsigned int chip;
    unsigned int chn;
} rsad_audio_playback;

typedef struct _rsad_audio_da_mute
{
    unsigned int chip;
	unsigned int chn;
} rsad_audio_da_mute;

typedef struct _rsad_audio_da_volume
{
    unsigned int chip;
    unsigned int volume;
} rsad_audio_da_volume;

typedef struct _rsad_video_scaler
{
    unsigned int chip;
    unsigned long long scaler_value;
}rsad_video_scaler;

typedef struct _vdec_clock_mode
{
    unsigned int chip;
    unsigned int mode;
}vdec_clock_mode;


typedef struct _vdec_motion_area
{
    unsigned char ch;
    int m_info[12];
}vdec_motion_area;

/*====start nvp6124====*/
typedef struct _nvp6124_motion_area
{
    unsigned char ch;
    int m_info[12];
}nvp6124_motion_area;
/*====end nvp6124====*/

typedef struct _vdec_input_videofmt
{
    //unsigned int ch;
    unsigned int inputvideofmt[16];
	unsigned int getvideofmt[16];
}vdec_input_videofmt;

/*====start nvp6124====*/
typedef struct _nvp6124_video_mode
{
    unsigned int chip;
    unsigned int mode;
	unsigned char vformat[16];
	unsigned char chmode[16];
}nvp6124_video_mode;
/*====end nvp6124====*/
/**************AHD_PROTOCOL*************/

typedef struct
{
	unsigned char chn;
	unsigned char command;
	unsigned char udata;
	unsigned char status;
}RSAD_PROTOCOL_S;

typedef enum
{
	MENU_PROTOCOL=0,
	DOWN_PROTOCOL,
	UP_PROTOCOL,
	LEFT_PROTOCOL,
	RIGHT_PROTOCOL,
	SET_PROTOCOL,

	KEY_TILT_UP=0x10,
	KEY_TILT_DOWN,
	KEY_PAN_RIGHT,
	KEY_PAN_LEFT,
	KEY_LEFT_UP,
	KEY_LEFT_DOWN,
	KEY_RIGTH_UP,
	KEY_RIGTH_DOWN,
	KEY_IRIS_CLOSE,
	KEY_IRIS_OPEN,
	KEY_FOCUS_NEAR,
	KEY_FOCUS_FAR,
	KEY_ZOOM_WIDE,
	KEY_ZOOM_TELE,
	KEY_MOTOR_STOP,
	KEY_PRESET_SET,
	KEY_PRESET_CLR,
	KEY_PRESET_CALL,
	KEY_SET_CAMERA,
	KEY_SET_LEDON,
	KEY_SET_LEDOFF,
	KEY_SET_PRINTRAIN,
	KEY_CMD_OSD,
	KEY_AUTO_STOP,
	KEY_CUSTOM,
	
	KEY_CAMERA_STATUS=0x40,
	KEY_SET_SPEED,
	KEY_SET_WHITE_LED,
	KEY_SET_WHITE_LED_MODE,
	KEY_OUT_BUTT
}RSAD_PROTOCOL_E;

/****************************************/

/*====start nvp6124====*/
/* AHD TVI 兼容使用的VI 输出类型枚举*/
enum
{
	/* AHD 使用的VI 输出类型*/
	AT_A_INPUT_VIDEOFMT_SD_NTSC = 0x01,
	AT_A_INPUT_VIDEOFMT_SD_PAL = 0x02,
	AT_A_INPUT_VIDEOFMT_720P_30FPS = 0x04,
	AT_A_INPUT_VIDEOFMT_720P_25FPS = 0x08,
	AT_A_INPUT_VIDEOFMT_720P_60FPS = 0x10,
	AT_A_INPUT_VIDEOFMT_720P_50FPS = 0x20,
	AT_A_INPUT_VIDEOFMT_1080P_30FPS = 0x40,
	AT_A_INPUT_VIDEOFMT_1080P_25FPS = 0x80,
	AT_A_INPUT_VIDEOFMT_EXC_720P_30FPS = 0x11,
	AT_A_INPUT_VIDEOFMT_EXC_720P_25FPS = 0x12,
	AT_A_INPUT_VIDEOFMT_EXTA_720P_30FPS = 0x21,
	AT_A_INPUT_VIDEOFMT_EXTA_720P_25FPS = 0x22,
	AT_A_INPUT_VIDEOFMT_EXTB_720P_30FPS = 0x24,
	AT_A_INPUT_VIDEOFMT_EXTB_720P_25FPS = 0x28,
	AT_A_INPUT_VIDEOFMT_EXC_720P_60FPS = 0x31,
	AT_A_INPUT_VIDEOFMT_EXC_720P_50FPS = 0x32,
	AT_A_INPUT_VIDEOFMT_EXT_720P_60FPS = 0x34,
	AT_A_INPUT_VIDEOFMT_EXT_720P_50FPS = 0x38,
	AT_A_INPUT_VIDEOFMT_EXC_1080P_30FPS = 0x41,
	AT_A_INPUT_VIDEOFMT_EXC_1080P_25FPS = 0x42,
	AT_A_INPUT_VIDEOFMT_EXT_1080P_30FPS = 0x44,
	AT_A_INPUT_VIDEOFMT_EXT_1080P_25FPS = 0x48,
	AT_A_INPUT_VIDEOFMT_1080P_NRT = 0x49,
	AT_A_INPUT_VIDEOFMT_1080P_12_5FPS = 0x50,
	//AT_A_INPUT_VIDEOFMT_QHD_30FPS = 0x51,
	//AT_A_INPUT_VIDEOFMT_QHD_25FPS = 0x52,
	AT_A_INPUT_VIDEOFMT_UHDX_30FPS = 0x54,
	AT_A_INPUT_VIDEOFMT_UHDX_25FPS = 0x58,
	AT_A_INPUT_VIDEOFMT_3M_NRT   = 0x60,
	AT_A_INPUT_VIDEOFMT_3M_30FPS   = 0x61,
	AT_A_INPUT_VIDEOFMT_3M_25FPS   = 0x62,
	AT_A_INPUT_VIDEOFMT_4M_NRT   = 0x63,
	AT_A_INPUT_VIDEOFMT_4M_30FPS   = 0x64,
	AT_A_INPUT_VIDEOFMT_4M_25FPS   = 0x65,
	AT_A_INPUT_VIDEOFMT_5M_NRT   = 0x66,
	AT_T_INPUT_VIDEOFMT_3M_NRT   = 0x67,
	AT_A_INPUT_VIDEOFMT_5M_20FPS  = 0x68,
	AT_T_INPUT_VIDEOFMT_5M_12_5FPS  = 0x69,

	AT_A_INPUT_VIDEOFMT_6M_18P  = 0x6A,
	AT_A_INPUT_VIDEOFMT_6M_20P  = 0x6B,
	AT_A_INPUT_VIDEOFMT_8M_7_5P  = 0x6C,
	AT_A_INPUT_VIDEOFMT_8M_12_5P  = 0x6D,
	AT_A_INPUT_VIDEOFMT_8M_15P  = 0x6E,
	
	AT_T_INPUT_VIDEOFMT_720P_60FPS=0x82,
	AT_T_INPUT_VIDEOFMT_720P_50FPS,
	AT_T_INPUT_VIDEOFMT_1080P_30FPS,
	AT_T_INPUT_VIDEOFMT_1080P_25FPS,
	AT_T_INPUT_VIDEOFMT_720P_30FPS,
	AT_T_INPUT_VIDEOFMT_720P_25FPS,
	AT_T_INPUT_VIDEOFMT_NT_PAL,
	AT_T_INPUT_VIDEOFMT_720P25V2,
	AT_T_INPUT_VIDEOFMT_720P30V2,
	AT_T_INPUT_VIDEOFMT_SD_NTSC,
	AT_T_INPUT_VIDEOFMT_SD_PAL,
	AT_T_INPUT_VIDEOFMT_3M18,
	AT_T_INPUT_VIDEOFMT_5M12,
	AT_T_INPUT_VIDEOFMT_4M15,
	AT_T_INPUT_VIDEOFMT_4M_30FPS,
	AT_T_INPUT_VIDEOFMT_4M_25FPS,
	AT_T_INPUT_VIDEOFMT_5M20=0x92,
	AT_T_INPUT_VIDEOFMT_8M12=0xa0,
	AT_T_INPUT_VIDEOFMT_8M15,

	AT_C_INPUT_VIDEOFMT_4M_25FPS=0xb2,
	AT_C_INPUT_VIDEOFMT_4M_30FPS,

	AT_C_INPUT_VIDEOFMT_8M_12_5FPS,
	AT_C_INPUT_VIDEOFMT_8M_15FPS,
	
	AHD_INPUT_VIDEOFMT_NOVIDEO=0xf0,
	AHD_TVI_INPUT_VIDEOFMT_BUTT
};
enum
{
	NVP6124_VI_SD = 0,
	NVP6124_VI_720P_2530,
	NVP6124_VI_720P_5060,
	NVP6124_VI_1080P_2530,
	NVP6124_VI_1920H,
	NVP6124_VI_720H,
	NVP6124_VI_1280H,
	NVP6124_VI_1440H,
	NVP6124_VI_960H2EX,   //nvp6124b
	NVP6124_VI_HDEX,
	NVP6124_VI_BUTT,
	
	TVI_720P25 = 50,//	    9
    TVI_720P30,//		4
    TVI_720P50,//	    1
    TVI_720P60,  //		0
    TVI_1080P25,//	    3
    TVI_1080P30, //	    2
    TVI_SD      ,
	TVI_INVALID_FORMAT ,
	TVI_720P25V2,
	TVI_720P30V2,
	TVI_PAL,
	TVI_NTSC,
	TVI_3M,
	TVI_5M,
	TVI_4M,
	
	NVP6124_VI_SD_2MUX_SD=80,
	NVP6124_VI_720P_2MUX_HD_X,//640*720
	NVP6124_VI_720P_2MUX_HD,//1280*720
	NVP6124_VI_1080P_2MUX_FHD_X,//960*1080
	NVP6124_VI_1080P_2MUX_FHD,  //1920*1080

	NVP6134_VI_720H			= 0x5b,	//720x576i(480)
	NVP6134_VI_960H,       			//960x576i(480)
	NVP6134_VI_1280H,				//1280x576i(480)
	NVP6134_VI_1440H,				//1440x576i(480)
	NVP6134_VI_1920H,				//1920x576i(480)
	NVP6134_VI_960H2EX,   			//3840x576i(480)
	NVP6134_VI_720P_2530	= 0x6b,	//1280x720@25p(30)
	NVP6134_VI_EXC_720P,			//1280x720@25p(30)
	NVP6134_VI_EXT_720PA,			//1280x720@25p(30)	
	NVP6134_VI_EXT_720PB,			//1280x720@25p(30)
	NVP6134_VI_HDEX,				//2560x720@25p(30)
	NVP6134_VI_EXC_HDEX,			//2560x720@25p(30)
	NVP6134_VI_EXT_HDAEX,			//2560x720@25p(30)
	NVP6134_VI_EXT_HDBEX,			//2560x720@25p(30)
	NVP6134_VI_720P_5060,			//1280x720@50p(60)
	NVP6134_VI_EXC_720PRT,			//1280x720@50p(60)
	NVP6134_VI_EXT_720PRT,			//1280x720@50p(60)
	NVP6134_VI_M_720PRT,			//for nextchip test only
	NVP6134_VI_1080P_2530	= 0x7b,	//1920x1080@25p(30)
	NVP6134_VI_EXC_1080P,			//1920x1080@25p(30)
	NVP6134_VI_EXT_1080P,			//1920x1080@25p(30)
	NVP6134_VI_1080P_NRT,
	NVP6134_VI_1080P_NOVIDEO,
	NVP6134_VI_3M_NRT		= 0x8b, //2048x1536@18p
	NVP6134_VI_3M,
	NVP6134_VI_EXC_3M_NRT,			//reserved
	NVP6134_VI_EXC_3M,				//reserved
	NVP6134_VI_EXT_3M_NRT,			//2048x1536@18p
	NVP6134_VI_EXT_3M,				//reserved
	NVP6134_VI_4M_NRT	= 0x9b, 	//2560x1440@NRT
	NVP6134_VI_4M,					//2560x1440@25p(30)
	NVP6134_VI_EXC_4M_NRT,			//reserved
	NVP6134_VI_EXC_4M,				//		2560x1440@25p(30)
	NVP6134_VI_EXT_4M_NRT,			//reserved
	NVP6134_VI_EXT_4M,				// 0xa0
	NVP6134_VI_5M_NRT  = 0xab,
	NVP6134_VI_5M,					//2592x1944@25P	
	NVP6134_VI_EXC_5M_NRT,			//reserved
	NVP6134_VI_EXC_5M,				//reserved
	NVP6134_VI_EXT_5M_NRT,			//2592x1944@12.5P
	NVP6134_VI_EXT_5M,				//reserved
	NVP6134_VI_5M_20P,				//reserved
	NVP6134_VI_8M_NRT		= 0xbb,	//reserved
	NVP6134_VI_8M,					//@12.5p(15)
	NVP6134_VI_EXC_8M_NRT,			//reserved
	NVP6134_VI_EXC_8M,				//reserved
	NVP6134_VI_EXT_8M_NRT,			//reserved
	NVP6134_VI_EXT_8M,				//reserved
	NVP6134_VI_UHD_X,				//reserved
	
	NVP6134_VI_BUTT,
	
};

typedef enum _nvp6124_outmode_sel
{
	NVP6124_OUTMODE_1MUX_SD = 0,
	NVP6124_OUTMODE_1MUX_HD,
	NVP6124_OUTMODE_1MUX_HD5060,
	NVP6124_OUTMODE_1MUX_FHD,
	NVP6124_OUTMODE_2MUX_SD,
	NVP6124_OUTMODE_2MUX_HD_X,
	NVP6124_OUTMODE_2MUX_HD,
	NVP6124_OUTMODE_2MUX_FHD_X,
	NVP6124_OUTMODE_4MUX_SD,
	NVP6124_OUTMODE_4MUX_HD_X,
	NVP6124_OUTMODE_4MUX_HD,
	NVP6124_OUTMODE_2MUX_FHD,
	NVP6124_OUTMODE_1MUX_HD_X,   //nvp6124b
	NVP6124_OUTMODE_1MUX_FHD_X,
	NVP6124_OUTMODE_4MUX_FHD_X,
	NVP6124_OUTMODE_4MUX_MIX,
	NVP6124_OUTMODE_2MUX_MIX,
	NVP6134_OUTMODE_1MUX_BT1120S,
	NVP6134_OUTMODE_1MUX_3M_RT, 
	NVP6134_OUTMODE_1MUX_4M_NRT,
	NVP6124_OUTMODE_BUTT
}NVP6124_OUTMODE_SEL;
/*====end nvp6124====*/

typedef enum _nvp6158_outmode_sel
{
	NVP6158_OUTMODE_1MUX_SD = 0,
	NVP6158_OUTMODE_1MUX_HD,
	NVP6158_OUTMODE_1MUX_HD5060,
	NVP6158_OUTMODE_1MUX_FHD,
	NVP6158_OUTMODE_2MUX_SD,
	NVP6158_OUTMODE_2MUX_HD_X,		// 5
	NVP6158_OUTMODE_2MUX_HD,
	NVP6158_OUTMODE_2MUX_FHD_X,
	NVP6158_OUTMODE_4MUX_SD,
	NVP6158_OUTMODE_4MUX_HD_X,
	NVP6158_OUTMODE_4MUX_HD,		// 10
	NVP6158_OUTMODE_2MUX_FHD,
	NVP6158_OUTMODE_1MUX_HD_X,   		//nvp6158c
	NVP6158_OUTMODE_1MUX_FHD_X,
	NVP6158_OUTMODE_4MUX_FHD_X,
	NVP6158_OUTMODE_4MUX_MIX,		// 15
	NVP6158_OUTMODE_2MUX_MIX,
	NVP6158_OUTMODE_1MUX_BT1120S,
	NVP6158_OUTMODE_1MUX_3M_RT, 
	NVP6158_OUTMODE_1MUX_4M_NRT,
	NVP6158_OUTMODE_1MUX_297MHz,
	NVP6158_OUTMODE_BUTT			// 20
}NVP6158_OUTMODE_SEL;
/*====end nvp6158C====*/

typedef enum _rsad_audio_samplerate
{
    RSAD_SAMPLE_RATE_8000=0,
	RSAD_SAMPLE_RATE_12000,
    RSAD_SAMPLE_RATE_16000,
	RSAD_SAMPLE_RATE_24000,
    RSAD_SAMPLE_RATE_32000,
    RSAD_SAMPLE_RATE_48000,
    RSAD_SAMPLE_RATE_44100,
    RSAD_SAMPLE_RATE_BUTT
} rsad_audio_samplerate;

typedef enum _rsad_audio_width
{
    RSAD_SAMPLE_WIDTH_16BIT=0,
	RSAD_SAMPLE_WIDTH_18BIT,
    RSAD_SAMPLE_WIDTH_20BIT,
	RSAD_SAMPLE_WIDTH_24BIT,
    RSAD_SAMPLE_WIDTH_32BIT,
    RSAD_SAMPLE_WIDTH_8BIT,
    RSAD_SAMPLE_WIDTH_BUTT
} rsad_audio_width;

typedef struct _rsad_audio_samplerate_width
{
    rsad_audio_samplerate samplerate;
    rsad_audio_width width;
} rsad_audio_samplerate_width;

typedef struct _rsad_audio_set_i2s
{
    unsigned char vender;//0:AHD 1:TVI
    unsigned char type;  //0:maser 1:slave
} rsad_audio_set_i2s;

typedef struct _rsad_acp_rw_data_
{
	unsigned char opt;
    unsigned char ch;
	unsigned int addr;
	unsigned char udata;
}rsad_acp_rw_data;

typedef struct _rsad_scan_mode_
{
    unsigned char ch;
	unsigned char mode;
}rsad_scan_mode;

typedef struct _rsad_eq_stage_
{
    unsigned char ch;
	unsigned char stage;
	unsigned char mode;
	unsigned char flag;
}rsad_eq_stage;

typedef struct _rsad_common_data_
{
    unsigned char ch;
	unsigned int data; //0:nrt 1:rt
}rsad_common_data;

typedef struct _rsad_acp_rw_data_ex_
{
	unsigned char opt;
    unsigned char ch;
	unsigned int addr;
	unsigned char udata[4];//udata[0]:pir udata[1]:agc
}rsad_acp_rw_data_ex;


typedef struct __file_information
{
	unsigned int	channel;
  	unsigned char 	filename[64];
  	unsigned char 	filePullname[64+32];
  	unsigned int	filesize;
  	unsigned int	filechecksum;			// (sum of file&0x0000FFFFF)
  	unsigned int	currentpacketnum;		// current packet sequnce number(0,1,2........)
  	unsigned int	filepacketnum;			// file packet number = (total size/128bytes), if remain exist, file packet number++
  	unsigned char 	onepacketbuf[128+32];

  	unsigned int	currentFileOffset;		// Current file offset
  	unsigned int	readsize;				// currnet read size

  	unsigned int	ispossiblefirmup[16]; 	// is it possible to update firmware?
  	int 			result;

  	int				appstatus[16];			// Application status

} FIRMWARE_UP_FILE_INFO, *PFIRMWARE_UP_FILE_INFO;

typedef struct _RS_VO_PORT_FMT_S
{

	const char *name;

	//For SoC
	int width;
	int height;

	unsigned char vo_clk;
	unsigned char merge;
	unsigned char mux_mode;
	unsigned char seq_ch01;
	unsigned char seq_ch23;
	unsigned char chid_vin01;
	unsigned char chid_vin23;

	unsigned char devnum;

}RS_VO_PORT_FMT_S;


#define RSAD_IOC_MAGIC            'c'

#define RSAD_GET_VIDEO_LOSS       _IOWR(RSAD_IOC_MAGIC, 1, rsad_video_loss)
#define RSAD_SET_IMAGE_ADJUST     _IOW(RSAD_IOC_MAGIC, 2, rsad_image_adjust)
#define RSAD_GET_IMAGE_ADJUST     _IOWR(RSAD_IOC_MAGIC, 3, rsad_image_adjust)
#define RSAD_SET_VIDEO_NORM       _IOW(RSAD_IOC_MAGIC, 4, rsad_video_norm)
#define RSAD_GET_VIDEO_NORM       _IOWR(RSAD_IOC_MAGIC, 5, rsad_video_norm)
#define RSAD_SET_WORK_MODE        _IOW(RSAD_IOC_MAGIC, 6, rsad_work_mode)

#define RSAD_SET_STABLE_WORKMODE			_IOWR(RSAD_IOC_MAGIC, 44,FIRMWARE_UP_FILE_INFO)


//#define RSAD_EN_AUDIO_DA_MUTE     _IOW(RSAD_IOC_MAGIC, 12, rsad_audio_da_mute)
#define RSAD_DIS_AUDIO_DA_MUTE	  _IOW(RSAD_IOC_MAGIC, 13, rsad_audio_da_mute)
#define RSAD_SET_SAMPLE_RATE      _IOW(RSAD_IOC_MAGIC, 7, rsad_audio_samplerate)
#define RSAD_SET_AUDIO_PLAYBACK   _IOW(RSAD_IOC_MAGIC, 8, rsad_audio_playback)
#define RSAD_SET_AUDIO_DA_MUTE    _IOW(RSAD_IOC_MAGIC, 9, rsad_audio_da_mute)
#define RSAD_SET_AUDIO_DA_VOLUME  _IOW(RSAD_IOC_MAGIC, 10, rsad_audio_da_volume)
#define RSAD_SET_AUDIO_FORMAT     _IOW(RSAD_IOC_MAGIC, 11, rsad_audio_format)
#define RSAD_SET_VIDEO_QUALITY    _IOW(RSAD_IOC_MAGIC, 12, int)
#define RSAD_SET_VIDEO_SCALER	  _IOW(RSAD_IOC_MAGIC, 14, rsad_video_scaler)
#define RSAD_GET_RSAD_AUTHOR	  _IOW(RSAD_IOC_MAGIC, 15, unsigned char) 
#define RSAD_INIT_VC_AUDIO	      _IOW(RSAD_IOC_MAGIC, 16, unsigned char) 
#define RSAD_SET_FLIR_TV_NORM	  _IOW(RSAD_IOC_MAGIC, 17, unsigned char) 
#define RSAD_SET_CAMERA_MODE      _IOW(RSAD_IOC_MAGIC, 18, unsigned char)
#define IOC_VDEC_SET_EQUALIZER	  _IOW(RSAD_IOC_MAGIC, 19, unsigned char)
#define RSAD_SET_CAMER_PROTOCOL   _IOW(RSAD_IOC_MAGIC, 20, unsigned int)
#define RSAD_GET_TVI_VERSION      _IOW(RSAD_IOC_MAGIC, 21, unsigned int)
#define RSAD_SET_AD_SAMPLE_RATE   _IOW(RSAD_IOC_MAGIC, 22, rsad_audio_samplerate_width)
#define RSAD_SET_DA_SAMPLE_RATE   _IOW(RSAD_IOC_MAGIC, 23, rsad_audio_samplerate_width)
#define RSAD_SET_PROTOCOL     	  _IOW(RSAD_IOC_MAGIC, 24,RSAD_PROTOCOL_S)
#define RSAD_SET_AUDIO_I2S    	  _IOW(RSAD_IOC_MAGIC, 25,rsad_audio_set_i2s)
#define RSAD_GET_AD_TYPE    	  _IOW(RSAD_IOC_MAGIC, 26,unsigned char)
#define RSAD_READ_ACP    	 	  _IOW(RSAD_IOC_MAGIC, 27,rsad_acp_rw_data)
#define RSAD_SET_UTC_MODE         _IOW(RSAD_IOC_MAGIC, 28,unsigned char)
#define RSAD_ACP_INIT         	  _IOW(RSAD_IOC_MAGIC, 29,rsad_acp_rw_data)
#define RSAD_SET_CUSTOM_FUNCTION  _IOW(RSAD_IOC_MAGIC, 30,unsigned char)
#define RSAD_SET_TVI_INIT	 	  _IOW(RSAD_IOC_MAGIC, 31,unsigned char)
#define RSAD_CLOSE_UTC_SINGLE	  _IOW(RSAD_IOC_MAGIC, 32,unsigned char)
#define RSAD_INIT_TVI_AUDIO_CASCADE	  _IOW(RSAD_IOC_MAGIC, 33,unsigned char)
#define RSAD_INIT_RESET_AHD_AUDIO  _IOW(RSAD_IOC_MAGIC, 34,unsigned char)
#define RSAD_SET_TVI_SCAN_MODE    _IOW(RSAD_IOC_MAGIC, 35,rsad_scan_mode)
#define RSAD_SET_EQ_STAGE         _IOW(RSAD_IOC_MAGIC, 36,rsad_eq_stage)
#define RSAD_RT_NRT_CHANGE     	  _IOW(RSAD_IOC_MAGIC, 37,rsad_common_data)
#define RSAD_GET_AGC     		  _IOWR(RSAD_IOC_MAGIC, 38,rsad_common_data)
#define RSAD_GET_PIR_AGC     	  _IOWR(RSAD_IOC_MAGIC, 60,rsad_acp_rw_data_ex)

/**************************ACP firmware update*****************************************/
#define IOC_VDEC_ACP_POSSIBLE_FIRMUP 	_IOWR(RSAD_IOC_MAGIC, 39,FIRMWARE_UP_FILE_INFO)
#define IOC_VDEC_ACP_CHECK_ISPSTATUS    _IOWR(RSAD_IOC_MAGIC, 40,FIRMWARE_UP_FILE_INFO)
#define IOC_VDEC_ACP_START_FIRMUP	 	_IOWR(RSAD_IOC_MAGIC, 41,FIRMWARE_UP_FILE_INFO)
#define IOC_VDEC_ACP_FIRMUP				_IOWR(RSAD_IOC_MAGIC, 42,FIRMWARE_UP_FILE_INFO)
#define IOC_VDEC_ACP_FIRMUP_END			_IOWR(RSAD_IOC_MAGIC, 43,FIRMWARE_UP_FILE_INFO)


//void Gpioi2cSpinLock();
//void Gpioi2cSpinUnLock();
void RS_AUTO_VFCtoFMTDEF(unsigned char ch,unsigned char VFC);

#endif

