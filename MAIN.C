/* MAIN.C
*
*	TETRIS for the Atari ST
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   Colton Paquette		cpaqu904@mtroyal.ca
*   COMP 2659           Term Project
*   Winter 2020         Tyson Kendon
*
*	Controls:	W: 		Rotate block
*				A/D: 	Move block left/right
*				S:		Drop block
*				Q:		Quit
*
*  	Functions:   		void rot90CW(UBYTE a[MATRIX_WIDTH][MATRIX_WIDTH]);
*							-
*
*						void nextBlock (UBYTE active_block[4][4], int block);
*							-
*
*						void updateState(int x, int y, UBYTE game_state[12][25], 
*								UBYTE block[4][4]);
*							-
*
*						int collides(int x, int y, UBYTE game_state[12][25],
*								UBYTE block[4][4]);
*							-
*
*						int getRandom();
*							-
*
*						int clear_lines(UBYTE game_state[12][25], int y, UWORD *base);
*							-
*
*						void drop(int start, int stop, UBYTE game_state[12][25]);
*							-
*
*						int get_max_height(UBYTE game_state[12][25]);
*							- Returns the y position of the highest block in the
*							  given game state.
*
*						void remove_block_from_state(UBYTE game_state[12][25], 
*								UBYTE block[4][4], int x, int y);
*							- Removes the given block from the given from the given
*							  game state at the given position.
*
*						void add_block_to_state(UBYTE game_state[12][25], 
*								UBYTE block[4][4], int x, int y);
*							- Adds the given block to the given game state at the
*							  given position.
*
*	TODO:	- Show controls
*			- Keyboard interrupts
*			- Score / display score
*			- Display next block
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

#define MATRIX_WIDTH 4
#define ACCEL_RATE 750		/* speeds up fall speed every # of ticks */
#define SOUND_EFF_LENGTH 3

