/*
*@Filename: hw1.c
*@brief:Implements key, special and reshape functions
*certain modifications and additions have been made to professor Schreuder's example 6
*for this code
*@author:Ravi Prakash Dubey
*@date:06/10/2018
*/

#include "keys.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

//#include "display.h"

//  Globals
int th = 0;     // Azimuth of view angle
int ph = 0;     // Elevation of view angle
double dim = 2; // Dimensions of orthogonal box

//lorenz parameters
double s = 10;
double b = 2.666;
double r = 28;

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{
    //  Exit on ESC
    if (ch == 27)
        exit(0);
    //  Reset view angle
    else if (ch == '0')
    {
        th = ph = 0;
        s = 10;
        b = 2.666;
        r = 28;
    }

    else if (ch == '1')
        s += 0.01 * s; // increase by 1%
    else if (ch == '2')
    {
        s -= 0.01 * s; // decrease by 1%
        s = s < 0 ? 0 : s;
    }
    else if (ch == '3')
        b += 0.01 * b; // increase by 1%
    else if (ch == '4')
    {
        b -= 0.01 * b; // decrease by 1%
        b = b < 0 ? 0 : b;
    }
    else if (ch == '5')
        r += 0.01 * r; // increase by 1%
    else if (ch == '6')
    {
        r -= 0.01 * r; // decrease by 1%
        r = r < 0 ? 0 : r;
    }
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
        th += 5;
    //  Left arrow key - decrease azimuth by 5 degrees
    else if (key == GLUT_KEY_LEFT)
        th -= 5;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP)
        ph += 5;
    //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
        ph -= 5;
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
    double w2h = (height > 0) ? (double)width / height : 1;
    //  Set the viewport to the entire window
    glViewport(0, 0, width, height);
    //  Tell OpenGL we want to manipulate the projection matrix
    glMatrixMode(GL_PROJECTION);
    //  Undo previous transformations
    glLoadIdentity();
    //  Orthogonal projection box adjusted for the
    //  aspect ratio of the window
    glOrtho(-dim * w2h, +dim * w2h, -dim, +dim, -dim, +dim);
    //  Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
    //  Undo previous transformations
    glLoadIdentity();
}
