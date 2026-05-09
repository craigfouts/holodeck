/* 
Authors: Craig Fouts
Contact: c.fouts25@imperial.ac.uk
License: Apache 2.0 license
*/

#include "stdio.h"
#include "SDL3/SDL.h"
#include "../inc/object.h"

int main(void) {
    Object *object = object_new();

    printf("%f\n", object->mass);

    object_free(object);

    return 0;
}
