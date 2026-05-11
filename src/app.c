/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#include "../inc/app.h"

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

    app->world = world_new(gravity, n_objects);

    return app;
}

App *_app_new_wrap(_app_new_args args) {
    const char *title = args.title ? args.title : "Untitled App";
    float width = args.width ? args.width : 500.0;
    float height = args.height ? args.height : 500.0;
    float gravity = args.gravity ? args.gravity : 9.8;
    size_t n_objects = args.n_objects ? args.n_objects : 0;

    return _app_new(title, width, height, gravity, n_objects);
}

void app_run(App *app) {    
    SDL_FRect objects[app->world->n_objects];

    for (size_t i = 0; i < app->world->n_objects; ++i) {
        objects[i] = (SDL_FRect) {
            app->world->objects[i]->position[0],
            app->world->objects[i]->position[1],
            100, 100
        };
    }

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_EVENT_QUIT)
                quit = true;

        if (quit)
            continue;

        for (size_t i = 0; i < app->world->n_objects; ++i) {
            objects[i].x = app->world->objects[i]->position[0];
            objects[i].y = app->world->objects[i]->position[1];
            SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
            SDL_RenderClear(app->renderer);
            SDL_SetRenderDrawColor(app->renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(app->renderer, &objects[i]);
            SDL_RenderPresent(app->renderer);
        }

        world_step(app->world);
    }
}

void app_free(App *app) {
    world_free(app->world);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}
