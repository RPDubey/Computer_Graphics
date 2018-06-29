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
int th = 25;  // Azimuth of view angle
int ph = 45;  // Elevation of view angle
int axes = 1; //determines axes options

double dim = DIM; // Dimensions of orthogonal box
double asp = 1;   //aspect ration
int fov = FOV;    //  Field of view (for perspective)
int mode = 1;     //orthogonal,perspective,first person
int obj = 3;      //object to be displayed

//light related
int light = 1; //light source on/off
int rot = 90;
int roty = 40;
int move = 1;

int emission = 0;  // Emission intensity (%)
int ambient = 20;  // Ambient intensity (%)
int diffuse = 100; // Diffuse intensity (%)
int specular = 75; // Specular intensity (%)
int shininess = 3; // Shininess (power of two)
float shiny = 8;   // Shininess (value)
float rep = 1;
extern double distance;

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

extern double a;
extern double r;
extern room_dim_t room;
/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
    //  Elapsed time in seconds
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    rot = fmod(90 * t, 360.0);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

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

    else if (mode == 2) //perspective
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
    double offset = 1 + dim / zratio;

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
        rot = 90;
        roty = 10;
    }
    else if (ch == 'o')
    {
        distance -= .25;
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
        move = 1 - move; //Toggle light movement
    else if (ch == 'l')
        light = 1 - light; //Toggle light source on / off

    else if (ch == 'z')
        axes = 1 - axes; //axes on/off

    else if (ch == 'n')
        obj = (obj + 1) % (NUMBER_OF_OBJET + 1); // object to be displayed
#ifdef PERSPECTIVE
    else if (ch == 'x')
        mode = (mode + 1) % 3;
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

            Ex1 = Ex1 < room.b - offset ? Ex1 : (room.b - offset - WSTEP);
            Ez1 = Ez1 < room.l - offset ? Ez1 : (room.l - offset - WSTEP);
            Ex1 = Ex1 > -1 * room.b + offset ? Ex1 : (-1 * room.b + offset + WSTEP);
            Ez1 = Ez1 > -1 * room.l + offset ? Ez1 : (-1 * room.l + offset + WSTEP);

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

            Ex1 = Ex1 < room.b - offset ? Ex1 : (room.b - offset - WSTEP);
            Ez1 = Ez1 < room.l - offset ? Ez1 : (room.l - offset - WSTEP);
            Ex1 = Ex1 > -1 * room.b + offset ? Ex1 : (-1 * room.b + offset + WSTEP);
            Ez1 = Ez1 > -1 * room.l + offset ? Ez1 : (-1 * room.l + offset + WSTEP);

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
    //  Animate if requested
    glutIdleFunc(move ? idle : NULL);
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
