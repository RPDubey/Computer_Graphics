/*
*@Filename: display.c
*@brief:Implements display function
*certain modifications and additions have been made to professor Schreuder's example 6
*for this code
*@author:Ravi Prakash Dubey
*@date:06/10/2018
*/

#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

//  Globals
extern int th; // Azimuth of view angle
extern int ph; // Elevation of view angle

//lorenz parameters
extern double s;
extern double b;
extern double r;

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192 // Maximum length of text string
void Print(const char *format, ...)
{
    char buf[LEN];
    char *ch = buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args, format);
    vsnprintf(buf, LEN, format, args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

/*
 *  Display the scene
 */
void display()
{
    //  Clear the image
    glClear(GL_COLOR_BUFFER_BIT);
    //  Reset previous transforms
    glLoadIdentity();
    //  Set view angle
    glRotated(ph, 1, 0, 0);
    glRotated(th, 0, 1, 0);

    // Create the objects - Lorentz curve
    glBegin(GL_LINE_STRIP);

    double dx = 0.0;
    double dy = 0.0;
    double dz = 0.0;

    double x = 1.0;
    double y = 1.0;
    double z = 1.0;

    double scale = 0.0;     //scaling factor, to limit max size to 1
    double dt = 0.001;      //Time Step = 1 ms
    double point[50000][3]; // array to store points to be plotted

    //integrate over 50,000 steps to cover 50 secs.
    for (int i = 0; i < 50000; i++)
    {
        dx = s * (y - x) * dt;
        dy = (x * (r - z) - y) * dt;
        dz = (x * y - b * z) * dt;
        x += dx;
        y += dy;
        z += dz;

        point[i][0] = x;
        point[i][1] = y;
        point[i][2] = z;

        //find the maximum coordinate
        scale = x > scale ? x : scale;
        scale = y > scale ? y : scale;
        scale = z > scale ? z : scale;
    }

    double col = 0.0;              // for color calculation
    scale = scale < 1 ? 1 : scale; // scaling only if it exceeds 1

    for (int i = 0; i < 50000; i++)
    {
        //initial points are reddish, later points are greenish
        col = (double)i / 50000.0;
        glColor3d(1 - col, col, 0.0);
        glVertex4d(point[i][0],
                   point[i][1],
                   point[i][2],
                   scale);
    }

    glEnd();
    //  Draw axes in white
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(1, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 1, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 1);
    glEnd();
    //  Label axes
    glRasterPos3d(1, 0, 0);
    Print("X");
    glRasterPos3d(0, 1, 0);
    Print("Y");
    glRasterPos3d(0, 0, 1);
    Print("Z");
    //  Display parameters
    glWindowPos2i(5, 5);
    Print("View Angle=%d,%d  s=%.2f, b=%.2f, r=%.2f ", th, ph, s, b, r);
    glFlush();
    glutSwapBuffers();
}
