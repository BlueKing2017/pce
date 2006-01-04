/*****************************************************************************
 * pce                                                                       *
 *****************************************************************************/

/*****************************************************************************
 * File name:     src/devices/video/ega.h                                    *
 * Created:       2003-09-06 by Hampa Hug <hampa@hampa.ch>                   *
 * Last modified: 2005-04-18 by Hampa Hug <hampa@hampa.ch>                   *
 * Copyright:     (C) 2003-2005 Hampa Hug <hampa@hampa.ch>                   *
 *****************************************************************************/

/*****************************************************************************
 * This program is free software. You can redistribute it and / or modify it *
 * under the terms of the GNU General Public License version 2 as  published *
 * by the Free Software Foundation.                                          *
 *                                                                           *
 * This program is distributed in the hope  that  it  will  be  useful,  but *
 * WITHOUT  ANY   WARRANTY,   without   even   the   implied   warranty   of *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  General *
 * Public License for more details.                                          *
 *****************************************************************************/

/* $Id$ */


#ifndef PCE_IBMPC_EGA_H
#define PCE_IBMPC_EGA_H 1


#include <libini/libini.h>
#include <terminal/terminal.h>
#include <devices/video/video.h>


typedef struct ega_t {
	video_t       vid;

	mem_blk_t     *mem;
	mem_blk_t     *reg;

	unsigned char *data;

	unsigned long base;
	unsigned long size;

	unsigned      mode_80x25_w;
	unsigned      mode_80x25_h;
	unsigned      mode_320x200_w;
	unsigned      mode_320x200_h;
	unsigned      mode_640x200_w;
	unsigned      mode_640x200_h;
	unsigned      mode_640x350_w;
	unsigned      mode_640x350_h;
	unsigned      mode_640x480_w;
	unsigned      mode_640x480_h;

	unsigned char crtc_reg[24];
	unsigned char ts_reg[5];
	unsigned char gdc_reg[9];
	unsigned char atc_reg[21];

	int           atc_index;

	unsigned char latch[4];

	unsigned long clkcnt;

	void          (*update) (struct ega_t *ega);
	int           (*screenshot) (struct ega_t *ega, FILE *fp);
	void          (*set_latches) (struct ega_t *ega, unsigned long addr, unsigned char val[4]);
	void          (*set_uint8) (struct ega_t *ega, unsigned long addr, unsigned char val);
	unsigned char (*get_uint8) (struct ega_t *ega, unsigned long addr);

	unsigned      crtc_pos;
	unsigned      crtc_ofs;

	int           crs_on;

	unsigned      mode;
	unsigned      mode_w;
	unsigned      mode_h;

	char          dirty;

	terminal_t    *trm;
} ega_t;


video_t *ega_new (terminal_t *trm, ini_sct_t *sct);

void ega_del (ega_t *ega);

void ega_prt_state (ega_t *ega, FILE *fp);

int ega_dump (ega_t *ega, FILE *fp);

mem_blk_t *ega_get_mem (ega_t *cga);
mem_blk_t *ega_get_reg (ega_t *cga);

int ega_screenshot (ega_t *ega, FILE *fp, unsigned mode);

void ega_mem_set_uint8 (ega_t *ega, unsigned long addr, unsigned char val);
void ega_mem_set_uint16 (ega_t *ega, unsigned long addr, unsigned short val);
unsigned char ega_mem_get_uint8 (ega_t *ega, unsigned long addr);
unsigned short ega_mem_get_uint16 (ega_t *ega, unsigned long addr);

void ega_reg_set_uint8 (ega_t *ega, unsigned long addr, unsigned char val);
void ega_reg_set_uint16 (ega_t *ega, unsigned long addr, unsigned short val);
unsigned char ega_reg_get_uint8 (ega_t *ega, unsigned long addr);
unsigned short ega_reg_get_uint16 (ega_t *ega, unsigned long addr);

void ega_clock (ega_t *ega, unsigned long cnt);


#endif