
/*
*@Filename: cone.c
*@brief:Implements cone drawing function
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#include "cone.h"
#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#define THSTEP (5)

void cone(const cone_t specs)
{
    //  Save transformation
    glPushMatrix();
    //  Transform cube
    glTranslated(specs.x, specs.y, specs.z);
    glRotated(specs.thx, 1, 0, 0);
    glRotated(specs.thz, 0, 0, 1);
    double m = specs.R / specs.H;
    double p, q;
    double HSTEP = (double)specs.H / 100;
    glBegin(GL_QUAD_STRIP);
    glColor3f(specs.surface.r, specs.surface.g, specs.surface.b);
    for (double d = 0; d <= (specs.h); d += HSTEP)
    {
        for (int th = 0; th <= 360; th += THSTEP)
        {
            p = (specs.H - d);
            q = p - HSTEP;
            glVertex3d(m * p * COS(th), d, m * p * SIN(th));
            glVertex3d(m * q * COS(th), d + HSTEP, m * q * SIN(th));

            // glVertex3d(m * p * COS(th + THSTEP), d, m * p * SIN(th + THSTEP));
            // glVertex3d(m * q * COS(th + THSTEP), d + HSTEP, m * q * SIN(th + THSTEP));
        }
    }
    glEnd();

    //bottom circle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(specs.bottom.r, specs.bottom.g, specs.bottom.b);
    glVertex3d(0, 0, 0);
    for (int th = 0; th <= 360; th += THSTEP)
    {
        glVertex3d(specs.R * COS(th), 0, specs.R * SIN(th));
    }
    glEnd();

    //top circle
    if (specs.h < specs.H)
    {
        q = m * (specs.H - specs.h);
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(specs.top.r, specs.top.g, specs.top.b);
        glVertex3d(0, 0, 0);
        for (int th = 0; th <= 360; th += THSTEP)
        {
            glVertex3d(q * COS(th), specs.h, q * SIN(th));
        }
        glEnd();
    }
    //  Undo transformations
    glPopMatrix();
}