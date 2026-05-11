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
    float gravity = args.gravity ? args.gravity : 9.8;
    size_t n_objects = args.n_objects ? args.n_objects : 0;

    return _world_new(gravity, n_objects);
}

static void _world_step(World *world, size_t n_steps, float dt) {
    for (size_t i = 0; i < n_steps; ++i)
        for (size_t j = 0; j < world->n_objects; ++j) {
            world->objects[j]->velocity[1] += world->gravity*dt;
            world->objects[j]->position[1] += world->objects[j]->velocity[1]*dt;
        }
}

void _world_step_wrap(World *world, _world_step_args args) {
    size_t n_steps = args.n_steps ? args.n_steps : 1;
    float dt = args.dt ? args.dt : 0.1;

    _world_step(world, n_steps, dt);
}

void world_free(World *world) {
    for (size_t i = 0; i < world->n_objects; ++i, --(world->n_objects))
        object_free(world->objects[i]);

    free(world);
}
