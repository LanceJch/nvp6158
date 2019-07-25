/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: video_output.h
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
#ifndef _RAPTOR3_VIDEO_OUTPUT_
#define _RAPTOR3_VIDEO_OUTPUT_

#include "common.h"

#define SEQUENCE_CH01	0x00
#define SEQUENCE_CH23  0x01

typedef struct _video_output_sequence
{
	unsigned char port;       // PORT_A, PORTB, PORTC, PORTD
	unsigned char ch01;			// [7:4] Sequence2 or 4, [3:0] Sequence1 or 3
	unsigned char ch23;			// [7:4] Sequence2 or 4, [3:0] Sequence1 or 3
	unsigned char devnum;
}video_output_sequence;

typedef struct _video_output_sequence_reg{
	unsigned char Port;					// PORT_A, PORTB, PORTC, PORTD
	unsigned char b1c0;
	unsigned char b1c1;
	unsigned char b1c2;
	unsigned char b1c3;
	unsigned char b1c4;
	unsigned char b1c5;
	unsigned char b1c6;
	unsigned char b1c7;
	unsigned char devnum;
}video_output_sequence_reg;

typedef struct _video_output_port_mux_mode
{
	unsigned char port;		//PORTAB PORTCD
	unsigned char mode;		//[7:4] PORTB or D [3:0] PORTA or C
	unsigned char devnum;
}video_output_port_mux_mode;

typedef struct _video_output_port_mux_chid
{
	unsigned char port;
	unsigned char chid;
	unsigned char devnum;
}video_output_port_mux_chid;

typedef struct _video_output_port_fmt_s
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
	unsigned char ch;

} video_output_port_fmt_s;

typedef struct _video_output_port_enable_s{
	unsigned char ch;
	unsigned char devnum;
	unsigned char Fmt_Def;
	unsigned char enable;
}video_output_port_enable_s;

void video_output_colorbar_set(unsigned char devnum);
void video_output_channel_sequence_set(video_output_sequence *vout_seq);
void video_output_channel_sequence_get(video_output_sequence_reg *vout_seq_reg);
void video_output_port_mux_mode_set(video_output_port_mux_mode *vout_port_mux_mode);
void video_out_port_enable(video_output_port_enable_s *portenable);
void video_output_port_format_mode_set( video_output_port_fmt_s *pformat );
void video_output_port_mux_chid_set(video_output_port_mux_chid *vout_chid);

void RS_VD_VO_Mode_Set_New( unsigned char ch, unsigned char devnum, int port, video_output_port_fmt_s *pPortFmt,
						   unsigned char SEQ0,  unsigned char SEQ1,  unsigned char SEQ2,  unsigned char SEQ3);
int nvp6158_set_portmode(const unsigned char chip, const unsigned char portsel, const unsigned char portmode, const unsigned char chid);


void nvp6158_acp_RT2NRT(unsigned char ch, unsigned char vfmt);
void nvp6158_acp_NRT2RT(unsigned char ch);
void nvp6158_acp_NTSCorPAL(unsigned char ch, unsigned char vfmt, unsigned char flag);


#endif

/********************************************************************
 *  End of file
 ********************************************************************/
