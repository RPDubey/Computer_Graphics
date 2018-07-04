/*
 *@Filename: keys.c
 *@brief:Implements key,project, special and reshape functions
 *certain modifications and additions have been made to professor Schreuder's
 *example for this code
 *@author:Ravi Prakash Dubey
 *@date:06/28/2018
 */

#include "keys.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

//  Globals
extern int th;   // Azimuth of view angle
extern int ph;   // Elevation of view angle
extern int axes; // determines axes options

extern double dim; // Dimensions of orthogonal box
extern double asp; // aspect ration
extern int fov;    //  Field of view (for perspective)
extern int mode;   // orthogonal,perspective,first person
extern int obj;    // object to be displayed

// light related
extern int light; // light source on/off
extern int rot;
extern int roty;
extern int move;

extern int emission;  // Emission intensity (%)
extern int ambient;   // Ambient intensity (%)
extern int diffuse;   // Diffuse intensity (%)
extern int specular;  // Specular intensity (%)
extern int shininess; // Shininess (power of two)
extern float shiny;   // Shininess (value)
extern float rep;
extern double distance;

// coordinated for first person perspective
extern double dx;
extern double dy;
extern double dz;
extern double Ex1;
extern double Ey1;
extern double Ez1;
extern double Cx;
extern double Cy;
extern double Cz;

extern int zratio;

extern double a;
extern double r;
extern room_dim_t room;
extern float sco;

extern double p[3];
extern double thyx;
extern double thxz;
extern double del;
extern double le;
extern double br;
extern double he;
extern double temp_p[3];
extern double rad;
extern volatile double unorm[3];
extern double box_pos[3];
extern float fog;
extern fence_t sym_fence[9]; //absolute fencing coordinates of objects symmetric around origin
extern obj_list fence_list;
extern fence_t fence_orig[9];
extern double ofst;
extern fence_t fence_final[9];
int obstacle_detect = 1;
int fence_view = 1;

int inFence(double Ex, double Ez, fence_t f)
{

  //check room fence
  if ((Ex <= f.xof + f.x) && (Ex >= f.xof - f.x) && (Ez >= f.zof - f.z) && (Ez <= f.zof + f.z))
    return 1;
  else
    return 0;
}

void UpdatePos(char ch)
{

  if (ch == 'w')
  {
    dx = -SIN(th);
    dy = 0;
    dz = -COS(th);

    Ex1 += WSTEP * dx;
    Ey1 += WSTEP * dy;
    Ez1 += WSTEP * dz;

    int status;
    //check colission with walls
    status = !inFence(Ex1, Ez1, (fence_t){room.b - ofst, room.l - ofst, 0, 0});
    //check for colission with fenced objects
    if (obstacle_detect == 1)
    {
      for (int i = 0; i < 9; i++)
      {
        status |= inFence(Ex1, Ez1, fence_final[i]);
      }
    }
    if (status)
    {
      Ex1 -= WSTEP * dx;
      Ez1 -= WSTEP * dz;
    }

    Cx = Ex1 + dx;
    Cy = Ey1 + dy;
    Cz = Ez1 + dz;
  }

  else if (ch == 's')
  {
    dx = SIN(th);
    dy = 0;
    dz = COS(th);

    Ex1 += WSTEP * dx;
    Ey1 += WSTEP * dy;
    Ez1 += WSTEP * dz;

    int status;
    //check colission with walls
    status = !inFence(Ex1, Ez1, (fence_t){room.b - ofst, room.l - ofst, 0, 0});
    if (obstacle_detect == 1)
    {
      for (int i = 0; i < 9; i++)
      {
        status |= inFence(Ex1, Ez1, fence_final[i]);
      }
    }
    if (status)

    {
      Ex1 -= WSTEP * dx;
      Ez1 -= WSTEP * dz;
    }

    Cx = Ex1 - dx;
    Cy = Ey1 + dy;
    Cz = Ez1 - dz;
  }

  else if (ch == 'a')
  {

    th += 5;
    dx = -SIN(th);
    dy = 0;
    dz = -COS(th);

    Cx = Ex1 + dx;
    Cy = Ey1 + dy;
    Cz = Ez1 + dz;
  }
  else if (ch == 'd')
  {
    th -= 5;
    dx = -SIN(th);
    dy = 0;
    dz = -COS(th);

    Cx = Ex1 + dx;
    Cy = Ey1 + dy;
    Cz = Ez1 + dz;
  }
}

