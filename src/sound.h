#ifndef _SOUND_H
#define _SOUND_H

#include <stdbool.h>

enum Sound
{
	BOUNCE,
	POINT
};

/*
 * Initialises the required sound components and loads the file for playback.
 * Returns true on success and false on failure.
*/
bool init_sound();

/*
 * Plays the bounce sound
*/
void play_sound(enum Sound sound);

/*
 * This method should be called on exit. It frees up memory used by the mixer
*/
void quit_sound();

#endif