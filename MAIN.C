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
#include <osbind.h>
#include <unistd.h>
#include "drawlib.h"
#include "typedef.h"
#include "fontlib.h"
#include "blocklib.h"
#include "audiolib.h"
#include "input.h"
#include "buffer.h"

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
int clearLines(UBYTE gameState[12][25], int y, UWORD *base);
void drop(int start, int stop, UBYTE gameState[12][25]);
void draw_updated_state(UWORD* base, UBYTE gameState[12][25], UBYTE state_to_update[12][25]);
void redraw_state(UWORD* base, UBYTE gameState[12][25]);
int getMaxHeight(UBYTE gameState[12][25]);

static volatile long *vsync_counter = 0x462;

int main()
{
	long old_super, current_vsync;
	int sound_effect_length = 3;
	int sound_effect_counter = 0;
	int sound_counter = 0;
	int music_counter = 0;
	int music_update = 10;
	int gameLoop = TRUE;
	int fall_delay = 10;
	int fall_counter = 0;

	int state_updated = 0;
	int lines_cleared = 0;

	int block;
	int x = 5;
	int old_x = 1;
	int y = 0;
	int y_fine = 0;
	int old_y = 0;
	int key;
	int i,j;
	int topStateStart,topStateEnd,anchor;
	int maxHeight;

	UBYTE active_block[4][4];
	UBYTE old_aBlock[4][4];
	UBYTE gameState[12][25];
	UBYTE * topState;

	UBYTE base_state[12][25];
	UBYTE buffer_state[12][25];


	UWORD *buffer = load_buffer();
	UWORD *base = Physbase();
	UWORD *current_buffer = base;
	UBYTE *current_state = *base_state;
	UWORD *back_buffer = buffer;
	UBYTE *back_state = *buffer_state;

	/*	Creates an initial 12 x 26 block game state matrix such that the 
		'perimeter'(Excluding the "top" of the play area) is set to 1, otherwise set to 0. */
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

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base, -1);     /* set screen to all black */
	fill_screen(buffer, -1);   
	
	draw_game_start(base);
	draw_game_start(buffer);

	srand(time(0));			/* Time based RNG. */
	block = getRandom();
	nextBlock(active_block, block);

	enable_channels();
	play_music(music_counter); /* plays first note */

	/* inits vsync checker */
	old_super = Super(0);
	current_vsync = *vsync_counter;
	Super(old_super);

	while (gameLoop == TRUE)    
	{
		if(collides(x, y, gameState, active_block)) {
			silence();
			sleep(2);
			gameLoop = FALSE;
		}
		old_x = x;
		old_y = y;

		if(is_pressed())
		{	
			key = read_key();

			if(key == 'a')
			{
				x -= 1;
				if (collides(x, y, gameState, active_block) == TRUE) {
					x = old_x;
					enable_sound_effect();
					sound_effect_counter = sound_effect_length;
				} else {
					draw_blank_matrix((old_x + OFFSET) * TILES,y * TILES,active_block,base);
					draw_matrix((x + OFFSET) * TILES,y * TILES,active_block,base);
				}

			} else if(key == 'd') {

				x += 1;
				if (collides(x, y, gameState, active_block) == TRUE) {
					x = old_x;
					enable_sound_effect();
					sound_effect_counter = sound_effect_length;
				} else {
					draw_blank_matrix((old_x + OFFSET) * TILES,y * TILES,active_block,base);
					draw_matrix((x + OFFSET) * TILES,y * TILES,active_block,base);
				}
			} else if(key == 's') {

				y += 1;
				if (collides(x, y, gameState, active_block) == TRUE) {
					y = old_y;
					updateState(x, y, gameState, active_block);
					clearLines(gameState, y, base);
					maxHeight = getMaxHeight(gameState);
					block = getRandom();
					nextBlock(active_block, block);
					x = 5;
					y = 0;
					y_fine = 0;
					enable_sound_effect();
					sound_effect_counter = sound_effect_length;
					state_updated = 2;
				} else {
					draw_blank_matrix((x + OFFSET) * TILES,old_y * TILES,active_block,base);
					draw_matrix((x + OFFSET) * TILES,y * TILES,active_block,base);
				}
			} else if(key == 'w') {
				copy_matrix(active_block,old_aBlock);
				rot90CW(active_block);
				if(collides(x, y, gameState, active_block) == TRUE) {
					copy_matrix(old_aBlock,active_block);
					enable_sound_effect();
					sound_effect_counter = sound_effect_length;
				} else {
					
					draw_blank_matrix((x + OFFSET) * TILES,y * TILES,old_aBlock,base);
					draw_matrix((x + OFFSET) * TILES,y * TILES,active_block,base);
				}
				
			} else if(key == 'q') {

				goto end;
			}
		}

		fall_counter++;

		if (fall_counter % fall_delay == 0)
		{
			fall_counter = 0;

			y_fine++;
			if((y_fine % 16) == 0) {
				y += 1;	
				if (collides(x, y, gameState, active_block) == TRUE) {
					y -= 1;
					updateState(x, y, gameState, active_block);
					clearLines(gameState, y, base);
					maxHeight = getMaxHeight(gameState);
					block = getRandom();
					nextBlock(active_block, block);
					x = 5;
					y = 0;
					y_fine = 0;
					enable_sound_effect();
					sound_effect_counter = sound_effect_length;
					state_updated = 2;

				} else {		
					draw_blank_matrix((old_x + OFFSET) * TILES,old_y * TILES,active_block,base);
					draw_matrix((x + OFFSET) * TILES,y * TILES,active_block,base);
				}
			}
		}

		if (state_updated > 0)
		{
			redraw_state(back_buffer,gameState);
			state_updated--;
		}


		old_super = Super(0);
		if (*vsync_counter != current_vsync)
		{
			current_vsync = *vsync_counter;
			Super(old_super);

			/* swaps the current buffer */
			if (current_buffer == base)
			{
				current_buffer = buffer;
				back_buffer = base;
				current_state = *buffer_state;
				back_state = *base_state;
			}
			else
			{
				current_buffer = base;
				back_buffer = buffer;
				current_state = *base_state;
				back_state = *buffer_state;
			}
			Setscreen(-1,current_buffer,-1);

			/* music processing */
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

			/* sound effect processing */
			if (sound_effect_counter > 0)
			{
				sound_effect_counter--;
				if (sound_effect_counter == 0)
				{
					disable_sound_effect();
				}
			}
		}
		else
		{
			Super(old_super);
		}

		
	}

	end:
	silence();
	fill_screen(base, 0);      /* set screen to all white */
	Setscreen(-1,base,-1);
	printState(gameState);
	printf("Current height: %d\n", maxHeight);
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
* 	the play area 
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
void nextBlock(UBYTE active_block[4][4], int block)
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

