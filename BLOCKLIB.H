/* BLOCKLIB.H
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   COMP 2659           Assignment 2
*   Winter 2020         Tyson Kendon
*
*   Purpose:    Handles all Tetronimo procedures.
*
*   Public Functions:   gen_X_block(UBYTE matrix[][4]);
*                       -   Where X = i, j, l, o, s, t, or z.
*                       -   Generates a tetronimo of the given letter.
*
*   TODO: Merge gen_x_block to a gen_block with a char argument
*/

#ifndef BLOCKLIB_H
#define BLOCKLIB_H

#include "typedef.h"

void copy_matrix(UBYTE src[][4], UBYTE dst[][4]);
void gen_i_block(UBYTE matrix[][4]);
void gen_j_block(UBYTE matrix[][4]);
void gen_l_block(UBYTE matrix[][4]);
void gen_o_block(UBYTE matrix[][4]);
void gen_s_block(UBYTE matrix[][4]);
void gen_t_block(UBYTE matrix[][4]);
void gen_z_block(UBYTE matrix[][4]);
#endif