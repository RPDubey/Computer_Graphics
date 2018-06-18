/*
*@Filename: hw2.h
*@brief:contains structure declaration for objects
*certain modifications and additions have been made to professor Schreuder's examples
*for this code
*@author:Ravi Prakash Dubey
*@date:06/16/2018
*/

#ifndef HW2_H
#define HW2_H
#include "common.h"
#include "objects.h"

//table description
const table_t table_specs = {
    .table_desc = {
        {1, 0, 0, 0, 1, .04, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}},

        {2, -.96, -.48 - .04, 0, 0.04, .48, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}}, //leftmost white

        {3, .96, -.17, 0, 0.04, .13, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}}, //left white

        {4, -.56, -0.48 - .04, 0, 0.04, .48, 1, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}},

        {5, -.76, -0.14, 0, .15, .09, 1, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}},

        {6, -.76, -0.63, 0, .15, .37, 1, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}},

        {7, .20, -0.14, 0, .71, .09, 1, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}},

        {8, .96, -.65, .96, 0.04, .35, .04, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}}, //right leg

        {9, .96, -.65, -.96, 0.04, .35, .04, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}} //right leg

    }};

//chair description
const chair_t chair_specs = {
    .chair_cube_desc = {
        {1, 0, 0, 0, .4, .02, .4, 0, 0, {OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE, OFWHITE}}, //plank

        {1, .38, -.3, .38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //front right

        {1, -.38, -.3, .38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //front left

        {1, .38, -.3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //back right

        {1, -.38, -.3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //back left

        {1, .38, .3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //brest right

        {1, -.38, .3, -.38, .02, .28, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}}, //brest left

        {1, 0, .6, -.38, .4, .02, .02, 0, 0, {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE}} //brest horizontol
    },
    .chair_cyl_desc = {{1, 0, .28, -.38, .02, .3, 0, 0, {OFWHITE, OFWHITE, OFWHITE}}, {1, .2, .28, -.38, .02, .3, 0, 0, {OFWHITE, OFWHITE, OFWHITE}}, {1, -.2, .28, -.38, .02, .3, 0, 0, {OFWHITE, OFWHITE, OFWHITE}}},

    .chair_sph_desc = {{1, .38, .65, -.38, .03, -90, 90, RED}, {1, -.38, .65, -.38, .03, -90, 90, RED}}};

//lamp description
const lamp_t lamp_specs =
    {
        .lamp_cyl_desc =
            {
                {1, 0, -.6, 0, 0.2, .03, 0, 0, {MB, MB, MB}},
                {1, 0, 0, 0, 0.02, .58, 0, 0, {MB, MB, MB}}},

        .lamp_sph_desc =
            {
                {1, 0, .83, 0, .25, -90, -10, YELLOW},
                {1, 0, .66, 0, .08, -90, 90, {1, 1, 0}}

            }};
#endif
