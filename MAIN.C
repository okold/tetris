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
