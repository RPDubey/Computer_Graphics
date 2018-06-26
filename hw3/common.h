/*
*@Filename: common.h
*@brief:contains some common definitions
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#ifndef COMMON_H
#define COMMON_H

#include <math.h>
//  Cosine and Sine in degrees
#define COS(x) (cos((x)*3.1415927 / 180))
#define SIN(x) (sin((x)*3.1415927 / 180))

#define WSTEP (.25)
#define FOV (55)
#define DIM (8)
#define NUMBER_OF_OBJET (7)

//some standard colors
#define BROWN ((color_t){.32, .24, .12, 1})
#define YELLOW ((color_t){1, 1, 0, 1})
#define CYAN ((color_t){0, 1, 1, 1})
#define MAGENTA ((color_t){1, 0, 1, 1})
#define RED ((color_t){1, 0, 0, 1})
#define GREEN ((color_t){0, 1, 0, 1})
#define BLUE ((color_t){0, 0, 1, 1})
#define WHITE ((color_t){1, 1, 1, 1})
#define BLACK ((color_t){0, 0, 0, 1})
#define OFWHITE ((color_t){1, 1, .94, 1})

//structure for color
typedef struct
{
    double r, g, b, a;
} color_t;

typedef struct
{
    float shininess;
    color_t specular, emission;
} material_t;
#endif
