#include <SDL2/SDL.h>

#include "window.h"

int initialise_main_window(SDL_Window** window, SDL_Renderer** renderer, const screen_size* size)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialised");
        return EXIT_FAILURE;
    }

    *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            size->x, size->y,
                            0);
    
    if(*window == NULL)
    {
        printf("Couldn't create a window");
        return EXIT_FAILURE;
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);
    return EXIT_SUCCESS;
}

void destroy(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}