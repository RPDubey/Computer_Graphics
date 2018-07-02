/*
*@Filename: errcheck.c
*@brief: Implements check for OpenGL errors
*@author:Implemented by professor Schreuder
*@date:06/28/2018
*/

#include "CSCIx229.h"

void ErrCheck(const char *where)
{
    int err = glGetError();
    if (err)
        fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), where);
}
