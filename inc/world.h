/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#ifndef WORLD_H
#define WORLD_H

#include "object.h"

typedef struct {
    float gravity;
    size_t n_objects;
    Object **objects;
} World;

typedef struct {
    float gravity;
    size_t n_objects;
} _world_new_args;

typedef struct {
    float dt;
} _world_step_args;

World *_world_new_wrap(_world_new_args args);
#define world_new(...) _world_new_wrap((_world_new_args) {__VA_ARGS__})

void _world_step_wrap(World *world, _world_step_args args);
#define world_step(world, ...) _world_step_wrap(world, (_world_step_args) {__VA_ARGS__})

void world_free(World *world);

#endif
