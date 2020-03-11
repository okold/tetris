/* AUDIOLIB.C
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   COMP 2659           Assignment 2
*   Winter 2020         Tyson Kendon
*
*	Private Functions:	void set_rough(int note)
*              			-   Sets the rough octave value of the given note.
*							Should only ever be called within play_music.
*
*	TODO:	Sound effects on Channel C.
*/
#include <osbind.h>
#include <unistd.h>
#include "audiolib.h"

#define CH_A_VOL 10
#define CH_B_VOL 6

/* Notes */
#define E5 0x0AA
#define D5 0x0BE
#define C5 0x0D6
#define E4 0x153
#define B4 0x0E2
#define A4 0x0FE
#define A4F 0x10D
#define E3 0x2A7
#define A3 0x1FC
#define A3F 0x21B

/* Chords
*	Holds two notes and their volumes.
*/
typedef struct {
	int note_a;
	int note_b;
	char note_a_vol;
	char note_b_vol;
} Chord;

static Chord E5_E3 = {E5,E3,CH_A_VOL,CH_B_VOL};
static Chord E5_A3 = {E5,A3,CH_A_VOL,CH_B_VOL};
static Chord E5_A3F = {E5,A3F,CH_A_VOL,CH_B_VOL};
static Chord E5_E4 = {E5,E4,CH_A_VOL,CH_B_VOL};
static Chord B4_E3 = {B4,E3,CH_A_VOL,CH_B_VOL};
static Chord B4_E4 = {B4,E4,CH_A_VOL,CH_B_VOL};
static Chord B4_A3F = {B4,A3F,CH_A_VOL,CH_B_VOL};
static Chord C5_E3 = {C5,E3,CH_A_VOL,CH_B_VOL};
static Chord C5_A3 = {C5,A3,CH_A_VOL,CH_B_VOL};
static Chord C5_A3F = {C5,A3F,CH_A_VOL,CH_B_VOL};
static Chord C5_E4 = {C5,E4,CH_A_VOL,CH_B_VOL};
static Chord D5_E3 = {D5,E3,CH_A_VOL,CH_B_VOL};
static Chord D5_A3 = {D5,A3,CH_A_VOL,CH_B_VOL};
static Chord D5_A3F = {D5,A3F,CH_A_VOL,CH_B_VOL};
static Chord D5_E4 = {D5,E4,CH_A_VOL,CH_B_VOL};
static Chord A4_A3 = {A4,A3,CH_A_VOL,CH_B_VOL};
static Chord A4_E4 = {A4,E4,CH_A_VOL,CH_B_VOL};
static Chord A4F_A3F = {A4F,A3F,CH_A_VOL,CH_B_VOL};
static Chord A4F_E4 = {A4F,E4,CH_A_VOL,CH_B_VOL};
static Chord  X_A3 = {A4,A3,0,CH_B_VOL};
static Chord  X_A3F = {A4,A3F,0,CH_B_VOL};
static Chord  X_E4 = {A4,E4,0,CH_B_VOL};
static Chord  X_E3 = {A4,E3,0,CH_B_VOL};

