/*
*@Filename: display.c
*@brief:Implements display function
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/10/2018
*/

#include "CSCIx229.h"
#include "display.h"
#include "cube.h"
#include "common.h"
#include "cylinder.h"
#include "sphere.h"
#include "cone.h"
#include "objects.h"
#include "final.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define LEN 8192 // Maximum length of text string

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
double Ez1 = 0;

double Cx = 0;
double Cy = 0;
double Cz = 0;

extern int obj;
extern int light;
extern int rot;
extern int roty;
int local = 0;
int side = 0;

double distance = 1.4 * DIM;

extern int emission;  // Emission intensity (%)
extern int ambient;   // Ambient intensity (%)
extern int diffuse;   // Diffuse intensity (%)
extern int specular;  // Specular intensity (%)
extern int shininess; // Shininess (power of two)
extern float shiny;   // Shininess (value)
double at0 = 1;
double at1 = 1;
double at2 = 0;
extern unsigned int texture[NUMBER_OF_TEXTURE]; //  Texture names
extern float rep;
extern float sco;

const room_dim_t room = {LENGTH, BREATH, HEIGHT};

#ifdef PARTICLE
double p[3] = {0, 0, 0};

double thyx = 10;
double thxz = 90;
double delx;
double dely;
double delz;

double le = 30;
double br = 30;
double he = 30;
double rad = 2;

#endif

static float lb_pos[] = {-48, 39, -60, 1}; //night light position for spotlight

// material_t stdmat;
void Print(const char *format, ...);
int trans = 0;
/*
 *  Display the scene
 */

