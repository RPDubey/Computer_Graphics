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
#include "hw3.h"

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

extern int obj;
extern int light;
extern int rot;
extern int roty;
int local = 0;
double distance = 8;

extern int emission;  // Emission intensity (%)
extern int ambient;   // Ambient intensity (%)
extern int diffuse;   // Diffuse intensity (%)
extern int specular;  // Specular intensity (%)
extern int shininess; // Shininess (power of two)
extern float shiny;   // Shininess (value)

extern unsigned int texture[NUMBER_OF_OBJET + 4]; //  Texture names
extern float rep;

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

#ifdef PERSPECTIVE
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
    /*********************Light***********************/
#endif
    //Flat or smooth(calculate color for each vertex and interpolate) shading
    glShadeModel(GL_SMOOTH);

    if (light)
    {
        //draw the ball representing light source

        glColor3f(1, 1, 1);
        //position of the light source
        float pos[] = {distance * SIN(rot) * COS(roty), distance * SIN(roty), distance * COS(rot) * COS(roty), 1};

        material_t mat = {shiny, YELLOW, {0.0, 0.0, 0.01 * emission, 1.0}};
        ball(pos[0], pos[1], pos[2], .2, WHITE, mat);

        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);

        //  glColor sets ambient and diffuse color materials
        //Ambient & diffuse material properties of front & back track the current color
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL); //apply color to the material described on color call

        //  Enable light 0
        glEnable(GL_LIGHT0);

        //  Translate intensity to color vectors
        float Ambient[] = {0.01 * ambient, 0.01 * ambient, 0.01 * ambient, 1.0};
        float Diffuse[] = {0.01 * diffuse, 0.01 * diffuse, 0.01 * diffuse, 1.0};
        float Specular[] = {0.01 * specular, 0.01 * specular, 0.01 * specular, 1.0};

        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
    }

    /*********************Draw objects***********************/

    //texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // glDisable(GL_TEXTURE_2D);

    //draw the entire scene
    if (obj == 0)
    {

        material_t stdmat = {shiny, WHITE, BLACK};

        glPushMatrix();

        /**********floor************/
        floortile();

        /**********Model of Leaf************/
        glPushMatrix();
        glTranslated(-3, 0, -4);
        glScaled(.5, .5, .5);
        leaf();
        glPopMatrix();

        /**********Plant Pot************/
        glPushMatrix();
        glTranslated(3, 1, -4);
        glRotated(180, 1, 0, 0);
        glScaled(1, 2, 1);
        glBindTexture(GL_TEXTURE_2D, texture[9]);
        cone((cone_t){4, 0, 0, 0, 1, 1, .5, 0, 0, WHITE, WHITE, BLACK, stdmat});
        glPopMatrix();

        /**********Model of earth resting on cone************/
        glTranslated(-3, 0, 4);
        glBindTexture(GL_TEXTURE_2D, texture[4]);
        unitcone(stdmat);

        glPushMatrix();
        glTranslated(0, 2, 0);
        glRotated(60, 0, 1, 0);
        glBindTexture(GL_TEXTURE_2D, texture[7]);
        material_t mat = {shiny, YELLOW, {0.0, 0.0, 0.01 * emission, 1.0}};
        unitsphere(mat);
        glPopMatrix();
        glPopMatrix();

        /**********Mona Lisa on a Crate************/
        glPushMatrix();

        glTranslated(3, 0, 4);
        glScaled(.5, .5, .5);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[6]);
        glTranslated(0, 1, 0);
        glScaled(2, 1, 1);
        unitcube(stdmat);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0, 4, 0);
        potrait();
        glPopMatrix();

        glPopMatrix();

        /**********CU Logo on Cylinder************/
        glPushMatrix();
        glScaled(1.25, 1.25, 1.25);
        glTranslated(0, 1, 0);
        glPushMatrix();
        glRotated(140, 0, 1, 0);
        glBindTexture(GL_TEXTURE_2D, texture[5]);
        unitcylinder(stdmat);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1, 2.8, 0);
        glRotated(90, 1, 0, 0);
        glScaled(.25, .25, .25);
        logo();
        glPopMatrix();

        glPopMatrix();
    }

    //draw the individual elements

    if (obj == 1)
    {
        glBindTexture(GL_TEXTURE_2D, texture[7]);
        material_t mat = {shiny, YELLOW, {0.0, 0.0, 0.01 * emission, 1.0}};
        unitsphere(mat);
    }
    if (obj == 2)
    {
        glBindTexture(GL_TEXTURE_2D, texture[6]);
        material_t stdmat = {shiny, YELLOW, BLACK};
        unitcube(stdmat);
    }

    if (obj == 3)
    {
        glBindTexture(GL_TEXTURE_2D, texture[5]);
        material_t stdmat = {shiny, WHITE, BLACK};
        unitcylinder(stdmat);
    }

    if (obj == 4)
    {
        glBindTexture(GL_TEXTURE_2D, texture[4]);
        material_t stdmat = {shiny, WHITE, BLACK};
        unitcone(stdmat);
    }

    if (obj == 5)
    {
        glPushMatrix();
        leaf();
        glPopMatrix();
    }

    if (obj == 6)
    {
        glPushMatrix();
        glScaled(.5, .5, .5);
        logo();
        glPopMatrix();
    }

    if (obj == 7)
    {
        potrait();
    }
    glDisable(GL_TEXTURE_2D);

    //  Switch off textures so it doesn't apply to the axis

    /**********************draw axes****************************/
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

    if (light)
    {
        glWindowPos2i(5, 45);
        Print("LocalViewer=%d Distance=%.2f Azimuth=%d, Elevation=%d rep =%.2f", local, distance, rot, roty, rep);
        glWindowPos2i(5, 25);
        Print("Ambient=%d, Diffuse=%d, Specular=%d, Emission=%d, Shininess=%d", ambient, diffuse, specular, emission, shininess);
    }

    glFlush();
    glutSwapBuffers();
}
