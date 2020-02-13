#include <linea.h>
#include "drawlib.h"

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

/* there might be a prettier way to do this idk */
void draw_play_area(int x, int y, int width, int height)
{
	/* left border */
	plot_line(x - 8, y,
	x - 8, y + height + 1,
	DASHED, XOR);
	
        plot_line(x - 6, y,
	x - 6, y + height + 1,
	DASHED2, XOR);
	
	plot_line(x - 5, y,
	x - 5, y + height + 1,
	DASHED, XOR);

	plot_line(x - 4, y,
	x - 4, y + height + 1,
	DASHED2, XOR);
	
	plot_line(x - 3, y,
	x - 3, y + height + 1,
	DASHED, XOR);

	plot_line(x - 2, y,
	x - 2, y + height + 1,
	SOLID, XOR);
	
	plot_line(x - 1, y,
	x - 1, y + height + 1,
	SOLID, XOR);
	
	/* right border */
	plot_line(x + width + 1, y,
	x + width + 1, y + height + 1,
	SOLID, XOR);
	
	plot_line(x + width + 2, y,
	x + width + 2, y + height + 1,
	SOLID, XOR);
	
	plot_line(x + width + 3, y,
	x + width + 3, y + height + 1,
	DASHED, XOR);
	
	plot_line(x + width + 4, y,
	x + width + 4, y + height + 1,
	DASHED2, XOR);

	plot_line(x + width + 5, y,
	x + width + 5, y + height + 1,
	DASHED, XOR);
	
	plot_line(x + width + 6, y,
	x + width + 6, y + height + 1,
	DASHED2, XOR);
	
	plot_line(x + width + 8, y,
	x + width + 8, y + height + 1,
	DASHED, XOR);

	/* bottom border */
	plot_line(x - 8, y + height + 1,
	x + width + 9, y + height + 1,
	SOLID, XOR);
	
	plot_line(x - 8, y + height + 2,
	x + width + 9, y + height + 2,
	SOLID, XOR);
	
	plot_line(x - 8, y + height + 3,
	x + width + 9, y + height + 3,
	DASHED, XOR);
	
	plot_line(x - 8, y + height + 4,
	x + width + 9, y + height + 4,
	DASHED2, XOR);
}
