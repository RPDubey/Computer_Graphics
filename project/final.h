/*
*@Filename: final.h
*@brief:contains data describing objects 
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/28/2018
*/

#ifndef HW2_H
#define HW2_H
#include "common.h"
#include "objects.h"

extern float shiny;
/*****************Cupboard Data******************/

const cbd_t cupboard = {
    // transform_t cbd[6] =
    {
        {{0, 1, 0}, {90, 0, 0, 0}, {20, 1, 10}},
        {{-19, 32, 0}, {90, 0, 0, 1}, {30, 1, 10}},
        {{19, 32, 0}, {90, 0, 0, 1}, {30, 1, 10}},
        {{0, 63, 0}, {90, 0, 0, 0}, {20, 1, 10}},
        {{0, 21, 0}, {90, 0, 0, 0}, {20, 1, 10}},
        {{0, 42, 0}, {90, 0, 0, 0}, {20, 1, 10}},
    },
    // quadr_t cbd_plank[4] =
    {
        {{{-20, 0, -10},
          {20, 0, -10},
          {20, 63, -10},
          {-20, 63, -10}},
         WHITE,
         1,
         0,
         {0, 0, 1}},
        {{{-20, 0, 7},
          {20, 0, 7},
          {20, 17, 7},
          {-20, 17, 7}},
         WHITE,
         1,
         0,
         {0, 0, 1}},
        {{{-20, 22, 7},
          {20, 22, 7},
          {20, 38, 7},
          {-20, 38, 7}},
         WHITE,
         1,
         0,
         {0, 0, 1}},
        {{{-20, 43, 7},
          {20, 43, 7},
          {20, 58, 7},
          {-20, 58, 7}},
         WHITE,
         1,
         0,
         {0, 0, 1}}}};

/*****************Chair Data******************/
const chair_t chair_specs = {
    //cylinder
    {
        {{-14, 12, 0}, {90, 1, 0, 0}, {3, 8, 2}},
        {{14, 12, 0}, {90, 1, 0, 0}, {3, 8, 2}},
        {{0, 30, -15}, {90, 0, 0, 1}, {3, 16, 3}},
        {{-12, -2, 6}, {0, 0, 0, 0}, {1, 2, 1}},
        {{12, -2, 6}, {0, 0, 0, 0}, {1, 2, 1}},
        {{-12, -2, -6}, {0, 0, 0, 0}, {1, 2, 1}},
        {{12, -2, -6}, {0, 0, 0, 0}, {1, 2, 1}},

    },
    //cube
    {
        {{0, 2, 0}, {90, 0, 0, 0}, {12, 2, 8}},
        {{14, 6, 0}, {90, 0, 0, 1}, {6, 2, 8}},
        {{-14, 6, 0}, {90, 0, 0, 1}, {6, 2, 8}},
        {{0, 10, -10}, {90, 1, 0, 0}, {16, 2, 10}}

    },
    {{0, 20, -10}, {0, 0, 0, 0}, {1, 1, 1}},
    {16, 16, 12, 45, WHITE, 1}

};

/*****************Potted Plant Data******************/
leaf_t l[10] =
    {
        {15, 1.2, {80, 1, 0, 0}, {{0, 0, 0}, {0, 0, 1, 0}, {7, 7, 7}}},
        {15, 1.2, {60, 1, 0, 0}, {{0, 1, 0}, {90, 0, 1, 0}, {7, 7, 7}}},
        {15, 1.2, {60, 1, 0, 0}, {{0, 3, 0}, {180, 0, 1, 0}, {6, 6, 6}}},
        {15, 1.2, {60, 1, 0, 0}, {{0, 6, 0}, {300, 0, 1, 0}, {6, 6, 6}}},

        {10, 1.2, {50, 1, 0, 0}, {{0, 8, 0}, {-10, 0, 1, 0}, {5, 5, 5}}},
        {10, 1.2, {40, 1, 0, 0}, {{0, 13, 0}, {70, 0, 1, 0}, {4, 4, 4}}},
        {10, 1.2, {30, 1, 0, 0}, {{0, 16, 0}, {160, 0, 1, 0}, {4, 4, 4}}},
        {10, 1.2, {30, 1, 0, 0}, {{0, 19, 0}, {270, 0, 1, 0}, {3, 3, 3}}},

        {8, 1.5, {20, 1, 0, 0}, {{0, 25, 0}, {100, 0, 1, 0}, {.5, .5, .5}}},
        {8, 1.5, {20, 1, 0, 0}, {{0, 25, 0}, {280, 0, 1, 0}, {.5, .5, .5}}},

};

plant_t pl =
    {
        3,
        18,
        9,
        19,
        10,
        l,
        {4, 0, 0, 0, 1, 1, .5, 0, 0, WHITE, WHITE, BLACK, {8, WHITE, BLACK}},
        {{0, 10, 0},
         {0, 0, 0, 0},
         {.6, 10, .6}},
        {{0, 0, 0}, {180, 1, 0, 0}, {15, 30, 15}},
        {{0, 0, 0}, {0, 0, 0, 0}, {15, .5, 15}}};

table_t table =
    {
        {4, 10, 8, 180, {1, 1, 1, .2}, 1},
        {{0, 10.5, -10}, {180, 0, 0, 0}, {20, 1, 20}}};

