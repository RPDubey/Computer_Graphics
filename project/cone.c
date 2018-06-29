
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

extern int emission; // Emission intensity (%)
extern float shiny;
extern float rep;

void cone(const cone_t specs)
{
    //Material Properties

    float spec[4] = {(float)specs.material.specular.r, (float)specs.material.specular.g,
                     (float)specs.material.specular.b, (float)specs.material.specular.a};

    float emis[4] = {(float)specs.material.emission.r, (float)specs.material.emission.g,
                     (float)specs.material.emission.b, (float)specs.material.emission.a};

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, specs.material.shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);

    //  Save transformation
    glPushMatrix();
    //  Transform cube
    glTranslated(specs.x, specs.y, specs.z);
    glRotated(specs.thx, 1, 0, 0);
    glRotated(specs.thz, 0, 0, 1);
    double m = specs.R / specs.H;
    double p, q;

    glBegin(GL_QUAD_STRIP);
    glColor3f(specs.surface.r, specs.surface.g, specs.surface.b);
    p = specs.R * (specs.H - specs.h) / specs.H;

    for (int th = 0; th <= 360; th += THSTEP)
    {
        glNormal3f(specs.H * SIN(th), specs.R, specs.H * COS(th));
        glTexCoord2d(th / 360.0, 0.0);
        glVertex3d(specs.R * SIN(th), 0, specs.R * COS(th));
        glTexCoord2d(th / 360.0, 1.0);
        glVertex3d(p * SIN(th), specs.h, p * COS(th));
    }

    glEnd();

    //bottom circle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(specs.bottom.r, specs.bottom.g, specs.bottom.b);
    glTexCoord2f(0.5, 0.5);
    glNormal3f(0, -1, 0);

    glVertex3d(0, 0, 0);
    for (int k = 0; k <= 360; k += THSTEP)
    {
        glTexCoord2f(rep / 2 * COS(k) + 0.5, rep / 2 * SIN(k) + 0.5);
        glVertex3d(specs.R * COS(k), 0, specs.R * SIN(k));
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