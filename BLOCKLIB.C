/* BLOCKLIB.C
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   COMP 2659           Assignment 2
*   Winter 2020         Tyson Kendon
*
*	Private Functions:	void copy_matrix(UBYTE src[][4], UBYTE dst[][4]);
*              			-   Copies the source matrix into the destination.
*/
#include "blocklib.h"

void copy_matrix(UBYTE src[][4], UBYTE dst[][4]);

/*  Block Matrices
*   Note:   the array is in the format [x][y], but the way the arrays are
*           declared statically, they're transposed visually in the code.
*/
static UBYTE i_block[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

static UBYTE j_block[4][4] = {
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0}};

static UBYTE l_block[4][4] = {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}};

static UBYTE o_block[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}};

static UBYTE s_block[4][4] = {
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}};

static UBYTE t_block[4][4] = {
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0}};

static UBYTE z_block[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0}};

void gen_i_block(UBYTE matrix[][4])
{
    copy_matrix(i_block,matrix);
}

void gen_j_block(UBYTE matrix[][4])
{
    copy_matrix(j_block,matrix);
}

void gen_l_block(UBYTE matrix[][4])
{
    copy_matrix(l_block,matrix);
}

void gen_o_block(UBYTE matrix[][4])
{
    copy_matrix(o_block,matrix);
}

void gen_s_block(UBYTE matrix[][4])
{
    copy_matrix(s_block,matrix);
}

void gen_t_block(UBYTE matrix[][4])
{
    copy_matrix(t_block,matrix);
}

void gen_z_block(UBYTE matrix[][4])
{
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