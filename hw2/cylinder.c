#include "cylinder.h"

#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define RSTEP 5
#define HSTEP 0.05

void cylinder(const cylinder_t cyl)
{
    //  Save transformation
    glPushMatrix();
    //  Transform cube
    glTranslated(cyl.x, cyl.y, cyl.z);
    glRotated(cyl.thx, 1, 0, 0);
    glRotated(cyl.thz, 0, 0, 1);

    glScaled(cyl.radius, cyl.height, cyl.radius);

    //  Cylinder
    glBegin(GL_QUADS);
    double col;
    //  curve
    for (double i = -1; i < 1; i += HSTEP)
    {
        for (int j = 0; j < 360; j += 5)
        {
            col = SIN(j);
            col = col < 0 ? -1 * col : col;
            col = col < .80 ? .80 : col;
            glColor3f(col * cyl.cyl_col.curve.r, col * cyl.cyl_col.curve.g, col * cyl.cyl_col.curve.b);
            glVertex3f(COS(j), i, SIN(j));
            glVertex3f(COS(j + RSTEP), i, SIN(j + RSTEP));
            glVertex3f(COS(j + RSTEP), i + HSTEP, SIN(j + RSTEP));
            glVertex3f(COS(j), i + HSTEP, SIN(j));
        }
    }
    glEnd(); //  End

    //draw the top  caps
    glColor3f(cyl.cyl_col.top.r, cyl.cyl_col.top.g, cyl.cyl_col.top.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 1, 0);
    for (int j = 0; j < 360; j += 5)
    {
        glVertex3f(COS(j), 1, SIN(j));
        glVertex3f(COS(j + RSTEP), 1, SIN(j + RSTEP));
    }
    glEnd();

    //draw the bottom  caps
    glColor3f(cyl.cyl_col.bottom.r, cyl.cyl_col.bottom.g, cyl.cyl_col.bottom.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, -1, 0);
    for (int j = 0; j < 360; j += 5)
    {
        glVertex3f(COS(j), -1, SIN(j));
        glVertex3f(COS(j + RSTEP), -1, SIN(j + RSTEP));
    }
    glEnd();

    //  Undo transformations
    glPopMatrix();
}
