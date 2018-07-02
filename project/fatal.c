/*
*@Filename: Fatal.c
*@brief:Implements print message to stderr and exit
*@author:Implemented by professor Schreuder
*@date:06/30/2018
*/

#include "CSCIx229.h"

void Fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}
