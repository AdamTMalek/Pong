#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "game.h"
#include "window.h"

void game_loop(SDL_Window** window, SDL_Renderer** renderer, screen_size* size)
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    uint32_t frameStart;
    int frameTime;

    bool run = true;
    bool wait = true;

    SDL_Event event;
    SDL_Rect left_player = {50, 50, 10, 90};
    SDL_Rect right_player = {size->x - 70, 50, 10, 90}; // 50 as the base position + 20 additional offset

    Ball ball = 
    {
        // SDL_Rect
        { 
            size-> x / 2, 
            size->y / 2,
            5, 5,
        },
        0 // y_movement
    };


    while(run)
    {
        render(renderer, &left_player, &right_player, &(ball.rect));

        // Update the array of keystates
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT) // Quit the game
            {
                run = false;
            }
            else if(event.type == SDL_KEYUP)
            {
                wait = false;
            }
        }
        if(wait)
            continue;

        frameStart = SDL_GetTicks();

        const uint8_t* key_state = SDL_GetKeyboardState(NULL);
        // Move players when keys were pressed
        move_player(&key_state, SDL_SCANCODE_W, SDL_SCANCODE_S, &left_player.y);
        move_player(&key_state, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, &right_player.y);
    
        move_ball(&ball, &left_player, &right_player, size->x, size->y);

        // Limit players so they stay on the screen
        limit_player(&left_player.y, left_player.h, (*size).y);
        limit_player(&right_player.y, right_player.h, (*size).y);

        // Delay for constant frame rate
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void render(SDL_Renderer** renderer, SDL_Rect* left_player, SDL_Rect* right_player, SDL_Rect* ball)
{
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
    SDL_RenderClear(*renderer);
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(*renderer, left_player);
    SDL_RenderFillRect(*renderer, right_player);
    SDL_RenderFillRect(*renderer, ball);
    SDL_RenderPresent(*renderer);
}

void move_player(const uint8_t** key_state, SDL_Scancode up, SDL_Scancode down, int* player_y)
{
    const short speed = 5;
    if((*key_state)[up])
    {
        *player_y -= speed;
    }
    else if((*key_state)[down])
    {
        *player_y += speed;
    }
}

void move_ball(Ball* ball, const SDL_Rect* left_player, const SDL_Rect* right_player, const int max_x, const int max_y)
{
    static bool going_right = true;
    const short speed = 2;

    if(going_right)
    {
        if(is_colliding(&(ball->rect), right_player->x, right_player->y, right_player->h))
        {
            going_right = false;
            ball->y_movement = calculate_bounce_angle(ball->rect.y, right_player->y, right_player->h);
        }

        ball->rect.x += speed;
    }
    else
    {
        if(is_colliding(&(ball->rect), left_player->x + left_player->w, left_player->y, right_player->h))
        {
            going_right = true;
            ball->y_movement = calculate_bounce_angle(ball->rect.y, left_player->y, left_player->h);
        }

        ball->rect.x -= speed;
    }
    if(ball->rect.y >= max_y || ball->rect.y <= 0)
    {
        ball->y_movement *= -1; // Inverse
    }
}

int calculate_bounce_angle(const int ball_y, const int player_y, const int player_h)
{
    const int max_bounce_angle = 75;

    float player_middle = player_y + (player_h / 2.0);
    float intersect = player_middle - ball_y;

    float normalised_intersect = intersect / player_middle;
    float angle = normalised_intersect * max_bounce_angle;

    printf("%f\n", angle);
    return -angle;
}

int is_colliding(SDL_Rect* ball, const int player_x, const int player_y, const int player_h)
{
    if(ball->x != player_x)
    {
        return 0;
    }

    if(ball->y + ball->h >= player_y && ball->y <= (player_y + player_h))
    {
        return 1;
    }
    
    return 0;
}

void limit_player(int* player_y, int player_height, int max_y)
{
    if(*player_y < 0)
    {
        *player_y = 0;
    }
    else if(*player_y > max_y - player_height)
    {
        *player_y = max_y - player_height;
    }
}