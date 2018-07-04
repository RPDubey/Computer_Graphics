/*
 *@Filename: CSCIx229.h
 *@brief: Some common generic functions
 *@author:Implemented by professor Schreuder
 *@date:06/29/2018
 */

#ifndef CSCIx229
#define CSCIx229

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926 / 180 * (th))
#define Sin(th) sin(3.1415926 / 180 * (th))

#ifdef __cplusplus
extern "C" {
#endif

void Fatal(const char *format, ...);
unsigned int LoadTexBMP(const char *file);
void ErrCheck(const char *where);
int LoadOBJ(const char *file);

#ifdef __cplusplus
}
#endif

#endif
