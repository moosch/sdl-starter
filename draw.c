#include <SDL2/SDL.h>
#include "types.h"

/**
   SDL2 specific draw functions
   This forms a simple API over SDL2 specifics.
   Useful abstraction!
*/

void get_current_color(SDL_Renderer *renderer, rgba *color) {
  SDL_GetRenderDrawColor(renderer, &color->r, &color->g, &color->b, &color->a);
}
void set_color(SDL_Renderer *renderer, rgba color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

// draws a simple, straight line.
void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, rgba c) {
  rgba initial_color = {0};
  get_current_color(renderer, &initial_color);

  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
  int result = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  if (result != 0) {
    printf("Failed to draw line at {%d, %d} {%d, %d}\n", x1, y1, x2, y2);
  }

  set_color(renderer, initial_color);
}

// Draws the outline of a triangle.
void draw_triangle(SDL_Renderer *renderer,
                   int x1, int y1,
                   int x2, int y2,
                   int x3, int y3,
                   rgba c) {
  rgba initial_color = {0};
  get_current_color(renderer, &initial_color);

  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
  int res0 = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  int res1 = SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
  int res2 = SDL_RenderDrawLine(renderer, x3, y3, x1, y1);
  if (res0 != 0 || res1 != 0 || res2 != 0) {
    printf("Failed to draw triangle at {%d, %d} {%d, %d}, {%d, %d}\n",
           x1, y1, x2, y2, x3, y3);
  }

  set_color(renderer, initial_color);
}

// Draws a filled triangle.
void fill_triangle(SDL_Renderer *renderer,
                   int x1, int y1,
                   int x2, int y2,
                   int x3, int y3,
                   rgba c) {
  rgba initial_color = {0};
  get_current_color(renderer, &initial_color);

  SDL_Color color = {c.r, c.g, c.b, c.a};
  u32 num_vertices = 3;
  const SDL_Vertex vertices[3] = {
    {(SDL_FPoint){x1, y1}, color, (SDL_FPoint){0}},
    {(SDL_FPoint){x2, y2}, color, (SDL_FPoint){0}},
    {(SDL_FPoint){x3, y3}, color, (SDL_FPoint){0}},
  };

  u32 result = SDL_RenderGeometry(renderer,
                                  NULL,
                                  vertices, num_vertices,
                                  NULL, 0);
  if (result != 0) {
    printf("Failed to draw triangle at {%d, %d} {%d, %d}, {%d, %d}\n",
           x1, y1, x2, y2, x3, y3);
    printf("error initializing SDL: %s\n", SDL_GetError());
    exit(1);
  }

  set_color(renderer, initial_color);
}
