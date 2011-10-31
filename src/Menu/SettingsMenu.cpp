#include "Menu/SettingsMenu.h"

void DrawSettingsMenu()
{
	glPushMatrix();
	glTranslatef(-1.f, 0, 0);
	glScalef(1.f/5.f, (200.f-10.f)/200.f, 1);
	
	DrawRightBorder();
	DrawMiscSettings();

	glTranslatef(1.f, 0, 0);
	
	DrawRightBorder();
//	DrawGraphicsDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	//DrawPhysicsDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
	//DrawGameDebug();

	glTranslatef(1.f, 0, 0);

	DrawRightBorder();
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
}
	
