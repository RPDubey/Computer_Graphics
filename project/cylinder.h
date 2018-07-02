/*
*@Filename: cylinder.h
*@brief:definition of function and data structure for cylinder
*@author:Ravi Prakash Dubey
*@date:06/28/2018
*/

#ifndef CYLINDER_H
#define CYLINDER_H

#include "common.h"

#define unitcylinder(mat) cylinder((cylinder_t){3, 0, 0, 0, 1, 1, 0, 0, {WHITE, WHITE, WHITE}, mat})

typedef struct
{
    color_t top, bottom, curve;

} cylinder_color_t;

typedef struct
{
    int id;
    double x, y, z, radius, height, thx, thz;
    cylinder_color_t cyl_col;
    material_t material;

} cylinder_t;

void cylinder(const cylinder_t cyl);

#endif