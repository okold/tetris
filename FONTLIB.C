/* FONTLIB.C
*
*   Colton Paquette		cpaqu904@mtroyal.ca
*   COMP 2659           Term Project
*   Winter 2020         Tyson Kendon
*/
#include <linea.h>
#include <osbind.h>
#include <stdio.h>
#include "fontlib.h"
#include "DRAWLIB.H"
#include "typedef.h"

/* Draws the bitmap of '0' at the provided x and y */
void num_0(UWORD *base, int x, int y)
{
	static const UWORD bitmap_0[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_0, 16, XOR);
}

/* Draws the bitmap of '1' at the provided x and y */
void num_1(UWORD *base, int x, int y)
{
	static const UWORD bitmap_1[16] =
	{
		0x0000,
		0x0000,
		0x03C0,
		0x03C0,
		0x0FC0,
		0x0FC0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_1, 16, XOR);
}

/* Draws the bitmap of '2' at the provided x and y */
void num_2(UWORD *base, int x, int y)
{
	static const UWORD bitmap_2[16] =
	{
		0x0000,
		0x0000,
		0x3FFC,
		0x3FFC,
		0x30FC,
		0x30FC,
		0x00FC,
		0x00FC,
		0x3FFC,
		0x3FFC,
		0x3F00,
		0x3F00,
		0x3FFC,
		0x3FFC,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_2, 16, XOR);
}

/* Draws the bitmap of '3' at the provided x and y */
void num_3(UWORD *base, int x, int y)
{
	static const UWORD bitmap_3[16] =
	{
		0x0000,
		0x0000,
		0x3FF0,
		0x3FF0,
		0x00FC,
		0x00FC,
		0x0FF0,
		0x0FF0,
		0x00FC,
		0x00FC,
		0x00FC,
		0x00FC,
		0x3FF0,
		0x3FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_3, 16, XOR);
}

/* Draws the bitmap of '4' at the provided x and y */
void num_4(UWORD *base, int x, int y)
{
	static const UWORD bitmap_4[16] =
	{
		0x0000,
		0x0000,
		0x07FC,
		0x0FF0,
		0x1CF0,
		0x38F0,
		0x30F0,
		0x30F0,
		0x30F0,
		0x30F0,
		0x3FFC,
		0x3FFC,
		0x00F0,
		0x00F0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_4, 16, XOR);
}

/* Draws the bitmap of '5' at the provided x and y */
void num_5(UWORD *base, int x, int y)
{
	static const UWORD bitmap_5[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_5, 16, XOR);
}

/* Draws the bitmap of '6' at the provided x and y */
void num_6(UWORD *base, int x, int y)
{
	static const UWORD bitmap_6[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_6, 16, XOR);
}

/* Draws the bitmap of '7' at the provided x and y */
void num_7(UWORD *base, int x, int y)
{
	static const UWORD bitmap_7[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_7, 16, XOR);
}

/* Draws the bitmap of '8' at the provided x and y */
void num_8(UWORD *base, int x, int y)
{
	static const UWORD bitmap_8[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_8, 16, XOR);
}

/* Draws the bitmap of '9' at the provided x and y */
void num_9(UWORD *base, int x, int y)
{
	static const UWORD bitmap_9[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, bitmap_9, 16, XOR);
}

/* Draws the bitmap of 'C' at the provided x and y */
void write_c(UWORD *base, int x, int y)
{
	static const UWORD c_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, c_bitmap, 16, XOR);
}

/* Draws the bitmap of 'E' at the provided x and y */
void write_e(UWORD *base, int x, int y)
{
	static const UWORD e_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3FFC,
		0x3FFC,
		0x3000,
		0x3000,
		0x3FF0,
		0x3FF0,
		0x3000,
		0x3000,
		0x3000,
		0x3000,
		0x3FFC,
		0x3FFC,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, e_bitmap, 16, XOR);
}

/* Draws the bitmap of 'I' at the provided x and y */
void write_i(UWORD *base, int x, int y)
{
	static const UWORD i_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, i_bitmap, 16, XOR);
}

/* Draws the bitmap of 'L' at the provided x and y */
void write_l(UWORD *base, int x, int y)
{
	static const UWORD l_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3C00,
		0x3FFC,
		0x3FFC,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, l_bitmap, 16, XOR);
}

/* Draws the bitmap of 'N' at the provided x and y */
void write_n(UWORD *base, int x, int y)
{
	static const UWORD n_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x303C,
		0x303C,
		0x3C3C,
		0x3C3C,
		0x3F3C,
		0x3F3C,
		0x33FC,
		0x33FC,
		0x30FC,
		0x30FC,
		0x303C,
		0x303C,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, n_bitmap, 16, XOR);
}

/* Draws the bitmap of 'O' at the provided x and y */
void write_o(UWORD *base, int x, int y)
{
	static const UWORD o_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, o_bitmap, 16, XOR);
}

/* Draws the bitmap of 'R' at the provided x and y */
void write_r(UWORD *base, int x, int y)
{
	static const UWORD r_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3FF0,
		0x3FF0,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3C3C,
		0x3FF0,
		0x3FF0,
		0x3CC0,
		0x3CC0,
		0x3C3C,
		0x3C3C,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, r_bitmap, 16, XOR);
}

/* Draws the bitmap of 'S' at the provided x and y */
void write_s(UWORD *base, int x, int y)
{
	static const UWORD s_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0FF0,
		0x0FF0,
		0x3C00,
		0x3C00,
		0x0FF0,
		0x0FF0,
		0x00FF,
		0x00FF,
		0x30FC,
		0x30FC,
		0x0FF0,
		0x0FF0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, s_bitmap, 16, XOR);
}

/* Draws the bitmap of 'T' at the provided x and y */
void write_t(UWORD *base, int x, int y)
{
	static const UWORD t_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x3FFC,
		0x3FFC,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x03C0,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, t_bitmap, 16, XOR);
}

/* Draws the bitmap of 'X' at the provided x and y */
void write_x(UWORD *base, int x, int y)
{
	static const UWORD x_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x303C,
		0x303C,
		0x0CF0,
		0x0CF0,
		0x03C0,
		0x03C0,
		0x0FC0,
		0x0FC0,
		0x3C30,
		0x3C30,
		0x300C,
		0x300C,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, x_bitmap, 16, XOR);
}

/* Draws the bitmap of ':' at the provided x and y */
void write_colon(UWORD *base, int x, int y)
{
	static const UWORD colon_bitmap[16] =
	{
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x3800,
		0x3800,
		0x3800,
		0x0000,
		0x0000,
		0x3800,
		0x3800,
		0x3800,
		0x0000,
		0x0000,
		0x0000,
		0x0000
	};

	draw_bitmap(base, x, y, colon_bitmap, 16, XOR);
}