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
#include "common.h"

extern float shiny;                               // Shininess (value)
extern unsigned int texture[NUMBER_OF_OBJET + 4]; //  Texture names
extern float rep;
extern double dim;

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

    double z = -0.25;

    glColor3f(0, 1, 0);
    double a1, a2, a3, a4;
    a1 = 90 - ((180 / 3.1415927) * atan(z / 0.7));
    a2 = 90 - ((180 / 3.1415927) * atan(z / 1.1));
    a3 = 90 + ((180 / 3.1415927) * atan(z));
    a4 = 90 + ((180 / 3.1415927) * atan(z / 1.2));

    //Coordinates for leaf taken from //http://www.cs.northwestern.edu/~ago820/cs351/proj2.html
    glBegin(GL_POLYGON);
    glNormal3f(0, COS(a1), SIN(a1));
    glTexCoord2f(0.5, 0);
    glVertex3f(0.0, 0.0, 2 * z);

    glNormal3f(0, COS(a2), SIN(a2));
    glTexCoord2f(.5 + 1.0 / 2.6, .7 / 4.0);
    glVertex3f(1.0, 0.7, z);

    glNormal3f(0, 0, 1);
    glTexCoord2f(.5 + 1.3 / 2.6, 1.8 / 4.0);
    glVertex3f(1.3, 1.8, 0);

    glNormal3f(0, COS(a3), SIN(a3));
    glTexCoord2f(.5 + 1.0 / 2.6, 2.8 / 4.0);
    glVertex3f(1.0, 2.8, z);

    glNormal3f(0, COS(a4), SIN(a4));
    glTexCoord2f(.5, 4.0 / 4.0);
    glVertex3f(0.0, 4.0, 2 * z);

    glNormal3f(0, COS(a3), SIN(a3));
    glTexCoord2f(.5 - 1.0 / 2.6, 2.8 / 4.0);
    glVertex3f(-1.0, 2.8, z);

    glNormal3f(0, 0, 1);
    glTexCoord2f(.5 - 1.3 / 2.6, 1.8 / 4.0);
    glVertex3f(-1.3, 1.8, 0);

    glNormal3f(0, COS(a2), SIN(a2));
    glTexCoord2f(.5 - 1.0 / 2.6, .7 / 4.0);
    glVertex3f(-1.0, 0.7, z);

    glNormal3f(0, COS(a1), SIN(a1));
    glTexCoord2f(.5, 0.0);
    glVertex3f(0.0, 0.0, 2 * z);

    glEnd();

    a1 += 180;
    a2 += 180;
    a3 += 180;
    a4 += 180;

    glTranslated(0, 0, -.005);
    // glEnable(GL_POLYGON_OFFSET_FILL);//not working??
    // glPolygonOffset(2.0f, 2.0f);

    glBegin(GL_POLYGON);
    glNormal3f(0, COS(a1), SIN(a1));
    glTexCoord2f(0.5, 0);
    glVertex3f(0.0, 0.0, 2 * z);

    glNormal3f(0, COS(a2), SIN(a2));
    glTexCoord2f(.5 + 1.0 / 2.6, .7 / 4.0);
    glVertex3f(1.0, 0.7, z);

    glNormal3f(0, 0, -1);
    glTexCoord2f(.5 + 1.3 / 2.6, 1.8 / 4.0);
    glVertex3f(1.3, 1.8, 0);

    glNormal3f(0, COS(a3), SIN(a3));
    glTexCoord2f(.5 + 1.0 / 2.6, 2.8 / 4.0);
    glVertex3f(1.0, 2.8, z);

    glNormal3f(0, COS(a4), SIN(a4));
    glTexCoord2f(.5, 4.0 / 4.0);
    glVertex3f(0.0, 4.0, 2 * z);

    glNormal3f(0, COS(a3), SIN(a3));
    glTexCoord2f(.5 - 1.0 / 2.6, 2.8 / 4.0);
    glVertex3f(-1.0, 2.8, z);

    glNormal3f(0, 0, -1);
    glTexCoord2f(.5 - 1.3 / 2.6, 1.8 / 4.0);
    glVertex3f(-1.3, 1.8, 0);

    glNormal3f(0, COS(a2), SIN(a2));
    glTexCoord2f(.5 - 1.0 / 2.6, .7 / 4.0);
    glVertex3f(-1.0, 0.7, z);

    glNormal3f(0, COS(a1), SIN(a1));
    glTexCoord2f(.5, 0.0);
    glVertex3f(0.0, 0.0, 2 * z);

    glEnd();
    glDisable(GL_POLYGON_OFFSET_FILL);

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

