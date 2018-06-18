/*
*@Filename: cube.h
*@brief:declares cube drawing function, and cube data structure
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#ifndef CUBE_H
#define CUBE_H
#include "common.h"
//structure to hold color of 6 faces
typedef struct
{
    color_t front, back, right, left, top, bottom;
} cube_color_t;

//structure to hold description of cube
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