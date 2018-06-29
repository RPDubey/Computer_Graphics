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

//lamp description
const lamp_t lamp_specs =
    {
        .lamp_cyl_desc =
            {
                {1, 0, -.6, 0, 0.2, .03, 0, 0, {BROWN, BROWN, BROWN}},
                {1, 0, 0, 0, 0.02, .58, 0, 0, {BROWN, BROWN, BROWN}}},

        .lamp_sph_desc =
            {
                {1, 0, .83, 0, .25, -90, -10, YELLOW},
                {1, 0, .66, 0, .08, -90, 90, {1, 1, 0}}

            }};
#endif
