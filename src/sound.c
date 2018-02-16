#include "sound.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "path.h"

#define MAX_PATH_LENGTH 100

Mix_Music *bounce;
Mix_Music *point;

void get_path(char *buffer, size_t size, const char *relative_path)
{
	get_cwd(buffer, size);
	path_append(buffer, relative_path);
}


bool init_sound()
{
	bool success = true; // Indicates whether sound was successfully initialised

	// Initialise required components
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("Failed to initialise AUDIO\n");
		success = false;
	}

	int mixer_result; // Result of mixer initialisation
	if ((mixer_result = Mix_Init(MIX_INIT_MP3)) != MIX_INIT_MP3)
	{
		printf("Unable to initialise MIXER\nResult: %d\n", mixer_result);
		printf("Error: %s\n", Mix_GetError());
		success = false;
	}

	if(Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640) == -1)
	{
		printf("Opening audio failed\n");
		success = false;
	}

	// Load the sound files
	char bounce_file[MAX_PATH_LENGTH];
	get_path(bounce_file, MAX_PATH_LENGTH, "/res/bounce.mp3");

	bounce = Mix_LoadMUS(bounce_file);
	if (!bounce)
	{
		printf("Error: %s\n", Mix_GetError());
		success = false;
	}

	char point_file[MAX_PATH_LENGTH];
	get_path(point_file, MAX_PATH_LENGTH, "/res/point.mp3");

	point = Mix_LoadMUS(point_file);
	if (!point)
	{
		printf("Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void play_sound(enum Sound sound)
{
	switch (sound)
	{
		case BOUNCE:
			Mix_PlayMusic(bounce, 1);
			break;
		case POINT:
			Mix_PlayMusic(point, 1);
			break;
		default:
			printf("Error: No such sound.\n");
			break;
	}
}

void quit_sound()
{
	Mix_FreeMusic(bounce);
	Mix_FreeMusic(point);
}