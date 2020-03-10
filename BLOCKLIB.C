#include "blocklib.h"
#include "drawlib.h"

void copy_matrix(UBYTE src[][4], UBYTE dst[][4]);

void draw_matrix(int x, int y, UBYTE matrix[][4], UWORD *base)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (matrix[i][j] == 0)
            {
                draw_blank_block(base, x + (i*16), y + (j*16));
            }
            else
            {
                draw_blank_block(base, x + (i*16), y + (j*16));
                draw_block(base, x + (i*16), y + (j*16), AND);
            }
        }
    } 
}

void gen_i_block(UBYTE matrix[][4])
{
    static UBYTE i_block[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    copy_matrix(i_block,matrix);
}

void gen_j_block(UBYTE matrix[][4])
{
    static UBYTE j_block[4][4] = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    copy_matrix(j_block,matrix);
}

void gen_l_block(UBYTE matrix[][4])
{
    static UBYTE l_block[4][4] = {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    copy_matrix(l_block,matrix);
}

void gen_o_block(UBYTE matrix[][4])
{
    static UBYTE o_block[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    copy_matrix(o_block,matrix);
}

void gen_s_block(UBYTE matrix[][4])
{
    static UBYTE s_block[4][4] = {
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };

    copy_matrix(s_block,matrix);
}

void gen_t_block(UBYTE matrix[][4])
{
    static UBYTE t_block[4][4] = {
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    copy_matrix(t_block,matrix);
}

void gen_z_block(UBYTE matrix[][4])
{
    static UBYTE z_block[4][4] = {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    copy_matrix(z_block,matrix);
}

void copy_matrix(UBYTE src[][4], UBYTE dst[][4])
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (i == 1)
            {
                dst[i][j] = src[i][j];
            }
            else
            {
                dst[i][j] = src[i][j];
            }
        }
    }
}