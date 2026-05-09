/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#include "stdio.h"
#include "SDL3/SDL.h"
#include "../inc/world.h"

int main(void) {
    World *world = world_new(.n_objects=2);
    world->objects[1]->mass = 10.0;

    printf("%f\n", world->objects[0]->mass);
    printf("%f\n", world->objects[1]->mass);

    world_free(world);

    return 0;
}
