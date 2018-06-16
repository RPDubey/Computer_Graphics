#ifndef CUBE_H
#define CUBE_H
#include "common.h"
typedef struct
{
    color_t front, back, right, left, top, bottom;
} cube_color_t;

typedef struct
{
    int id;
    double x, y, z, dx, dy, dz, th, Zp;
    cube_color_t cube_col;
} cube_t;

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */

void cube(const cube_t cube);

#endif