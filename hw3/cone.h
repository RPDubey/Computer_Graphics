/*
*@Filename: cone.h
*@brief:function definition and data structure for cone
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#ifndef CONE_H
#define CONE_H

#include "common.h"

#define unitcone(mat) cone((cone_t){4, 0, 0, 0, 1, 1, 1, 0, 0, WHITE, WHITE, BLACK, mat})

typedef struct
{
    int id;
    double x, y, z, H, R, h, thx, thz;
    color_t surface, bottom, top;
    material_t material;

} cone_t;

void cone(const cone_t specs);
#endif