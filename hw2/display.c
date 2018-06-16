/*
*@Filename: display.c
*@brief:Implements display function
*certain modifications and additions have been made to professor Schreuder's example 6
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

//lorenz parameters
extern double s;
extern double b;
extern double r;

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192 // Maximum length of text string
// const cube_color_t cube_OFWHITE = {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE};
// const cube_color_t cube_BLUE = {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE};

static cube_t table_desc[9] = {
    {1, 0, 0, 0, 1, .04, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}},
    {2, -.96, -.48 - .04, 0, 0.04, .48, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}}, //leftmost white
    {3, .96, -.17, 0, 0.04, .13, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}},        //left white
    {4, -.56, -0.48 - .04, 0, 0.04, .48, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}},
    {5, -.76, -0.14, 0, .15, .09, 1, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}},
    {6, -.76, -0.63, 0, .15, .37, 1, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}},
    {7, .20, -0.14, 0, .71, .09, 1, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}},
    {8, .96, -.65, .96, 0.04, .35, .04, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}}, //right leg
    {9, .96, -.65, -.96, 0.04, .35, .04, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}} //right leg

};

static cube_t chair_cube_desc[8] = {
    {1, 0, 0, 0, .4, .02, .4, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}}, //plank

    {1, .38, -.3, .38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //front right

    {1, -.38, -.3, .38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //front left

    {1, .38, -.3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //back right

    {1, -.38, -.3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //back left

    {1, .38, .3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //brest right

    {1, -.38, .3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //brest left

    {1, 0, .6, -.38, .4, .02, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}} //brest horizontol
};

static cylinder_t chair_cyl_desc[3] =
    {
        {1, 0, .28, -.38, .02, .3, 0, 0, {OFWHITE, OFWHITE, OFWHITE}},

        {1, .2, .28, -.38, .02, .3, 0, 0, {OFWHITE, OFWHITE, OFWHITE}},

        {1, -.2, .28, -.38, .02, .3, 0, 0, {OFWHITE, OFWHITE, OFWHITE}}

};

static const sphere_t chair_sph_desc[2] =
    {
        {1, .38, .65, -.38, .03, -90, 90, RED},
        {1, -.38, .65, -.38, .03, -90, 90, RED}

};

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
    //  Reset previous transforms
    glLoadIdentity();

    //  Set view angle
    glRotated(ph, 1, 0, 0);
    glRotated(th, 0, 1, 0);

    //enable Z buffering
    glEnable(GL_DEPTH_TEST);

    /*********************Draw objects***********************/
    // //cube
    // glPushMatrix();
    // glTranslated(-.5, .5, 0);
    // glScaled(.5, .5, .5);

    // for (int i = 0; i < 9; i++)
    // {
    //     cube(table_desc[i]);
    // }
    // glPopMatrix();

    // //cylinder
    // cylinder_t cyl = {1, .5, .5, 0, 0.25, .25, 0, 0, {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}}};
    // cylinder(cyl);

    // //sphere
    // sphere_t sph = {1, .5, -.5, 0, .5, -90, 90, BLUE};
    // sphere(sph);

    //chair

    // glPushMatrix();
    // glTranslated(-.5, -.5, 0);
    // glScaled(.5, .5, .5);

    // for (int i = 0; i < 8; i++)
    //     cube(chair_cube_desc[i]);
    // for (int i = 0; i < 3; i++)
    //     cylinder(chair_cyl_desc[i]);
    // for (int i = 0; i < 2; i++)
    //     sphere(chair_sph_desc[i]);
    // glPopMatrix();

    //lamp

    glPushMatrix();
    glTranslated(.5, .5, 0);
    //glScaled(.5, .5, .5);

    // cylinder
    cylinder_t cyl = {1, 0, -.6, 0, 0.2, .03, 0, 0, {MB, MB, MB}};
    cylinder(cyl);
    cylinder_t cyl2 = {1, 0, 0, 0, 0.02, .58, 0, 0, {MB, MB, MB}};
    cylinder(cyl2);

    // cylinder_t cyl3 = {1, .23, .38, 0, 0.02, .26, 0, -60, {MB, MB, MB}};
    // cylinder(cyl3);

    //sphere
    sphere_t sph = {1, 0, .83, 0, .25, -90, -10, YELLOW};
    sphere(sph);
    sphere_t sph1 = {1, 0, .66, 0, .08, -90, 90, {1, 1, 0}};
    sphere(sph1);

    glPopMatrix();

    //cone
    cone_t con = {0, 0, 0, .5, .3, .3, 0, 180};
    cone(con);

    if (axes != 0)
    {
        if (axes == 2)
            glDisable(GL_DEPTH_TEST);

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
    }

    //  Display parameters
    glWindowPos2i(5, 5);
    Print("View Angle=%d,%d  s=%.2f, b=%.2f, r=%.2f ", th, ph, s, b, r);
    glFlush();
    glutSwapBuffers();
}
