/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#include "../inc/object.h"

static Object *_object_new(float px, float py, float vx, float vy, float mass) {
    Object *object = malloc(sizeof(Object));
    object->position[0] = px;
    object->position[1] = py;
    object->velocity[0] = vx;
    object->velocity[1] = vy;
    object->mass = mass;

    return object;
}

Object *_object_new_wrap(_object_new_args args) {
    float px = args.px ? args.px : 0.0;
    float py = args.py ? args.py : 0.0;
    float vx = args.vx ? args.vx : 0.0;
    float vy = args.vy ? args.vy : 0.0;
    float mass = args.mass ? args.mass : 1.0;

    return _object_new(px, py, vx, vy, mass);
}

void object_free(Object *object) {
    free(object);
}
