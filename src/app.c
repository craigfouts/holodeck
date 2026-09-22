/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#include "../inc/app.h"

static void _app_init_world(App *app, float gravity, size_t n_objects) {
    app->world = world_new(gravity, n_objects);
    app->objects = malloc(n_objects*sizeof(SDL_FRect));

    for (size_t i = 0; i < n_objects; ++i)
        app->objects[i] = &(SDL_FRect) {
            app->world->objects[i]->position[0],
            app->world->objects[i]->position[1],
            100, 100
        };
}

static App *_app_new(const char *title, float width, float height, float gravity, size_t n_objects) {
    SDL_Init(SDL_INIT_VIDEO);
    App *app = malloc(sizeof(App));
    app->window = SDL_CreateWindow(title, width, height, 0);

    if (!app->window) {
        printf("APP ERROR: Failed to create window.\n");

        return NULL;
    }

    app->renderer = SDL_CreateRenderer(app->window, NULL);

    if (!app->renderer) {
        printf("APP ERROR: Failed to create renderer.\n");

        return NULL;
    }

    _app_init_world(app, gravity, n_objects);

    return app;
}

static void _app_draw_objects(App *app) {
    for (size_t i = 0; i < app->world->n_objects; ++i) {
        app->objects[i]->x = app->world->objects[i]->position[0];
        app->objects[i]->y = app->world->objects[i]->position[1];
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
        SDL_RenderClear(app->renderer);
        SDL_SetRenderDrawColor(app->renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(app->renderer, app->objects[i]);
        SDL_RenderPresent(app->renderer);
    }
}

static bool _app_step(App *app, SDL_Event *e, float dt) {
    while (SDL_PollEvent(e))
        if ((*e).type == SDL_EVENT_QUIT)
            return false;

    _app_draw_objects(app);
    world_step(app->world, .dt=dt);

    return true;
}

static void _app_run(App *app, float dt) {    
    SDL_Event e;

    while (app_step(app, &e, .dt=dt));
}

App *_app_new_wrap(_app_new_args args) {
    const char *title = args.title ? args.title : "Untitled App";
    float width = args.width ? args.width : 500.0;
    float height = args.height ? args.height : 500.0;
    float gravity = args.gravity ? args.gravity : 9.8;
    size_t n_objects = args.n_objects ? args.n_objects : 0;

    return _app_new(title, width, height, gravity, n_objects);
}

bool _app_step_wrap(App *app, SDL_Event *e, _app_step_args args) {
    float dt = args.dt ? args.dt : 0.1;

    return _app_step(app, e, dt);
}

void _app_run_wrap(App *app, _app_run_args args) {
    float dt = args.dt ? args.dt : 0.1;

    _app_run(app, dt);
}

void app_free(App *app) {
    world_free(app->world);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}