/*	Rotate a block matrix 90 degress clockwise. */
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

/*	Check if a row has been completed and clears it if so.
	Returns true if 1 or more lines were cleared, false otherwise. */
int clearLines(UBYTE gameState[12][25], int y, UWORD *base)
{
	int i,j,cap,dif;
	int counter = 0;
	int lineNum = 0;
	int flag = FALSE; 

	/* Ensures no lines outside of the play area are checked */
	if(y > 20) {
		dif = y - 20;
		cap = y + 4 - dif;
	} else {
		cap = y + 4;
	}

	for(j = y; j < cap; j++) {
		for(i = 1; i < 11; i++){
			if(gameState[i][j] == 1) {
				counter++;
			}
		}

		if(counter == 10) {
			drop(j, lineNum, gameState);
			lineNum++;
			flag = TRUE;
			/* clear_line(j, base);  Visually deletes the completed line */
		}
		counter = 0;
	}
	return flag;
} 

/*	Drops each line in the above the cleared line down one in the gamestate.
	Zeroes the appro */
void drop(int start, int stop, UBYTE gameState[12][25])
{
	int i,j;
	for(j = start; j >= stop; j--) {
		for(i = 1; i < 11; i++) {
			if(j == stop) {
				gameState[i][j] = 0;
			} else {
				gameState[i][j] = gameState[i][j - 1];
			}
		}
	}
}

int getMaxHeight(UBYTE gameState[12][25])
{
	int i,j;
	for(j = 0; j < 24; j++) {
		for(i = 1; i < 11; i++) {
			if(gameState[i][j] == 1) {
				return j;
			}
		}
	}
	/* Possibly return -1 or 23 (lowest line) if no blocks exist*/
	return -1;
}

void draw_updated_state(UWORD* base, UBYTE gameState[12][25], UBYTE state_to_update[12][25])
{
	int i,j;
	for(i = 1; i < 11; i++)
	{
		for (j = 0; j < 24; j++)
		{
			if (state_to_update[i][j] != gameState[i][j])
			{
				state_to_update[i][j] = gameState[i][j];
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

void redraw_state(UWORD* base, UBYTE gameState[12][25])
{
	int i,j;
	for(i = 1; i < 11; i++)
	{
		for (j = 0; j < 24; j++)
		{
			if (gameState[i][j] == 0)
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