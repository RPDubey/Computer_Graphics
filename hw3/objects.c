/*
*@Filename: objects.c
*@brief:Implements functions for drawing complex objects(using primitive objects)
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#include "objects.h"

#include <stdlib.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

extern float shiny;                               // Shininess (value)
extern unsigned int texture[NUMBER_OF_OBJET + 4]; //  Texture names
extern float rep;

void table(table_t specs)
{
    for (int i = 0; i < 9; i++)
    {
        cube(specs.table_desc[i]);
    }
}

void chair(chair_t specs)
{
    for (int i = 0; i < 8; i++)
        cube(specs.chair_cube_desc[i]);
    for (int i = 0; i < 3; i++)
        cylinder(specs.chair_cyl_desc[i]);
    for (int i = 0; i < 2; i++)
        sphere(specs.chair_sph_desc[i]);
}

void lamp(lamp_t specs)
{
    for (int i = 0; i < 2; i++)
        cylinder(specs.lamp_cyl_desc[i]);
    for (int i = 0; i < 2; i++)
        sphere(specs.lamp_sph_desc[i]);
}

void letterBlock(int element)
{

    double ratio = .6;
    double ang = 90 - (180.0 / 3.1415927) * atan(2 / (1 - ratio));
    float spec[4] = {1, 1, 1, 1};
    float emis[4] = {0, 0, 0, 1};

    glPushMatrix();
    if (element == 0)
    {

        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);

        glColor3f(1, 1, 1);
        glPushMatrix();
        glTranslatef(0, 2, 0);

        glBegin(GL_QUADS);
        //  Front - counter c w
        // glColor3f(cube.cube_col.front.r, cube.cube_col.front.g, cube.cube_col.front.b);
        glNormal3f(0, SIN(ang), COS(ang));
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1, -1, 1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(+1, -1, 1);
        glTexCoord2f(rep, rep);
        glVertex3f(+1, +1, ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(-1, +1, ratio);

        //  Back - counter clock wise
        // glColor3f(cube.cube_col.back.r, cube.cube_col.back.g, cube.cube_col.back.b);
        glNormal3f(0, SIN(ang), -COS(ang));
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1, -1, -1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(+1, -1, -1);
        glTexCoord2f(rep, rep);
        glVertex3f(+1, +1, -ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(-1, +1, -ratio);

        //  Right
        // glColor3f(cube.cube_col.right.r, cube.cube_col.right.g, cube.cube_col.right.b);
        glNormal3f(COS(ang), SIN(ang), 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(+1, -1, +1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(+1, -1, -1);
        glTexCoord2f(rep, rep);
        glVertex3f(+1, +1, -ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(+1, +1, +ratio);

        //  Left
        // glColor3f(cube.cube_col.left.r, cube.cube_col.left.g, cube.cube_col.left.b);
        glNormal3f(-COS(ang), SIN(ang), 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1, -1, +1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(-1, -1, -1);
        glTexCoord2f(rep, rep);
        glVertex3f(-1, +1, -ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(-1, +1, +ratio);

        //  Top
        // glColor3f(cube.cube_col.top.r, cube.cube_col.top.g, cube.cube_col.top.b);
        glNormal3f(0, +1, 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1, +1, ratio);
        glTexCoord2f(rep, 0.0);
        glVertex3f(1, +1, ratio);
        glTexCoord2f(rep, rep);
        glVertex3f(+1, +1, -ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(-1, +1, -ratio);

        //  Bottom
        //  Counter clockwise
        // glColor3f(cube.cube_col.top.r, cube.cube_col.top.g, cube.cube_col.top.b);
        glNormal3f(0, -1, 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1, -1, +1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(+1, -1, +1);
        glTexCoord2f(rep, rep);
        glVertex3f(+1, -1, -1);
        glTexCoord2f(0.0, rep);
        glVertex3f(-1, -1, -1);

        glEnd();
    }
    else if (element == 1)
    {

        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
        glColor3f(1, 1, 1);

        glPushMatrix();
        glScaled(.5, .5, .5);

        glBegin(GL_QUADS);

        //  Bottom
        glNormal3f(0, -1, 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-2, -1, 1);
        glTexCoord2f(rep, rep);
        glVertex3f(0, -1, -1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(0, -1, 1);
        glTexCoord2f(0.0, rep);
        glVertex3f(-2, -1, 1);

        //  Top
        glNormal3f(0, +1, 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(ratio - 1, +1, 1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(0, +1, ratio);
        glTexCoord2f(rep, rep);
        glVertex3f(0, +1, -ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(-ratio - 1, +1, 1);

        //  Front - counter c w
        glNormal3f(0, 0, 1);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-2, -1, 1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(0, -1, 1);
        glTexCoord2f(rep, rep);
        glVertex3f(ratio - 1, 1, 1);
        glTexCoord2f(0.0, rep);
        glVertex3f(-ratio - 1, +1, 1);

        //  Back - counter clock wise
        glNormal3f(1, 0, 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0, -1, 1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(0, -1, -1);
        glTexCoord2f(rep, rep);
        glVertex3f(0, +1, -ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(0, +1, ratio);

        //  RIGHT
        glNormal3f(COS(ang) * SIN(45), SIN(ang), COS(ang) * COS(45));
        glTexCoord2f(0.0, 0.0);
        glVertex3f(ratio - 1, 1, 1);
        glTexCoord2f(rep, 0.0);
        glVertex3f(0, -1, 1);
        glTexCoord2f(rep, rep);
        glVertex3f(0, +1, ratio);
        glTexCoord2f(0.0, rep);
        glVertex3f(ratio - 1, +1, 1);

        //  Left
        glNormal3f(-COS(ang) * SIN(45), SIN(ang), -COS(ang) * COS(45));
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0, 1, -ratio);
        glTexCoord2f(rep, 0.0);
        glVertex3f(0, -1, -1);
        glTexCoord2f(rep, rep);
        glVertex3f(-2, -1, 1);
        glTexCoord2f(0.0, rep);
        glVertex3f(-1 - ratio, +1, 1);
        glPopMatrix();
        glEnd();
    }
    glPopMatrix();
}

void logo(void)
{
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    glPushMatrix();

    glPushMatrix();
    glScaled(.5 * 4, .25, .5);
    glTranslated(1, 0, 0);
    letterBlock((int)0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, .5, 0);
    glScaled(1, .5, 1);
    letterBlock((int)1);
    glPopMatrix();

    glPushMatrix();
    glScaled(.5 * 4, .25, .5);
    glTranslated(1, 0, 10);
    letterBlock((int)0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-.5, 0, 2.5);
    glRotated(90, 0, 1, 0);
    glScaled(.5 * 4, .25, .5);
    letterBlock((int)0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-.5, .5, 4.5);
    glRotated(90, 0, 1, 0);
    glScaled(1, .5, 1);
    letterBlock((int)1);
    glPopMatrix();

    glPopMatrix();
    /***************************************/
    glPushMatrix();
    glTranslated(2, 0, 2);

    glPushMatrix();
    glTranslated(-.5, 0, 2);
    glRotated(90, 0, 1, 0);
    glScaled(.5 * 5, .25, .5);
    letterBlock((int)0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-.5, .5, 4.5);
    glRotated(90, 0, 1, 0);
    glScaled(1, .5, 1);
    letterBlock((int)1);
    glPopMatrix();

    glPushMatrix();
    glScaled(.5 * 4, .25, .5);
    glTranslated(1, 0, 10);
    letterBlock((int)0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4, .5, 5);
    glRotated(180, 0, 1, 0);
    glScaled(1, .5, 1);
    letterBlock((int)1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4.5, 0, 2);
    glRotated(90, 0, 1, 0);
    glScaled(.5 * 5, .25, .5);
    letterBlock((int)0);
    glPopMatrix();

    glPopMatrix();
}

