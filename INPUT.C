/* INPUT.C
*
*   Colton Paquette		cpaqu904@mtroyal.ca
*   COMP 2659           Term Project
*   Winter 2020         Tyson Kendon
*/
#include "input.h"
#include <osbind.h>

int is_pressed()
{
    return Cconis();
}

int read_key()
{
    return Cnecin();
}

