#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#define BYTES_PER_SCREEN 32000

#define PLAY_AREA_HEIGHT_PIXELS 320
#define PLAY_AREA_WIDTH_PIXELS 80
#define PLAY_AREA_HEIGHT 40
#define PLAY_AREA_WIDTH 10
#define PLAY_AREA_OFFSET_X 100
#define PLAY_AREA_OFFSET_Y 40

#define SOLID 0xFFFF
#define DASHED 0xCCCC
#define DASHED2 0x3333 
#define XOR   2

void draw_play_area();
void disable_cursor();
void fill_screen(char *base, char pattern);
void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode);

int main()
{
	char *base = Physbase();

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base, -1);     /* set screen to all black */
	
	linea0();		   /* needs this, otherwise linea3() will crash the program */
	
	draw_play_area();
	
	Cnecin();                  /* wait for key press */

	fill_screen(base, 0);      /* set screen to all white */

	return 0;
}


/* there might be a prettier way to do this idk */
void draw_play_area()
{
	/* left border */
	plot_line(PLAY_AREA_OFFSET_X - 8, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X - 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED, XOR);
	
        plot_line(PLAY_AREA_OFFSET_X - 6, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X - 6, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED2, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X - 5, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X - 5, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED, XOR);

	plot_line(PLAY_AREA_OFFSET_X - 4, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X - 4, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED2, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X - 3, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X - 3, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED, XOR);

	plot_line(PLAY_AREA_OFFSET_X - 2, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X - 2, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	SOLID, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X - 1, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X - 1, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	SOLID, XOR);
	
	/* right border */
	plot_line(PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 1, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 1, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	SOLID, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 2, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 2, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	SOLID, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 3, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 3, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 4, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 4, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED2, XOR);

	plot_line(PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 5, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 5, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 6, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 6, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED2, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 8, PLAY_AREA_OFFSET_Y,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	DASHED, XOR);

	/* bottom border */
	plot_line(PLAY_AREA_OFFSET_X - 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 1,
	SOLID, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X - 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 2,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 2,
	SOLID, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X - 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 3,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 3,
	DASHED, XOR);
	
	plot_line(PLAY_AREA_OFFSET_X - 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 4,
	PLAY_AREA_OFFSET_X + PLAY_AREA_WIDTH_PIXELS + 8, PLAY_AREA_OFFSET_Y + PLAY_AREA_HEIGHT_PIXELS + 4,
	DASHED2, XOR);
}

void disable_cursor()
{
	printf("\033f"); /* i still don't get what this does */
	fflush(stdout);
}

void fill_screen(char *base, char pattern)
{
	register int i = 0;
	register char *loc = base;

	while (i++ < BYTES_PER_SCREEN)
		*(loc++) = pattern;
}

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode)
{
	/* do line-a call to plot a line */

	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = style;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}