/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#include "../inc/world.h"

static World *_world_new(float gravity, size_t n_objects) {
    World *world = malloc(sizeof(World));
    world->gravity = gravity;
    world->n_objects = n_objects;
    world->objects = malloc(n_objects*sizeof(Object));

    for (size_t i = 0; i < n_objects; ++i) 
        world->objects[i] = object_new();

    return world;
}

World *_world_new_wrap(_world_new_args args) {
    float gravity = args.gravity ? args.gravity : -9.8;
    size_t n_objects = args.n_objects ? args.n_objects : 0;

    return _world_new(gravity, n_objects);
}

static void _world_step(World *world, float dt) {
    for (size_t i = 0; i < world->n_objects; ++i) {
        world->objects[i]->position[1] += world->objects[i]->velocity[1]*dt;
        world->objects[i]->velocity[1] += world->gravity*dt;
    }
}

void _world_step_wrap(World *world, _world_step_args args) {
    float dt = args.dt ? args.dt : 1.0;

    _world_step(world, dt);
}

void world_free(World *world) {
    for (size_t i = 0; i < world->n_objects; ++i, --(world->n_objects))
        object_free(world->objects[i]);

    free(world);
}
