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

typedef struct
{
    int id;
    double x, y, z, H, R, h, thx, thz;
    color_t surface, bottom, top;
} cone_t;

void cone(const cone_t specs);
#endif