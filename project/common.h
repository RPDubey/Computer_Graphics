/*
*@Filename: common.h
*@brief:contains some common definitions
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#ifndef COMMON_H
#define COMMON_H

#include "CSCIx229.h"
#include <math.h>
//  Cosine and Sine in degrees
#define COS(x) (cos((x)*3.1415927 / 180))
#define SIN(x) (sin((x)*3.1415927 / 180))
#define PERSPECTIVE
// #define PRODUCTION
#define PARTICLE

#define WSTEP (1.0)
#define FOV (55)
#define DIM (100)
#define NUMBER_OF_OBJET (7)
#define NUMBER_OF_TEXTURE (30)
#define LENGTH 0.75 * DIM
#define BREATH 0.75 * DIM
#define HEIGHT 0.5 * DIM

#define ENABLE_TRANSPARENCY                \
    {                                      \
        glEnable(GL_BLEND);                \
        glBlendFunc(GL_SRC_ALPHA, GL_ONE); \
        glDepthMask(0);                    \
    }

#define setMatPr(spec, emis, shiny)                          \
    {                                                        \
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);  \
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);  \
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny); \
    }

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

//structure for room dimensions
typedef struct
{
    double l, b, h;
} room_dim_t;

//structure describing the wall properties
typedef struct
{
    double vert[4][3];
    color_t col;
    int repeat, offset;
    double norm[3];

} quadr_t;

typedef struct
{
    double l, rb, rs, ang;
    color_t col;
    int repeat;

} curve_t;

typedef struct
{
    float t[3], r[4], s[3];
} transform_t;

#endif
