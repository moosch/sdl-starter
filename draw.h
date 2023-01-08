#ifndef _GRAPHICS_DRAW_H_
#define _GRAPHICS_DRAW_H_

#include <SDL2/SDL.h>
#include "types.h"

void get_current_color(SDL_Renderer *renderer, rgba *color);
void set_color(SDL_Renderer *renderer, rgba color);
void draw_line(SDL_Renderer *renderer, i32 x1, i32 y1, i32 x2, i32 y2, rgba c);
void draw_triangle(SDL_Renderer *renderer,
                   i32 x1, i32 y1,
                   i32 x2, i32 y2,
                   i32 x3, i32 y3,
                   rgba c);
void fill_triangle(SDL_Renderer *renderer,
                   int x1, int y1,
                   int x2, int y2,
                   int x3, int y3,
                   rgba c);

#endif
