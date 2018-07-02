/*
*@Filename: sphere.c
*@brief:Implements sphere drawing function
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/29/2018
*/

#include "sphere.h"
#include "common.h"
#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

extern int emission; // Emission intensity (%)
extern float shiny;
extern float rep;

static double del;
/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th, double ph, double phbottom)
{
    double x = SIN(th) * COS(ph);
    double y = SIN(ph);
    double z = COS(th) * COS(ph);
    glNormal3d(x, y, z);
    glTexCoord2d(th / 360.0, (ph - phbottom) / del);
    glVertex3d(x, y, z);
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
void sphere(const sphere_t spec)
{
    float splr[4] = {(float)spec.material.specular.r, (float)spec.material.specular.g,
                     (float)spec.material.specular.b, (float)spec.material.specular.a};

    float emis[4] = {(float)spec.material.emission.r, (float)spec.material.emission.g,
                     (float)spec.material.emission.b, (float)spec.material.emission.a};

    glMaterialf(GL_FRONT, GL_SHININESS, spec.material.shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, splr);
    glMaterialfv(GL_FRONT, GL_EMISSION, emis);
    del = (spec.phtop - spec.phbottom);
    const int d = 5;
    int th, ph;
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(spec.x, spec.y, spec.z);
    glScaled(spec.r, spec.r, spec.r);
    glColor4f(spec.color.r, spec.color.g, spec.color.b, spec.color.a);

    //  Latitude bands
    for (ph = spec.phbottom; ph < spec.phtop; ph += d)
    {
        glBegin(GL_QUAD_STRIP);
        for (th = 0; th <= 360; th += d)
        {
            Vertex(th, ph, spec.phbottom);
            Vertex(th, ph + d, spec.phbottom);
        }
        glEnd();
    }

    //  Undo transformations
    glPopMatrix();
}