/*
 *Resets Parameters to default
 */
void Reset(void)
{
  th = ph = 0;
  dim = DIM;
  fov = FOV;
  rot = 90;
  roty = 40;

  Ex1 = 0;
  Ey1 = 20;
  Ez1 = 40;

  Cx = 0;
  Cy = 20;
  Cz = Ez1 - 1;

  mode = 2;

  thyx = 60;
  thxz = 70;
  unorm[0] = COS(thyx) * SIN(thxz);
  unorm[1] = SIN(thyx);
  unorm[2] = COS(thyx) * COS(thxz);
  light = 1;

  box_pos[0] = p[0] = XPOS;
  box_pos[1] = p[1] = YPOS;
  box_pos[2] = p[2] = ZPOS;
  le = br = he = 10;
  rad = 1;
  fog = 0;
}

/*
 *Checks for colission and updates normals
 */
int ifcolission(double pos[3])
{
  double norm[3] = {0, 0, 0};

  if (pos[0] <= -le + box_pos[0] + rad)
    norm[0] = 1;
  else if (pos[0] >= le + box_pos[0] - rad)
    norm[0] = -1;
  else if (pos[2] >= br + box_pos[2] - rad)
    norm[2] = -1;
  else if (pos[2] <= -br + box_pos[2] + rad)
    norm[2] = 1;
  else if (pos[1] >= he + box_pos[1] - rad)
    norm[1] = -1;
  else if (pos[1] <= -he + box_pos[1] + rad)
    norm[1] = 1;
  else
    return 0;

  double i[3] = {
      (pos[0] - temp_p[0]),
      (pos[1] - temp_p[1]),
      (pos[2] - temp_p[2]),
  };
  double mag = pow((i[0] * i[0] + i[1] * i[1] + i[2] * i[2]), 0.5);
  i[0] /= mag;
  i[1] /= mag;
  i[2] /= mag;

  double dot = norm[0] * i[0] + norm[1] * i[1] + norm[2] * i[2];
  double r[3];
  for (int j = 0; j < 3; j++)
  {
    r[j] = i[j] - 2 * dot * norm[j];
  }
  mag = pow((r[0] * r[0] + r[1] * r[1] + r[2] * r[2]), 0.5);
  unorm[0] = r[0] / mag;
  unorm[1] = r[1] / mag;
  unorm[2] = r[2] / mag;

  return 1;
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
  //  Elapsed time in seconds
  double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  rot = fmod(45 * t, 360.0);

  // update the bounce ball position
  temp_p[0] = p[0];
  temp_p[1] = p[1];
  temp_p[2] = p[2];

  p[0] += del * unorm[0];
  p[1] += del * unorm[1];
  p[2] += del * unorm[2];

  if (ifcolission(p))
  {
    p[0] += 1 * del * unorm[0];
    p[1] += 1 * del * unorm[1];
    p[2] += 1 * del * unorm[2];
  }

  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
  ErrCheck("idle");
}

