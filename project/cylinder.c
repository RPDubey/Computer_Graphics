/*
*@Filename: cylinder.c
*@brief:Implements cylinder drawing function
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#include "cylinder.h"
#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define RSTEP 1.0
//#define HSTEP 0.05
extern float shiny;
extern float rep;
void cylinder(const cylinder_t cyl)
{
    float spec[4] = {(float)cyl.material.specular.r, (float)cyl.material.specular.g,
                     (float)cyl.material.specular.b, (float)cyl.material.specular.a};

    float emis[4] = {(float)cyl.material.emission.r, (float)cyl.material.emission.g,
                     (float)cyl.material.emission.b, (float)cyl.material.emission.a};

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cyl.material.shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);

    //  Save transformation
    glPushMatrix();
    //  Transform cube
    glTranslated(cyl.x, cyl.y, cyl.z);
    glRotated(cyl.thx, 1, 0, 0);
    glRotated(cyl.thz, 0, 0, 1);

    glScaled(cyl.radius, cyl.height, cyl.radius);

    //  Cylinder
    glBegin(GL_QUADS);
    //  curve
    glColor3f(cyl.cyl_col.curve.r, cyl.cyl_col.curve.g, cyl.cyl_col.curve.b);
    for (int j = 0; j <= 360 + RSTEP; j += RSTEP)
    {
        glNormal3f(SIN(j), 0, COS(j));

        glTexCoord2f((j / 360.0), 0.0);
        glVertex3f(SIN(j), -1, COS(j));

        glTexCoord2f((j / 360.0), 1);
        glVertex3f(SIN(j), 1, COS(j));

        glNormal3f(SIN(j + RSTEP), 0, COS(j + RSTEP));

        glTexCoord2f(((j + RSTEP) / 360.0), 1);
        glVertex3f(SIN(j + RSTEP), 1, COS(j + RSTEP));

        glTexCoord2f(((j + RSTEP) / 360.0), 0);
        glVertex3f(SIN(j + RSTEP), -1, COS(j + RSTEP));
    }
    glEnd(); //  End

    //draw the top   caps
    glColor3f(cyl.cyl_col.top.r, cyl.cyl_col.top.g, cyl.cyl_col.top.b);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 1, 0);
    for (int j = 0; j <= 360; j += 3)
    {
        glTexCoord2f(rep / 2 * COS(j) + 0.5, rep / 2 * SIN(j) + 0.5);
        glVertex3f(COS(j), 1, SIN(j));
    }
    glEnd();

    //draw the bottom  caps
    glColor3f(cyl.cyl_col.bottom.r, cyl.cyl_col.bottom.g, cyl.cyl_col.bottom.b);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, -1, 0);
    for (int j = 0; j <= 360; j += 5)
    {
        glTexCoord2f(rep / 2 * COS(j) + 0.5, rep / 2 * SIN(j) + 0.5);
        glVertex3f(COS(j), -1, SIN(j));
    }
    glEnd();

    //  Undo transformations
    glPopMatrix();
}
