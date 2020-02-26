#include <linea.h>
#include <osbind.h>
#include <stdio.h>
#include "drawlib.h"
#include "typedef.h"


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

void draw_block(UWORD *base, int x, int y)
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
	draw_bitmap(base, x, y, block_bitmap, 16, AND);	
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

void draw_game_start(UWORD *base)
{
	int i;
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
		0x0000,
	};

	for(i = 0; i < 25; i++) {
		draw_bitmap(base,12*16,i*16,border_block_bitmap,16,AND);
	}

	for(i = 1; i < 13; i++) {
		draw_bitmap(base,(i+12)*16,24*16,border_block_bitmap,16,AND);
	}

	for(i = 24; i > -1; i--) {
		draw_bitmap(base,(12+12)*16,i*16,border_block_bitmap,16,AND);
	}
	
	for(i = 12; i < 21; i++) {
		draw_bitmap(base,(12+i)*16,0,border_block_bitmap,16,AND);
	}

	for(i = 0; i < 12; i++) {
		draw_bitmap(base,(12+20)*16,i*16,border_block_bitmap,16,AND);
	}

	for(i = 20; i > 12; i--) {
		draw_bitmap(base,(12+i)*16,11*16,border_block_bitmap,16,AND);
	}
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