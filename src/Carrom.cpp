#include <iostream>
#include "Carrom.h"
#include "Coin.h"
#include<GL/freeglut.h>
#include "Main.h"

#define RADIUS_HOLE (4.5f/2.f/74.0f)
#define COIN_RADIUS (3.1f/74.f)
#define COIN_HEIGHT (0.8f*2.f/74.f)

GLfloat CarromBaseData[2000];
GLfloat CarromColorData[2000];
GLfloat CarromNormalData[2000];
GLfloat CarromTextureData[2000];
GLubyte CarromVerticalBorderOut[2000];
GLubyte CarromTopIn[2000];
GLubyte CarromVerticalBorderIn[2000];
GLuint CarromCoinFace[100];
//GLuint CarromBase[2000];


GLuint listID;
GLuint textureID[10];

void CarromBaseInit(GLfloat scale)
{
	GLfloat height = 2.5f/74.f;

	for(int i = 0; i<120; i=i+12)
	{
		CarromBaseData[i] = scale * (0.05f * (1.f - sin((double) i*M_PI/2.0/120.0)) - 0.05f);
		CarromBaseData[i+1] = scale * (0.05f * (1.f - cos((double) i*M_PI/2.0/120.0)) - 0.05f);
		CarromBaseData[i+2] = scale * 0;
		CarromBaseData[i+3] = CarromBaseData[i];
		CarromBaseData[i+4] = CarromBaseData[i+1];
		CarromBaseData[i+5] = scale * height;
		CarromBaseData[i+6] = scale * 0.05f + CarromBaseData[i]/2.f;
		CarromBaseData[i+7] = scale * 0.05f + CarromBaseData[i+1]/2.f;
		CarromBaseData[i+8] = CarromBaseData[i+5];
		CarromBaseData[i+9] = CarromBaseData[i+6];
		CarromBaseData[i+10] = CarromBaseData[i+7];
		CarromBaseData[i+11] = CarromBaseData[i+2];

		CarromTextureData[i] = 0.2f; //i/120.f;
		CarromTextureData[i+1] = i/120.f; //0.f;
		CarromTextureData[i+2] = 0.f;
		CarromTextureData[i+3] = 0.2f; //i/120.f;
		CarromTextureData[i+4] = i/120.f; //0.2f;
		CarromTextureData[i+5] = 0.f;
		CarromTextureData[i+6] = 0.f;
		CarromTextureData[i+7] = i/120.f;
		CarromTextureData[i+8] = 0.f;
		CarromTextureData[i+9] = 0.f;
		CarromTextureData[i+10] = i/120.f;
		CarromTextureData[i+11] = 0.f;
		
		CarromNormalData[i] = -sin((double) i*M_PI/2.0/120.0);
		CarromNormalData[i+1] = cos((double) i*M_PI/2.0/120.0);
		CarromNormalData[i+2] = -1.f;
		CarromNormalData[i+3] = CarromNormalData[i];
		CarromNormalData[i+4] = CarromNormalData[i+1];
		CarromNormalData[i+5] = 1.f;
		CarromNormalData[i+6] = -CarromNormalData[i];
		CarromNormalData[i+7] = -CarromNormalData[i+1];
		CarromNormalData[i+8] = 1.f;
		CarromNormalData[i+9] = CarromNormalData[i+6];
		CarromNormalData[i+10] = CarromNormalData[i+7];
		CarromNormalData[i+11] = -1.f;
	}
	for(int i = 120; i<240; i=i+12)
	{
		CarromBaseData[i] = scale *  (0.05f * (1.f - cos((double) (i-120)*M_PI/2.0/120.0)) - 0.05f);
		CarromBaseData[i+1] = scale *  (0.95f + 0.05f*sin((double) (i-120)*M_PI/2.0/120.0) + 0.05f);
		CarromBaseData[i+2] = scale *  0;
		CarromBaseData[i+3] = CarromBaseData[i];
		CarromBaseData[i+4] = CarromBaseData[i+1];
		CarromBaseData[i+5] = scale * height;	
		CarromBaseData[i+6] =  scale * 0.05f + CarromBaseData[i]/2.f;
		CarromBaseData[i+7] =  scale * (0.95f +  0.025f*sin((double) (i-120)*M_PI/2.0/120.0));
		CarromBaseData[i+8] = CarromBaseData[i+5];
		CarromBaseData[i+9] = CarromBaseData[i+6];
		CarromBaseData[i+10] = CarromBaseData[i+7];
		CarromBaseData[i+11] = CarromBaseData[i+2];
	
		CarromTextureData[i] = 0.2f; //i/120.f;
		CarromTextureData[i+1] = 1.f + i/120.f; //0.f;
		CarromTextureData[i+2] = 0.f;
		CarromTextureData[i+3] = 0.2f; //i/120.f;
		CarromTextureData[i+4] = 1.f + i/120.f; //0.2f;
		CarromTextureData[i+5] = 0.f;
		CarromTextureData[i+6] = 0.f;
		CarromTextureData[i+7] = 1.f + i/120.f;
		CarromTextureData[i+8] = 0.f;
		CarromTextureData[i+9] = 0.f;
		CarromTextureData[i+10] = 1.f + i/120.f;
		CarromTextureData[i+11] = 0.f;
		
		CarromNormalData[i] = - cos((double) (i-120)*M_PI/2.0/120.0);
		CarromNormalData[i+1] = - sin((double) (i-120)*M_PI/2.0/120.0);
		CarromNormalData[i+2] = -1.f;
		CarromNormalData[i+3] = CarromNormalData[i];
		CarromNormalData[i+4] = CarromNormalData[i+1];
		CarromNormalData[i+5] = 1.f;
		CarromNormalData[i+6] = -CarromNormalData[i];
		CarromNormalData[i+7] = -CarromNormalData[i+1];
		CarromNormalData[i+8] = 1.f;
		CarromNormalData[i+9] = CarromNormalData[i+6];
		CarromNormalData[i+10] = CarromNormalData[i+7];
		CarromNormalData[i+11] = -1.f;
	}
	for(int i = 240; i<360; i=i+12)
	{
		CarromBaseData[i] = scale *  (0.95f + 0.05f*sin((double) (i-240)*M_PI/2.0/120.0) + 0.05f);
		CarromBaseData[i+1] = scale *  (0.95f + 0.05f*cos((double) (i-240)*M_PI/2.0/120.0) + 0.05f);
		CarromBaseData[i+2] = scale *  0;
		CarromBaseData[i+3] = CarromBaseData[i];
		CarromBaseData[i+4] = CarromBaseData[i+1];
		CarromBaseData[i+5] = scale * height;
		CarromBaseData[i+6] = scale * (0.95f + 0.025f*sin((double) (i-240)*M_PI/2.0/120.0));
		CarromBaseData[i+7] = scale *  (0.95f + 0.025f*cos((double) (i-240)*M_PI/2.0/120.0));
		CarromBaseData[i+8] = CarromBaseData[i+5];
		CarromBaseData[i+9] = CarromBaseData[i+6];
		CarromBaseData[i+10] = CarromBaseData[i+7];
		CarromBaseData[i+11] = CarromBaseData[i+2];
	
		CarromTextureData[i] = 0.2f; //i/120.f;
		CarromTextureData[i+1] = 2.f + i/120.f; //0.f;
		CarromTextureData[i+2] = 0.f;
		CarromTextureData[i+3] = 0.2f; //i/120.f;
		CarromTextureData[i+4] = 2.f + i/120.f; //0.2f;
		CarromTextureData[i+5] = 0.f;
		CarromTextureData[i+6] = 0.f;
		CarromTextureData[i+7] = 2.f + i/120.f;
		CarromTextureData[i+8] = 0.f;
		CarromTextureData[i+9] = 0.f;
		CarromTextureData[i+10] = 2.f + i/120.f;
		CarromTextureData[i+11] = 0.f;
		
		CarromNormalData[i] = sin((double) (i-240)*M_PI/2.0/120.0);
		CarromNormalData[i+1] = -cos((double) (i-240)*M_PI/2.0/120.0);
		CarromNormalData[i+2] = -1.f;
		CarromNormalData[i+3] = CarromNormalData[i];
		CarromNormalData[i+4] = CarromNormalData[i+1];
		CarromNormalData[i+5] = 1.f;
		CarromNormalData[i+6] = -CarromNormalData[i];
		CarromNormalData[i+7] = -CarromNormalData[i+1];
		CarromNormalData[i+8] = 1.f;
		CarromNormalData[i+9] = CarromNormalData[i+6];
		CarromNormalData[i+10] = CarromNormalData[i+7];
		CarromNormalData[i+11] = -1.f;
	}
	for(int i = 360; i<480; i=i+12)
	{
		CarromBaseData[i] = scale * (0.95f + 0.05f*cos((double) (i-360)*M_PI/2.0/120.0) + 0.05f);
		CarromBaseData[i+1] = scale * ( 0.05f*(1.f - sin((double) (i-360)*M_PI/2.0/120.0)) - 0.05f);
		CarromBaseData[i+2] = scale * 0;
		CarromBaseData[i+3] = CarromBaseData[i];
		CarromBaseData[i+4] = CarromBaseData[i+1];
		CarromBaseData[i+5] = scale * height;	
		CarromBaseData[i+6] = scale * (0.95f + 0.025f*cos((double) (i-360)*M_PI/2.0/120.0));
		CarromBaseData[i+7] = scale * (0.025f +  0.025f*(1.f - sin((double) (i-360)*M_PI/2.0/120.0)));
		CarromBaseData[i+8] = CarromBaseData[i+5];
		CarromBaseData[i+9] = CarromBaseData[i+6];
		CarromBaseData[i+10] = CarromBaseData[i+7];
		CarromBaseData[i+11] = CarromBaseData[i+2];
	
		CarromTextureData[i] = 0.2f; //i/120.f;
		CarromTextureData[i+1] = 3.f + i/120.f; //0.f;
		CarromTextureData[i+2] = 0.f;
		CarromTextureData[i+3] = 0.2f; //i/120.f;
		CarromTextureData[i+4] = 3.f + i/120.f; //0.2f;
		CarromTextureData[i+5] = 0.f;
		CarromTextureData[i+6] = 0.f;
		CarromTextureData[i+7] = 3.f + i/120.f;
		CarromTextureData[i+8] = 0.f;
		CarromTextureData[i+9] = 0.f;
		CarromTextureData[i+10] = 3.f + i/120.f;
		CarromTextureData[i+11] = 0.f;
		
		CarromNormalData[i] = cos((double) (i-360)*M_PI/2.0/120.0);
		CarromNormalData[i+1] = sin((double) (i-360)*M_PI/2.0/120.0);
		CarromNormalData[i+2] = -1.f;
		CarromNormalData[i+3] = CarromNormalData[i];
		CarromNormalData[i+4] = CarromNormalData[i+1];
		CarromNormalData[i+5] = 1.f;
		CarromNormalData[i+6] = -CarromNormalData[i];
		CarromNormalData[i+7] = -CarromNormalData[i+1];
		CarromNormalData[i+8] = 1.f;
		CarromNormalData[i+9] = CarromNormalData[i+6];
		CarromNormalData[i+10] = CarromNormalData[i+7];
		CarromNormalData[i+11] = -1.f;
	}
	for(int i=480; i<492; i=i+12)
	{
		CarromBaseData[i] = scale * (0.05f * (1.f - sin((double) (i-480)*M_PI/2.0/12.0)) - 0.05f);
		CarromBaseData[i+1] = scale * (0.05f * (1.f - cos((double) (i-480)*M_PI/2.0/12.0)) - 0.05f);
		CarromBaseData[i+2] = scale * 0;
		CarromBaseData[i+3] = CarromBaseData[i];
		CarromBaseData[i+4] = CarromBaseData[i+1];
		CarromBaseData[i+5] = scale * height;
		CarromBaseData[i+6] = scale * 0.05f + CarromBaseData[i]/2.f;
		CarromBaseData[i+7] = scale * 0.05f + CarromBaseData[i+1]/2.f;
		CarromBaseData[i+8] = CarromBaseData[i+5];
		CarromBaseData[i+9] = CarromBaseData[i+6];
		CarromBaseData[i+10] = CarromBaseData[i+7];
		CarromBaseData[i+11] = CarromBaseData[i+2];
	
		CarromTextureData[i] = 0.2f; //i/120.f;
		CarromTextureData[i+1] = 4.f + i/120.f; //0.f;
		CarromTextureData[i+2] = 0.f;
		CarromTextureData[i+3] = 0.2f; //i/120.f;
		CarromTextureData[i+4] = 4.f + i/120.f; //0.2f;
		CarromTextureData[i+5] = 0.f;
		CarromTextureData[i+6] = 0.f;
		CarromTextureData[i+7] = 4.f + i/120.f;
		CarromTextureData[i+8] = 0.f;
		CarromTextureData[i+9] = 0.f;
		CarromTextureData[i+10] = 4.f + i/120.f;
		CarromTextureData[i+11] = 0.f;
		
		CarromNormalData[i] = -sin((double) i*M_PI/2.0/120.0);
		CarromNormalData[i+1] = cos((double) i*M_PI/2.0/120.0);
		CarromNormalData[i+2] = -1.f;
		CarromNormalData[i+3] = CarromNormalData[i];
		CarromNormalData[i+4] = CarromNormalData[i+1];
		CarromNormalData[i+5] = 1.f;
		CarromNormalData[i+6] = -CarromNormalData[i];
		CarromNormalData[i+7] = -CarromNormalData[i+1];
		CarromNormalData[i+8] = 1.f;
		CarromNormalData[i+9] = CarromNormalData[i+6];
		CarromNormalData[i+10] = CarromNormalData[i+7];
		CarromNormalData[i+11] = -1.f;
	}
	for(int i = 0, j = 0; i<492; i=i+4, j=j+2)
	{
		CarromVerticalBorderOut[j] = i;
		CarromVerticalBorderOut[j+1] = i+1;

		CarromTopIn[j] = i+1;
		CarromTopIn[j+1] = i+2;

		CarromVerticalBorderIn[j] = i+2;
		CarromVerticalBorderIn[j+1] = i+3;

		CarromColorData[i] = 1.f;
		CarromColorData[i+1] = 1.f;
		CarromColorData[i+2] = 1.f;
		CarromColorData[i+3] = 1.f;
	}
	
	{
		int i = 492;
	CarromColorData[i] = 0.7215f;
	CarromColorData[i+1] = 0.4509f;
	CarromColorData[i+2] = 0.1249f;
	CarromBaseData[i] = scale * 0.025f;
	CarromBaseData[i+1] = scale * 0.025f;
	CarromBaseData[i+2] = 0.f;
	CarromTextureData[i] = 0.f;
	CarromTextureData[i+1] = 0.f;
	CarromTextureData[i+2] = 0.f;
	CarromNormalData[i] = 0.f;
	CarromNormalData[i+1] = 0.f;
	CarromNormalData[i+2] = 1.f;

	i = 495;
	CarromColorData[i] = 0.7215f;
	CarromColorData[i+1] = 0.4509f;
	CarromColorData[i+2] = 0.1249f;
	CarromBaseData[i] = scale * 0.975f;
	CarromBaseData[i+1] = scale * 0.025f;
	CarromBaseData[i+2] =0.f;
	CarromTextureData[i] = 1.f;
	CarromTextureData[i+1] = 0.f;
	CarromTextureData[i+2] = 0.f;
	CarromNormalData[i] = 0.f;
	CarromNormalData[i+1] = 0.f;
	CarromNormalData[i+2] = 1.f;

	i = 498;
	CarromColorData[i] = 0.7215f;
	CarromColorData[i+1] = 0.4509f;
	CarromColorData[i+2] = 0.1249f;
	CarromBaseData[i] = scale * 0.975f;
	CarromBaseData[i+1] = scale * 0.975f;
	CarromBaseData[i+2] = 0.f;
	CarromTextureData[i] = 1.f;
	CarromTextureData[i+1] = 1.f;
	CarromTextureData[i+2] = 0.f;
	CarromNormalData[i] = 0.f;
	CarromNormalData[i+1] = 0.f;
	CarromNormalData[i+2] = 1.f;

	i = 501;
	CarromColorData[i] = 0.7215f;
	CarromColorData[i+1] = 0.4509f;
	CarromColorData[i+2] = 0.1249f;
	CarromBaseData[i] = scale * 0.025f;
	CarromBaseData[i+1] = scale * 0.975f;
	CarromBaseData[i+2] = 0.f;
	CarromTextureData[i] = 0.f;
	CarromTextureData[i+1] = 1.f;
	CarromTextureData[i+2] = 0.f;
	CarromNormalData[i] = 0.f;
	CarromNormalData[i+1] = 0.f;
	CarromNormalData[i+2] = 1.f;
	}

	for(int i = 504; i<624; i=i+3)
	{
		CarromColorData[i] = 1.f;
		CarromColorData[i+1] = 1.f;
		CarromColorData[i+2] = 1.f;
		CarromBaseData[i] = scale * (0.025f + RADIUS_HOLE*(1.f + cos((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+1] = scale * (0.025f + RADIUS_HOLE*(1.f + sin((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+2] = 0.f;
	}
	for(int i = 624; i<744; i=i+3)
	{
		CarromColorData[i] = 1.f;
		CarromColorData[i+1] = 1.f;
		CarromColorData[i+2] = 1.f;
		CarromBaseData[i] = scale * (0.975f - RADIUS_HOLE*(1.f + cos((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+1] = scale * (0.025f + RADIUS_HOLE*(1.f + sin((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+2] = 0.f;
	}
	for(int i = 744; i<864; i=i+3)
	{
		CarromColorData[i] = 1.f;
		CarromColorData[i+1] = 1.f;
		CarromColorData[i+2] = 1.f;
		CarromBaseData[i] = scale * (0.975f - RADIUS_HOLE*(1.f + cos((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+1] = scale * (0.975f - RADIUS_HOLE*(1.f + sin((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+2] = 0.f;
	}
	for(int i = 864; i<984; i=i+3)
	{
		CarromColorData[i] = 1.f;
		CarromColorData[i+1] = 1.f;
		CarromColorData[i+2] = 1.f;
		CarromBaseData[i] = scale * (0.025f + RADIUS_HOLE*(1.f + cos((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+1] = scale * (0.975f - RADIUS_HOLE*(1.f + sin((double) (i-504)*2.0*M_PI/120)));
		CarromBaseData[i+2] = 0.f;
	}
	
	for(int i = 984; i < 984 + 240; i=i+6)
	{
		 CarromBaseData[i] = COIN_RADIUS * cos((double) (i-984)*2.0*M_PI/240);
		 CarromBaseData[i+1] = COIN_RADIUS * sin((double) (i-984)*2.0*M_PI/240);
		 CarromBaseData[i+2] = 0.f;
		 CarromBaseData[i+3] = CarromBaseData[i];
		 CarromBaseData[i+4] = CarromBaseData[i+1];
		 CarromBaseData[i+5] = COIN_HEIGHT;

		 CarromTextureData[i+3] = (CarromBaseData[i] / COIN_RADIUS + 1.f) / 2.f;
		 CarromTextureData[i+4] = (CarromBaseData[i+1] / COIN_RADIUS +1.f) / 2.f;
		 CarromTextureData[i+5] = 0.f;
		 CarromTextureData[i] = CarromTextureData[i+3];
		 CarromTextureData[i+1] = CarromTextureData[i+4];
		 CarromTextureData[i+2] = 0.f;
	}
	for(int i = 0; i < 40 ; i++)
	{
		 CarromCoinFace[i] = 984 / 3 + i * 2;
		 CarromCoinFace[i+40] = 984 / 3 + i * 2 + 1;
	}
}


void CarromBaseGlInit()
{
	glutSetWindow(GAMEWINDOW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_POINT_SPRITE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColorPointer(3, GL_FLOAT, 0, CarromColorData);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	
	glPolygonOffset(1.f, 1.f);
	glEnable(GL_POLYGON_OFFSET_FILL);
	
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	
	glVertexPointer(3, GL_FLOAT, 0, CarromBaseData);
	glTexCoordPointer(3, GL_FLOAT, 0, CarromTextureData);
	glNormalPointer(GL_FLOAT, 0, CarromNormalData);
	
//	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
//	glLineWidth(4.f);

	glHint(GL_FOG_HINT, GL_NICEST);
	listID = glGenLists(1);
}

void LoadCarromTextures()
{
	glGenTextures(6, textureID);
	
	glBindTexture(GL_TEXTURE_2D, textureID[0]);	
	BMPLoadGL("Textures/DarkWood.bmp");
	
	glBindTexture(GL_TEXTURE_2D, textureID[1]);	
	BMPLoadGL("Textures/Carrom.bmp");

	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	BMPLoadGL("Textures/WhiteCoin.bmp");

	glBindTexture(GL_TEXTURE_2D, textureID[3]);
	BMPLoadGL("Textures/BlackCoin.bmp");

	glBindTexture(GL_TEXTURE_2D, textureID[4]);
	BMPLoadGL("Textures/QueenCoin.bmp");
	
	glBindTexture(GL_TEXTURE_2D, textureID[5]);
	BMPLoadGL("Textures/Striker.bmp");
}

void DrawCarromBoard()
{
	glPushMatrix();
	glTranslated(-1,-1,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glDrawElements(GL_QUAD_STRIP, 82, GL_UNSIGNED_BYTE, CarromVerticalBorderOut);
	glDrawElements(GL_QUAD_STRIP, 82, GL_UNSIGNED_BYTE, CarromTopIn);
	glDrawElements(GL_QUAD_STRIP, 82, GL_UNSIGNED_BYTE, CarromVerticalBorderIn);
	
//	glDisableClientState(GL_COLOR_ARRAY);	
	
	glEnable(GL_POLYGON_OFFSET_FILL);
	
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glDrawArrays(GL_QUADS, 164, 4);
	
	glDisable(GL_POLYGON_OFFSET_FILL);
	glEnableClientState(GL_COLOR_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glDrawArrays(GL_POLYGON, 168, 40);
	glDrawArrays(GL_POLYGON, 208, 40);
	glDrawArrays(GL_POLYGON, 248, 40);
	glDrawArrays(GL_POLYGON, 288, 40);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
