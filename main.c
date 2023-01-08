#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "draw.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define COLOR_BACKGROUND (rgba){255, 0, 0, 255}
#define COLOR_WHITE (rgba){255, 255, 255, 255}
#define COLOR_BLACK (rgba){0, 0, 0, 255}

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *surface;
  SDL_Surface *window_surface;
  SDL_Texture *texture;
} Context;

void init_SDL(char *title, Context *context);
void prepare_scene(Context *context);
void present_scene(Context *context);
void handle_events(Context *context, bool *running, float delta_time);
void cleanup(Context *context);

int main(void) {
  char *title = "3D Graphics Engine";
  Context context = {0};

  init_SDL(title, &context);

  bool running = true;

  u64 tick_last = 0;
  u64 tick_now = SDL_GetPerformanceCounter();
  float delta_time = 0;

  while (running) {
    tick_last = tick_now;
    tick_now = SDL_GetPerformanceCounter();
    delta_time = (float)((tick_now - tick_last)*10000 / (float)tick_now);
    printf("dt:%f\n", delta_time);

    prepare_scene(&context);

    handle_events(&context, &running, delta_time);

    present_scene(&context);

    // wait 1/60th of a second
    SDL_Delay(1000/60);
  }

  cleanup(&context);

  return 0;
}

void init_SDL(char *title, Context *context) {
  // attempt to initialize graphics and timer system
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
    exit(1);
  }

  u32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

  context->window = SDL_CreateWindow(title,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            flags);
  if (context->window == NULL) {
    printf("error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }

  context->window_surface = SDL_GetWindowSurface(context->window);
  if (context->window_surface == NULL) {
    printf("error getting window surface: %s\n", SDL_GetError());
    cleanup(context);
    exit(3);
  }

  context->surface = SDL_CreateRGBSurface(0,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          32, 0, 0, 0, 0);
  if (context->surface == NULL) {
    printf("error creating surface: %s\n", SDL_GetError());
    cleanup(context);
    exit(4);
  }

  // https://wiki.libsdl.org/SDL2/SDL_RendererFlags
  u32 render_flags = SDL_RENDERER_ACCELERATED;
  context->renderer = SDL_CreateRenderer(context->window, -1, render_flags);
}

/**
   Clear the surface by drawing a single color to it.
 */
void prepare_scene(Context *context) {
  SDL_FillRect(context->surface, NULL, SDL_MapRGBA(context->surface->format, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a));

  // Initializes backbuffer
  SDL_RenderClear(context->renderer);
}

/**
   Events, even time changing, will update the surface.
 */
void handle_events(Context *context, bool *running,float delta_time) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      *running = false;
    }

    // Handle keyboard input
    if (event.type == SDL_KEYDOWN) {
      if (SDL_SCANCODE_UP) {}
      if (SDL_SCANCODE_DOWN) {}
      if (SDL_SCANCODE_RIGHT) {}
      if (SDL_SCANCODE_LEFT) {}
      if (SDL_SCANCODE_A) {}
      if (SDL_SCANCODE_D) {}
      if (SDL_SCANCODE_W) {}
      if (SDL_SCANCODE_S) {}
    }
  }
}

/**
   Update the surface (blit to it) with the window surface to update the screen.
 */
void present_scene(Context *context) {
  // For using multiple backbuffers
  SDL_BlitSurface(context->surface, NULL, context->window_surface, NULL);
  SDL_UpdateWindowSurface(context->window);

  /* SDL_RenderPresent(context->renderer); */
}

void cleanup(Context *context) {
  if (context->surface != NULL) {
    SDL_FreeSurface(context->surface);
  }

  if (context->renderer != NULL) {
    SDL_DestroyRenderer(context->renderer);
  }

  if (context->window != NULL) {
    SDL_DestroyWindow(context->window);
  }

  SDL_Quit();
}
