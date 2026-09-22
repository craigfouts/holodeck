/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#include "stdio.h"
#include "SDL3/SDL.h"
#include "../inc/app.h"

int main(void) {
    // World *world = world_new(.n_objects=2);
    // world->objects[1]->mass = 10.0;

    // printf("%f\n", world->objects[1]->position[0]);
    // printf("%f\n", world->objects[1]->position[1]);

    // world_step(world, .n_steps=10);

    // printf("%f\n", world->objects[1]->position[0]);
    // printf("%f\n", world->objects[1]->position[1]);

    // world_free(world);

    App *app = app_new("Test App", .n_objects=1);

    if (!app) {
        printf("APP ERROR: Failed to create App.\n");

        return 1;
    }

    app->world->objects[0]->position[0] = 200.0;
    app->world->objects[0]->position[1] = 50.0;

    app_run(app, .dt=.01);
    
    app_free(app);

    return 0;
}
