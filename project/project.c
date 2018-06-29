
/*
*@Filename: hw2.c
*@brief:Implements requirements for CSCI 5229 hw2
*certain modifications and additions have been made to professor Schreuder's example 6
*for this code
*@author:Ravi Prakash Dubey
*@date:06/10/2018
*/

#include "display.h"
#include "keys.h"
#include "CSCIx229.h"
#include "common.h"

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

unsigned int texture[NUMBER_OF_TEXTURE]; //  Texture names

extern double Ex1;
extern double Ey1;
extern double Ez1;

extern double Cx;
extern double Cy;
extern double Cz;

extern room_dim_t room;
/*
 *  Start up GLUT and tell it what to do
 */

extern int zratio;
int main(int argc, char *argv[])
{

      //some global initialization
      Ex1 = 0;
      Ey1 = 16;
      Ez1 = 1 + (double)DIM / zratio;

      Cx = 0;
      Cy = 16;
      Cz = Ez1 - 1;

      //  Initialize GLUT and process user parameters
      glutInit(&argc, argv);
      //  Request true color window,double buffered,z buffer
      glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
      //  Request 500 x 500 pixel window
      glutInitWindowSize(1024, 1024);
      //  Create the window
      glutCreateWindow("Ravi Prakash Dubey hw3");
      //  Tell GLUT to call "display" when the scene should be drawn
      glutDisplayFunc(display);
      //  Tell GLUT to call "reshape" when the window is resized
      glutReshapeFunc(reshape);
      //  Tell GLUT to call "special" when an arrow key is pressed
      glutSpecialFunc(special);
      //  Tell GLUT to call "key" when a key is pressed
      glutKeyboardFunc(key);
      //register idle function, to be called when glut is idle
      glutIdleFunc(idle);

      texture[0] = LoadTexBMP("./texture/mlf.bmp");
      texture[1] = LoadTexBMP("./texture/back.bmp");
      texture[2] = LoadTexBMP("./texture/gold.bmp");
      texture[3] = LoadTexBMP("./texture/leaf.bmp");
      texture[4] = LoadTexBMP("./texture/metal.bmp");
      texture[5] = LoadTexBMP("./texture/logo.bmp");
      texture[6] = LoadTexBMP("./texture/crate.bmp");
      texture[7] = LoadTexBMP("./texture/earth.bmp");
      texture[8] = LoadTexBMP("./texture/floor.bmp");
      texture[9] = LoadTexBMP("./texture/pot.bmp");
      texture[10] = LoadTexBMP("./texture/wall1.bmp");
      texture[11] = LoadTexBMP("./texture/roof.bmp");
      texture[12] = LoadTexBMP("./texture/final.bmp");
      texture[13] = LoadTexBMP("./texture/book.bmp");
      texture[14] = LoadTexBMP("./texture/book1.bmp");
      texture[15] = LoadTexBMP("./texture/book2.bmp");
      texture[16] = LoadTexBMP("./texture/sofa.bmp");
      texture[17] = LoadTexBMP("./texture/water.bmp");

      //  Pass control to GLUT so it can interact with the user
      glutMainLoop();
      //  Return code
      return 0;
}
