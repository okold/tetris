/* MAIN.C
*
*	TETRIS for the Atari ST
*
*   Olga Koldachenko	okold525@mtroyal.ca
*	Colton Paquette		cpaqu904@mtroyal.ca
*   COMP 2659           Assignment 2
*   Winter 2020         Tyson Kendon
*/
#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include "drawlib.h"
#include "typedef.h"
#include "fontlib.h"
#include "blocklib.h"
#include "audiolib.h"
#include "input.h"

#define TILES 16
#define PLAY_AREA_ROWS 24
#define PLAY_AREA_COLS 10
#define PLAY_AREA_OFFSET_X 60
#define PLAY_AREA_OFFSET_Y 5

#define SCORE_BOX_HEIGHT 144
#define SCORE_BOX_WIDTH 96
#define SCORE_BOX_OFFSET_X 250
#define SCORE_BOX_OFFSET_Y 10

void printState(UBYTE arr[12][26]);
int collides(int x, int y, UBYTE gameState[12][26], UBYTE block[4][4]);
void vsync_wait(int x);

int main()
{
	int slow_mo = FALSE;
	int vsync_counter = 0;
	int music_counter = 0;
	int music_update = 10;
	int block_speed = 1;
	
	int x = ;
	int old_x = 0;
	int y = 0;
	int old_y = 0;
	int key;
	int i,j;

	UBYTE active_block[4][4];
	UBYTE gameState[12][26];

	UBYTE *base8 = Physbase();
	UWORD *base16 = Physbase();
	ULONG *base32 = Physbase();

	/*	Creates an initial 12 x 26 block game state matrix such that the 
		'perimeter' is set to 1, otherwise set to 0. */
	for(i = 0; i < 12; i++) {
		for(j = 0; j < 26; j++) {
			if(i == 0 || i == 11 ||
			   j == 0 || j == 25)
			{
				gameState[i][j] = 1;
			} else {
				gameState[i][j] = 0;
			}
		}
	}

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base32, -1);     /* set screen to all black */

	linea0();		   /* needs this, otherwise linea3() will crash the program */
	
	draw_game_start(base16);

	gen_z_block(active_block);

	enable_channels();
	play_music(music_counter); /* plays first note */

	while (1)    
	{	
		old_x = x;
		old_y = y;

		if(is_pressed())
		{	
			key = read_key();

			if(key == 'a')
			{
				x -= 1;
				if (collides(x, y, gameState, active_block) == 1) {
					x = old_x;
				}

			} else if(key == 'd') {

				x += 1;
				if (collides(x, y, gameState, active_block) == 1) {
					x = old_x;
				}
			} else if(key == 's') {

				y += 1;
				if (collides(x, y, gameState, active_block) == 1) {
					y = old_y;
				}
			} else if(key == 'q') {

				goto end;
			}
			  else if(key == 'e') {
				  if (slow_mo)
				  {
					  slow_mo = FALSE;
				  }
				  else
				  {
					  slow_mo = TRUE;
				  }
			  }
		}

		draw_blank_matrix(old_x * TILES,old_y * TILES,active_block,base16);
		y += block_speed;			
		draw_matrix(x * TILES,y * TILES,active_block,base16);

		Vsync(); 
		
		if (y * TILES >= 400)
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
				/*	imo this is the minimum interval for 
					the music to sound good */
				if (music_update > 5)
				{
					music_update--;
				}
			}
			play_music(music_counter);
		}

		if (slow_mo)
		{
			vsync_wait(10); /* for debug, slows the game down*/
		}
		
	}

	end:
	silence();
	fill_screen(base32, 0);      /* set screen to all white */
	printState(gameState);
	return 0;
}

/*	Prints the current active game state to console */
void printState(UBYTE arr[12][26]) 
{ 
    int i, j; 
    for (i = 0; i < 12; i++) {
      	for (j = 0; j < 26; j++) { 
        	printf("%d ", arr[i][j]);
		} 
		printf("\n");
	}
} 

/*	Checks if the new x,y positioning of the block will cause any collisions.
	returns 1 if there is a collision, 0 otherwise. */
int collides(int x, int y, UBYTE gameState[12][26], UBYTE block[4][4])
{
	int i,j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++){
			if(gameState[i + x][j + y] == 1 &&
			   block[i][j] == 1) 
			{
				return 1;
			}
		}
	}
	return 0;
}

void vsync_wait(int x)
{
	int i;

	for (i = 0; i < x; i++)
	{
		Vsync();
	}
}