void display()
{

    ErrCheck("display1");

    //  Clear the image, depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //enable Z buffering
    glEnable(GL_DEPTH_TEST);
    //  Reset previous transforms
    glLoadIdentity();

    // stdmat = {shiny, WHITE, BLACK};
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

    else if (mode == 2) //first person perspective
    {
        //up vector is constant in y direction
        gluLookAt(Ex1, Ey1, Ez1, Cx, Cy, Cz, 0, 1, 0);
    }
    /*********************Light***********************/
#endif
    //Flat or smooth(calculate color for each vertex and interpolate) shading
    glShadeModel(GL_SMOOTH);

    ErrCheck("display2");

    if (light)
    {
        //position of the light source
        float pos[] = {distance * SIN(rot) * COS(roty), distance * SIN(roty), distance * COS(rot) * COS(roty), 1};

        //draw the ball representing light source
        glColor3f(1, 1, 1);
        material_t mat = {shiny, YELLOW, YELLOW};
        ball(pos[0], pos[1], pos[2], 1, YELLOW, mat);

        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);
        //  Two sided mode
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, side);

        //  glColor sets ambient and diffuse color materials
        //Ambient & diffuse material properties of front & back track the current color
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL); //apply color to the material described on color call
        // float yellow[] = {1.0, 1.0, 0, 1.0};
        // //  Set specular colors
        // glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
        // glMaterialf(GL_FRONT, GL_SHININESS, shiny);
        //  Enable light 0
        glEnable(GL_LIGHT0);

        //  Translate intensity to color vectors
        float Ambient[] = {0.01 * ambient, 0.01 * ambient, 0.01 * ambient, 1.0};
        float Diffuse[] = {0.01 * diffuse, 0.01 * diffuse, 0.01 * diffuse, 1.0};
        float Specular[] = {0.01 * specular, 0.01 * specular, 0.01 * specular, 1.0};
        glColor3f(1, 1, 1); //color for light
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);

        //  Set spotlight parameters
        // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Direction);
        // glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, sco);
        // glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Exp);

        //  Set attenuation
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, at0 / 100.0);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, at1 / 100.0);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, at2 / 100.0);
    }
    else if (!light)
    {
        ambient = 0;
        diffuse = 100;
        specular = 0;
        local = 1;

        //draw the ball representing light source
        glColor3f(1, 1, 1);
        material_t mat = {shiny, YELLOW, YELLOW};
        ball(lb_pos[0], lb_pos[1], lb_pos[2], 1, YELLOW, mat);

        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);
        //  Two sided mode
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, side);

        //  glColor sets ambient and diffuse color materials
        //Ambient & diffuse material properties of front & back track the current color
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL); //apply color to the material described on color call

        //  Enable light 1
        glEnable(GL_LIGHT0);

        //  Translate intensity to color vectors
        float Ambient[] = {0.01 * ambient, 0.01 * ambient, 0.01 * ambient, 1.0};
        float Diffuse[] = {0.01 * diffuse, 0.01 * diffuse, 0.01 * diffuse, 1.0};
        float Specular[] = {0.01 * specular, 0.01 * specular, 0.01 * specular, 1.0};
        glColor3f(1, 1, 1); //color for light
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
        glLightfv(GL_LIGHT0, GL_POSITION, lb_pos);

        float Exp = 1; //  Spot exponent
        float Direction[] = {-COS(10), -SIN(10), 0, 0};

        //        Set spotlight parameters
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Direction);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, sco);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Exp);

        //  Set attenuation
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, at0 / 100.0);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, at1 / 100.0);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, at2 / 100.0);
    }
    ErrCheck("display3");

    /*********************Draw objects***********************/

    //Enable texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //draw the entire scene
    if (obj == 0)
    {
        trans = 0;
        // glPushMatrix();

        material_t stdmat = {shiny, WHITE, BLACK};

        glPushMatrix();
        glTranslated(-65, 0, 0);
        glRotated(90, 0, 1, 0);
        glScaled(.7, 0.7, .7);
        Cupboard(cupboard);
        glPopMatrix();

        glPushMatrix();
        glTranslated(30, 4, -60);
        glScaled(.5, .5, .5);
        Chair(chair_specs);
        glPopMatrix();

        glPushMatrix();
        glTranslated(60, 4, -30);
        glRotated(-90, 0, 1, 0);
        glScaled(.5, .5, .5);
        Chair(chair_specs);
        glPopMatrix();

        glPushMatrix();
        glTranslated(65, 0, 0);
        glRotated(0, 0, 0, 0);
        glScaled(.5, 0.5, 0.5);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        Plant(pl);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0, 0, -65);
        glRotated(0, 0, 0, 0);
        glScaled(.5, 0.6, 0.5);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        Plant(pl);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-73, 30, -60);
        glRotated(90, 0, 1, 0);
        glScaled(.25, .25, 1);
        Potrait(100, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-33, 1, -60);
        glRotated(-90, 0, 1, 0);
        glScaled(.6, 0.7, 0.6);
        Lamp(lamp);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0, 0, 75.6);
        // glRotated(-90, 0, 1, 0);
        glScaled(1, 1, 1);
        Door(door);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0, 0, 74.4);
        glRotated(180, 0, 1, 0);
        glScaled(1, 1, 1);
        Door(door);
        glPopMatrix();

        // draw objects with transparent parts.FIrst iteration, solid, 2nd transparent
        for (trans = 0; trans < 2; trans++)
        {
            glPushMatrix();
            glTranslated(30, 0, -40);
            glRotated(180, 0, 1, 0);
            glScaled(1, 1, 1);
            Table(table);
            glPopMatrix();

            glPushMatrix();
            Building(building);
            glPopMatrix();
        }

        // glPopMatrix();
        ErrCheck("display4");
    }

    //draw the individual elements

    //building
    if (obj == 1)
    {
        trans = 0;
        Building(building);
        trans = 1;
        Building(building);
    }

    if (obj == 2) //cupboard
    {
        trans = 0;
        Cupboard(cupboard);
    }

    if (obj == 3) // chair
    {
        trans = 0;
        Chair(chair_specs);
    }

    if (obj == 4) //table
    {
        trans = 0;
        Table(table);
        trans = 1;
        Table(table);
    }

    if (obj == 5) //potted plant
    {
        trans = 0;
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        Plant(pl);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
    }

    if (obj == 6) //Table lamp
    {

        Lamp(lamp);
    }

    if (obj == 7) //potrait //text
    {
#ifdef PARTICLE
        //emissive sphere
        color_t col = {1, 1, 0, 1};
        material_t mat = {8, {0, 0, 0, 0}, {1, 0, 0, 1}};
        ball(p[0], p[1], p[2], rad, col, mat);
        material_t stdmat = {shiny, WHITE, BLACK};

        //box
        glBindTexture(GL_TEXTURE_2D, texture[4]);
        ENABLE_TRANSPARENCY
        glPushMatrix();
        glTranslated(0, 0, 0);
        glRotated(0, 0, 0, 0);
        glScaled(le, br, he);
        unitcube(stdmat);
        glPopMatrix();
        glDisable(GL_BLEND);
        glDepthMask(1);
#endif
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    ErrCheck("display5");

    //particle system
    //night mode

    //  Switch off textures so it doesn't apply to the axis

    /**********************draw axes****************************/
    if (axes != 0)
    {
        glDisable(GL_DEPTH_TEST); //see axes through the objects
        //  Draw axes in white
        glColor3f(1.0, 1.0, 1.0);
        // double l = 4;
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
    ErrCheck("display6");

    //  Display parameters
    glWindowPos2i(5, 5);
    glColor3f(1.0, 1.0, 1.0);

    Print("View Angle=%d,%d, z=%d, mode=%d, dim=%.2f, fov=%d", th, ph, axes, mode, dim, fov);
    if (mode == 2)
        Print(", Eye Position (%.2f,%.2f,%.2f)", Ex1, Ey1, Ez1);

    if (1)
    {
        glWindowPos2i(5, 65);
        Print("thyx=%.2f,thxz=%.2f", thyx, thxz);
        glWindowPos2i(5, 45);
        Print("LocalViewer=%d Distance=%.2f Azimuth=%d, Elevation=%d rep =%.2f", local, distance, rot, roty, rep);
        glWindowPos2i(5, 25);
        Print("Ambient=%d, Diffuse=%d, Specular=%d, Emission=%d, Shininess=%d", ambient, diffuse, specular, emission, shininess);
    }

    glFlush();
    glutSwapBuffers();

    ErrCheck("display");
    ErrCheck("displayF");
}

void Print(const char *format, ...)
{
    glColor3f(1, 1, 1);
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

    ErrCheck("Print");
}
