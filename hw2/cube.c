#include "cube.h"
#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

//global variables
int rev = 0; //  Reverse bottom of cube

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void cube(cube_t cube)
{
    //  Save transformation
    glPushMatrix();
    //  Transform cube
    glTranslated(cube.x, cube.y, cube.z);
    glRotated(cube.th, 0, 1, 0);
    glScaled(cube.dx, cube.dy, cube.dz);

    //  Cube
    glBegin(GL_QUADS);
    //  Front - counter c w
    glColor3f(cube.cube_col.front.r, cube.cube_col.front.g, cube.cube_col.front.b);
    glVertex3f(-1, -1, 1);
    glVertex3f(+1, -1, 1);
    glVertex3f(+1, +1, 1);
    glVertex3f(-1, +1, 1);

    //  Back - clock wise
    glColor3f(cube.cube_col.back.r, cube.cube_col.back.g, cube.cube_col.back.b);
    glVertex3f(+1, -1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, +1, -1);
    glVertex3f(+1, +1, -1);

    //  Right
    glColor3f(cube.cube_col.right.r, cube.cube_col.right.g, cube.cube_col.right.b);
    glVertex3f(+1, -1, +1);
    glVertex3f(+1, -1, -1);
    glVertex3f(+1, +1, -1);
    glVertex3f(+1, +1, +1);

    //  Left
    glColor3f(cube.cube_col.left.r, cube.cube_col.left.g, cube.cube_col.left.b);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, +1);
    glVertex3f(-1, +1, +1);
    glVertex3f(-1, +1, -1);

    //  Top
    glColor3f(cube.cube_col.top.r, cube.cube_col.top.g, cube.cube_col.top.b);
    glVertex3f(-1, +1, +1);
    glVertex3f(+1, +1, +1);
    glVertex3f(+1, +1, -1);
    glVertex3f(-1, +1, -1);

    //  Bottom
    glColor3f(cube.cube_col.bottom.r, cube.cube_col.bottom.g, cube.cube_col.bottom.b);
    //  Counter clockwise

    glVertex3f(-1, -1, -1);
    glVertex3f(+1, -1, -1);
    glVertex3f(+1, -1, +1);
    glVertex3f(-1, -1, +1);

    //  End
    glEnd();

    //  Undo transformations
    glPopMatrix();
}
