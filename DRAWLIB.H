#ifndef DRAWLIB_H
#define DRAWLIB_H

#include "typedef.h"

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode);
void draw_play_area(int x, int y, int width, int height);
void draw_score_box(int x, int y, int width, int height);
void draw_blank_block(UWORD *base, int x, int y);
void draw_block(UWORD *base, int x, int y, short mode);
void draw_matrix(int x, int y, UBYTE matrix[][4], UWORD *base);
void draw_blank_matrix(int x, int y, UBYTE matrix[][4], UWORD *base);
void draw_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height, short mode);
void disable_cursor();
void fill_screen(ULONG *base, char pattern);
void draw_game_start(UWORD *base);
#endif