void rot90CW(UBYTE a[MATRIX_WIDTH][MATRIX_WIDTH]);
void nextBlock (UBYTE active_block[4][4], int block);
void updateState(int x, int y, UBYTE game_state[12][25], UBYTE block[4][4]);
int collides(int x, int y, UBYTE game_state[12][25], UBYTE block[4][4]);
int getRandom();
int clear_lines(UBYTE game_state[12][25], int y, UWORD *base);
void drop(int start, int stop, UBYTE game_state[12][25]);
int get_max_height(UBYTE game_state[12][25]);
void remove_block_from_state(UBYTE game_state[12][25], UBYTE block[4][4], int x, int y);
void add_block_to_state(UBYTE game_state[12][25], UBYTE bloc

/* Built-in vertical blank counter in the Atari ST */
static volatile long *vsync_counter = 0x462;

int main()
{
	/* SYSTEM VARIABLES */
	long old_super;					/* for Super() call */
	long current_vsync;				/* to compare to vsync_counter */
	int game_loop = TRUE;
	int key;						/* Key press */
	int i,j;

	/* SOUND VARIABLES */
	int sound_effect_counter = 0;
	int sound_counter = 0;
	int music_counter = 0;
	int music_update = 6;

	/* ACTIVE BLOCK */
	UBYTE active_block[4][4];
	UBYTE old_a_block[4][4]; 	/* For rotation */
	int block;		/* Integer representation of the block type */		
	int x = 5;
	int old_x = 1;
	int y = 0;
	int y_fine = 0;
	int old_y = 0;
	int fall_speed = 1;
	int acceleration_counter = 0;

	/* GAME STATE */
	UBYTE game_state[12][25];	/* Actual state */
	UBYTE base_state[12][25];	/* State within graphics 1 */
	UBYTE buffer_state[12][25]; /* State within graphics 2 */
	UBYTE *current_state = *base_state;
	UBYTE *back_state = *buffer_state;
	int state_update_counter = 0;
	int clear_line_counter = 0;
	int max_height;

	/* GRAPHICS BUFFERS */
	UWORD *buffer = load_buffer();
	UWORD *base = Physbase();
	UWORD *current_buffer = base;
	UWORD *back_buffer = buffer;

	/*	Creates an initial 12 x 26 block game state matrix such that the 
		'perimeter'(Excluding the "top" of the play area) is set to 1, otherwise set to 0. */
	for(i = 0; i < 12; i++) {
		for(j = 0; j < 25; j++) {
			if(i == 0 || i == 11 || j == 24)
			{
				game_state[i][j] = 1;
			} else {
				game_state[i][j] = 0;
			}
		}
	}

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base, -1);     /* set screen to all black */
	fill_screen(buffer, -1);   
	
	draw_game_start(base);
	draw_game_start(buffer);

	srand(time(0));			/* generates blocks with time based RNG. */
	block = getRandom();
	nextBlock(active_block, block);

	enable_channels();
	play_music(music_counter); /* plays first note */

	old_super = Super(0);		/* inits vsync checker */
	current_vsync = *vsync_counter;
	Super(old_super);

	while (game_loop == TRUE)    
	{
		remove_block_from_state(game_state,active_block,x,y);

		old_x = x;
		old_y = y;

		/* check for top of play area collision */
		if(y == 0 && collides(x, y + 1, game_state, active_block)) 
		{
			silence();
			sleep(1);
			game_loop = FALSE;
		}

		if(is_pressed())
		{	
			key = read_key();

			if(key == 'a') /* Move left */
			{
				x -= 1;
				if (collides(x, y, game_state, active_block) == TRUE) {
					x = old_x;
					enable_sound_effect();
					sound_effect_counter = SOUND_EFF_LENGTH;
				}

			} else if(key == 'd') /* Move right */
			{

				x += 1;
				if (collides(x, y, game_state, active_block) == TRUE) {
					x = old_x;
					enable_sound_effect();
					sound_effect_counter = SOUND_EFF_LENGTH;
				}
			} else if(key == 's') /* Drop block */
			{
				y += 1;
				if (collides(x, y, game_state, active_block) == TRUE) {
					y = old_y;
					updateState(x, y, game_state, active_block);
					max_height = get_max_height(game_state);
					if (clear_lines(game_state, y, base))
					{
						clear_line_counter = 2;
					}
					block = getRandom();
					nextBlock(active_block, block);
					x = 5;
					y = 0;
					y_fine = 0;
					enable_sound_effect();
					sound_effect_counter = SOUND_EFF_LENGTH;
					if (clear_line_counter < 2)
					{
						if (state_update_counter == 0)
						{
							state_update_counter = 2;
						}
					}
				}
			} else if(key == 'w') /* Rotate block */
			{
				copy_matrix(active_block,old_a_block);
				rot90CW(active_block);
				if(collides(x, y, game_state, active_block) == TRUE) {
					copy_matrix(old_a_block,active_block);
					enable_sound_effect();
					sound_effect_counter = SOUND_EFF_LENGTH;
				}
			} else if(key == 'q') /* Quit */
			{

				goto end;
			}
		}
		
		/* Accelerates fall speed */
		acceleration_counter++;
		if (acceleration_counter % ACCEL_RATE == 0)
		{
			fall_speed++;
			acceleration_counter = 0;
		}

		/* Drops the block */
		y_fine+= fall_speed;
		if(y_fine >= 16)
		{
			y += 1;
			y_fine = 0;

			/* Collision handling */
			if (collides(x, y, game_state, active_block) == TRUE) 
			{
				y -= 1;
				updateState(x, y, game_state, active_block);

				max_height = get_max_height(game_state);
				if (clear_lines(game_state, y, base))
				{
					clear_line_counter = 2;
				}

				block = getRandom();
				nextBlock(active_block, block);
				x = 5;
				y = 0;
				
				enable_sound_effect();
				sound_effect_counter = SOUND_EFF_LENGTH;
				if (clear_line_counter < 2)
				{
					if (state_update_counter == 0)
					{
						state_update_counter = 2;
					}
				}

			}
		}

		/* Movement logic complete, places the block back in the game */
		add_block_to_state(game_state,active_block,x,y);

		/* Redraws everything if a line has been cleared, otherwise
		*  redraws only the portion that has changed */
		if (clear_line_counter > 0)
		{
			redraw_state(back_buffer,game_state,max_height);
			clear_line_counter--;
		}
		else
		{
			draw_updated_state(back_buffer, game_state, back_state);
		}

		/* Updates things based on the framerate*/
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
					if (music_update > 2)
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
	printf("GAME OVER\nThanks for playing!\n");
	return 0;
}

/*	Checks if the new x,y positioning of the block will cause any collisions.
	returns 1 if there is a collision, 0 otherwise. */
int collides(int x, int y, UBYTE game_state[12][25], UBYTE block[4][4])
{
	int i,j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++){
			if(game_state[i + x][j + y] == 1 &&
			   block[i][j] == 1) 
			{
				return 1;
			}
		}
	}
	return 0;
}