void rowsub(double v1[3], double v2[3], double *v3)
{
    *v3 = (v1[0] - v2[0]);
    *(v3 + 1) = (v1[1] - v2[1]);
    *(v3 + 2) = (v1[2] - v2[2]);
}
void unitNorm(double vp[3], double vm[3], double vn[3], double *n1)
{

    double v1[3] = {0, 0, 0};
    double v2[3] = {0, 0, 0};
    rowsub(vm, vn, v1);
    rowsub(vm, vp, v2);

    double len1 = pow((v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]), 0.5);
    double len2 = len1 * pow((v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]), 0.5);

    *n1 = (v1[1] * v2[2] - v1[2] * v2[1]) / len2;
    *(n1 + 1) = (v1[2] * v2[0] - v1[0] * v2[2]) / len2;
    *(n1 + 2) = (v1[0] * v2[1] - v1[1] * v2[0]) / len2;
}

#define STEP (double)2
void leaf(void)
{
    glBindTexture(GL_TEXTURE_2D, texture[3]);

    glPushMatrix();

    float spec[4] = {1, 1, 1, 1};
    float emis[4] = {0, 0, 0, 1};
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);

    double a1 = 5;
    double a2 = 8;
    double z1 = SIN(a1);
    double z2 = SIN(a2);

    double v[9][3] = {{0.0, 0.0, 0},
                      {1.0, 0.7, z1},
                      {1.3, 1.8, 1.3 * z2},
                      {1.0, 2.8, z1},
                      {0.0, 4.0, 0},
                      {-1.0, 2.8, z1},
                      {-1.3, 1.8, 1.3 * z2},
                      {-1.0, 0.7, z1},
                      {0.0, 0.0, 0}};
    double a1 = 5;
    double a2 = 8;
    double norm[9] = {90, 90 + a1, 90 + a2, 90 + a1, 90, 90 - a1, 90 - a2, 90 - a1, 90};
    double norm1[9] = {-90, -90 + a1, -90 + a2, -90 + a1, -90, 90 * 3 - a1, 90 * 3 - a2, 90 * 3 - a1, 90};

    //Coordinates for leaf taken from //http://www.cs.northwestern.edu/~ago820/cs351/proj2.html
    double xmax = 1.3 * 2;
    double ymax = 4;
    glColor3f(0, 1, 0);
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < 5; i++)
    {
        glNormal3f(COS(norm[8 - i]), 0, SIN(norm[8 - i]));
        glTexCoord2f(.5 + v[8 - i][0] / xmax, v[8 - i][1] / ymax);
        glVertex3dv(v[8 - i]);

        glNormal3f(COS(norm[i]), 0, SIN(norm[i]));
        glTexCoord2f(.5 + v[i][0] / xmax, v[i][1] / ymax);
        glVertex3dv(v[i]);
    }

    glEnd();

    // glColor3f(.2, .8, .2);
    // glTranslated(0, 0, -.001);
    // // glNormal3f(0.0, 0.0, -1.0);
    // // glEnable(GL_POLYGON_OFFSET_FILL); //not giving desired effect?
    // // glPolygonOffset(2, 2);
    // glBegin(GL_QUAD_STRIP);

    // for (int i = 8; i > 3; i--)
    // {
    //     glNormal3f(COS(norm1[8 - i]), 0, SIN(norm1[8 - i]));
    //     // glNormal3f(COS(180 + norm[8 - i]), 0, SIN(180 + norm[8 - i]));
    //     glTexCoord2f(.5 + v[8 - i][0] / xmax, v[8 - i][1] / ymax);
    //     glVertex3dv(v[8 - i]);

    //     glNormal3f(COS(norm[i]), 0, SIN(norm1[i]));
    //     glTexCoord2f(.5 + v[i][0] / xmax, v[i][1] / ymax);
    //     glVertex3dv(v[i]);
    // }

    glEnd();

    glPopMatrix();
}

