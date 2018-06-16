#include "sphere.h"
#include "common.h"
#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th, double ph)
{
    //  glColor3f(COS(th) * COS(th), SIN(ph) * SIN(ph), SIN(th) * SIN(th));
    glVertex3d(SIN(th) * COS(ph), SIN(ph), COS(th) * COS(ph));
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
void sphere(const sphere_t spec)
{
    const int d = 5;
    int th, ph;

    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(spec.x, spec.y, spec.z);
    glScaled(spec.r, spec.r, spec.r);
    double col;
    //  Latitude bands
    for (ph = spec.phbottom; ph < spec.phtop; ph += d)
    {
        col = COS(ph);
        col = col < 0 ? -1 * col : col;
        col = col < .80 ? .80 : col;
        glColor3f(col * spec.color.r, col * spec.color.g, col * spec.color.b);

        glBegin(GL_QUAD_STRIP);
        for (th = 0; th <= 360; th += d)
        {
            Vertex(th, ph);
            Vertex(th, ph + d);
        }
        glEnd();
    }

    //  Undo transformations
    glPopMatrix();
}
