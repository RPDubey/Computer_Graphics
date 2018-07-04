/*
 *@Filename: display.c
 *@brief:Implements display function
 *certain modifications and additions have been made to professor Schreuder's
 *examples for this code
 *@author:Ravi Prakash Dubey
 *@date:06/28/2018
 */

#include "display.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "CSCIx229.h"
#include "common.h"
#include "cone.h"
#include "cube.h"
#include "cylinder.h"
#include "final.h"
#include "objects.h"
#include "sphere.h"
#include "objects.h"

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define LEN 8192 // Maximum length of text string

//  Globals
extern int th;   // Azimuth of view angle
extern int ph;   // Elevation of view angle
extern int axes; // axes options

extern double dim; // Dimensions of orthogonal box
extern double asp; // aspect ration
extern int mode;   // orthogonal,perspective,first person
extern int fov;    // field of view

extern double dx;
extern double dy;
extern double dz;

extern double Ex1;
extern double Ey1;
extern double Ez1;

extern double Cx;
extern double Cy;
extern double Cz;

extern int obj;
extern int light;
extern int rot;
extern int roty;
extern int local;
extern int side;

extern double distance;

extern int emission;  // Emission intensity (%)
extern int ambient;   // Ambient intensity (%)
extern int diffuse;   // Diffuse intensity (%)
extern int specular;  // Specular intensity (%)
extern int shininess; // Shininess (power of two)
extern float shiny;   // Shininess (value)
extern double at0;
extern double at1;
extern double at2;

extern unsigned int texture[NUMBER_OF_TEXTURE]; //  Texture names
extern float rep;
extern float sco;

extern double p[3];       // ball position
extern double box_pos[3]; // transparent box position

extern double unorm[3];
extern double le;
extern double br;
extern double he;
extern double rad;
extern room_dim_t room;
static float lb_pos[] = {-48, 39, -60, 1}; // night light position for
                                           // spotlight

void Print(const char *format, ...);
int trans = 0;
/******object related*****/
float Shinyness[] = {16};
float RGBA[4] = {1, 1, 1, 1}; //  Colors
float Specular[] = {1, 1, 1, 1.0};
float Emission[] = {0.0, 0.0, 0.0, 1.0};
extern int ld_obj;

float fog = 0;
obj_list fence_list;

fence_t fence_co;
fence_t sym_fence[9]; //absolute fencing coordinates of objects symmetric around origin

/*
 *  Display the scene
 */

//translate fencing coordinates. works for 90/180 rot across y only
fence_t translate(const fence_t f, const transform_t tr)
{
  volatile double temp;
  double fenc[4] = {f.x, f.z, f.xof, f.zof};
  fenc[0] *= tr.s[0];
  fenc[2] *= tr.s[0];
  fenc[1] *= tr.s[2];
  fenc[3] *= tr.s[2];

  if (((int)(tr.r[0] == 90) | ((int)tr.r[0] == -90)) && ((int)tr.r[2] == 1))
  {
    temp = fenc[0];
    fenc[0] = fenc[1];
    fenc[1] = temp;

    temp = fenc[2];
    fenc[2] = fenc[3];
    fenc[3] = temp;
  }

  fenc[2] += tr.t[0];
  fenc[3] += tr.t[2];

  return (fence_t){fenc[0], fenc[1], fenc[2], fenc[3]};
};

void display()
{

  //  Clear the image, depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // enable Z buffering
  glEnable(GL_DEPTH_TEST);
  //  Reset previous transforms
  glLoadIdentity();

  if (mode == 0) // orthogonal
  {
    glRotatef(ph, 1, 0, 0);
    glRotatef(th, 0, 1, 0);
  }
#ifdef PERSPECTIVE
  else if (mode == 1) // perspective
  {
    double Ex = -2 * dim * SIN(th) * COS(ph);
    double Ey = +2 * dim * SIN(ph);
    double Ez = +2 * dim * COS(th) * COS(ph);
    gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, COS(ph), 0);
  }

  else if (mode == 2) // first person perspective
  {
    // up vector is constant in y direction
    gluLookAt(Ex1, Ey1, Ez1, Cx, Cy, Cz, 0, 1, 0);
  }
  /*********************Light***********************/
