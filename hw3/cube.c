/*
*@Filename: cube.c
*@brief:Implements cube drawing function
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#include "cube.h"
#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

// extern int emission; // Emission intensity (%)
extern float shiny;
extern int th; // Azimuth of view angle
// extern float rep;

//global variables
int rev = 0; //  Reverse bottom of cube

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void cube(const cube_t cube)
{
    float spec[4] = {(float)cube.material.specular.r, (float)cube.material.specular.g,
                     (float)cube.material.specular.b, (float)cube.material.specular.a};

    float emis[4] = {(float)cube.material.emission.r, (float)cube.material.emission.g,
                     (float)cube.material.emission.b, (float)cube.material.emission.a};

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cube.material.shininess);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);

    //  Save transformation
    glPushMatrix();
    //  Transform cube
    glTranslated(cube.x, cube.y, cube.z);
    glRotated(cube.thy, 0, 1, 0);
    glScaled(cube.dx, cube.dy, cube.dz);
    float rep = 1.0;
    //  Cube
    glBegin(GL_QUADS);
    //  Front - counter c w
    glColor3f(cube.cube_col.front.r, cube.cube_col.front.g, cube.cube_col.front.b);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(rep, 0.0);
    glVertex3f(+1, -1, 1);
    glTexCoord2f(rep, rep);
    glVertex3f(+1, +1, 1);
    glTexCoord2f(0.0, rep);
    glVertex3f(-1, +1, 1);

    //  Back - counter clock wise
    glColor3f(cube.cube_col.back.r, cube.cube_col.back.g, cube.cube_col.back.b);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(rep, 0.0);
    glVertex3f(+1, -1, -1);
    glTexCoord2f(rep, rep);
    glVertex3f(+1, +1, -1);
    glTexCoord2f(0.0, rep);
    glVertex3f(-1, +1, -1);

    //  Right
    glColor3f(cube.cube_col.right.r, cube.cube_col.right.g, cube.cube_col.right.b);
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(+1, -1, +1);
    glTexCoord2f(rep, 0.0);
    glVertex3f(+1, -1, -1);
    glTexCoord2f(rep, rep);
    glVertex3f(+1, +1, -1);
    glTexCoord2f(0.0, rep);
    glVertex3f(+1, +1, +1);

    //  Left
    glColor3f(cube.cube_col.left.r, cube.cube_col.left.g, cube.cube_col.left.b);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1, -1, +1);
    glTexCoord2f(rep, 0.0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(rep, rep);
    glVertex3f(-1, +1, -1);
    glTexCoord2f(0.0, rep);
    glVertex3f(-1, +1, +1);

    //  Top
    glColor3f(cube.cube_col.top.r, cube.cube_col.top.g, cube.cube_col.top.b);
    glNormal3f(0, +1, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1, +1, +1);
    glTexCoord2f(rep, 0.0);
    glVertex3f(+1, +1, +1);
    glTexCoord2f(rep, rep);
    glVertex3f(+1, +1, -1);
    glTexCoord2f(0.0, rep);
    glVertex3f(-1, +1, -1);

    //  Bottom
    glColor3f(cube.cube_col.bottom.r, cube.cube_col.bottom.g, cube.cube_col.bottom.b);
    //  Counter clockwise
    glNormal3f(0, -1, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1, -1, +1);
    glTexCoord2f(rep, 0.0);
    glVertex3f(+1, -1, +1);
    glTexCoord2f(rep, rep);
    glVertex3f(+1, -1, -1);
    glTexCoord2f(0.0, rep);
    glVertex3f(-1, -1, -1);

    //  End
    glEnd();

    //  Undo transformations
    glPopMatrix();
}
