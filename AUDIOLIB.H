/* AUDIOLIB.H
*
*   Olga Koldachenko	okold525@mtroyal.ca
*   COMP 2659           Term Project
*   Winter 2020         Tyson Kendon
*
*   Purpose:    Handles all audio.
*
*   Music:      Korobeiniki, a Russian folk song.
                Referenced sheet music found at:
*	            https://musescore.com/user/2330636/scores/836516
*	            March 11, 2020
*
*   Public Functions:   void enable_channels();
*                       -   Enables sound. Must be run before play_music().
*
*                       void silence();
*                       -   Silences all audio.
*
*                       void play_music(int index);
*                       -   Plays the chord at the given index.
*                       -   There are NUM_CHORDS indices in the song.
*
*                       void enable_sound_effect();
*                       -   Plays the impact sound effect until disabled.
*
*                       void disable_sound_effect();
*                       -   Disables the impact sound effect..
*/
#ifndef AUDIOLIB_H
#define AUDIOLIB_H

#define NUM_CHORDS 328

void enable_channels();
void silence();
void play_music(int index);
void enable_sound_effect();
void disable_sound_effect();

#endif