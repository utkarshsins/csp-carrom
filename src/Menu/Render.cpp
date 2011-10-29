#include "Menu/Render.h"
#include <GL/gl.h>

//void glWindowPos2i(GLint x, GLint y);
#define GL_GLEXT_PROTOTYPES 1

void MenuGlInit()
{
	GLuint TextureIDMenu[2];

	glutSetWindow(MENUWINDOW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, MenuColorData);
	glVertexPointer(3, GL_FLOAT, 0, MenuData);
	glTexCoordPointer(3, GL_FLOAT, 0, MenuTextureData);
	
	glGenTextures(2, TextureIDMenu);
	glBindTexture(GL_TEXTURE_2D, TextureIDMenu[0]);	
	BMPLoadGL("Textures/Utkarsh.bmp");
	glBindTexture(GL_TEXTURE_2D, TextureIDMenu[1]);	
	BMPLoadGL("Textures/Harshal.bmp");
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	glHint(GL_FOG_HINT, GL_NICEST);
}


void WriteTitle(int i)
{
	GLfloat WriteX = -1.f/3.f;
	GLfloat WriteY = 0.0f;

	glColor4f(1, 1, 1, 1);

	if(i==0)
		WriteText("GAME", WriteX, WriteY);
	else if(i==1)
		WriteText("VERBOSE", WriteX, WriteY);
	else if(i==2)
		WriteText("THEME", WriteX, WriteY);
	else if(i==3)
		WriteText("SETTINGS", WriteX, WriteY);
	else
		WriteText("CREDITS", WriteX, WriteY);
}

void DrawMenuButton()
{
	glutSetWindow(MENUWINDOW);
	glPushMatrix();
	
	glLoadIdentity();
	
	glTranslatef(-1.f + 5.f / windowX, 1.f - 5.f / 250.f, 0.f); 
	glScalef((windowX - 10.f)/5.f/windowX,50.f/250.f,1);	
	glTranslatef(0, -1.f, 0);

	for(int i = 0; i<5; i++)
	{
		glTranslatef(1.f + 5.f / windowX, 0, 0);
		glDrawArrays(GL_QUADS, 0, 4);
		if(MenuMouse::IsMenuSelected(i))
			glDrawArrays(GL_POLYGON, 48, 22);
		else if(MenuMouse::IsMouseOnMenuButton(i))
			glDrawArrays(GL_POLYGON, 4, 22);
		else
			glDrawArrays(GL_POLYGON, 26, 22);

		WriteTitle(i);
		glTranslatef(1.f + 5.f / windowX, 0, 0);
	}
	
	glPopMatrix();
}

void RenderMenu(void)
{
        glutSetWindow(MENUWINDOW);

	glClearColor(1,1,1,0.1f);
	glClear(GL_COLOR_BUFFER_BIT);
//	glClearColor(Theme::ReturnRGB(0)/255.f,Theme::ReturnRGB(1)/255.f,Theme::ReturnRGB(2)/255.f,0);

        glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glColor4f(Theme::ReturnRGB(0)/255.f, Theme::ReturnRGB(1)/255.f, Theme::ReturnRGB(2)/255.f, 0.1f);
	glDisableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnableClientState(GL_COLOR_ARRAY);

	DrawMenuButton();
        DrawMenuFrame();

	glutSwapBuffers();
//	glutPostRedisplay();
}

void DrawMenuFrame()
{
	glutSetWindow(MENUWINDOW);
	glPushMatrix();

	glLoadIdentity();

	glTranslatef(0, -50.f / 250.f, 0);
	glScalef((windowX - 10.f)/windowX, 180.f / 250.f, 1);

	glLineWidth(5.f);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glLineWidth(1.f);

	if(MenuMouse::IsMenuSelected(0))
		DrawGameMenu();
	else if(MenuMouse::IsMenuSelected(1))
		DrawDebugMenu();
	else if(MenuMouse::IsMenuSelected(2))
		DrawThemeMenu();
	else if(MenuMouse::IsMenuSelected(4))
		DrawCreditsMenu();

	glPopMatrix();
}

void DrawGameMenu()
{
	glPushMatrix();
	glTranslatef(-1.f, 0, 0);
	glScalef(1.f/5.f, (200.f-10.f)/200.f, 1);

	DrawRightBorder();
	DrawNetwork();
	glPopMatrix();
}

