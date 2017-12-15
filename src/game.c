#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "game.h"
#include "window.h"
#include "map.h"
#include "score.h"

#define RAD(deg) ((deg)*(M_PI)/(180))

#define BALL_SPEED 2

void game_loop(SDL_Window** window, SDL_Renderer** renderer, screen_size* size)
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    uint32_t frameStart;
    int frameTime;

    bool run = true;
    bool wait = true;

    Score score;
    Text score_text;
    init_score_text(&score_text, (size->x / 2));
    init_score(&score);
    update_score_text(renderer, score, &score_text);

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
        BALL_SPEED,
        0,
    };

    while(run)
    {
        render(renderer, &left_player, &right_player, &(ball.rect), &score_text);

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
    
        int ball_pos = move_ball(&ball, &left_player, &right_player, size->x, size->y);
        if(ball_pos != ONSCREEN)
        {
            int player_scored = ball_pos == OFF_LEFT ? RIGHT : LEFT;
            add_point(&score, player_scored);
            update_score_text(renderer, score, &score_text);
            reset_ball_position(&ball, size->x / 2, size->y / 2);
            wait = true;
            continue;
        }

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

    terminate_score(&score_text);
}

void render(SDL_Renderer** renderer, SDL_Rect* left_player, SDL_Rect* right_player, SDL_Rect* ball, const Text* score_text)
{
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
    SDL_RenderClear(*renderer);
    SDL_RenderCopy(*renderer, score_text->texture, NULL, &(score_text->rect));
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

int move_ball(Ball* ball, const SDL_Rect* left_player, const SDL_Rect* right_player, const int max_x, const int max_y)
{
    bool going_right = ball->x_velocity > 0 ? true : false;
    
    const SDL_Rect* player = going_right ? right_player : left_player;

    if(is_colliding(&(ball->rect),player->x, player->y, player->h))
    {
        double bounce_angle = calculate_bounce_angle(ball->rect.y, player->y, player->h, true);
        ball->y_velocity = BALL_SPEED * sin(RAD(bounce_angle));
        ball->x_velocity = BALL_SPEED * sin(RAD(bounce_angle - 90));

        if(going_right)
            ball->x_velocity *= -1;
    }


    if(ball_out_y(ball->rect.y, max_y))
    {
        ball->y_velocity *= -1; // Inverse
    }

    ball->rect.x += (int)round(ball->x_velocity);
    ball->rect.y += (int)round(ball->y_velocity);

    if(ball->rect.x > max_x)
        return OFF_RIGHT;
    else if(ball->rect.x < 0)
        return OFF_LEFT;
    else
        return ONSCREEN;
}

bool ball_out_y(const int y, const int max_y)
{
    return y >= max_y || y <= 0;
}

double calculate_bounce_angle(const int ball_y, const int player_y, const int player_h, const bool right)
{
    float difference = ball_y - (player_y + player_h / 2);
    return map(difference, -(player_h / 2.0), (player_h / 2.0), 225.0, 135.0);
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

void reset_ball_position(Ball* ball, const int x, const int y)
{
    ball->y_velocity = 0;
    ball->x_velocity = 2;
    ball->rect.x = x;
    ball->rect.y = y;
}
