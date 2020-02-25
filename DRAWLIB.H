#ifndef DRAWLIB_H
#define DRAWLIB_H

#include "typedef.h"

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode);
void draw_play_area(int x, int y, int width, int height);
void draw_score_box(int x, int y, int width, int height);
void draw_block(UWORD *base, int x, int y);
void draw_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height);
void disable_cursor();
void fill_screen(ULONG *base, char pattern);

#endif
