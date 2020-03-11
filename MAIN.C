#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include "drawlib.h"
#include "typedef.h"
#include "fontlib.h"
#include "blocklib.h"
#include "audiolib.h"

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
	int vsync_counter = 0;
	int music_counter = 0;
	int music_update = 10;
	int block_speed = 1;

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

	enable_channels();
	play_music(music_counter); /* plays first note */

	while (!Cconis())    
	{
		draw_blank_matrix(0,y,active_block,base16);
		y += block_speed;			
		draw_matrix(0,y,active_block,base16);

		Vsync(); 
		
		if (y >= 400)
		{
			y = 0;
		}
		
		vsync_counter++;
		if (vsync_counter % music_update == 0)
		{
			music_counter++;
			if (music_counter == NUM_CHORDS)
			{
				vsync_counter = 0;
				music_counter = 0;
				if (music_update > 5) /* imo this is the minimum interval for the music to sound good */
				{
					music_update--;
					block_speed++;
				}
			}
			play_music(music_counter);
		}
	}

	silence();

	Cnecin();                  /* wait for key press */

	fill_screen(base32, 0);      /* set screen to all white */

	return 0;
}
