/*
*@Filename: objects.h
*@brief:function definition and data structures for drawing complex objects.
*@author:Ravi Prakash Dubey
*@date:06/29/2018
*/

#ifndef OBJECTS_H
#define OBJECTS_H
#include "common.h"
#include "cylinder.h"
#include "sphere.h"
#include "cube.h"
#include "cone.h"

typedef struct
{
    transform_t cyl[7];
    transform_t cube[4];
    transform_t cur;
    curve_t curv;
} chair_t;

typedef struct
{
    double r, d;
    float ti[4];    //tilt
    transform_t tr; //transform
} leaf_t;

typedef struct
{
    int leaf, stem, pt, soil; //textures
    int num;
    leaf_t *l;
    cone_t pot;
    transform_t st, p, so;
} plant_t;

typedef struct
{
    transform_t cbd[6];
    quadr_t cbd_plank[4];
} cbd_t;

typedef struct
{
    curve_t stand;
    transform_t top;
} table_t;

typedef struct
{
    transform_t tra[5];
    curve_t cur;
    sphere_t sph;
    int base, stem, shade, bulb;
} lamp_t;

typedef struct
{
    transform_t t1, t2;
    quadr_t q;
} door_t;

void Chair(chair_t chair);
void LetterBlock(int);
void Logo(void);
void Leaf(double r, double depth);
void Potrait(int num, int tex);
void Quad(quadr_t prop);
void Curve(curve_t prop);
void Plant(plant_t pl);
void Cupboard(cbd_t c);
void Table(table_t table);
void Building(quadr_t *building);
void Lamp(lamp_t lamp);
void Door(door_t door);
void bounceBall();

#endif