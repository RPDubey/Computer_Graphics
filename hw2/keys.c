/*
*@Filename: keys.c
*@brief:Implements key,project, special and reshape functions
*certain modifications and additions have been made to professor Schreuder's example 6
*for this code
*@author:Ravi Prakash Dubey
*@date:06/10/2018
*/

#include "keys.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

//  Globals
int th = 0;   // Azimuth of view angle
int ph = 0;   // Elevation of view angle
int axes = 0; //determines axes options

double dim = DIM; // Dimensions of orthogonal box
double asp = 1;   //aspect ration
int fov = FOV;    //  Field of view (for perspective)
int mode = 0;     //orthogonal,perspective,first person

//coordinated for first person perspective
double dx = 0;
double dy = 0;
double dz = 0;

extern double Ex1;
extern double Ey1;
extern double Ez1;
extern double Cx;
extern double Cy;
extern double Cz;

int zratio = 4;
void Project()
{
    //  Tell OpenGL we want to manipulate the projection matrix
    glMatrixMode(GL_PROJECTION);
    //  Undo previous transformations
    glLoadIdentity();

    if (mode == 1) //perspective
        gluPerspective(fov, asp, dim / zratio, zratio * dim);

    else if (mode == 0) //  Orthogonal projection
        glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);

    if (mode == 2) //perspective
        gluPerspective(fov, asp, dim / zratio, zratio * dim);

    //  Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
    //  Undo previous transformations
    glLoadIdentity();
}

void changeview()
{
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
        th = ph = 0;
        dim = DIM;
        fov = FOV;
        Ex1 = 0;
        Ey1 = 0;
        Ez1 = DIM;
        Cx = 0;
        Cy = 0;
        Cz = DIM - 1;
    }
    else if (ch == 'z')
        axes = 1 - axes;

    else if (ch == 'x')
        mode = (mode + 1) % 3;

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
    else if (ch == 'w')
    {
        if (mode == 2)
        {
            dx = -SIN(th);
            dy = 0;
            dz = -COS(th);

            Ex1 += WSTEP * dx;
            Ey1 += WSTEP * dy;
            Ez1 += WSTEP * dz;

            Ex1 = Ex1 < DIM ? Ex1 : (DIM - WSTEP);
            Ez1 = Ez1 < DIM ? Ez1 : (DIM - WSTEP);
            Ex1 = Ex1 > -1 * DIM ? Ex1 : (-1 * DIM + WSTEP);
            Ez1 = Ez1 > -1 * DIM ? Ez1 : (-1 * DIM + WSTEP);

            Cx = Ex1 + dx;
            Cy = Ey1 + dy;
            Cz = Ez1 + dz;
        }
    }
    else if (ch == 's')
    {
        if (mode == 2)
        {
            dx = SIN(th);
            dy = 0;
            dz = COS(th);

            Ex1 += WSTEP * dx;
            Ey1 += WSTEP * dy;
            Ez1 += WSTEP * dz;

            Ex1 = Ex1 < DIM ? Ex1 : (DIM - WSTEP);
            Ez1 = Ez1 < DIM ? Ez1 : (DIM - WSTEP);
            Ex1 = Ex1 > -1 * DIM ? Ex1 : (-1 * DIM + WSTEP);
            Ez1 = Ez1 > -1 * DIM ? Ez1 : (-1 * DIM + WSTEP);

            Cx = Ex1 - dx;
            Cy = Ey1 + dy;
            Cz = Ez1 - dz;
        }
    }

    else if (ch == 'a')
    {
        if (mode == 2)
        {
            th += 5;
            dx = -SIN(th);
            dy = 0;
            dz = -COS(th);

            Cx = Ex1 + dx;
            Cy = Ey1 + dy;
            Cz = Ez1 + dz;
        }
    }
    else if (ch == 'd')
    {
        if (mode == 2)
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

    Project();
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
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
}