#endif
  // Flat or smooth(calculate color for each vertex and interpolate) shading
  glShadeModel(GL_SMOOTH);

  ErrCheck("display2");

  if (light)
  {
    glDisable(GL_LIGHT1);

    // position of the light source
    float pos[] = {distance * SIN(rot) * COS(roty), distance * SIN(roty),
                   distance * COS(rot) * COS(roty), 1};

    // draw the ball representing light source
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
    // Ambient & diffuse material properties of front & back track the current
    // color
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL); // apply color to the material described on
    // color call
    //  Enable light 0
    glEnable(GL_LIGHT0);

    //  Translate intensity to color vectors
    float Ambient[] = {0.01 * ambient, 0.01 * ambient, 0.01 * ambient, 1.0};
    float Diffuse[] = {0.01 * diffuse, 0.01 * diffuse, 0.01 * diffuse, 1.0};
    float Specular[] = {0.01 * specular, 0.01 * specular, 0.01 * specular, 1.0};
    glColor3f(1, 1, 1); // color for light
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    //  Set attenuation
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, at0 / 100.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, at1 / 100.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, at2 / 100.0);
  }
  else if (!light)
  {
    glDisable(GL_LIGHT0);

    ambient = 0;
    diffuse = 100;
    specular = 0;
    local = 0;

    // draw the ball representing light source
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
    // Ambient & diffuse material properties of front & back track the current
    // color
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL); // apply color to the material described on
                                 // color call

    //  Enable light 1
    glEnable(GL_LIGHT1);

    //  Translate intensity to color vectors
    float Ambient[] = {0.01 * ambient, 0.01 * ambient, 0.01 * ambient, 1.0};
    float Diffuse[] = {0.01 * diffuse, 0.01 * diffuse, 0.01 * diffuse, 1.0};
    float Specular[] = {0.01 * specular, 0.01 * specular, 0.01 * specular, 1.0};
    glColor3f(1, 1, 1); // color for light
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);
    glLightfv(GL_LIGHT1, GL_POSITION, lb_pos);

    float Exp = 1; //  Spot exponent
    float Direction[] = {-COS(10), -SIN(10), 0, 0};

    //        Set spotlight parameters
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, sco);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Exp);

    //  Set attenuation
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, at0 / 100.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, at1 / 100.0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, at2 / 100.0);
  }
  ErrCheck("display3");

  /*********************Draw objects***********************/

  // Enable texture
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // draw the entire scene
  if (obj == 0)
  {
    if (fog)
    {
      float fog_col[4] = {.3, .3, .3, 1};
      // Draw fog first if required
      glFogf(GL_FOG_MODE, GL_LINEAR);
      glFogf(GL_FOG_START, 0);
      glFogf(GL_FOG_END, 150);
      glFogfv(GL_FOG_COLOR, fog_col);
      //glFogf(GL_FOG_DENSITY, 1); //not required for linear
      glEnable(GL_FOG);
    }

    // draw solid objects before transparent

    // Cupboard
    trans = 0;
    glPushMatrix();
    glTranslated(-65, 0, 0);
    glRotated(90, 0, 1, 0);
    glScaled(.7, 0.7, .7);
    Cupboard(cupboard);
    glPopMatrix();

    // Chair 1

    glPushMatrix();
    glTranslated(30, 3.2, -60);
    glScaled(.8, .8, .8);
    Chair(chair_specs);
    glPopMatrix();

    // Chair 2

    glPushMatrix();
    glTranslated(60, 3.2, -30);
    glRotated(-90, 0, 1, 0);
    glScaled(.8, .8, .8);
    Chair(chair_specs);

    glPopMatrix();
    // Plant1

    glPushMatrix();
    glTranslated(65, 0, 0);
    glRotated(0, 0, 0, 0);
    glScaled(.4, 0.5, 0.4);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    Plant(pl);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
    glPopMatrix();

    //Plant 2
    glPushMatrix();
    glTranslated(0, 0, -65);
    glRotated(0, 0, 0, 0);
    glScaled(.5, 0.6, 0.5);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    Plant(pl);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
    glPopMatrix();

    // Potrait
    glPushMatrix();
    glTranslated(-73, 30, -60);
    glRotated(90, 0, 1, 0);
    glScaled(.25, .25, 1);
    Potrait(100, 0);
    glPopMatrix();

    //lamp

    glPushMatrix();
    glTranslated(-33, 1, -60);
    glRotated(-90, 0, 1, 0);
    glScaled(.6, 0.7, 0.6);
    Lamp(lamp);
    glPopMatrix();

    // Door
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

    //Loaded Object
    glDisable(GL_COLOR_MATERIAL);

    //  Set materials
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Shinyness);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RGBA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, RGBA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Emission);

    //  Draw the model
    glPushMatrix();
    glTranslated(60, 0, 40);
    glRotated(-90, 0, 1, 0);
    glScaled(.2, .2, .2);
    glCallList(ld_obj);
    glPopMatrix();
    glEnable(GL_COLOR_MATERIAL);

    // draw objects with transparent parts.FIrst iteration, solid, 2nd
    // transparent

    for (trans = 0; trans < 2; trans++)
    {
      glPushMatrix();
      glTranslated(30, 0, -40);
      glRotated(180, 0, 1, 0);
      glScaled(1, 1, 1);
      Table(table);
      glPopMatrix();

      glPushMatrix();
      glTranslated(0, -.1, 0);
      Building(building);
      glPopMatrix();

      bounceBall();
    }
    if (fog)
      glDisable(GL_FOG);

    //Calculate fencing coordinates in scene and draw
    for (int i = 0; i < 9; i++)
    {
      sym_fence[i] = translate(fence_orig[i], tfm[i]);
      DRAW_FENCE(sym_fence[i].x, sym_fence[i].z, sym_fence[i].xof, sym_fence[i].zof);
    }

    ErrCheck("display4");
  }

  // draw the individual elements

  // building
  if (obj == 1)
  {
    mode = 1;
    trans = 0;
    Building(building);
    trans = 1;
    Building(building);
  }

  if (obj == 2) // cupboard
  {
    fence_list = cbrd;
    mode = 1;
    trans = 0;
    Cupboard(cupboard);
    DRAW_FENCE(fence_orig[fence_list].x, fence_orig[fence_list].z, fence_orig[fence_list].xof, fence_orig[fence_list].zof);
  }

  if (obj == 3) // chair
  {
    fence_list = chair1;
    mode = 1;
    trans = 0;
    glPushMatrix();
    // glTranslated(30, 3.2, -60);
    // glScaled(2, 2, 2);
    Chair(chair_specs);
    DRAW_FENCE(fence_orig[fence_list].x, fence_orig[fence_list].z, fence_orig[fence_list].xof, fence_orig[fence_list].zof);
    glPopMatrix();
  }

  if (obj == 4) // table
  {
    fence_list = tbl;
    mode = 1;
    glPushMatrix();
    // glTranslated(30, 3.2, -60);
    // glScaled(2, 2, 2);
    trans = 0;
    Table(table);
    trans = 1;
    Table(table);
    DRAW_FENCE(fence_orig[fence_list].x, fence_orig[fence_list].z, fence_orig[fence_list].xof, fence_orig[fence_list].zof);
    glPopMatrix();
  }

  if (obj == 5) // potted plant
  {
    mode = 1;
    fence_list = plant1;
    trans = 0;
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    Plant(pl);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
    DRAW_FENCE(fence_orig[fence_list].x, fence_orig[fence_list].z, fence_orig[fence_list].xof, fence_orig[fence_list].zof);
  }

  if (obj == 6) // Table lamp
  {
    mode = 1;
    fence_list = lmp;
    glPushMatrix();
    // glRotated(90, 0, 1, 0);
    Lamp(lamp);
    DRAW_FENCE(fence_orig[fence_list].x, fence_orig[fence_list].z, fence_orig[fence_list].xof, fence_orig[fence_list].zof);

    glPopMatrix();
  }

  if (obj == 7) // bounce ball
  {
    mode = 1;
    fence_list = bball;
    for (trans = 0; trans <= 2; trans++)
    {
      bounceBall();
    }
    DRAW_FENCE(fence_orig[fence_list].x, fence_orig[fence_list].z, fence_orig[fence_list].xof, fence_orig[fence_list].zof);
  }

  if (obj == 8) // Loaded Object
  {
    mode = 1;
    fence_list = object;

    glDisable(GL_COLOR_MATERIAL);

    //  Set materials
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Shinyness);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RGBA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, RGBA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Emission);

    //  Draw the model
    // double scale = .01;
    glPushMatrix();
    glTranslated(0, -15, 0);
    glScaled(.2, .2, .2);
    glCallList(ld_obj);
    DRAW_FENCE(fence_orig[fence_list].x, fence_orig[fence_list].z, fence_orig[fence_list].xof, fence_orig[fence_list].zof);

    glPopMatrix();
    glEnable(GL_COLOR_MATERIAL);
  }

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  ErrCheck("display5");

  //  Switch off textures so it doesn't apply to the axis

  /**********************draw axes****************************/
  if (axes != 0)
  {
    glDisable(GL_DEPTH_TEST); // see axes through the objects
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
  Print("fence = %.2f,%.2f,%.2f,%.2f", fence_co.x, fence_co.z, fence_co.xof, fence_co.zof);

  Print("View Angle=%d,%d, z=%d, mode=%d, dim=%.2f, fov=%d", th, ph, axes, mode,
        dim, fov);
  if (mode == 2)
    Print(", Eye Position (%.2f,%.2f,%.2f)", Ex1, Ey1, Ez1);

  if (1)
  {
    glColor3f(1.0, 1.0, 1.0);
    glWindowPos2i(5, 45);
    Print("LocalViewer=%d Distance=%.2f Azimuth=%d, Elevation=%d rep =%.2f",
          local, distance, rot, roty, rep);
    glWindowPos2i(5, 25);
    Print("Ambient=%d, Diffuse=%d, Specular=%d, Emission=%d, Shininess=%d",
          ambient, diffuse, specular, emission, shininess);
  }

  glFlush();
  glutSwapBuffers();

  ErrCheck("displayF");
}

void Print(const char *format, ...)
{
  char buf[LEN];
  char *ch = buf;
  va_list args;
  //  Turn the parameters into a character string
  va_start(args, format);
  vsnprintf(buf, LEN, format, args);
  va_end(args);
  glColor3f(1, 1, 1);

  //  Display the characters one at a time at the current raster position
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);

  ErrCheck("Print");
}
