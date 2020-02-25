#include <linea.h>
#include <osbind.h>
#include <stdio.h>
#include "drawlib.h"
#include "typedef.h"


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

void draw_block(UWORD *base, int x, int y)
{
	static const UWORD block_bitmap[16] =
	{
		0x8001,
		0x4003,
		0x2007,
		0x1FFF,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x100F,
		0x1FF7,
		0x3FFB,
		0x7FFD,
		0xFFFE
	};
	draw_bitmap(base, x, y, block_bitmap, 16);	
}

void draw_bitmap(UWORD *base, int x, int y,
				  const UWORD *bitmap, unsigned int height)
{
	int i;
	int offset;
	offset = (x>>4) + (y*40);
	for (i = 0; i < height; i++)
	{
		*(base + offset + (40*i)) &= bitmap[i];
	}
}

void fill_screen(ULONG *base, char pattern)
{
	register int i = 0;
	register ULONG *loc = base;

	while (i++ < BYTES_PER_SCREEN)
		*(loc++) = pattern;
}

void disable_cursor()
{
	printf("\033f"); /* i still don't get what this does */
	fflush(stdout);
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

void draw_score_box(int x, int y, int width, int height)
{
  /* -Draw top border- */
  /* Inner Bound */
  plot_line(x, y,
	x + width, y,
	SOLID, XOR);
  /* Diagonals */
  plot_line(x - 1, y - 1,
	x - 1, y - 1,
	SOLID, XOR);
  plot_line(x + width + 1, y - 1,
	x + width + 1, y - 1,
	SOLID, XOR);
  plot_line(x - 2, y - 2,
	x - 2, y - 2,
	SOLID, XOR);
  plot_line(x + width + 2, y - 2,
	x + width + 2, y - 2,
	SOLID, XOR);
  plot_line(x - 3, y - 3,
	x -3, y - 3,
	SOLID, XOR);
  plot_line(x + width + 3, y - 3,
	x + width + 3, y - 3,
	SOLID, XOR);
  plot_line(x - 4, y - 4,
	x - 4, y - 4,
	SOLID, XOR);
  plot_line(x + width + 4, y - 4,
	x + width + 4, y - 4,
	SOLID, XOR);
  /* Outer Bound */
  plot_line(x - 5, y - 5,
	x + width + 5, y - 5,
	SOLID, XOR);

  /* -Draw left border- */
  /* Inner Bound */
  plot_line(x, y,
	x, y + height,
	SOLID, XOR);
  /* Outer Bound */
  plot_line(x - 5, y - 5,
	x - 5, y + height + 5,
	SOLID, XOR);

  /* -Draw right border- */
  /* Inner Bound */
  plot_line(x + width, y,
	x + width, y + height,
	SOLID, XOR);
  /* Fill */
  plot_line(x + width + 1, y - 1,
	x + width + 1, y + height + 1,
	SOLID, XOR);
  plot_line(x + width + 2, y - 2,
	x + width + 2, y + height + 2,
	SOLID, XOR);
  plot_line(x + width + 3, y - 3,
	x + width + 3, y + height + 3,
	SOLID, XOR);
  plot_line(x + width + 4, y - 4,
	x + width + 4, y + height + 4,
	SOLID, XOR);
  /*Outer Bound*/
  plot_line(x + width + 5, y - 5,
	x + width + 5, y + height + 5,
	SOLID, XOR);

  /* -Draw bottom border- */
  /* Inner Bound */
  plot_line(x, y + height,
	x + width, y + height,
	SOLID, XOR);
  /* Fill */
  plot_line(x - 1, y + height + 1,
	x + width + 1, y + height + 1,
	SOLID, XOR);
  plot_line(x - 2, y + height + 2,
	x + width + 2, y + height + 2,
	SOLID, XOR);
  plot_line(x - 3, y + height + 3,
	x + width + 3, y + height + 3,
	SOLID, XOR);
  plot_line(x - 4, y + height + 4,
	x + width + 4, y + height + 4,
	SOLID, XOR);
  /* OuterBound */
  plot_line(x - 5, y + height + 5,
	x + width + 5, y + height + 5,
	SOLID, XOR);
}
