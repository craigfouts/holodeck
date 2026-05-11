/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#ifndef APP_H
#define APP_H

#include "stdbool.h"
#include "SDL3/SDL.h"
#include "world.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    World *world;
} App;

typedef struct {
    const char *title;
    float width;
    float height;
    float gravity;
    size_t n_objects;
} _app_new_args;

typedef struct {
    float dt;
} _app_step_args;

App *_app_new_wrap(_app_new_args args);
#define app_new(...) _app_new_wrap((_app_new_args) {__VA_ARGS__})

void _app_step_wrap(App *app, _app_step_args args);
#define app_step(app, ...) _app_step_wrap(app, (_app_step_args) {__VA_ARGS__})

void app_run(App *app);
void app_free(App *app);

#endif
