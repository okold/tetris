#include <linea.h>
#include <osbind.h>

#define SOLID  0xFFFF
#define DASHED 0xF0F0

#define XOR 2

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode);

int main()
{
	linea0();
	plot_line(0, 399, 649, 0, DASHED, XOR);
	Cnecin();
	return 0;
}

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode)
{
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = style;
	WMODE = mode;
	LSTLIN = 0;         /* always draw last pixel of line */
	linea3();
}
