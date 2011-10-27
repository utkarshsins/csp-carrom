#include "Menu/DebugMenu.h"

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
	WriteText("PHYSICS", -1.f, 0.5f);
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
	GLfloat DebugIsOn = 0.25f;
	if(DebugStatus::IsDebugOn(i))
		DebugIsOn = 1.f;

	glPushMatrix();
	
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
