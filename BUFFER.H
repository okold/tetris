/* BUFFER.H
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   COMP 2659           Term Project
*   Winter 2020         Tyson Kendon
*
*   Purpose:    Handles memory allocation of the secondary buffer
*
*   Public Functions:   UWORD* load_buffer();
*                       -   Returns a 256-byte aligned buffer of
*                           32000 bytes, for double buffering.
*/
#ifndef BUFFER_H
#define BUFFER_H

#include "typedef.h"

UWORD* load_buffer();
#endif