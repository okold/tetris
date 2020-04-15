/* DRAWLIB.C
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   Colton Paquette		cpaqu904@mtroyal.ca
*   COMP 2659           Term Project
*   Winter 2020         Tyson Kendon
*
*	Private Functions:	void draw_bitmap(UWORD *base, int x, int y,
*				  			const UWORD *bitmap, unsigned int height, short mode);
*						-	Draws a bitmap at the given base.
*
*						void draw_block(UWORD *base, int x, int y, short mode);
*                       -   Draws a block in Style 1.	
*
*						void draw_border_block(UWORD *base, int x, int y);
*						-	Draws a block in Style 2.
*
*						void draw_blank_block(UWORD *base, int x, int y);
*                       -   Draws a block with a fully black bitmap.
*/
#include <linea.h>
#include <osbind.h>
#include <stdio.h>
#include "drawlib.h"
#include "typedef.h"
#include "fontlib.h"

#define TILES 16	/* tile size by pixels */
#define OFFSET 12	/* x-offset of the play area */

/* BITMAPS */
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

void draw_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height, short mode);
void draw_border_block(UWORD *base, int x, int y);
void draw_blank_block(UWORD *base, int x, int y);
void draw_block(UWORD *base, int x, int y, short mode);

/* Block drawing functions */
void draw_block(UWORD *base, int x, int y, short mode)
{
	draw_bitmap(base, x, y, block_bitmap, 16, mode);	
}

void draw_border_block(UWORD *base, int x, int y)
{
	draw_bitmap(base, x, y, border_block_bitmap, 16, AND);
}

void draw_blank_block(UWORD *base, int x, int y)
{
	draw_bitmap(base, x, y, black_bitmap, 16, OR);
}

/* Draws the play area border */
void draw_game_start(UWORD *base)
{
	int i;
	for(i = 0; i < 25; i++) {
		draw_border_block(base,12*16,i*16);
	}

	for(i = 1; i < 11; i++) {
		draw_border_block(base,(i+12)*16,24*16);
	}

	for(i = 24; i > -1; i--) {
		draw_border_block(base,(11+12)*16,i*16);
	}
	
}

/* Draws a bitmap of the given height on the given physbase 
*  at the given coordinates using the given mode
*/
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

/* Fills the screen with the given pattern.
*  -1 for black, 0 for white.
*/
void fill_screen(UWORD *base, char pattern)
{
	register int i = 0;
	register UWORD *loc = base;

	while (i++ < WORDS_PER_SCREEN)
		*(loc++) = pattern;
}

/* Disables the blinking text cursor */
void disable_cursor()
{
	printf("\033f"); /* i still don't get what this does */
	fflush(stdout);
}

/* Updates the second state based on the game state,
*  and draws changed blocks to the given base */
void draw_updated_state(UWORD* base, UBYTE game_state[12][25], 
			UBYTE state_to_update[12][25])
{
	int i,j;
	for(i = 1; i < 11; i++)
	{
		for (j = 0; j < 24; j++)
		{
			if (state_to_update[i][j] != game_state[i][j])
			{
				state_to_update[i][j] = game_state[i][j];
				if (state_to_update[i][j] == 0)
				{
					draw_blank_block(base, (i + OFFSET) * TILES, j * TILES);
				}
				else
				{
					draw_block(base, (i + OFFSET) * TILES, j * TILES,AND);	
				}
			}
		}
	}
}

/* Redraws the entire game state from max_height down. */
void redraw_state(UWORD* base, UBYTE game_state[12][25],
				int max_height)
{
	int i,j;
	for(i = 1; i < 11; i++)
	{
		for (j = max_height; j < 24; j++)
		{
			if (game_state[i][j] == 0)
			{
				draw_blank_block(base, (i + OFFSET) * TILES, j * TILES);
			}
			else
			{
				draw_block(base, (i + OFFSET) * TILES, j * TILES,AND);	
			}
		}
	}
}