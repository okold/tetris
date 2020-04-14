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
#include <stdlib.h>
#include <time.h>
#include <linea.h>
#include <osbind.h>
#include "drawlib.h"
#include "typedef.h"
#include "fontlib.h"
#include "blocklib.h"
#include "audiolib.h"
#include "input.h"
#include "buffer.h"

#include <unistd.h>

#define N 4
#define TILES 16
#define OFFSET 12
#define PLAY_AREA_ROWS 24
#define PLAY_AREA_COLS 10
#define PLAY_AREA_OFFSET_X 60
#define PLAY_AREA_OFFSET_Y 5

#define SCORE_BOX_HEIGHT 144
#define SCORE_BOX_WIDTH 96
#define SCORE_BOX_OFFSET_X 250
#define SCORE_BOX_OFFSET_Y 10

void rot90CW(UBYTE a[N][N]);
void nextBlock (UBYTE active_block[4][4], int block);
void printState(UBYTE arr[12][25]);
void updateState(int x, int y, UBYTE gameState[12][25], UBYTE block[4][4]);
int collides(int x, int y, UBYTE gameState[12][25], UBYTE block[4][4]);
int getRandom();
void vsync_wait(int x);
void draw_state(int x, int y, UBYTE gameState[12][25], UBYTE block[4][4], UWORD *base, int row_start, int row_end, int col_start, int col_end);

static volatile long *vsync_counter = 0x462;

int main()
{
	long old_super, current_vsync;
	int sound_counter = 0;
	int music_counter = 0;
	int music_update = 10;
	int gameLoop = TRUE;
	int state_updated, rotating = FALSE;

	int update_row_start, update_row_end;
	int update_col_start, update_col_end;

	int block;
	int x = 5;
	int old_x = 1;
	int y = 0;
	int y_fine = 0;
	int old_y = 0;
	int key;
	int i,j;

	int fall_delay = 1;
	int fall_counter = 0;

	UBYTE active_block[4][4];
	UBYTE old_aBlock[4][4];
	UBYTE gameState[12][25];

	UWORD *buffer = load_buffer();
	UWORD *base = Physbase();
	UWORD *current_buffer = base;
	UWORD *back_buffer = buffer;

	disable_cursor();          /* hide blinking text cursor */

	/*	Creates an initial 12 x 26 block game state matrix such that the 
		'perimeter' is set to 1, otherwise set to 0. */
	for(i = 0; i < 12; i++) {
		for(j = 0; j < 25; j++) {
			if(i == 0 || i == 11 || j == 24)
			{
				gameState[i][j] = 1;
			} else {
				gameState[i][j] = 0;
			}
		}
	}

	fill_screen(buffer, -1);     /* set screen to all black */
	fill_screen(base, -1);

	draw_game_start(buffer);
	draw_game_start(base);

	srand(time(0));			/* Time based RNG. */
	block = getRandom();
	nextBlock(active_block, block);

	enable_channels();
	play_music(music_counter); /* plays first note */

	old_super = Super(0);
	current_vsync = *vsync_counter;
	Super(old_super);

	while (gameLoop == TRUE)    
	{
		/* checks input */
		if(is_pressed())
		{	
			key = read_key();
			if(key == 'a')
			{
				x -= 1;
				if (collides(x, y, gameState, active_block) == TRUE) {
					x = old_x;
				} else {
					update_row_start = y;
					update_row_end = y + 4;
					update_col_start = x;
					update_col_end = old_x + 4;
					state_updated = TRUE;
				}

			} else if(key == 'd') {

				x += 1;
				if (collides(x, y, gameState, active_block) == TRUE) {
					x = old_x;
				} else {
					update_row_start = y;
					update_row_end = y + 4;
					update_col_start = old_x;
					update_col_end = x + 4;
					state_updated = TRUE;
				}
			} else if(key == 's') {

				y += 1;
				if (collides(x, y, gameState, active_block) == TRUE) {
					y = old_y;
					updateState(x, y, gameState, active_block);
					block = getRandom();
					nextBlock(active_block, block);
					x = 5;
					y = 0;
					y_fine = 0; 
				} else {
					update_row_start = old_y;
					update_row_end = y + 4;
					update_col_start = x;
					update_col_end = x + 4;
					state_updated = TRUE;
				}
			} else if(key == 'w') {
				old_aBlock[4][4] = active_block[4][4];
				rot90CW(active_block);
				if(collides(x, y, gameState, active_block) == TRUE) {
					active_block[4][4] = old_aBlock[4][4];
				} else {
					state_updated = TRUE;
					rotating = TRUE;
					update_row_start = y;
					update_row_end = y + 4;
					update_col_start = x;
					update_col_end = x + 4;
				}
				
			} else if(key == 'q') {

				goto end;
			}
		}

		/* drops the active block */
		if (fall_counter % fall_delay == 0)
		{
			/* hit the top of the play area, end game (?) */
			if(collides(x, y, gameState, active_block)) {
				sleep(2);
				silence();
				gameLoop = FALSE;
			}
			old_x = x;
			old_y = y;

			y_fine++;
			if((y_fine % 16) == 0) 
			{
				state_updated = TRUE;
				y_fine = 0;
				y++;
				/* puts static block in play area and updates state */
				if (collides(x, y, gameState, active_block) == TRUE) 
				{
					y--;
					updateState(x, y, gameState, active_block);
					block = getRandom();
					nextBlock(active_block, block);
					x = 5;
					y = 0;
					y_fine = 0;
				}
			}
			update_row_start = old_y;
			update_row_end = y + 4;
			update_col_start = x;
			update_col_end = x + 4;
		}

		if (state_updated)
		{
			draw_state(x, y, gameState, active_block, back_buffer, update_row_start, update_row_end, update_col_start, update_col_end);
		}
		
		draw_blank_matrix((old_x + OFFSET) * TILES, old_y * TILES, block, back_buffer);
		draw_matrix((x + OFFSET) * TILES,y * TILES,block,back_buffer);

		/* checks for the next frame */
		old_super = Super(0);
		if (*vsync_counter != current_vsync)
		{
			current_vsync = *vsync_counter;
			Super(old_super);

			/* drop speed. the smaller the delay, the faster the fall */
			fall_counter++;
			if (fall_counter >= 500)
			{
				if (fall_delay >= 5)
				{
					fall_delay--;
				}
				fall_counter = 0;
			}

			/* swaps the current buffer */
			if (current_buffer == base)
			{
				current_buffer = buffer;
				back_buffer = base;
			}
			else
			{
				current_buffer = base;
				back_buffer = buffer;
			}
			Setscreen(-1,current_buffer,-1);

			/* updates sound */
			sound_counter++;
			if (sound_counter % music_update == 0)
			{
				music_counter++;
				if (music_counter == NUM_CHORDS)
				{
					sound_counter = 0;
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
		}
		else
		{
			Super(old_super);
		}
	}

	end:
	silence();
	Setscreen(-1,base,-1);
	fill_screen(base, 0);      /* set screen to all white */
		printf("%p\n",base);
    printf("%p\n",buffer);
	printState(gameState);
	return 0;
}

/*	Prints the current active game state to console */
void printState(UBYTE arr[12][25]) 
{ 
    int i, j; 
    for (i = 0; i < 12; i++) {
      	for (j = 0; j < 25; j++) { 
        	printf("%d ", arr[i][j]);
		} 
		printf("\n");
	}
} 

/*	Checks if the new x,y positioning of the block will cause any collisions.
	returns 1 if there is a collision, 0 otherwise. */
int collides(int x, int y, UBYTE gameState[12][25], UBYTE block[4][4])
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

/*	Updates the gameState matrix to reflect the permanent blocks in
 *	the play area 
*/
void updateState(int x, int y, UBYTE gameState[12][25], UBYTE block[4][4])
{
	int i,j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++){
			if(block[i][j] == 1) {
				gameState[i + x][j + y] = 1;
			}
		}
	}
} 

