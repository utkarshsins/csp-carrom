#ifndef  __CARROMH__
#define  __CARROMH__

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#define COIN_RADIUS (3.1f/74.f)
#define COIN_HEIGHT (0.8f*2.f/74.f)

#include "BMPLoader.h"

void CarromBaseInit(GLfloat = 0.5f);
void CarromBaseGlInit();
void LoadCarromTextures();
void DrawCarromBoard();

void DrawMenuButton();

extern GLfloat CarromBaseData[2000];
extern GLfloat CarromColorData[2000];
extern GLfloat CarromTextureData[2000];
extern GLubyte CarromVerticalBorderOut[2000];
extern GLubyte CarromTopIn[2000];
extern GLubyte CarromVerticalBorderIn[2000];
extern GLuint CarromCoinFace[100];
extern GLuint CarromBase[2000];


extern GLuint listID;
extern GLuint textureID[10];

#endif
