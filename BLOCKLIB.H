#ifndef BLOCKLIB_H
#define BLOCKLIB_H

#include "typedef.h"

void draw_matrix(int x, int y, UBYTE matrix[][4], UWORD *base);
void gen_i_block(UBYTE matrix[][4]);
void gen_j_block(UBYTE matrix[][4]);
void gen_l_block(UBYTE matrix[][4]);
void gen_o_block(UBYTE matrix[][4]);
void gen_s_block(UBYTE matrix[][4]);
void gen_t_block(UBYTE matrix[][4]);
void gen_z_block(UBYTE matrix[][4]);
#endif