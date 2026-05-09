/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "stdlib.h"

typedef struct {
    float position[2];
    float velocity[2];
    float mass;
} Object;

typedef struct {
    float px, py;
    float vx, vy;
    float mass;
} _object_new_args;

Object *_object_new_wrap(_object_new_args args);
#define object_new(...) _object_new_wrap((_object_new_args) {__VA_ARGS__})

void object_free(Object *object);

#endif
