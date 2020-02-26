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
		0x0000
	};

	static const UWORD zero_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	static const UWORD s_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C00,
		0x3C00,
		0x0FF0,
		0x0FF0,
		0x00FF,
		0x00FF,
		0x30FC,
		0x30FC,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	static const UWORD c_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	static const UWORD r_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3FF0,
		0x3FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3FF0,
		0x3FF0,
		0x3CC0,
		0x3CC0,
		0x3C3C,
		0x3C3C,
		0x0000,
		0x0000
	};

	static const UWORD e_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3FFC,
		0x3FFC,
		0x3000,
		0x3000,
		0x3FF0,
		0x3FF0,
		0x3000,
		0x3000,
		0x3000,
		0x3000,
		0x3FFC,
		0x3FFC,
		0x0000,
		0x0000
	};

	static const UWORD l_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3FFC,
		0x3FFC,
		0x0000,
		0x0000
	};

	static const UWORD i_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	static const UWORD n_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x303C,
		0x303C,
		0x3C3C,
		0x3C3C,
		0x3F3C,
		0x3F3C,
		0x33FC,
		0x33FC,
		0x30FC,
		0x30FC,
		0x303C,
		0x303C,
		0x0000,
		0x0000
	};

	static const UWORD x_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x303C,
		0x303C,
		0x0CF0,
		0x0CF0,
		0x03C0,
		0x03C0,
		0x0FC0,
		0x0FC0,
		0x3C30,
		0x3C30,
		0x300C,
		0x300C,
		0x0000,
		0x0000
	};

	static const UWORD t_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3FFC,
		0x3FFC,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x0000,
		0x0000
	};

	static const UWORD colon_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x3800,
		0x3800,
		0x3800,
		0x0000,
		0x0000,
		0x3800,
		0x3800,
		0x3800,
		0x0000,
		0x0000,
		0x0000,
		0x0000
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

	draw_bitmap(base,25*16,1*16,s_bitmap,16,XOR);
	draw_bitmap(base,26*16,1*16,c_bitmap,16,XOR);
	draw_bitmap(base,27*16,1*16,zero_bitmap,16,XOR);
	draw_bitmap(base,28*16,1*16,r_bitmap,16,XOR);
	draw_bitmap(base,29*16,1*16,e_bitmap,16,XOR);
	draw_bitmap(base,30*16,1*16,colon_bitmap,16,XOR);

	draw_bitmap(base,27*16,2*16,zero_bitmap,16,XOR);
	draw_bitmap(base,28*16,2*16,zero_bitmap,16,XOR);
	draw_bitmap(base,29*16,2*16,zero_bitmap,16,XOR);
	draw_bitmap(base,30*16,2*16,zero_bitmap,16,XOR);
	draw_bitmap(base,31*16,2*16,zero_bitmap,16,XOR);

	draw_bitmap(base,25*16,3*16,l_bitmap,16,XOR);
	draw_bitmap(base,26*16,3*16,i_bitmap,16,XOR);
	draw_bitmap(base,27*16,3*16,n_bitmap,16,XOR);
	draw_bitmap(base,28*16,3*16,e_bitmap,16,XOR);
	draw_bitmap(base,29*16,3*16,s_bitmap,16,XOR);
	draw_bitmap(base,30*16,3*16,colon_bitmap,16,XOR);

	draw_bitmap(base,29*16,4*16,zero_bitmap,16,XOR);
	draw_bitmap(base,30*16,4*16,zero_bitmap,16,XOR);
	draw_bitmap(base,31*16,4*16,zero_bitmap,16,XOR);

	draw_bitmap(base,25*16,5*16,n_bitmap,16,XOR);
	draw_bitmap(base,26*16,5*16,e_bitmap,16,XOR);
	draw_bitmap(base,27*16,5*16,x_bitmap,16,XOR);
	draw_bitmap(base,28*16,5*16,t_bitmap,16,XOR);
	draw_bitmap(base,29*16,5*16,colon_bitmap,16,XOR);
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