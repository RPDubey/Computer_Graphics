
/*
*@Filename: final.c
*@brief:Implements  CSCI 5229 Project
*certain modifications and additions have been made to professor Schreuder's example
*for this code
*@author:Ravi Prakash Dubey
*@date:06/28/2018
*/

#include "display.h"
#include "keys.h"
#include "CSCIx229.h"
#include "common.h"
#include <time.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

/*************Global Variable***************/

unsigned int texture[NUMBER_OF_TEXTURE]; //  Texture names

int th = 25;  // Azimuth of view angle
int ph = 45;  // Elevation of view angle
int axes = 1; //determines axes options

double dim = DIM; // Dimensions of orthogonal box
double asp = 1;   //aspect ration
int fov = FOV;    //  Field of view (for perspective)
int mode = 2;     //orthogonal,perspective,first person
int obj = 0;      //object to be displayed

//perspective related
double Ex1 = 0;
double Ey1 = 0;
double Ez1 = 0;
double Cx = 0;
double Cy = 0;
double Cz = 0;
double dx = 0;
double dy = 0;
double dz = 0;

const room_dim_t room = {LENGTH, BREATH, HEIGHT};

int zratio = 4;

//bounce ball system related
double p[3] = {XPOS, YPOS, ZPOS};       //ball position
double box_pos[3] = {XPOS, YPOS, ZPOS}; //transparent box position

double thyx;
double thxz;
double le = BOX_LE;
double br = BOX_BR;
double he = BOX_HE;
double rad = 1;
double del = 0.2;
double temp_p[3];
volatile double unorm[3];

//attenuation
double at0 = 1;
double at1 = 1;
double at2 = 0;

//light related
int light = 1; //light source on/off
int rot = 90;
int roty = 40;
int move = 1;
int emission = 0;  // Emission intensity (%)
int ambient = 20;  // Ambient intensity (%)
int diffuse = 100; // Diffuse intensity (%)
int specular = 75; // Specular intensity (%)
int shininess = 3; // Shininess (power of two)
float shiny = 8;   // Shininess (value)
float rep = 1;
double distance = 1.4 * DIM;
int local = 0;
int side = 0;
float sco = 20;
int ld_obj;

double ofst;
/*
 *  Start up GLUT and tell it what to do
 */
int LoadOBJ(const char *file);

int main(int argc, char *argv[])
{

      //some global initialization

      //initil eye and object position
      Ex1 = 0;
      Ey1 = 20;
      Ez1 = 45;
      Cx = 0;
      Cy = 20;
      Cz = Ez1 - 1;

      //intial direction of bounce ball
      thyx = 60;
      thxz = 70;
      unorm[0] = COS(thyx) * SIN(thxz);
      unorm[1] = SIN(thyx);
      unorm[2] = COS(thyx) * COS(thxz);

      ofst = 1 + dim / zratio;

      //  Initialize GLUT and process user parameters
      glutInit(&argc, argv);
      //  Request true color window,double buffered,z buffer
      glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
      glutInitWindowSize(1024, 1024);
      //  Create the window
      glutCreateWindow("Ravi Prakash Dubey - Final");
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

      texture[0] = LoadTexBMP("./texture/painting.bmp");
      texture[1] = LoadTexBMP("./texture/back.bmp");
      texture[2] = LoadTexBMP("./texture/gold.bmp");
      texture[3] = LoadTexBMP("./texture/leaf.bmp");
      texture[4] = LoadTexBMP("./texture/metal.bmp");
      texture[8] = LoadTexBMP("./texture/floor.bmp");
      texture[9] = LoadTexBMP("./texture/pot.bmp");
      texture[10] = LoadTexBMP("./texture/wall1.bmp");
      texture[11] = LoadTexBMP("./texture/roof.bmp");
      texture[12] = LoadTexBMP("./texture/wood.bmp");
      texture[13] = LoadTexBMP("./texture/book.bmp");
      texture[14] = LoadTexBMP("./texture/book1.bmp");
      texture[15] = LoadTexBMP("./texture/book2.bmp");
      texture[16] = LoadTexBMP("./texture/sofa.bmp");
      texture[17] = LoadTexBMP("./texture/water.bmp");
      texture[18] = LoadTexBMP("./texture/stem.bmp");
      texture[19] = LoadTexBMP("./texture/soil1.bmp");
      texture[20] = LoadTexBMP("./texture/door.bmp");
      texture[21] = LoadTexBMP("./texture/glaas.bmp");

      //  Load object
      ld_obj = LoadOBJ("./IronMan.obj");
      ErrCheck("Main");

      //  Pass control to GLUT so it can interact with the user
      glutMainLoop();
      //  Return code
      return 0;
}
