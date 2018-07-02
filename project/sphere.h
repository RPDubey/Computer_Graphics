/*
*@Filename: sphere.h
*@brief:definition of function and data structure for sphere
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/29/2018
*/

#ifndef SPHERE_H
#define SPHERE_H
#include "common.h"

#define ball(x, y, z, r, col, mat) sphere((sphere_t){1, x, y, z, r, -90, 90, col, mat})
#define unitsphere(mat) sphere((sphere_t){1, 0, 0, 0, 1, -90, 90, WHITE, mat})

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
    material_t material;
} sphere_t;

void sphere(const sphere_t spec);

#endif