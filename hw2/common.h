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

//some standard colors
#define YELLOW   \
    {            \
        1, 1, .6 \
    }

#define MB             \
    {                  \
        0.32, .24, .12 \
    }
#define RED     \
    {           \
        1, 0, 0 \
    }

#define GREEN   \
    {           \
        0, 1, 0 \
    }

#define BLUE    \
    {           \
        0, 0, 1 \
    }

#define RNG     \
    {           \
        1, 1, 0 \
    }
#define RNB     \
    {           \
        1, 0, 1 \
    }

#define GNB     \
    {           \
        0, 1, 1 \
    }
#define WHITE   \
    {           \
        1, 1, 1 \
    }
#define BLACK   \
    {           \
        0, 0, 0 \
    }

#define OFWHITE   \
    {             \
        1, 1, .94 \
    }

//structure for color
typedef struct
{
    double r, g, b;
} color_t;

#endif