void DrawSliderTab(int i)
{
	glPushMatrix();
	glTranslatef(1.f/3.f, 0, 0);
	glScalef(.5f, .4f, 1);

	glScalef(2.f/256.f, 1, 1);
	glTranslatef(-256.f/2.f, 0, 0);

	i = Theme::ReturnRGB(i);
	glTranslatef(i, 0, 0);

	glScalef(5,1,1);
	glDrawArrays(GL_QUADS, 0, 4);

	glPopMatrix();
}

void DrawSlider(int i)
{
	glPushMatrix();
	glTranslatef(1.f/3.f, 0, 0);
	glScalef(.5f, .1f ,1 );

	glDrawArrays(GL_QUADS, 0, 4);

	glPopMatrix();
	DrawSliderTab(i);
}

void DrawThemeMenu()
{
	glPushMatrix();
	glScalef(1.f/3.f, (200.f-10.f)/200.f, 1);
	
	glTranslatef(-3.f, 0,0);
	DrawRightBorder();
	glTranslatef(1.f, 0,0);
	DrawRightBorder();

	glScalef(1, 1.f/3.f,1);
	glTranslatef(0, 2, 0);

//	glDrawArrays(GL_QUADS, 0, 4);
	DrawRed();

	glTranslatef(0,-2,0);
	DrawGreen();

	glTranslatef(0,-2,0);
	DrawBlue();

	glPopMatrix();
}

void DrawCreditsMenu()
{
	glPushMatrix();
	glScalef(1.f/3.f, (200.f-10.f)/200.f, 1);

	glTranslatef(-3.f, 0, 0);
	DrawRightBorder();

	DrawPic(0);

	glTranslatef(1.f, 0, 0);
	DrawRightBorder();
	WriteText(" CARROM\n\n  Get a life\n\nAssignment 3\n   CSP301", -1.f/3.f, 0.9f);

	glTranslatef(2.f, 0, 0);
	DrawPic(1);

	glPopMatrix();
}

void DrawPic(int i)
{
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glScalef(180.f*3.f/5.f*3.f/windowX*(200.f-10.f)/200.f,3.f/5.f, 1);
	glTranslatef(1.25f, 0, 0);
	glBindTexture(GL_TEXTURE_2D, i+1);
	glEnable(GL_TEXTURE_2D);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);

	glColor4f(0,0,0,1);
	if(i == 0)
		WriteText("UTKARSH\n2010CS50299\n\"Coding was fun... \n...until IIT happened\"", 1.5f, 0.8f);
	else
		WriteText("HARSHAL\n2010CS50283\n\"Physics Theek Karo...\"", 1.5f, 0.8f);
	glPopMatrix();

}

void DrawRed()
{
	glColor4f(0,0,0,1);
	WriteText("RED", -1.f, 0);
	DrawSlider(0);
}

void DrawGreen()
{
	glColor4f(0,0,0,1);
	WriteText("GREEN", -1.f, 0);
	DrawSlider(1);
}

void DrawBlue()
{
	glColor4f(0,0,0,1);
	WriteText("BLUE", -1.f, 0);
	DrawSlider(2);
}

void DrawNetwork()
{
	glColor4f(0,0,0,1);
	WriteText("NETWORK", -1.f, 1.f);
	if(!NetworkStatus::IsConnected())
		DrawConnectToBox();
//	else 
//		DrawConnectedTo();

}

void DrawRightBorder()
{
	glTranslatef(1.f, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 70, 3);
}

void DrawConnectToBox()
{
	glPushMatrix();

	glDisableClientState(GL_COLOR_ARRAY);

	glScalef(0.8f, 0.2f, 1);

	glColor4f(0,0,0,0.5f);
	glDrawArrays(GL_QUADS, 0, 4);

	glColor4f(1,1,1,1);
	WriteText(NetworkStatus::ReturnNetworkIP(), -1.f, -0.1f);
	if(MenuMouse::IsCursorOn())
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '|');

	glEnableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void WriteText(const char *TextToRender, GLfloat RasterX, GLfloat RasterY)
{
//	glColor4f(0,0,0,1);
	unsigned char *TextToRenderUnsigned = (unsigned char *) TextToRender;
	glRasterPos2f(RasterX + 0.1f, RasterY - 0.2f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, TextToRenderUnsigned);
}

