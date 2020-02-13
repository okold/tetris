#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include "drawlib.h"

#define BYTES_PER_SCREEN 32000

#define BLOCK_HEIGHT 16

#define PLAY_AREA_ROWS 24
#define PLAY_AREA_COLS 10
#define PLAY_AREA_OFFSET_X 60
#define PLAY_AREA_OFFSET_Y 5

typedef unsigned char UBYTE;
typedef unsigned int  UWORD;
typedef unsigned long ULONG;

void disable_cursor();
void fill_screen(ULONG *base, char pattern);

void print_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height);

int main()
{
	UWORD block_bitmap[BLOCK_HEIGHT] = 
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

	UBYTE *base8 = Physbase();
	UWORD *base16 = Physbase();
	ULONG *base32 = Physbase();

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base32, -1);     /* set screen to all black */
	
	linea0();		   /* needs this, otherwise linea3() will crash the program */
	
	draw_play_area(PLAY_AREA_OFFSET_X, PLAY_AREA_OFFSET_Y, (PLAY_AREA_COLS * BLOCK_HEIGHT), (PLAY_AREA_ROWS * BLOCK_HEIGHT));
	
	/* test tiled blocks */
	print_bitmap(base16,0,0,block_bitmap,BLOCK_HEIGHT);
	print_bitmap(base16,16,0,block_bitmap,BLOCK_HEIGHT);
	print_bitmap(base16,0,16,block_bitmap,BLOCK_HEIGHT);
	print_bitmap(base16,16,16,block_bitmap,BLOCK_HEIGHT);

	Cnecin();                  /* wait for key press */

	fill_screen(base32, 0);      /* set screen to all white */

	return 0;
}




void disable_cursor()
{
	printf("\033f"); /* i still don't get what this does */
	fflush(stdout);
}

void fill_screen(ULONG *base, char pattern)
{
	register int i = 0;
	register ULONG *loc = base;

	while (i++ < BYTES_PER_SCREEN)
		*(loc++) = pattern;
}



void print_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height)
{
	int i;
	int offset;
	offset = (x>>4) + (y*40);
	for (i = 0; i < height; i++)
	{
		*(base + offset + (40*i)) &= bitmap[i];
	}		
}
