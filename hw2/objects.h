/*
*@Filename: objects.h
*@brief:function definition and data structures for drawing complex objects.
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#ifndef OBJECTS_H
#define OBJECTS_H
#include "common.h"
#include "cylinder.h"
#include "sphere.h"
#include "cube.h"

typedef struct
{
    cube_t chair_cube_desc[8];
    cylinder_t chair_cyl_desc[3];
    sphere_t chair_sph_desc[2];
} chair_t;

typedef struct
{
    cube_t table_desc[9];
} table_t;

typedef struct
{
    cylinder_t lamp_cyl_desc[2];
    sphere_t lamp_sph_desc[2];

} lamp_t;

void table(table_t specs);
void chair(chair_t specs);
void lamp(lamp_t specs);

#endif