/*	Generates a random number from 1 to 7 inclusive.
*	Each number represents one of the seven block shapes. 
* 	Note: Uses time as seed for random renerator.
*/
int getRandom() {
	int num = (rand() % 7) + 1;
	return num;
}

/*	'Redraws' the active block matrix to the provided block number. */
void nextBlock (UBYTE active_block[4][4], int block)
{
	switch(block)
	{
		case 1:
			gen_i_block(active_block);
			break;
		case 2:
			gen_j_block(active_block);
			break;
		case 3:
			gen_l_block(active_block);
			break;
		case 4:
			gen_o_block(active_block);
			break;
		case 5:
			gen_s_block(active_block);
			break;
		case 6:
			gen_t_block(active_block);
			break;
		case 7:
			gen_z_block(active_block);
			break;
	}
}

/*	Rotate a block matrix 90 degress clockwise. 
	Works for any N x N matrix, however this one is
	always 4 x 4 and we can optimize it.
	currently buggy - I think its just Steem sucking */
void rot90CW(UBYTE a[N][N])
{
	
	int i,j,temp;
	for(i = 0; i < N / 2; i++) {
		for(j = i; j < N - i - 1; j++) {
			
			temp = a[i][j];
			a[i][j] = a[N - 1 - j][i];
			a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
			a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
			a[j][N - 1 - i] = temp;
		}
	}
}

/*	Updates the gameState matrix to reflect the permanent blocks in
 *	the play area 
*/
void draw_state(int x, int y, UBYTE gameState[12][25], UBYTE block[4][4], UWORD *base, int row_start, int row_end, int col_start, int col_end)
{
	int i,j;
	for (i = col_start; i > 1 && i < col_end && i < 12; i++)
	{
		for (j = row_start; j > 0 && j <= row_end && j < 25; j++)
		{
			if (gameState[i][j] == 0)
			{
				draw_blank_block(base, (i * 16) + 200,j * 16);
			}
			else
			{
				draw_block(base, (i * 16) + 200, j * 16,AND);
			}
		}
	}
} 

/*	Check if a row has been completed. 
int rowComplete()
{
	return 0;
} */