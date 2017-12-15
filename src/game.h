#ifndef _GAME_H
#define _GAME_H

#include "window.h"
#include "score.h"

typedef struct
{
    SDL_Rect rect;
    float x_velocity;
    float y_velocity;
} Ball;

enum Ball_Position
{
    ONSCREEN,
    OFF_LEFT,
    OFF_RIGHT
};

void game_loop(SDL_Window** window, SDL_Renderer** renderer, screen_size* size);
void render(SDL_Renderer** renderer, SDL_Rect* left_player, SDL_Rect* right_player, SDL_Rect* ball, const Text* score_text);
void move_player(const uint8_t** key_state, SDL_Scancode up, SDL_Scancode down, int* player_y);

/*
 * Returns different values depending on whether the ball is onscreen or offscreen
*/
int move_ball(Ball* ball, const SDL_Rect* left_player, const SDL_Rect* right_player, const int max_x, const int max_y);
/*
 * Returns true whenever ball's y position is above or equal to max_y or below or equal to 0.
*/
bool ball_out_y(const int y, const int max_y);

double calculate_bounce_angle(const int ball_y, const int player_y, const int player_h, const bool right);

/*
 * Returns 1 if the ball collides with the player. Otherwise return 0
*/
int is_colliding(SDL_Rect* ball,const int player_x, const int player_y, const int player_h);

/*
 * Limit the player to the boundaries of the screen
*/
void limit_player(int* player_y, int player_height, int max_y);

/*
 * Sets the ball position to x and y, resets y-velocity to 0
 * and sets x-velocity to 2
*/
void reset_ball_position(Ball* ball, const int x, const int y);
#endif