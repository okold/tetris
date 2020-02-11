#ifndef DRAWLIB_H
#define DRAWLIB_H

#define PLAY_AREA_HEIGHT_PIXELS 384
#define PLAY_AREA_WIDTH_PIXELS 160
#define PLAY_AREA_HEIGHT 24
#define PLAY_AREA_WIDTH 10
#define PLAY_AREA_OFFSET_X 60
#define PLAY_AREA_OFFSET_Y 5

#define SOLID 0xFFFF
#define DASHED 0xCCCC
#define DASHED2 0x3333 
#define XOR   2

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode);
void draw_play_area();

#endif
