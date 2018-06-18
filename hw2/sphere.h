/*
*@Filename: sphere.h
*@brief:definition of function and data structure for sphere
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

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