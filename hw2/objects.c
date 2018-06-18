/*
*@Filename: objects.c
*@brief:Implements functions for drawing complex objects(using primitive objects)
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#include "objects.h"

#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

void table(table_t specs)
{
    for (int i = 0; i < 9; i++)
    {
        cube(specs.table_desc[i]);
    }
}

void chair(chair_t specs)
{
    for (int i = 0; i < 8; i++)
        cube(specs.chair_cube_desc[i]);
    for (int i = 0; i < 3; i++)
        cylinder(specs.chair_cyl_desc[i]);
    for (int i = 0; i < 2; i++)
        sphere(specs.chair_sph_desc[i]);
}

void lamp(lamp_t specs)
{
    for (int i = 0; i < 2; i++)
        cylinder(specs.lamp_cyl_desc[i]);
    for (int i = 0; i < 2; i++)
        sphere(specs.lamp_sph_desc[i]);
}
