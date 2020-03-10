#include <osbind.h>
#include <unistd.h>

void play_e5_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_b4_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_c5_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_d5_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_a4_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_e4_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_e3_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_a3_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void play_a3f_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void silence_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void silence_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write);
void vsync_wait(int num);

int main()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	long old_ssp = Super(0);

	*PSG_reg_select = 7;		/* enable channel A on mixer */
	*PSG_reg_write  = 0x3C;

	/* #1 */
	play_e5_a(PSG_reg_select, PSG_reg_write);
	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_b4_a(PSG_reg_select, PSG_reg_write);
	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_c5_a(PSG_reg_select, PSG_reg_write);
	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	/* #2 */
	play_d5_a(PSG_reg_select, PSG_reg_write);
	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_c5_a(PSG_reg_select, PSG_reg_write);
	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_b4_a(PSG_reg_select, PSG_reg_write);
	play_e3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	/* #3 */
	play_a4_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	silence_a(PSG_reg_select, PSG_reg_write);
	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a4_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_c5_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	/* #4 */
	play_e5_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_d5_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_c5_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	/* #5 */
	play_b4_a(PSG_reg_select, PSG_reg_write);
	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	silence_a(PSG_reg_select, PSG_reg_write);
	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_b4_a(PSG_reg_select, PSG_reg_write);
	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_c5_a(PSG_reg_select, PSG_reg_write);
	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	/* #6 */
	play_d5_a(PSG_reg_select, PSG_reg_write);
	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e5_a(PSG_reg_select, PSG_reg_write);
	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	silence_a(PSG_reg_select, PSG_reg_write);
	play_a3f_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	/* #7 */
	play_c5_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	silence_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a4_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	silence_a(PSG_reg_select, PSG_reg_write);
	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	/* #8 */
	play_a4_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	silence_a(PSG_reg_select, PSG_reg_write);
	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_a3_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);

	play_e4_b(PSG_reg_select, PSG_reg_write);
	vsync_wait(10);
	
	silence_a(PSG_reg_select, PSG_reg_write);
	silence_b(PSG_reg_select, PSG_reg_write);

	Cnecin();
	Super(old_ssp);
	return 0;
}

void play_e5_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 170;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = 11;
}

void play_b4_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 226;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = 11;
}

void play_c5_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 214;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = 11;
}

void play_d5_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 190;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = 11;
}

void play_a4_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 254;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = 11;
}

void play_e4_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 2;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 339;

	*PSG_reg_select = 9;		/* set channel A volume = 11 */
	*PSG_reg_write  = 6;
}

void play_e3_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 2;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 679;

	*PSG_reg_select = 9;		/* set channel A volume = 11 */
	*PSG_reg_write  = 6;
}

void play_a3_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 2;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 508;

	*PSG_reg_select = 9;		/* set channel A volume = 11 */
	*PSG_reg_write  = 6;
}

void play_a3f_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 2;		/* set channel A fine tune = 248 */
	/**PSG_reg_write  = 539;*/
	*PSG_reg_write  = 508;

	*PSG_reg_select = 9;		/* set channel A volume = 11 */
	*PSG_reg_write  = 6;
}

void silence_a(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 8;		/* set channel A volume = 0 */
	*PSG_reg_write  = 0;
}

void silence_b(volatile char *PSG_reg_select, volatile char *PSG_reg_write)
{
	*PSG_reg_select = 9;		/* set channel A volume = 0 */
	*PSG_reg_write  = 0;
}

void vsync_wait(int num)
{
	int i;

	for (i = 0; i < num; i++)
	{
		Vsync();
	}
}