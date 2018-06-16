#ifndef SPHERE_H
#define SPHERE_H
#include "common.h"
/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */

typedef struct
{
    int id;
    double x, y, z, r, phbottom, phtop;
    color_t color;
} sphere_t;

void sphere(const sphere_t spec);

#endif