void Project()
{
  //  Tell OpenGL we want to manipulate the projection matrix
  glMatrixMode(GL_PROJECTION);
  //  Undo previous transformations
  glLoadIdentity();

  if (mode == 1) // perspective
    gluPerspective(fov, asp, dim / zratio, zratio * dim);

  else if (mode == 0) //  Orthogonal projection
    glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);

  else if (mode == 2) // perspective
    gluPerspective(fov, asp, dim / zratio, zratio * dim);

  //  Switch to manipulating the model matrix
  glMatrixMode(GL_MODELVIEW);
  //  Undo previous transformations
  glLoadIdentity();

  ErrCheck("Project");
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{

  //  Exit on ESC
  if (ch == 27)
    exit(0);
  //  Reset to default
  else if (ch == '0')
  {
    Reset();
  }
  else if (ch == 'e')
  {
    fence_view += 1;
    fence_view = fence_view > 1 ? 0 : fence_view;
  }

  else if (ch == 'r')
  {
    obstacle_detect += 1;
    obstacle_detect = obstacle_detect > 1 ? 0 : obstacle_detect;
  }
  else if (ch == '{' && sco > 5)
    sco = sco == 180 ? 90 : sco - 5;
  else if (ch == '}' && sco < 180)
    sco = sco < 90 ? sco + 5 : 180;
  else if (ch == 't')
  {
    fog += 1;
    fog = (fog == 2) ? 0 : fog;
  }

  else if (ch == 'o')
  {
    distance -= 1;
    distance = distance < 0 ? 0 : distance;
  }

  else if (ch == 'O')
  {
    distance += .5;
    distance = distance > 1.4 * DIM ? 2 * DIM : distance;
  }
  else if (ch == 'p')
  {
    rep -= .2;
    rep = rep < 1 ? 1 : rep;
  }

  else if (ch == 'P')
  {
    rep += .2;
    rep = rep > 16 ? 16 : rep;
  }

  //  Ambient level
  else if (ch == 'f' && ambient > 0)
    ambient -= 5;
  else if (ch == 'F' && ambient < 100)
    ambient += 5;
  //  Diffuse level
  else if (ch == 'g' && diffuse > 0)
    diffuse -= 5;
  else if (ch == 'G' && diffuse < 100)
    diffuse += 5;
  //  Specular level
  else if (ch == 'h' && specular > 0)
    specular -= 5;
  else if (ch == 'H' && specular < 100)
    specular += 5;
  //  Emission level
  else if (ch == 'j' && emission > 0)
    emission -= 5;
  else if (ch == 'J' && emission < 100)
    emission += 5;
  //  Shininess level
  else if (ch == 'k' && shininess > -1)
  {
    shininess -= 1;
    shiny = shininess < 0 ? 0 : pow(2.0, shininess);
  }
  else if (ch == 'K' && shininess < 7)
  {
    shininess += 1;
    //  Translate shininess power to value (-1 => 0)
    shiny = shininess < 0 ? 0 : pow(2.0, shininess);
  }
  else if ((ch == ',') && (move == 0))
  {
    rot -= 4;
    rot %= 360;
  }
  else if ((ch == '.') && (move == 0))
  {
    rot += 4;
    rot %= 360;
  }
  else if (ch == '/')
  {
    roty = roty >= 90 ? 90 : (roty + 5);
  }
  else if (ch == '?')
  {
    roty = roty <= -90 ? -90 : (roty - 5);
  }
  else if (ch == 'm')
    move = 1 - move; // Toggle light movement
  else if (ch == 'l')
    light = 1 - light; // Toggle light source on / off

  else if (ch == 'z')
    axes = 1 - axes; // axes on/off

  else if (ch == 'n')
  {
    obj = (obj + 1) % (NUMBER_OF_OBJET + 1); // object to be displayed

    if (obj == 7)
    {
      box_pos[0] = p[0] = 0;
      box_pos[1] = p[1] = 0;
      box_pos[2] = p[2] = 0;
      le = br = he = 30;
      rad = 2;
    }
    else if (obj == 0)
      Reset();
  }
#ifdef PERSPECTIVE
  else if (ch == 'x')
  {
    mode = (mode + 1) % 3;
#ifndef ORTHOGONAL
    mode = mode == 0 ? 1 : mode;
#endif
  }
#endif

  else if (ch == 'c')
  {
    if (mode == 0)
      dim += 0.1;
    else
      fov++;
  }
  else if (ch == 'v')
  {
    if (mode == 0)
      dim -= 0.1;
    else
      fov--;
  }

  else if (mode == 2)
    UpdatePos(ch);

  //  Animate if requested
  glutIdleFunc(move ? idle : NULL);
  Project();
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
  ErrCheck("key");
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
  //  Right arrow key - increase azimuth by 5 degrees
  if (key == GLUT_KEY_RIGHT)
  {
    th += 5;
  }
  //  Left arrow key - decrease azimuth by 5 degrees
  else if (key == GLUT_KEY_LEFT)
  {
    th -= 5;
  }
  //  Up arrow key - increase elevation by 5 degrees
  else if (key == GLUT_KEY_UP)
  {
    if (mode != 2)
      ph += 5;
  }
  //  Down arrow key - decrease elevation by 5 degrees
  else if (key == GLUT_KEY_DOWN)
  {
    if (mode != 2)
      ph -= 5;
  }
  //  Keep angles to +/-360 degrees
  th %= 360;
  ph %= 360;

  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
  ErrCheck("special");
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height)
{
  //  Ratio of the width to the height of the window
  asp = (height > 0) ? (double)width / height : 1;
  //  Set the viewport to the entire window
  glViewport(0, 0, width, height);

  Project();
  ErrCheck("reshape");
}
