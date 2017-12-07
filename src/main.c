#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "window.h"
#include "game.h"

int main(int argc, char* args[])
{   
    SDL_Window* window;
    SDL_Renderer* renderer;

    screen_size size;
    size.x = 640;
    size.y = 480;

    if(initialise_main_window(&window, &renderer, &size) != 0)
    {
        printf("Something went wrong...");
        return EXIT_FAILURE;
    }
    game_loop(&window, &renderer, &size);

    destroy(window, renderer);
    return EXIT_SUCCESS;
}