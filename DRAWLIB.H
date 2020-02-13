#ifndef DRAWLIB_H
#define DRAWLIB_H

#define SOLID 0xFFFF
#define DASHED 0xCCCC
#define DASHED2 0x3333 
#define XOR   2

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode);
void draw_play_area(int x, int y, int width, int height);

#endif
