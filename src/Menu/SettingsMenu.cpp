#include "Menu/SettingsMenu.h"
#include "AIStatus.h"

void DrawHumanMode(int i)
{
	glColor4f(0,0,0,1);
	if(MenuMouse::IsMouseOnAI(i*3))
	{
		glDrawArrays(GL_QUADS, 0, 4);
		glColor4f(1,1,1,1);
	}
	WriteText("HUMAN", -0.75, 0.1);
	float HumanIsOn = 0.25f;
	if(AIStatus::ReturnAIStatusOfPlayer(i) == HUMAN)
		 HumanIsOn = 1.f;
		 
	glPushMatrix();
	glTranslatef(0.65, 0, 0);
	glScalef(0.25, 0.25, 1);
	if(MenuMouse::IsMouseOnAI(i*3))
		glColor4f(1,1,1,HumanIsOn);
	else
		glColor4f(Theme::ReturnRGB(0)/255.f, Theme::ReturnRGB(1)/255.f, Theme::ReturnRGB(2)/255.f,HumanIsOn);
	glDisableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
}

void DrawHarshalAI(int i)
{
	glColor4f(0,0,0,1);
	if(MenuMouse::IsMouseOnAI(i*3 + 1))
	{
		glDrawArrays(GL_QUADS, 0, 4);
		glColor4f(1,1,1,1);
	}
	WriteText("HARSHAL AI", -0.75, 0.1);
	float HumanIsOn = 0.25f;
	if(AIStatus::ReturnAIStatusOfPlayer(i) == AIHARSHAL)
		 HumanIsOn = 1.f;
		 
	glPushMatrix();
	glTranslatef(0.65, 0, 0);
	glScalef(0.25, 0.25, 1);
	if(MenuMouse::IsMouseOnAI(i*3 + 1))
		glColor4f(1,1,1,HumanIsOn);
	else
		glColor4f(Theme::ReturnRGB(0)/255.f, Theme::ReturnRGB(1)/255.f, Theme::ReturnRGB(2)/255.f,HumanIsOn);
	glDisableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
}

void DrawUtkarshAI(int i)
{
	glColor4f(0,0,0,1);
	if(MenuMouse::IsMouseOnAI(i*3 + 2))
	{
		glDrawArrays(GL_QUADS, 0, 4);
		glColor4f(1,1,1,1);
	}
	WriteText("UTKARSH AI", -0.75, 0.1);
	float HumanIsOn = 0.25f;
	if(AIStatus::ReturnAIStatusOfPlayer(i) == AIUTKARSH)
		 HumanIsOn = 1.f;
		 
	glPushMatrix();
	glTranslatef(0.65, 0, 0);
	glScalef(0.25, 0.25, 1);
	if(MenuMouse::IsMouseOnAI(i*3 + 2))
		glColor4f(1,1,1,HumanIsOn);
	else
		glColor4f(Theme::ReturnRGB(0)/255.f, Theme::ReturnRGB(1)/255.f, Theme::ReturnRGB(2)/255.f,HumanIsOn);
	glDisableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
}
		 
		 
void DrawPlayerMode(int i)
{
	glColor4f(0,0,0,1);
	if(i == 0)
		WriteText("Player 1", -0.7, 0.8);
	else if(i==1)
		WriteText("Player 2", -0.7, 0.8);
	else if(i==2)
		WriteText("Player 3", -0.7, 0.8);
	else
		WriteText("Player 4", -0.7, 0.8);
		
	glPushMatrix();
	glScalef(1, 0.25, 1);
	glTranslatef(0,1,0);
	DrawHumanMode(i);
	glTranslatef(0,-2, 0);
	DrawHarshalAI(i);
	glTranslatef(0,-2, 0);
	DrawUtkarshAI(i);
	glPopMatrix();
}

void DrawSettingsMenu()
{
	glPushMatrix();
	glTranslatef(-1.f, 0, 0);
	glScalef(1.f/5.f, (200.f-10.f)/200.f, 1);
	
	DrawRightBorder();
	DrawMiscSettings();

	glTranslatef(1.f, 0, 0);
	
	DrawRightBorder();
	DrawPlayerMode(0);
//	DrawGraphicsDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	DrawPlayerMode(1);
	//DrawPhysicsDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	DrawPlayerMode(2);
	//DrawGameDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	DrawPlayerMode(3);
	//DrawAIDebug();

	glPopMatrix();
}

void DrawLocalPlayer(int i)
{
	if(i == 0)
		WriteText("1", -1, 0);
	else if(i==1)
		WriteText("2", -1, 0);
	else if(i==2)
		WriteText("3", -1, 0);
	else
		WriteText("4", -1, 0);
		
	float LocalIsOn = 0.25f;
	if(i+1 == Players::MyNumberOfPlayers)
		 LocalIsOn = 1.f;
		 
	glPushMatrix();
	glTranslatef(0.65, 0, 0);
	glScalef(0.25, 0.5, 1);
	if(MenuMouse::IsMouseOnLocalPlayers(i))
		glColor4f(1,1,1,LocalIsOn);
	else
		glColor4f(Theme::ReturnRGB(0)/255.f, Theme::ReturnRGB(1)/255.f, Theme::ReturnRGB(2)/255.f,LocalIsOn);
	glDisableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
	
}

void DrawWireframe()
{
	glColor4f(0,0,0,1);
	if(MenuMouse::IsMouseOnWireframe())
	{
		glDrawArrays(GL_QUADS, 0, 4);
		glColor4f(1,1,1,1);
	}
	WriteText("Wireframe", -0.75, 0.1);
	float WireframeIsOn = 0.25f;
	if(MenuMouse::IsWireframeOn())
		 WireframeIsOn = 1.f;
		 
	glPushMatrix();
	glTranslatef(0.65, 0, 0);
	glScalef(0.25, 0.25, 1);
	if(MenuMouse::IsMouseOnWireframe())
		glColor4f(1,1,1,WireframeIsOn);
	else
		glColor4f(Theme::ReturnRGB(0)/255.f, Theme::ReturnRGB(1)/255.f, Theme::ReturnRGB(2)/255.f,WireframeIsOn);
	glDisableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
}
	
void DrawMiscSettings()
{
	glPushMatrix();
	glScalef(1, 0.5, 1);
	glTranslatef(0, 1, 0);
	
	glColor4f(0,0,0,1);
	WriteText("LOCAL PLAYERS", -0.75f, 0.75f);
	glPopMatrix();
	
	glPushMatrix();
	glScalef(1, 0.25, 1);
	glTranslatef(-0.75, 1, 0);
	glScalef(0.25, 1, 1);
	
	for(int i = 0; i < 4 ; i++)
	{
		if(MenuMouse::IsMouseOnLocalPlayers(i))
		{
			glDrawArrays(GL_QUADS, 0, 4);			
			glColor4f(1,1,1,1);
		}
		else
			glColor4f(0,0,0,1);
		DrawLocalPlayer(i);
		glTranslatef(2,0,0);
	}
	glPopMatrix();
	
	glPushMatrix();
	glScalef(1, 0.5, 1);
	glTranslatef(0, -1, 0);
	DrawWireframe();
	glPopMatrix();
}
	
