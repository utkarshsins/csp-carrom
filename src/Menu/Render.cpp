#include "Menu/Render.h"


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
