/*
*@Filename: keys.h
*@brief:declaration for functions in keys.c
*@author:Ravi Prakash Dubey
*@date:06/10/2018
*/

#ifndef KEYS_H
#define KEYS_H

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height);

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y);

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y);

/*
 *  GLUT calls this routine when idle
 */
void idle(void);
#endif