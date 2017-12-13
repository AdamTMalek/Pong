#ifndef _SCORE_H
#define _SCORE_H

#include <SDL2/SDL_ttf.h>

typedef struct
{
    uint8_t left_player;
    uint8_t right_player;
} Score;

enum Player
{
    LEFT,
    RIGHT
};

typedef struct
{
    TTF_Font* font;
    SDL_Color color;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
} Text;

void init_score_text(Text* text, const int x);
void get_font_path(char* path, size_t size);
void init_score(Score* const score);
void add_point(Score* score, enum Player player);
void update_score_text(SDL_Renderer** renderer, const Score score, Text* const text);
void terminate_score(Text* text);

#endif