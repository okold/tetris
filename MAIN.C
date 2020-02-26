#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include "drawlib.h"
#include "typedef.h"

#define PLAY_AREA_ROWS 24
#define PLAY_AREA_COLS 10
#define PLAY_AREA_OFFSET_X 60
#define PLAY_AREA_OFFSET_Y 5

#define SCORE_BOX_HEIGHT 144
#define SCORE_BOX_WIDTH 96
#define SCORE_BOX_OFFSET_X 250
#define SCORE_BOX_OFFSET_Y 10
/*
void print_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height);
*/
int main()
{
	int y = 0;

	UBYTE *base8 = Physbase();
	UWORD *base16 = Physbase();
	ULONG *base32 = Physbase();

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base32, -1);     /* set screen to all black */

	linea0();		   /* needs this, otherwise linea3() will crash the program */
	
	draw_game_start(base16);
/*
	draw_play_area(PLAY_AREA_OFFSET_X, PLAY_AREA_OFFSET_Y, (PLAY_AREA_COLS * BLOCK_HEIGHT), (PLAY_AREA_ROWS * BLOCK_HEIGHT));
	draw_score_box(SCORE_BOX_OFFSET_X, SCORE_BOX_OFFSET_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT);

	draw_block(base16, 0, 0);
	draw_block(base16, 8, 8);
*/
	while (!Cconis())     /* repeat until key press... */
	{
		Vsync();
		draw_blank_block(base16,0,y);
		y++;				      /* move down */
		draw_block(base16,0,y);
		
		if (y == 400)
			y = 0;
	}

	Cnecin();                  /* wait for key press */

	fill_screen(base32, 0);      /* set screen to all white */

	return 0;
}
