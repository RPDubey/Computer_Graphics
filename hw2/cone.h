#ifndef CONE_H
#define CONE_H

#include "common.h"

typedef struct
{
    double x, y, z, H, R, h, thx, thz;
    color_t surface, bottom, top;
} cone_t;

void cone(const cone_t specs);
#endif