/* Music
*	Each index in the array represents half a beat.
*/
static Chord *music[NUM_CHORDS] =
	{&E5_E3,  &E5_E4, &E5_E3,  &E5_E4, &E5_E3,  &E5_E4, &E5_E3,  &E5_E4,
	&E5_E3,  &E5_E4, &E5_E3,  &E5_E4,  &X_E3,   &X_E4,  &X_E3,   &X_E4,

	&E5_E3,  &E5_E4, &E5_E3,  &E5_E4, &B4_E3,  &B4_E4, &C5_E3,  &C5_E4,
	&D5_E3,  &D5_E4, &D5_E3,  &D5_E4, &C5_E3,  &C5_E4, &B4_E3,  &B4_E4,
	&A4_A3,  &A4_E4, &A4_A3,   &X_E4, &A4_A3,  &A4_E4, &C5_A3,  &C5_E4,
	&E5_A3,  &E5_E4, &E5_A3,  &E5_E4, &D5_A3,  &D5_E4, &C5_A3,  &C5_E4,
	&B4_A3F, &B4_E4, &B4_A3F,  &X_E4, &B4_A3F, &B4_E4, &C5_A3F, &C5_E4,
	&D5_A3F, &D5_E4, &D5_A3F, &D5_E4, &E5_A3F, &E5_E4, &E5_A3F,  &X_E4,
	&C5_A3,  &C5_E4, &C5_A3,   &X_E4, &A4_A3,  &A4_E4, &A4_A3,   &X_E4,
	&A4_A3,  &A4_E4, &A4_A3,  &A4_E4,  &X_A3,   &X_E4,  &X_A3,   &X_E4,

	&E5_E3,  &E5_E4, &E5_E3,  &E5_E4, &B4_E3,  &B4_E4, &C5_E3,  &C5_E4,
	&D5_E3,  &D5_E4, &D5_E3,  &D5_E4, &C5_E3,  &C5_E4, &B4_E3,  &B4_E4,
	&A4_A3,  &A4_E4, &A4_A3,   &X_E4, &A4_A3,  &A4_E4, &C5_A3,  &C5_E4,
	&E5_A3,  &E5_E4, &E5_A3,  &E5_E4, &D5_A3,  &D5_E4, &C5_A3,  &C5_E4,
	&B4_A3F, &B4_E4, &B4_A3F,  &X_E4, &B4_A3F, &B4_E4, &C5_A3F, &C5_E4,
	&D5_A3F, &D5_E4, &D5_A3F, &D5_E4, &E5_A3F, &E5_E4, &E5_A3F,  &X_E4,
	&C5_A3,  &C5_E4, &C5_A3,   &X_E4, &A4_A3,  &A4_E4, &A4_A3,   &X_E4,
	&A4_A3,  &A4_E4, &A4_A3,  &A4_E4,  &X_A3,   &X_E4,  &X_A3,   &X_E4,

	&E5_A3,  &E5_E4, &E5_A3,  &E5_E4, &C5_A3,  &C5_E4, &C5_A3,  &C5_E4,
	&D5_A3F, &D5_E4, &D5_A3F, &D5_E4, &B4_A3F, &B4_E4, &B4_A3F, &B4_E4,
	&C5_A3,  &C5_E4, &C5_A3,  &C5_E4, &A4_A3,  &A4_E4, &A4_A3,  &A4_E4,
	&A4F_A3F, &A4F_E4, &A4F_A3F, &A4F_E4, &B4_A3F, &B4_E4, &B4_A3F, &B4_E4,

	&E5_A3,  &E5_E4, &E5_A3,  &E5_E4, &C5_A3,  &C5_E4, &C5_A3,  &C5_E4,
	&D5_A3F, &D5_E4, &D5_A3F, &D5_E4, &B4_A3F, &B4_E4, &B4_A3F, &B4_E4,
	&C5_A3,  &C5_E4, &C5_A3,  &C5_E4, &A4_A3,  &A4_E4, &A4_A3,  &A4_E4,
	&A4F_A3F, &A4F_E4, &A4F_A3F, &A4F_E4, &A4F_A3F, &A4F_E4, &A4F_A3F, &X_E4,

	&E5_E3,  &E5_E4, &E5_E3,  &E5_E4, &B4_E3,  &B4_E4, &C5_E3,  &C5_E4,
	&D5_E3,  &D5_E4, &D5_E3,  &D5_E4, &C5_E3,  &C5_E4, &B4_E3,  &B4_E4,
	&A4_A3,  &A4_E4, &A4_A3,   &X_E4, &A4_A3,  &A4_E4, &C5_A3,  &C5_E4,
	&E5_A3,  &E5_E4, &E5_A3,  &E5_E4, &D5_A3,  &D5_E4, &C5_A3,  &C5_E4,
	&B4_A3F, &B4_E4, &B4_A3F,  &X_E4, &B4_A3F, &B4_E4, &C5_A3F, &C5_E4,
	&D5_A3F, &D5_E4, &D5_A3F, &D5_E4, &E5_A3F, &E5_E4, &E5_A3F,  &X_E4,
	&C5_A3,  &C5_E4, &C5_A3,   &X_E4, &A4_A3,  &A4_E4, &A4_A3,   &X_E4,
	&A4_A3,  &A4_E4, &A4_A3,  &A4_E4,  &X_A3,   &X_E4,  &X_A3,   &X_E4,
	
	&E5_E3,  &E5_E4, &E5_E3,  &E5_E4, &B4_E3,  &B4_E4, &C5_E3,  &C5_E4,
	&D5_E3,  &D5_E4, &D5_E3,  &D5_E4, &C5_E3,  &C5_E4, &B4_E3,  &B4_E4,
	&A4_A3,  &A4_E4, &A4_A3,   &X_E4, &A4_A3,  &A4_E4, &C5_A3,  &C5_E4,
	&E5_A3,  &E5_E4, &E5_A3,  &E5_E4, &D5_A3,  &D5_E4, &C5_A3,  &C5_E4,
	&B4_A3F, &B4_E4, &B4_A3F,  &X_E4, &B4_A3F, &B4_E4, &C5_A3F, &C5_E4,
	&D5_A3F, &D5_E4, &D5_A3F, &D5_E4, &E5_A3F, &E5_E4, &E5_A3F,  &X_E4,
	&C5_A3,  &C5_E4, &C5_A3,   &X_E4, &A4_A3,  &A4_E4, &A4_A3,   &X_E4};

void set_rough(int note);

static volatile char *PSG_reg_select = 0xFF8800;
static volatile char *PSG_reg_write  = 0xFF8802;

void enable_channels()
{
	long old_ssp = Super(0);

	*PSG_reg_select = 7;						/* enable channels A and B */
	*PSG_reg_write  = 0x3C;

	Super(old_ssp);
}

void silence()
{
	long old_ssp = Super(0);

	*PSG_reg_select = 8;						/* set channel A volume */
	*PSG_reg_write  = 0;

	*PSG_reg_select = 9;						/* set channel B volume */
	*PSG_reg_write  = 0;

	Super(old_ssp);	
}

void play_music(int index)
{
	long old_ssp = Super(0);

	*PSG_reg_select = 8;						/* set channel A volume */
	*PSG_reg_write  = music[index]->note_a_vol;

	*PSG_reg_select = 0;						/* set channel A fine*/
	*PSG_reg_write  = music[index]->note_a;

	*PSG_reg_select = 1;						/* set channel A rough */
	set_rough(music[index]->note_a);

	*PSG_reg_select = 9;						/* set channel B volume */
	*PSG_reg_write  = music[index]->note_b_vol;

	*PSG_reg_select = 2;						/* set channel B fine */
	*PSG_reg_write  = music[index]->note_b;

	*PSG_reg_select = 3;						/* set channel B rough */
	set_rough(music[index]->note_b);

	Super(old_ssp);
}

void set_rough(int note)
{
	if (note >= 0x200)
	{
		*PSG_reg_write  = 2;
	}
	else if (note >= 0x100)
	{
		*PSG_reg_write  = 1;
	}
	else
	{
		*PSG_reg_write  = 0;
	}
}