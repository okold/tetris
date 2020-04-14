/* DRAWLIB.H
*
*   Olga Koldachenko	okold525@mtroyal.ca
*	Colton Paquette		cpaqu904@mtroyal.ca
*   COMP 2659           Assignment 2
*   Winter 2020         Tyson Kendon
*
*   Purpose:    Handles graphics.
*
*   Public Functions:   void draw_matrix(int x, int y, 
*                                           UBYTE matrix[][4], UWORD *base);
*                       -   Draws a tetronimo with visible blocks.
*
*                       void draw_blank_matrix(int x, int y,
*                                       UBYTE matrix[][4], UWORD *base);
*                       -   Draws an all-black tetronimo.
*
*                       void draw_bitmap(UWORD *base, int x, int y,
*				                        const UWORD *bitmap,
*                                       unsigned int height, short mode);
*                       -   Draws a bitmap at the given location;
*                           Note that the x value will move to the closest
*                           multiple of the size of the base.
*
*                       void disable_cursor();
*                       -   Disables the blinking text cursor.
*
*                       void fill_screen(ULONG *base, char pattern);
*                       -   Fills the screen with a given pattern.
*                       -   -1 is black and 0 is white.
*
*                       void draw_game_start(UWORD *base);
*                       -   Draws the gameplay area.
*/

#ifndef DRAWLIB_H
#define DRAWLIB_H

#include "typedef.h"

void draw_blank_block(UWORD *base, int x, int y);
void draw_block(UWORD *base, int x, int y, short mode);
void draw_matrix(int x, int y, UBYTE matrix[][4], UWORD *base);
void draw_blank_matrix(int x, int y, UBYTE matrix[][4], UWORD *base);
void draw_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height, short mode);
void disable_cursor();
void fill_screen(UWORD *base, char pattern);
void draw_game_start(UWORD *base);

#endif
