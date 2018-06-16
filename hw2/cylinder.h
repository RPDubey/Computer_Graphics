#ifndef CYLINDER_H
#define CYLINDER_H

#include "common.h"

typedef struct
{
    color_t top, bottom, curve;

} cylinder_color_t;

typedef struct
{
    int id;
    double x, y, z, radius, height, thx, thz;
    cylinder_color_t cyl_col;
} cylinder_t;

void cylinder(const cylinder_t cyl);

#endif