/*	Updates the game_state matrix to reflect the permanent blocks in
* 	the play area 
*/
void updateState(int x, int y, UBYTE game_state[12][25], UBYTE block[4][4])
{
	int i,j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++){
			if(block[i][j] == 1) {
				game_state[i + x][j + y] = 1;
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
void rot90CW(UBYTE a[MATRIX_WIDTH][MATRIX_WIDTH])
{
	int i,j,temp;
	for(i = 0; i < MATRIX_WIDTH / 2; i++) {
		for(j = i; j < MATRIX_WIDTH - i - 1; j++) {
			
			temp = a[i][j];
			a[i][j] = a[MATRIX_WIDTH - 1 - j][i];
			a[MATRIX_WIDTH - 1 - j][i] = a[MATRIX_WIDTH - 1 - i][MATRIX_WIDTH - 1 - j];
			a[MATRIX_WIDTH - 1 - i][MATRIX_WIDTH - 1 - j] = a[j][MATRIX_WIDTH - 1 - i];
			a[j][MATRIX_WIDTH - 1 - i] = temp;
		}
	}
}

/*	Check if a row has been completed and clears it if so.
	Returns true if 1 or more lines were cleared, false otherwise. */
int clear_lines(UBYTE game_state[12][25], int y, UWORD *base)
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
			if(game_state[i][j] == 1) {
				counter++;
			}
		}

		if(counter == 10) {
			drop(j, lineNum, game_state);
			lineNum++;
			flag = TRUE;
			/* clear_line(j, base);  Visually deletes the completed line */
		}
		counter = 0;
	}
	return flag;
} 

/*	Drops each line in the above the cleared line down one in the game_state.
	Zeroes the appro */
void drop(int start, int stop, UBYTE game_state[12][25])
{
	int i,j;
	for(j = start; j >= stop; j--) {
		for(i = 1; i < 11; i++) {
			if(j == stop) {
				game_state[i][j] = 0;
			} else {
				game_state[i][j] = game_state[i][j - 1];
			}
		}
	}
}

int get_max_height(UBYTE game_state[12][25])
{
	int i,j;
	for(j = 0; j < 24; j++) {
		for(i = 1; i < 11; i++) {
			if(game_state[i][j] == 1) {
				return j;
			}
		}
	}
	/* Possibly return -1 or 23 (lowest line) if no blocks exist*/
	return -1;
}

/* Removes the given block from the state at the given coordinates */
void remove_block_from_state(UBYTE game_state[12][25], 
	UBYTE block[4][4], int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[i][j] == 1)
			{
				game_state[i + x][j + y] = 0;
			}
		}
	}
}

/* Adds the given block to the state at the given coordinates */
void add_block_to_state(UBYTE game_state[12][25], 
	UBYTE block[4][4], int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[i][j] == 1)
			{
				game_state[i + x][j + y] = 1;
			}
		}
	}
}
