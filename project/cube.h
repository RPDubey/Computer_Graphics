/*
*@Filename: cube.h
*@brief:declares cube drawing function, and cube data structure
*@author:Ravi Prakash Dubey
*@date:06/29/2018
*/

#ifndef CUBE_H
#define CUBE_H
#include "common.h"

#define cub(x, y, z, dx, dy, dz, col, mat) cube((cube_t){2, x, y, z, dx, dy, dz, 0, 0, col, mat})
#define unitcube(mat) cube((cube_t){2, 0, 0, 0, 1, 1, 1, 0, 0, {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE}, mat})

//structure to hold color of 6 faces
typedef struct
{
    color_t front, back, right, left, top, bottom;
} cube_color_t;

//structure to hold description of cube
typedef struct
{
    int id;
    double x, y, z, dx, dy, dz, thy, Zp;
    cube_color_t cube_col;
    material_t material;
} cube_t;

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */

void cube(const cube_t cube);

#endif