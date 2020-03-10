#include <linea.h>
#include <osbind.h>
#include <stdio.h>
#include "drawlib.h"
#include "typedef.h"
#include "fontlib.h"

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode)
{
	/* do line-a call to plot a line */

	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = style;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}

void draw_block(UWORD *base, int x, int y, short mode)
{
	static const UWORD block_bitmap[16] =
	{
		0x8001,
		0x4003,
		0x2007,
		0x1FFF,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x1FF7,
		0x3FFB,
		0x7FFD,
		0xFFFE
	};
	draw_bitmap(base, x, y, block_bitmap, 16, mode);	
}

void draw_blank_block(UWORD *base, int x, int y)
{
	static const UWORD black_bitmap[16] =
	{
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF
	};

	draw_bitmap(base, x, y, black_bitmap, 16, OR);
}

void border_block(UWORD *base, int x, int y)
{
	static const UWORD border_block_bitmap[16] =
	{
		0x0000,
		0x7FFE,
		0x4002,
		0x4002,
		0x401A,
		0x4016,
		0x401A,
		0x4016,
		0x401A,
		0x4016,
		0x4FFA,
		0x5556,
		0x6AAA,
		0x5556,
		0x7FFE,
		0x0000
	};

	draw_bitmap(base, x, y, border_block_bitmap, 16, AND);
}

void draw_game_start(UWORD *base)
{
	int i;
	for(i = 0; i < 25; i++) {
		border_block(base,12*16,i*16);
	}

	for(i = 1; i < 13; i++) {
		border_block(base,(i+12)*16,24*16);
	}

	for(i = 24; i > -1; i--) {
		border_block(base,(12+12)*16,i*16);
	}
	
	for(i = 12; i < 21; i++) {
		border_block(base,(12+i)*16,0);
	}

	for(i = 0; i < 12; i++) {
		border_block(base,(12+20)*16,i*16);
	}

	for(i = 20; i > 12; i--) {
		border_block(base,(12+i)*16,11*16);
	}

	write_s(base,25*16,1*16);
	write_c(base,26*16,1*16);
	write_o(base,27*16,1*16);
	write_r(base,28*16,1*16);
	write_e(base,29*16,1*16);
	write_colon(base,30*16,1*16);

	num_0(base,27*16,2*16);
	num_0(base,28*16,2*16);
	num_0(base,29*16,2*16);
	num_0(base,30*16,2*16);
	num_0(base,31*16,2*16);

	write_l(base,25*16,3*16);
	write_i(base,26*16,3*16);
	write_n(base,27*16,3*16);
	write_e(base,28*16,3*16);
	write_s(base,29*16,3*16);
	write_colon(base,30*16,3*16);

	num_0(base,29*16,4*16);
	num_0(base,30*16,4*16);
	num_0(base,31*16,4*16);

	write_n(base,25*16,5*16);
	write_e(base,26*16,5*16);
	write_x(base,27*16,5*16);
	write_t(base,28*16,5*16);
	write_colon(base,29*16,5*16);

	draw_block(base,27*16,8*16, AND);
	draw_block(base,28*16,8*16, AND);
	draw_block(base,28*16,7*16, AND);
	draw_block(base,29*16,7*16, AND);
}

void draw_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height, short mode)
{
	int i;
	int offset;
	offset = (x>>4) + (y*40);

	if (mode == AND)
	{
		for (i = 0; i < height; i++)
		{
		*(base + offset + (40*i)) &= bitmap[i];
		}
	}
	else if (mode == OR)
	{
		for (i = 0; i < height; i++)
		{
			*(base + offset + (40*i)) |= bitmap[i];
		}
	}
	else if (mode == XOR)
	{
		for (i = 0; i < height; i++)
		{
			*(base + offset + (40*i)) ^= bitmap[i];
		}
	}
}

void fill_screen(ULONG *base, char pattern)
{
	register int i = 0;
	register ULONG *loc = base;

	while (i++ < BYTES_PER_SCREEN)
		*(loc++) = pattern;
}

void disable_cursor()
{
	printf("\033f"); /* i still don't get what this does */
	fflush(stdout);
}