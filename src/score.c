#include <stdio.h>
#include <limits.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "score.h"
#include "path.h"

void init_score_text(Text* text, const int x)
{
    char font_path[PATH_MAX];
    get_font_path(font_path, sizeof(char) * PATH_MAX);
    TTF_Init();
    text->font = TTF_OpenFont(font_path, 24);
    if(text->font == NULL)
    {
        printf("%s\n", TTF_GetError());
    }
    text->color.r = 255;
    text->color.g = 255;
    text->color.b = 255;

    const int width = 100;
    const int height = 100;
    
    text->rect.x = x - width / 2;
    text->rect.y = 10;
    text->rect.w = width;
    text->rect.h = height;
}

void get_font_path(char* path, size_t size)
{
    const char font_rel_path[] = "/res/FreeMono.ttf";

    get_cwd(path, size);
    path_append(path, font_rel_path);
}

void init_score(Score* const score)
{
    score->left_player = 0;
    score->right_player = 0;
}

void add_point(Score* score, enum Player player)
{
    if(player == LEFT)
    {
        score->left_player++;
    }
    else
    {
        score->right_player++;
    }
}

void update_score_text(SDL_Renderer** renderer, const Score score, Text* const text)
{
    char score_as_text[8];
    sprintf(score_as_text, "%d:%d", score.left_player, score.right_player);
    text->surface = TTF_RenderText_Solid(text->font, score_as_text, text->color);
    text->texture = SDL_CreateTextureFromSurface(*renderer, text->surface);
}

void terminate_score(Text* text)
{
    SDL_DestroyTexture(text->texture);
    TTF_Quit();
}