void potrait(void)
{
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glPushMatrix();
    float spec[4] = {1, 1, 0, 1};
    float emis[4] = {0, 0, 0, 1};

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

    glPushMatrix();
    glScaled(2, 2, 1);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1, -1, 0);
    glTexCoord2f(1, 0.0);
    glVertex3f(+1, -1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(+1, +1, 0);
    glTexCoord2f(0.0, 1);
    glVertex3f(-1, +1, 0);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 1);
    glPushMatrix();
    glTranslatef(0, 0, -.1);
    glScaled(2, 2, .1);
    material_t stdmat = {shiny, WHITE, BLACK};
    unitcube(stdmat);
    glPopMatrix();
    glDisable(GL_POLYGON_OFFSET_FILL);

    glPopMatrix();
}

void floortile(void)
{

    glPushMatrix();

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 1);
    glBindTexture(GL_TEXTURE_2D, texture[8]);

    float spec[4] = {1, 1, 0, 1};
    float emis[4] = {0, 0, 0, 1};

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    double size = 6;
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size, -.1, size);
    glTexCoord2f(8, 0.0);
    glVertex3f(size, -.1, size);
    glTexCoord2f(8, 8);
    glVertex3f(size, -.1, -size);
    glTexCoord2f(0.0, 8);
    glVertex3f(-size, -.1, -size);

    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnd();
    glPopMatrix();
}