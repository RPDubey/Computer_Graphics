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
#include "project.h"

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
double distance = 1.4 * DIM;

extern int emission;  // Emission intensity (%)
extern int ambient;   // Ambient intensity (%)
extern int diffuse;   // Diffuse intensity (%)
extern int specular;  // Specular intensity (%)
extern int shininess; // Shininess (power of two)
extern float shiny;   // Shininess (value)

extern unsigned int texture[NUMBER_OF_TEXTURE]; //  Texture names
extern float rep;

room_dim_t room = {.75 * DIM, .75 * DIM, .5 * DIM};
// material_t stdmat;
void Print(const char *format, ...);

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

    if (light)
    {
        //draw the ball representing light source

        glColor3f(1, 1, 1);
        //position of the light source
        float pos[] = {distance * SIN(rot) * COS(roty), distance * SIN(roty), distance * COS(rot) * COS(roty), 1};

        material_t mat = {shiny, YELLOW, YELLOW};
        ball(pos[0], pos[1], pos[2], 2, YELLOW, mat);

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
        glColor3f(1, 1, 1); //color for light
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
        glBindTexture(GL_TEXTURE_2D, texture[8]);
        //Quad(dim, dim, WHITE);

        /**********Model of Leaf************/
        glPushMatrix();
        glTranslated(-3, 0, -4);
        glScaled(.5, .5, .5);
        // leaf();
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

    //building
    if (obj == 1)
    {

        quadr_t building[6] =
            {
                //floor
                {
                    {{-room.b, 0, room.l},
                     {room.b, 0, room.l},
                     {room.b, 0, -room.l},
                     {-room.b, 0, -room.l}},
                    WHITE,
                    16,
                    1,
                    {0, 1, 0}},
                //left Wall
                {
                    {{-room.b, 0, -room.l},
                     {-room.b, 0, room.l},
                     {-room.b, room.h, room.l},
                     {-room.b, room.h, -room.l}},
                    (color_t){1, 1, 1, .4},
                    4,
                    1,
                    {-1, 0, 0}},
                //right wall
                {
                    {{room.b, 0, room.l},
                     {room.b, 0, -room.l},
                     {room.b, room.h, -room.l},
                     {room.b, room.h, room.l}},
                    (color_t){1, 1, 1, .4},
                    4,
                    1,
                    {1, 0, 0}},
                //back wall
                {{{room.b, 0, -room.l},
                  {-room.b, 0, -room.l},
                  {-room.b, room.h, -room.l},
                  {room.b, room.h, -room.l}},
                 (color_t){1, 1, 1, .4},
                 4,
                 1,
                 {0, 0, -1}},
                //front wall
                {
                    {{room.b, 0, room.l},
                     {-room.b, 0, room.l},
                     {-room.b, room.h, room.l},
                     {room.b, room.h, room.l}},
                    (color_t){1, 1, 1, .4},
                    4,
                    1,
                    {0, 0, 1}},
                //roof
                {
                    {{-room.b, room.h, room.l},
                     {room.b, room.h, room.l},
                     {room.b, room.h, -room.l},
                     {-room.b, room.h, -room.l}},
                    (color_t){1, 1, 1, .2},
                    8,
                    1,
                    {0, 1, 0}}};

        glBindTexture(GL_TEXTURE_2D, texture[8]);
        Quad(building[0]);
        ENABLE_TRANSPARENCY
        glBindTexture(GL_TEXTURE_2D, texture[10]);
        Quad(building[1]);
        Quad(building[2]);
        Quad(building[3]);
        Quad(building[4]);
        glBindTexture(GL_TEXTURE_2D, texture[11]);
        Quad(building[5]);
        glDisable(GL_BLEND);
        glDepthMask(1);
    }

    if (obj == 2) //cupboard
    {

        transform_t cbd[6] =
            {
                {{0, 1, 0}, {90, 0, 0, 0}, {20, 1, 10}},
                {{-19, 32, 0}, {90, 0, 0, 1}, {30, 1, 10}},
                {{19, 32, 0}, {90, 0, 0, 1}, {30, 1, 10}},
                {{0, 63, 0}, {90, 0, 0, 0}, {20, 1, 10}},
                {{0, 21, 0}, {90, 0, 0, 0}, {20, 1, 10}},
                {{0, 42, 0}, {90, 0, 0, 0}, {20, 1, 10}},
            };
        glBindTexture(GL_TEXTURE_2D, texture[12]);

        material_t stdmat = {shiny, WHITE, BLACK};
        for (int i = 0; i < 6; i++)
        {
            glPushMatrix();
            glTranslated(cbd[i].t[0], cbd[i].t[1], cbd[i].t[2]);
            glRotated(cbd[i].r[0], cbd[i].r[1], cbd[i].r[2], cbd[i].r[3]);
            glScaled(cbd[i].s[0], cbd[i].s[1], cbd[i].s[2]);
            unitcube(stdmat);
            glPopMatrix();
        }

        glPushMatrix();
        quadr_t back[4] = {
            {{{-20, 0, -10},
              {20, 0, -10},
              {20, 63, -10},
              {-20, 63, -10}},
             WHITE,
             1,
             0,
             {0, 0, 1}},
            {{{-20, 0, 7},
              {20, 0, 7},
              {20, 17, 7},
              {-20, 17, 7}},
             WHITE,
             1,
             0,
             {0, 0, 1}},
            {{{-20, 22, 7},
              {20, 22, 7},
              {20, 38, 7},
              {-20, 38, 7}},
             WHITE,
             1,
             0,
             {0, 0, 1}},
            {{{-20, 43, 7},
              {20, 43, 7},
              {20, 58, 7},
              {-20, 58, 7}},
             WHITE,
             1,
             0,
             {0, 0, 1}}};

        for (int i = 0; i < 4; i++)
        {
            glBindTexture(GL_TEXTURE_2D, texture[12 + i]);
            Quad(back[i]);
        }

        glPopMatrix();
    }

    if (obj == 3) // chair
    {

        //chair
        chair_t specs = {
            //cylinder
            {
                {{-14, 12, 0}, {90, 1, 0, 0}, {3, 8, 2}},
                {{14, 12, 0}, {90, 1, 0, 0}, {3, 8, 2}},
                {{0, 30, -15}, {90, 0, 0, 1}, {3, 16, 3}},
                {{-12, -2, 6}, {0, 0, 0, 0}, {1, 2, 1}},
                {{12, -2, 6}, {0, 0, 0, 0}, {1, 2, 1}},
                {{-12, -2, -6}, {0, 0, 0, 0}, {1, 2, 1}},
                {{12, -2, -6}, {0, 0, 0, 0}, {1, 2, 1}},

            },
            //cube
            {
                {{0, 2, 0}, {90, 0, 0, 0}, {12, 2, 8}},
                {{14, 6, 0}, {90, 0, 0, 1}, {6, 2, 8}},
                {{-14, 6, 0}, {90, 0, 0, 1}, {6, 2, 8}},
                {{0, 10, -10}, {90, 1, 0, 0}, {16, 2, 10}}

            },
            {{0, 20, -10}, {0, 0, 0, 0}, {1, 1, 1}},
            {16, 16, 12, 45, WHITE, 1}

        };
        chair(specs);
    }

    if (obj == 4) //table
    {

        //stand
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[12]);
        material_t stdmat = {shiny, WHITE, BLACK};

        curve_t stand = {4, 10, 8, 180, {1, 1, 1, .2}, 1};
        Curve(stand);
        unitcone(stdmat);
        glPopMatrix();

        ENABLE_TRANSPARENCY;
        //transparent
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[17]);
        glTranslated(0, 10.5, -10);
        glRotated(180, 0, 0, 0);
        glScaled(20, 1, 20);
        unitcylinder(stdmat);
        glPopMatrix();
        glDisable(GL_BLEND);
        glDepthMask(1);
    }

    if (obj == 5) //potted plant
    {

        leaf_t l[10] =
            {
                {15, 1.2, {80, 1, 0, 0}, {{0, 0, 0}, {0, 0, 1, 0}, {7, 7, 7}}},
                {15, 1.2, {60, 1, 0, 0}, {{0, 1, 0}, {90, 0, 1, 0}, {7, 7, 7}}},
                {15, 1.2, {60, 1, 0, 0}, {{0, 3, 0}, {180, 0, 1, 0}, {6, 6, 6}}},
                {15, 1.2, {60, 1, 0, 0}, {{0, 6, 0}, {300, 0, 1, 0}, {6, 6, 6}}},

                {10, 1.2, {50, 1, 0, 0}, {{0, 8, 0}, {-10, 0, 1, 0}, {5, 5, 5}}},
                {10, 1.2, {40, 1, 0, 0}, {{0, 13, 0}, {70, 0, 1, 0}, {4, 4, 4}}},
                {10, 1.2, {30, 1, 0, 0}, {{0, 16, 0}, {160, 0, 1, 0}, {4, 4, 4}}},
                {10, 1.2, {30, 1, 0, 0}, {{0, 19, 0}, {270, 0, 1, 0}, {3, 3, 3}}},

                {8, 1.5, {20, 1, 0, 0}, {{0, 40, 0}, {100, 0, 1, 0}, {.5, .5, .5}}},
                {8, 1.5, {20, 1, 0, 0}, {{0, 40, 0}, {280, 0, 1, 0}, {.5, .5, .5}}},

            };

        plant_t pl =
            {
                3, 18, 9, 19, 10, l, {4, 0, 0, 0, 1, 1, .5, 0, 0, WHITE, WHITE, BLACK, {shiny, WHITE, BLACK}}, {{0, 10, 0}, {0, 0, 0, 0}, {.6, 10, .6}}, {{0, 0, 0}, {180, 1, 0, 0}, {15, 30, 15}}, {{0, 0, 0}, {0, 0, 0, 0}, {15, .5, 15}}};

        Plant(pl);
    }

    if (obj == 6) //Table lamp
    {
        material_t stdmat = {shiny, WHITE, BLACK};

        glPushMatrix();

        unitcylinder(stdmat);

        glPopMatrix();
    }

    if (obj == 7) //potrait //text
    {

        glPushMatrix();
        logo();
        glPopMatrix();

        potrait();
    }
    glDisable(GL_TEXTURE_2D);

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
}
