#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include "drawlib.h"
#include "typedef.h"
#include "blocklib.h"

#define PLAY_AREA_ROWS 24
#define PLAY_AREA_COLS 10
#define PLAY_AREA_OFFSET_X 60
#define PLAY_AREA_OFFSET_Y 5

#define SCORE_BOX_HEIGHT 144
#define SCORE_BOX_WIDTH 96
#define SCORE_BOX_OFFSET_X 250
#define SCORE_BOX_OFFSET_Y 10

int main()
{
	UBYTE active_block[4][4];

	int y = 0;

	UBYTE *base8 = Physbase();
	UWORD *base16 = Physbase();
	ULONG *base32 = Physbase();

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base32, -1);     /* set screen to all black */

	linea0();		   /* needs this, otherwise linea3() will crash the program */
	
	draw_game_start(base16);

	gen_z_block(active_block);

	while (!Cconis())    
	{
		Vsync();
		y++;				     
		draw_matrix(0,y,active_block,base16);
		
		if (y == 400)
			y = 0;
	}

	Cnecin();                  /* wait for key press */

	fill_screen(base32, 0);      /* set screen to all white */

	return 0;
}
