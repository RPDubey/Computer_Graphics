#include "cone.h"

#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#define THSTEP (15)

void cone(const cone_t specs)
{
    //  Save transformation
    glPushMatrix();
    //  Transform cube
    glTranslated(specs.x, specs.y, specs.z);
    glRotated(specs.thx, 1, 0, 0);
    glRotated(specs.thz, 0, 0, 1);
    //glScaled(specs.R, specs.H, specs.R);
    glColor3f(1, 0, 0);
    double m = specs.R / specs.H;
    double p, q;
    double HSTEP = specs.H / 2000;
    glBegin(GL_QUAD_STRIP);
    for (double d = 0; d < (specs.h); d += HSTEP)
    {
        for (int th = 0; th < 360; th += THSTEP)
        {
            // glVertex3d(specs.R * COS(th), 0, specs.R * SIN(th));
            // glVertex3d(specs.R * COS(th + THSTEP), 0, specs.R * SIN(th + THSTEP));
            // glVertex3d(m * COS(th + THSTEP), specs.h, m * SIN(th + THSTEP));
            // glVertex3d(m * COS(th), specs.h, m * SIN(th));
            p = (specs.H - d);
            q = p - HSTEP;
            glVertex3d(m * p * COS(th), d, m * p * SIN(th));
            glVertex3d(m * p * COS(th + THSTEP), d, m * p * SIN(th + THSTEP));
            glVertex3d(m * q * COS(th + THSTEP), d + HSTEP, m * q * SIN(th + THSTEP));
            glVertex3d(m * q * COS(th), d + HSTEP, m * q * SIN(th));
        }
    }
    glEnd();
    //  Undo transformations
    glPopMatrix();
}