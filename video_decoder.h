#ifndef _VIDEO_DECODER_H_
#define _VIDEO_DECODER_H_

#include <raptor3_fmt.h>

#define MAX_CH_PER_DECODERCHIP (16)
#define MAX_PORT_PER_DECODERCHIP (16)

typedef struct VDEC_CH_CFG_S
{
	NC_VIVO_CH_FORMATDEF FmtDef;

} VDEC_CH_CFG_S;

typedef struct VDEC_PORT_CFG_S
{
	NC_OUTPUT_MUX_MODE mux_mode;
	NC_OUTPUT_INTERFACE output_interface;
	NC_OUTPUT_EDGE edge;
	NC_CH SEQ[16];
} VDEC_PORT_CFG_S;

typedef struct FMT_DETECT_CONFIG_S
{
	void *pVdevDev;
	int ch_in_dev;

} FMT_DETECT_CONFIG_S;

typedef struct VDEC_DEV_S
{
	int i2c_dev_num;
	int i2c_dev_addr;
	int vid_port_total;
	int vid_port_start;
	
	int ch_per_chip;
	int port_per_chip;

	int detection_process_lock;
	int detection_process_inuse[MAX_CH_PER_DECODERCHIP];

	void (*CallbackFunc_OnFormatChanged) ( struct VDEC_DEV_S *pVdevDev, int dev_ch );

	VDEC_CH_CFG_S soc_saved_ch_cfg[MAX_CH_PER_DECODERCHIP];
	VDEC_PORT_CFG_S soc_saved_port_cfg[MAX_PORT_PER_DECODERCHIP];

	VDEC_CH_CFG_S vdec_saved_ch_cfg[MAX_CH_PER_DECODERCHIP];
	VDEC_PORT_CFG_S vdec_saved_port_cfg[MAX_PORT_PER_DECODERCHIP];

	FMT_DETECT_CONFIG_S detect_cfg[MAX_CH_PER_DECODERCHIP];

	// 170508 Add (RAPTOR3_FMT_DETECT_RESULT_S 삭제 예정)
	NC_VIVO_CH_FORMATDEF FmtDef[MAX_CH_PER_DECODERCHIP];
	int FormatChanged[MAX_CH_PER_DECODERCHIP];

	int Mux_Mode;

} VDEC_DEV_S;

typedef struct VDEC_DEV_INFORM_S{

	unsigned char chip_id[4];
	unsigned char chip_rev[4];
	unsigned char chip_addr[4];

	unsigned char Total_Port_Num;
	unsigned char Total_Chip_Cnt;

}VDEC_DEV_INFORM_S;


#endif