void Quad(quadr_t prop)
{

    glPushMatrix();

    if (prop.offset)
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1, 1);
    }

    float spec[4] = {1, 1, 1, 1};
    float emis[4] = {0, 0, 0, 1};

    setMatPr(spec, emis, shiny);
    glNormal3f(prop.norm[0], prop.norm[1], prop.norm[2]);

    glPushMatrix();
    glColor4f(prop.col.r, prop.col.g, prop.col.b, prop.col.a);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3dv(prop.vert[0]);
    glTexCoord2f(prop.repeat, 0.0);
    glVertex3dv(prop.vert[1]);
    glTexCoord2f(prop.repeat, prop.repeat);
    glVertex3dv(prop.vert[2]);
    glTexCoord2f(0.0, prop.repeat);
    glVertex3dv(prop.vert[3]);
    if (prop.offset)
        glDisable(GL_POLYGON_OFFSET_FILL);
    glEnd();
    glPopMatrix();
}

void Curve(curve_t prop)
{
    glPushMatrix();
    glTranslated(0, 0, -(prop.rs + prop.rb) / 2.0);

    for (int i = 0; i < prop.ang; i += 5)
    {
        quadr_t back = {
            {
                {-prop.l, prop.rb * SIN(i), prop.rb * COS(i)},
                {prop.l, prop.rb * SIN(i), prop.rb * COS(i)},
                {prop.l, prop.rb * SIN(i + 5), prop.rb * COS(i + 5)},
                {-prop.l, prop.rb * SIN(i + 5), prop.rb * COS(i + 5)},
            },
            prop.col,
            prop.repeat,
            0,
            {0, SIN(i), COS(i)}};
        Quad(back);

        back = (quadr_t){
            {
                {-prop.l, prop.rs * SIN(i), prop.rs * COS(i)},
                {prop.l, prop.rs * SIN(i), prop.rs * COS(i)},
                {prop.l, prop.rs * SIN(i + 5), prop.rs * COS(i + 5)},
                {-prop.l, prop.rs * SIN(i + 5), prop.rs * COS(i + 5)},
            },
            prop.col,
            prop.repeat,
            0,
            {0, SIN(i), -COS(i)}};
        Quad(back);

        back = (quadr_t){
            {
                {-prop.l, prop.rs * SIN(i), prop.rs * COS(i)},
                {-prop.l, prop.rb * SIN(i), prop.rb * COS(i)},
                {-prop.l, prop.rb * SIN(i + 5), prop.rb * COS(i + 5)},
                {-prop.l, prop.rs * SIN(i + 5), prop.rs * COS(i + 5)},
            },
            prop.col,
            prop.repeat,
            0,
            {-1, 0, 0}};
        Quad(back);

        back = (quadr_t){
            {
                {prop.l, prop.rs * SIN(i), prop.rs * COS(i)},
                {prop.l, prop.rb * SIN(i), prop.rb * COS(i)},
                {prop.l, prop.rb * SIN(i + 5), prop.rb * COS(i + 5)},
                {prop.l, prop.rs * SIN(i + 5), prop.rs * COS(i + 5)},
            },
            prop.col,
            prop.repeat,
            0,
            {1, 0, 0}};
        Quad(back);
    }

    //top and bottom
    for (int i = 0; i < 2 * prop.l; i += 1)
    {

        quadr_t back = {
            {
                {-prop.l + i, 0, prop.rs},
                {-prop.l + i, 0, prop.rb},
                {-prop.l + i + 1, 0, prop.rb},
                {-prop.l + i + 1, 0, prop.rs},

            },
            prop.col,
            prop.repeat,
            0,
            {0, -1, 0}};
        Quad(back);

        back = (quadr_t){
            {
                {-prop.l + i, prop.rs * SIN(prop.ang), prop.rs * COS(prop.ang)},
                {-prop.l + i, prop.rb * SIN(prop.ang), prop.rb * COS(prop.ang)},
                {-prop.l + i + 1, prop.rb * SIN(prop.ang), prop.rb * COS(prop.ang)},
                {-prop.l + i + 1, prop.rs * SIN(prop.ang), prop.rs * COS(prop.ang)},
            },
            prop.col,
            prop.repeat,
            0,
            {0, COS(prop.ang), -SIN(prop.ang)}};

        Quad(back);
    }
    glPopMatrix();
}

// void CurveQuad(curve_quadr_t prop)
// {

//     for (int i = 0; i < prop.ang; i += 5)
//     {
//         double l = prop.l;
//         double r = prop.r;
//         quadr_t back = {
//             {
//                 {-l, r * SIN(i), r * COS(i)},
//                 {l, r * SIN(i), r * COS(i)},
//                 {l, r * SIN(i + 5), r * COS(i + 5)},
//                 {-l, r * SIN(i + 5), r * COS(i + 5)},
//             },
//             prop.col,
//             prop.repeat,
//             0,
//             {0, SIN(i), COS(i)}};
//         Quad(back);
//     }
// }
