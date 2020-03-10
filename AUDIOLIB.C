#include <osbind.h>
#include <unistd.h>
#include "audiolib.h"

#define E5 0x0AA
#define D5 0x0BE
#define C5 0x0D6
#define E4 0x153
#define B4 0x0E2
#define A4 0x0FE
#define E3 0x2A7
#define A3 0x1FC
#define A3F 0x21B

#define CH_A_VOL 10
#define CH_B_VOL 6

#define NUM_BARS 8
#define CHORDS_PER_BAR 8

typedef struct {
	int note_a;
	int note_b;
	char note_a_vol;
	char note_b_vol;
} Chord;

void play_chord(Chord *chord, volatile char *PSG_reg_select, volatile char *PSG_reg_write);

void play_music(int index)
{
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
	static Chord  X_A3 = {A4,A3,0,CH_B_VOL};
	static Chord  X_A3F = {A4,A3F,0,CH_B_VOL};
	static Chord  X_E4 = {A4,E4,0,CH_B_VOL};

	static Chord *music[(NUM_BARS * CHORDS_PER_BAR)] =
					 {&E5_E3,  &E5_E4, &E5_E3,  &E5_E4, &B4_E3,  &B4_E4, &C5_E3,  &C5_E4,
					  &D5_E3,  &D5_E4, &D5_E3,  &D5_E4, &C5_E3,  &C5_E4, &B4_E3,  &B4_E4,
					  &A4_A3,  &A4_E4, &A4_A3,   &X_E4, &A4_A3,  &A4_E4, &C5_A3,  &C5_E4,
					  &E5_A3,  &E5_E4, &E5_A3,  &E5_E4, &D5_A3,  &D5_E4, &C5_A3,  &C5_E4,
					  &B4_A3F, &B4_E4, &B4_A3F,  &X_E4, &B4_A3F, &B4_E4, &C5_A3F, &C5_E4,
					  &D5_A3F, &D5_E4, &D5_A3F, &D5_E4, &E5_A3F, &E5_E4,  &X_A3F,  &X_E4,
					  &C5_A3,  &C5_E4,  &X_A3,   &X_E4, &A4_A3,  &A4_E4, &A4_A3,   &X_E4,
					  &A4_A3,  &A4_E4,  &X_A3,   &X_E4,  &X_A3,   &X_E4,  &X_A3,   &X_E4};

	long old_ssp = Super(0);

	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	play_chord(music[index],PSG_reg_select, PSG_reg_write);

	Super(old_ssp);
}

int music_length()
{
	return NUM_BARS * CHORDS_PER_BAR;
}

void enable_channels()
{
	long old_ssp = Super(0);

	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	*PSG_reg_select = 7;		/* enable channels A and B */
	*PSG_reg_write  = 0x3C;

	Super(old_ssp);
}

void silence_music()
{
	long old_ssp = Super(0);

	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	*PSG_reg_select = 8;		/* set channel A volume = 0 */
	*PSG_reg_write  = 0;

	*PSG_reg_select = 9;		/* set channel B volume = 0 */
	*PSG_reg_write  = 0;

	Super(old_ssp);	
}

void play_chord(Chord *chord, volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 0;		/* set channel A */
	*PSG_reg_write  = chord->note_a;

	*PSG_reg_select = 8;		/* set channel A volume */
	*PSG_reg_write  = chord->note_a_vol;

	*PSG_reg_select = 2;		/* set channel B */
	*PSG_reg_write  = chord->note_b;

	*PSG_reg_select = 3;		/* set channel B rough */
	if (chord->note_b >= 0x200)
	{
		*PSG_reg_write  = 2;
	}
	else if (chord->note_b >= 0x100)
	{
		*PSG_reg_write  = 1;
	}
	else
	{
		*PSG_reg_write  = 0;
	}

	*PSG_reg_select = 9;		/* set channel B volume */
	*PSG_reg_write  = chord->note_b_vol;
}