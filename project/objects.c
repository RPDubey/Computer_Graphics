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

extern float shiny;                             // Shininess (value)
extern unsigned int texture[NUMBER_OF_TEXTURE]; //  Texture names
extern float rep;
extern double dim;

void table(table_t specs)
{
    for (int i = 0; i < 9; i++)
    {
    }
}

void chair(chair_t chair)
{
    material_t stdmat = {shiny, WHITE, BLACK};

    for (int i = 0; i < 7; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture[16]);
        if (i == 0)
        {

            glPushMatrix();
            glTranslated(chair.cur.t[0], chair.cur.t[1], chair.cur.t[2]);
            glRotated(chair.cur.r[0], chair.cur.r[1], chair.cur.r[2], chair.cur.r[3]);
            glScaled(chair.cur.s[0], chair.cur.s[1], chair.cur.s[2]);
            Curve(chair.curv);
            glPopMatrix();
        }
        if (i < 4)
        {
            glPushMatrix();
            glTranslated(chair.cube[i].t[0], chair.cube[i].t[1], chair.cube[i].t[2]);
            glRotated(chair.cube[i].r[0], chair.cube[i].r[1], chair.cube[i].r[2], chair.cube[i].r[3]);
            glScaled(chair.cube[i].s[0], chair.cube[i].s[1], chair.cube[i].s[2]);
            unitcube(stdmat);
            glPopMatrix();
        }
        if (i > 2)
            glBindTexture(GL_TEXTURE_2D, texture[4]);

        glPushMatrix();
        glTranslated(chair.cyl[i].t[0], chair.cyl[i].t[1], chair.cyl[i].t[2]);
        glRotated(chair.cyl[i].r[0], chair.cyl[i].r[1], chair.cyl[i].r[2], chair.cyl[i].r[3]);
        glScaled(chair.cyl[i].s[0], chair.cyl[i].s[1], chair.cyl[i].s[2]);
        unitcylinder(stdmat);
        glPopMatrix();
    }
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
void leaf(double r, double depth)
{
    glPushMatrix();

    // double r = 10.0;
    // double depth = 1.2;

    float spec[4] = {1, 1, 1, 1};
    float emis[4] = {0, 0, 0, 1};
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);

    double x[5] = {0, 1, 1.3, 1, 0};
    double y[5] = {0, .7, 1.8, 2.8, 4.0};
    double ang[5];
    double z[5];
    double normr[5][3];
    // double norml[5][3];

    double a; //angle from centre of leaf to edge, along its breadth
    double val;
    for (int i = 0; i < 5; i++)
    {
        ang[i] = (y[i] - y[0]) / r;
        z[i] = -r + r * cos(ang[i]);

        if (x[i] != 0)
            a = acos((2 * depth * z[i] - z[i]) / x[i]);
        else
            a = 3.14 / 2;

        normr[i][0] = -cos(a);
        normr[i][1] = sin(ang[i]);
        normr[i][2] = cos(ang[i] + sin(a));
        val = pow((pow(normr[i][0], 2),
                   pow(normr[i][1], 2),
                   pow(normr[i][2], 2)),
                  .5);

        normr[i][0] /= val;
        normr[i][0] *= -1;

        normr[i][1] /= val;
        normr[i][2] /= val;
    }

    //Coordinates for leaf taken from //http://www.cs.northwestern.edu/~ago820/cs351/proj2.html

    glColor3f(1, 1, 1);
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < 5; i++)
    {
        glNormal3dv(normr[0]);
        glTexCoord2f(.5, y[i] / 4.0);
        glVertex3d(x[0], y[i], i == 4 ? .5 * z[i] * (1 + 2 * depth) : 2 * depth * z[i]);

        glNormal3dv(normr[i]);
        glTexCoord2f((.5 + x[i] / 2.6), y[i] / 4.0);
        glVertex3d(x[i], y[i], i == 4 ? (z[i] + 2 * depth * z[i]) / 2.0 : z[i]);
    }

    glEnd();

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < 5; i++)
    {
        glNormal3d(-normr[i][0], normr[i][1], normr[i][2]);
        glTexCoord2f((.5 - x[i] / 2.6), y[i] / 4.0);
        glVertex3d(-x[i], y[i], i == 4 ? .5 * z[i] * (1 + 2 * depth) : z[i]);

        glNormal3dv(normr[0]);
        glTexCoord2f(.5, y[i] / 4.0);
        glVertex3d(0, y[i], i == 4 ? .5 * z[i] * (1 + 2 * depth) : 2 * depth * z[i]);
    }

    glEnd();

    glPopMatrix();
}

void Plant(plant_t pl)
{

    glBindTexture(GL_TEXTURE_2D, texture[pl.leaf]);
    for (int i = 0; i < pl.num; i++)
    {

        glPushMatrix();
        glTranslated((pl.l + i)->tr.t[0], (pl.l + i)->tr.t[1], (pl.l + i)->tr.t[2]);
        glRotated((pl.l + i)->tr.r[0], (pl.l + i)->tr.r[1], (pl.l + i)->tr.r[2], (pl.l + i)->tr.r[3]);
        glRotated((pl.l + i)->ti[0], (pl.l + i)->ti[1], (pl.l + i)->ti[2], (pl.l + i)->ti[3]);
        glScaled((pl.l + i)->tr.s[0], (pl.l + i)->tr.s[1], (pl.l + i)->tr.s[2]);
        leaf((pl.l + i)->r, (pl.l + i)->d);
        glPopMatrix();
    }

    material_t stdmat = {shiny, WHITE, BLACK};
    //stem
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[pl.stem]);
    glTranslated(pl.st.t[0], pl.st.t[1], pl.st.t[2]);
    glRotated(pl.st.r[0], pl.st.r[1], pl.st.r[2], pl.st.r[3]);
    glScaled(pl.st.s[0], pl.st.s[1], pl.st.s[2]);
    unitcylinder(stdmat);
    glPopMatrix();

    //pot
    glBindTexture(GL_TEXTURE_2D, texture[pl.pt]);
    glPushMatrix();
    glTranslated(pl.p.t[0], pl.p.t[1], pl.p.t[2]);
    glRotated(pl.p.r[0], pl.p.r[1], pl.p.r[2], pl.p.r[3]);
    glScaled(pl.p.s[0], pl.p.s[1], pl.p.s[2]);
    cone(pl.pot);
    glPopMatrix();

    //soil
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[pl.soil]);
    glTranslated(pl.so.t[0], pl.so.t[1], pl.so.t[2]);
    glRotated(pl.so.r[0], pl.so.r[1], pl.so.r[2], pl.so.r[3]);
    glScaled(pl.so.s[0], pl.so.s[1], pl.so.s[2]);
    unitcone(stdmat);
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
