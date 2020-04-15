/* DRAWLIB.H
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   Colton Paquette		cpaqu904@mtroyal.ca
*   COMP 2659           Term Project
*   Winter 2020         Tyson Kendon
*
*   Purpose:    Handles graphics.
*
*   Public Functions:   void draw_updated_state(UWORD* base, UBYTE game_state[12][25],
*									UBYTE state_to_update[12][25]);
*                       -   Compares the given state to the actual game state,
*							updating it to match it, and drawing the differing block
*							to the given base.
*
*                       void redraw_state(UWORD* base, UBYTE game_state[12][25],
*									int max_height);
*                       -   Redraws the entire game state on the given base,
*							starting at the x position of max_height.
*
*                       void disable_cursor();
*                       -   Disables the blinking text cursor.
*
*                       void fill_screen(ULONG *base, char pattern);
*                       -   Fills the screen with a given pattern.
*                       -   -1 is black and 0 is white.
*
*                       void draw_game_start(UWORD *base);
*                       -   Draws the gameplay area border.
*						
*						void draw_bitmap(UWORD *base, int x, int y,
*				  			const UWORD *bitmap, unsigned int height, short mode);
*						-	Draws a bitmap at the given base.
*/

#ifndef DRAWLIB_H
#define DRAWLIB_H

#include "typedef.h"

void draw_updated_state(UWORD* base, UBYTE game_state[12][25],
			UBYTE state_to_update[12][25]);
void redraw_state(UWORD* base, UBYTE game_state[12][25],
			int max_height);
void disable_cursor();
void fill_screen(UWORD *base, char pattern);
void draw_game_start(UWORD *base);
void draw_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height, short mode);
#endif
