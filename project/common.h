/*
*@Filename: common.h
*@brief:contains some common definitions
*@author:Ravi Prakash Dubey
*@date:06/28/2018
*/

#ifndef COMMON_H
#define COMMON_H

#include "CSCIx229.h"
#include <math.h>
//  Cosine and Sine in degrees
#define COS(x) (cos((x)*3.1415927 / 180))
#define SIN(x) (sin((x)*3.1415927 / 180))

#define XPOS -60
#define YPOS 10
#define ZPOS 40
#define BOX_LE 10
#define BOX_BR 10
#define BOX_HE 10

#define PERSPECTIVE
// #define PRODUCTION
#define ORTHOGONAL
#define PARTICLE

#define WSTEP (1.0)
#define FOV (55)
#define DIM (100)
#define NUMBER_OF_OBJET (8)
#define NUMBER_OF_TEXTURE (30)
#define LENGTH 0.75 * DIM
#define BREATH 0.75 * DIM
#define HEIGHT 0.5 * DIM
#define FENCE_HEIGHT (10)
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
extern int fence_view;
/*
// #define DRAW_FENCE(l, b, xof, zof)                                        \
//     {                                                                     \
//         glDisable(GL_DEPTH_TEST);                                         \
//         glDisable(GL_TEXTURE_2D);                                         \
//         glDisable(GL_LIGHTING);                                           \
//         glColor3f(1.0, 1.0, 1.0);                                         \
//         glBegin(GL_LINE_STRIP);                                           \
//         glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(b + zof));  \
//         glVertex3d((double)(l + xof), FENCE_HEIGHT, (double)(b + zof));   \
//         glVertex3d((double)(l + xof), FENCE_HEIGHT, (double)(-b + zof));  \
//         glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(-b + zof)); \
//         glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(b + zof));  \
//         glEnd();                                                          \
//         glEnable(GL_DEPTH_TEST);                                          \
//         glEnable(GL_TEXTURE_2D);                                          \
//         glEnable(GL_LIGHTING);                                            \
//     }

*/

#define DRAW_FENCE(l, b, xof, zof)                                            \
    if (fence_view == 1)                                                      \
    {                                                                         \
        {                                                                     \
            glDisable(GL_DEPTH_TEST);                                         \
            glDisable(GL_TEXTURE_2D);                                         \
            glDisable(GL_LIGHTING);                                           \
            glColor3f(1.0, 1.0, 1.0);                                         \
            glBegin(GL_LINE_STRIP);                                           \
            glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(b + zof));  \
            glVertex3d((double)(l + xof), FENCE_HEIGHT, (double)(b + zof));   \
            glVertex3d((double)(l + xof), FENCE_HEIGHT, (double)(-b + zof));  \
            glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(-b + zof)); \
            glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(b + zof));  \
            glEnd();                                                          \
            glEnable(GL_DEPTH_TEST);                                          \
            glEnable(GL_TEXTURE_2D);                                          \
            glEnable(GL_LIGHTING);                                            \
        }                                                                     \
    }
/*
#define DRAW_FENCE(l, b, xof, zof)                                        \
    {                                                                     \
        glDisable(GL_DEPTH_TEST);                                         \
        glDisable(GL_TEXTURE_2D);                                         \
        glDisable(GL_LIGHTING);                                           \
        glColor3f(1.0, 1.0, 1.0);                                         \
        glBegin(GL_LINE_STRIP);                                           \
        glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(b + zof));  \
        glVertex3d((double)(l + xof), FENCE_HEIGHT, (double)(b + zof));   \
        glVertex3d((double)(l + xof), FENCE_HEIGHT, (double)(-b + zof));  \
        glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(-b + zof)); \
        glVertex3d((double)(-l + xof), FENCE_HEIGHT, (double)(b + zof));  \
        glEnd();                                                          \
        glEnable(GL_DEPTH_TEST);                                          \
        glEnable(GL_TEXTURE_2D);                                          \
        glEnable(GL_LIGHTING);                                            \
    }
*/
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

//some common structures

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

typedef struct
{
    double x, z, xof, zof;
} fence_t;

//enumeration of fenced objects in order
typedef enum
{
    cbrd,
    chair1,
    chair2,
    plant1,
    plant2,
    lmp,
    object,
    tbl,
    bball,
} obj_list;

#endif