quadr_t building[6] =
    {
        //floor
        {
            {{-BREATH, 0, LENGTH},
             {BREATH, 0, LENGTH},
             {BREATH, 0, -LENGTH},
             {-BREATH, 0, -LENGTH}},
            WHITE,
            16,
            1,
            {0, 1, 0}},
        //left Wall
        {
            {{-BREATH, 0, -LENGTH},
             {-BREATH, 0, LENGTH},
             {-BREATH, HEIGHT, LENGTH},
             {-BREATH, HEIGHT, -LENGTH}},
            (color_t){1, 1, 1, .4},
            4,
            1,
            {-1, 0, 0}},
        //right wall
        {
            {{BREATH, 0, LENGTH},
             {BREATH, 0, -LENGTH},
             {BREATH, HEIGHT, -LENGTH},
             {BREATH, HEIGHT, LENGTH}},
            (color_t){1, 1, 1, .4},
            4,
            1,
            {1, 0, 0}},
        //back wall
        {{{BREATH, 0, -LENGTH},
          {-BREATH, 0, -LENGTH},
          {-BREATH, HEIGHT, -LENGTH},
          {BREATH, HEIGHT, -LENGTH}},
         (color_t){1, 1, 1, .4},
         4,
         1,
         {0, 0, -1}},
        //front wall
        {
            {{BREATH, 0, LENGTH},
             {-BREATH, 0, LENGTH},
             {-BREATH, HEIGHT, LENGTH},
             {BREATH, HEIGHT, LENGTH}},
            (color_t){1, 1, 1, .4},
            4,
            1,
            {0, 0, 1}},
        //roof
        {
            {{-BREATH, HEIGHT, LENGTH},
             {BREATH, HEIGHT, LENGTH},
             {BREATH, HEIGHT, -LENGTH},
             {-BREATH, HEIGHT, -LENGTH}},
            (color_t){1, 1, 1, .2},
            8,
            1,
            {0, 1, 0}}};
/*********************lamp dara****************/
lamp_t lamp =
    {
        {
            {{0, 15, 0}, {0, 0, 0, 0}, {1, 15, 1}},
            {{0, 0, 0}, {0, 0, 0, 0}, {10, 1, 10}},
            {{0, 30, 0}, {180, 0, 1, 0}, {1, 1, 1}},
            {{0, 53, 28}, {-70, 1, 0, 0}, {5, 5, 5}},
            {{0, 54, 26}, {0, 0, 0, 0}, {2, 2, 2}},
        },
        {.5, 25, 24.5, 90, WHITE, 1},
        {1, 0, 0, 0, 1, 0, 90, {1, 1, 1, .9}, {4, WHITE, BLACK}},
        4,
        4,
        17,
        4};

door_t door =
    {
        {{0, 0, 0},
         {0, 0, 0, 0},
         {20, 15, 20}},
        {{0, 15, -.51},
         {0, 0, 0, 0},
         {10, 15, .25}},
        {{{-0.5, 0, 0},
          {0.5, 0, 0},
          {0.5, 2, 0},
          {-0.5, 2, 0}},
         WHITE,
         1,
         0,
         {0, 0, -1}}};

/******************Transformations for fenced objects*************/
transform_t tfm[9] =
    {
        //Cupboard
        {{-65, 0, 0}, {90, 0, 1, 0}, {.7, .7, .7}},

        // chair1,
        {{30, 3.2, -60}, {0, 0, 0, 0}, {.8, .8, .8}},

        // chair2,
        {{70, 3.2, -30}, {-90, 0, 1, 0}, {.8, .8, .8}},

        // plant1,
        {{65, 0, 0}, {0, 0, 0, 0}, {.4, .5, .4}},

        // plant2,
        {{0, 0, -65}, {0, 0, 0, 0}, {.5, .6, .5}},

        // lamp,
        {{-33, 1, -60}, {90, 0, 1, 0}, {.6, .7, .6}},

        // ld_obj,
        {{60, 0, 40}, {-90, 0, 1, 0}, {.2, .2, .2}},

        // table,
        {{30, 0, -40}, {180, 0, 1, 0}, {1, 1, 1}},
        // bball
        {{0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1}},

};
fence_t fence_orig[9] =
    {
        // cbrd,
        {22, 11, 0, 1},

        // chair1,
        {20, 16, 0, -5},

        // chair2,
        {20, 16, 0, -5},

        // plant1,
        {23, 25, 0, 2},

        // plant2,
        {23, 25, 0, 2},

        // lmp,
        {10, 10, 0, 0},

        // object,
        {50, 60, 0, 20},

        // tbl,
        {21, 21, 0, 10},

        // bball
        {BOX_LE, BOX_BR, XPOS, ZPOS}};

fence_t fence_final[9] =
    {
        // cbrd,
        {8, 16, -40, 0},

        // chair1,
        {16, 13, 26, -41},

        // chair2,
        {13, 16, 42, -28},

        // plant1,
        {10, 10, 0, -41},

        // plant2,
        {8, 12, 40, -1},

        // lmp,
        {6, 6, -33, -36},

        // object,
        {10, 12, 40, 40},

        // tbl,
        {41, 41, 26, -24},

        // bball
        {BOX_LE, BOX_BR, -36, ZPOS}};

#endif
