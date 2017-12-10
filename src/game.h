#ifndef _GAME_H
#define _GAME_H

#include "window.h"

typedef struct
{
    SDL_Rect rect;
    float x_velocity;
    float y_velocity;
} Ball;

void game_loop(SDL_Window** window, SDL_Renderer** renderer, screen_size* size);
void render(SDL_Renderer** renderer, SDL_Rect* left_player, SDL_Rect* right_player, SDL_Rect* ball);
void move_player(const uint8_t** key_state, SDL_Scancode up, SDL_Scancode down, int* player_y);
void move_ball(Ball* ball, const SDL_Rect* left_player, const SDL_Rect* right_player, const int max_x, const int max_y);
double calculate_bounce_angle(const int ball_y, const int player_y, const int player_h, const bool right);
/*
 * Returns 1 if the ball collides with the player. Otherwise return 0
*/
int is_colliding(SDL_Rect* ball,const int player_x, const int player_y, const int player_h);
/*
 * Limit the player to the boundaries of the screen
*/
void limit_player(int* player_y, int player_height, int max_y);

#endif