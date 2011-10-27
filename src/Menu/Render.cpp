#include "Menu/Render.h"
#include <GL/gl.h>

//void glWindowPos2i(GLint x, GLint y);
#define GL_GLEXT_PROTOTYPES 1

void MenuGlInit()
{
	glutSetWindow(MENUWINDOW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, MenuColorData);
	glVertexPointer(3, GL_FLOAT, 0, MenuData);

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
		glTranslatef(1.f + 5.f / windowX, 0, 0);
	}
	
	glPopMatrix();
}

void RenderMenu(void)
{
        glutSetWindow(MENUWINDOW);
        glClear(GL_COLOR_BUFFER_BIT);
//        glClearColor(0,0,1,1);
	glClearColor(1,1,1,1);
//      glPushMatrix();

        glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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

void DrawDebugMenu()
{

	// Network, Graphics, Physics, Game, AI
	glPushMatrix();
	glTranslatef(-1.f, 0, 0);
	glScalef(1.f/5.f, (200.f-10.f)/200.f, 1);
	
	DrawRightBorder();
	DrawNetworkDebug();

	glTranslatef(1.f, 0, 0);
	
	DrawRightBorder();
	DrawGraphicsDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	DrawPhysicsDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	DrawGameDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	DrawAIDebug();

	glPopMatrix();
}

void DrawNetworkDebug()
{
	glColor4f(0,0,0,1);
	CheckDebugSelected(0);
	WriteText("NETWORK", -1.f, 0.5f);
	DrawDebugTick(0);
}

void DrawGraphicsDebug()
{
	glColor4f(0,0,0,1);
	CheckDebugSelected(1);
	WriteText("GRAPHICS", -1.f, 0.5f);
	DrawDebugTick(1);
}

void DrawPhysicsDebug()
{
	glColor4f(0,0,0,1);
	CheckDebugSelected(2);
	WriteText("GRAPHICS", -1.f, 0.5f);
	DrawDebugTick(2);
}

void DrawGameDebug()
{
	glColor4f(0,0,0,1);
	CheckDebugSelected(3);
	WriteText("GAME", -1.f, 0.5f);
	DrawDebugTick(3);
}

void DrawAIDebug()
{
	glColor4f(0,0,0,1);
	CheckDebugSelected(4);
	WriteText("A.I.", -1.f, 0.5f);
	DrawDebugTick(4);
}

void DrawDebugTick(int i)
{
	GLfloat DebugIsOn = 0.5f;
	if(DebugStatus::IsDebugOn(i))
		DebugIsOn = 1.f;

	glPushMatrix();

	//DebugIsOn = 0.25f;
	if(MenuMouse::IsMouseOnDebugButton(i))
		glColor4f(1,1,1,DebugIsOn);
	else
		glColor4f(0,0,0,DebugIsOn);

	glDisableClientState(GL_COLOR_ARRAY);
	glTranslatef(0.8f, 0,0);
	glScalef(1.f/10.f * windowY / windowX, 1.f/10.f * windowX / 250, 1);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
}

void CheckDebugSelected(int i)
{
	if(MenuMouse::IsMouseOnDebugButton(i))
	{
		glDrawArrays(GL_QUADS, 0, 4);
		glColor4f(1,1,1,1);
	}
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

