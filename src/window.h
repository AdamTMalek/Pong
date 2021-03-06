#ifndef _WINDOW_H
#define _WINDOW_H

typedef struct
{
    int x;
    int y;
} screen_size;

int initialise_main_window(SDL_Window** window, SDL_Renderer** renderer, const screen_size* size);
void destroy(SDL_Window* window, SDL_Renderer* renderer);

#endif