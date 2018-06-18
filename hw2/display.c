/*
*@Filename: display.c
*@brief:Implements display function
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/10/2018
*/

#include "display.h"
#include "cube.h"
#include "common.h"
#include "cylinder.h"
#include "sphere.h"
#include "cone.h"
#include "objects.h"
#include "hw2.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

//  Globals
extern int th;   // Azimuth of view angle
extern int ph;   // Elevation of view angle
extern int axes; //axes options

extern double dim; // Dimensions of orthogonal box
extern double asp; //aspect ration
extern int mode;   //orthogonal,perspective,first person
extern int fov;    // field of view

extern double dx;
extern double dy;
extern double dz;

double Ex1 = 0;
double Ey1 = 0;
double Ez1 = DIM;

double Cx = 0;
double Cy = 0;
double Cz = DIM - 1;

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
    //  Clear the image, depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //enable Z buffering
    glEnable(GL_DEPTH_TEST);
    //  Reset previous transforms
    glLoadIdentity();

    if (mode == 0) //orthogonal
    {
        glRotatef(ph, 1, 0, 0);
        glRotatef(th, 0, 1, 0);
    }

    else if (mode == 1) //perspective
    {
        double Ex = -2 * dim * SIN(th) * COS(ph);
        double Ey = +2 * dim * SIN(ph);
        double Ez = +2 * dim * COS(th) * COS(ph);

        gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, COS(ph), 0);
    }
    //  Orthogonal - set world orientation

    else if (mode == 2) //first person perspective
    {
        //up vector is constant in y direction
        gluLookAt(Ex1, Ey1, Ez1, Cx, Cy, Cz, 0, 1, 0);
    }
    /*********************Draw objects***********************/

    //Table1
    glPushMatrix();
    glTranslated(4, 0, -3);
    glRotated(90, 0, 1, 0);
    table(table_specs);
    glPopMatrix();

    // //chair1
    glPushMatrix();
    glTranslated(2, -.3, -3.3);
    glRotated(90, 0, 1, 0);
    glScaled(1.2, 1.2, 1.2);
    chair(chair_specs);
    glPopMatrix();

    //Table 2
    glPushMatrix();
    glTranslated(4, 0, 3);
    glRotated(90, 0, 1, 0);
    table(table_specs);
    glPopMatrix();

    //chair 2
    glPushMatrix();
    glTranslated(2, -.3, 2.7);
    glRotated(90, 0, 1, 0);
    glScaled(1.2, 1.2, 1.2);
    chair(chair_specs);
    glPopMatrix();

    //Table 3
    glPushMatrix();
    glTranslated(4, 0, 0);
    glRotated(90, 0, 1, 0);
    table(table_specs);
    glPopMatrix();

    //chair 3
    glPushMatrix();
    glTranslated(2, -.3, -.3);
    glRotated(90, 0, 1, 0);
    glScaled(1.2, 1.2, 1.2);
    chair(chair_specs);
    glPopMatrix();

    //lamp 1
    glPushMatrix();
    glTranslated(-4, -.1, 3);
    glScaled(1.5, 1.5, 1.5);
    lamp(lamp_specs);
    glPopMatrix();

    //lamp 2
    glPushMatrix();
    glTranslated(-4, -.1, 0);
    glScaled(1.5, 1.5, 1.5);
    lamp(lamp_specs);
    glPopMatrix();

    //lamp 3
    glPushMatrix();
    glTranslated(-4, -.1, -3);
    glScaled(1.5, 1.5, 1.5);
    lamp(lamp_specs);
    glPopMatrix();

    //cone - plant pot 1
    glPushMatrix();
    glTranslated(-4, -.5, -2);
    glScaled(.8, .8, .8);
    cone_t con = {0, 0, 0, 0, 1, .5, .6, 180, 0, RED, MB, BLUE};
    cone(con);
    glPopMatrix();

    //cone - plant pot 2
    glPushMatrix();
    glTranslated(-4, -.5, 2);
    glScaled(.8, .8, .8);
    cone_t con1 = {0, 0, 0, 0, 1, .5, .6, 180, 0, RED, MB, BLUE};
    cone(con1);
    glPopMatrix();

    //decorative cylinder+sphere+cone 1
    //    cylinder
    cylinder_t cyl5 = {1, -4, -.5, 4.5, .25, .5, 0, 0, {RED, GREEN, RED}};
    cylinder(cyl5);
    //sphere
    sphere_t sph5 = {1, -4, .25, 4.5, .25, -90, 90, BLUE};
    sphere(sph5);
    //cone
    cone_t con5 = {1, -4, 1, 4.5, .5, .5, .6, 180, 0, RED, YELLOW, RED};
    cone(con5);

    //decorative cylinder+sphere+cone 2
    //    cylinder
    cylinder_t cyl6 = {1, -4, -.5, -4.5, .25, .5, 0, 0, {RED, GREEN, RED}};
    cylinder(cyl6);
    //sphere
    sphere_t sph6 = {1, -4, .25, -4.5, .25, -90, 90, BLUE};
    sphere(sph6);
    //cone
    cone_t con6 = {1, -4, 1, -4.5, .5, .5, .6, 180, 0, RED, YELLOW, RED};
    cone(con6);

    //draw axes
    if (axes != 0)
    {
        glDisable(GL_DEPTH_TEST); //see axes through the objects
        //  Draw axes in white
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(dim / 2, 0, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, dim / 2, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, dim / 2);
        glEnd();
        //  Label axes
        glRasterPos3d(dim / 2, 0, 0);
        Print("X");
        glRasterPos3d(0, dim / 2, 0);
        Print("Y");
        glRasterPos3d(0, 0, dim / 2);
        Print("Z");
    }

    //  Display parameters
    glWindowPos2i(5, 5);
    glColor3f(1.0, 1.0, 1.0);

    Print("View Angle=%d,%d, z=%d, mode=%d, dim=%.2f, fov=%d", th, ph, axes, mode, dim, fov);
    if (mode == 2)
        Print(", Eye Position (%.2f,%.2f,%.2f)", Ex1, Ey1, Ez1);
    glFlush();
    glutSwapBuffers();
}
