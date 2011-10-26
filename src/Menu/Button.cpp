#include "Menu/Button.h"

GLfloat MenuData[2000];
GLfloat MenuColorData[2000];

void ReshapeFunctionMenu(int w, int h)
{
	glutSetWindow(MENUWINDOW);
	glViewport(0, 0, w, h);
}

void MenuInit()
{
	glutSetWindow(MAINWINDOW);
	glutCreateSubWindow(glutGetWindow(), 0, 0, 1920, 250);
	glutReshapeFunc(ReshapeFunctionMenu);
	glutDisplayFunc(RenderMenu);
	glutPassiveMotionFunc(MenuMouse::MouseMenuFunction);
	glutMouseFunc(MenuMouse::SetMenuSelected);
	
	MenuDataInit();
	MenuGlInit();

	NetworkStatus::ChangeIP("localhost");
	glutTimerFunc(1000, MenuMouse::CursorDisplayChange, 0);
}

void MenuDataInit()
{
	///////// Button Box Back Data
	for(int i = 0; i<12; i=i+12)
	{
		MenuData[i] = -1.f;
		MenuData[i+1] = 1.f;
		MenuData[i+2] = 0.f;
		MenuData[i+3] = 1.f;
		MenuData[i+4] = 1.f;
		MenuData[i+5] = 0.f;
		MenuData[i+6] = 1.f;
		MenuData[i+7] = -1.f;
		MenuData[i+8] = 0.f;
		MenuData[i+9] = -1.f;
		MenuData[i+10] = -1.f;
		MenuData[i+11] = 0.f;
	}

	for(int i = 0; i<12; i++)
		MenuColorData[i] = 0.f;


	///////// Button Mouse Over Shade Data
	{
		int i = 12;
		MenuData[i] = 0.f;
		MenuData[i+1] = -1.f;
		MenuData[i+2] = 0.f;
		MenuColorData[i] = 2.f/3.f;
		MenuColorData[i+1] = 2.f/3.f;
		MenuColorData[i+2] = 2.f/3.f;
	}
	for(int i = 15; i <= 15 + 20*3; i = i+3)
	{
		GLfloat theta  = ((i-15.f)/60.f*M_PI);
		MenuData[i] = -0.5f*cos(theta);
		MenuData[i+1] = -1.f + 0.75f*sin(theta);
		MenuData[i+2] = 0;
		MenuColorData[i] = 0.f;
		MenuColorData[i+1] = 0.f;
		MenuColorData[i+2] = 0.f;
	}
		
	///////// Button Mouse Not Over Shade Data
	{
		int i = 78;
		MenuData[i] = 0.f;
		MenuData[i+1] = -1.f;
		MenuData[i+2] = 0.f;
		MenuColorData[i] = 1/3.f;
		MenuColorData[i+1] = 1/3.f;
		MenuColorData[i+2] = 1/3.f;
	}
	for(int i = 81; i <= 81 + 20*3; i = i+3)
	{
		GLfloat theta  = ((i-81.f)/60.f*M_PI);
		MenuData[i] = -0.5f*cos(theta);
		MenuData[i+1] = -1.f + 0.75f*sin(theta);
		MenuData[i+2] = 0;
		MenuColorData[i] = 0.f;
		MenuColorData[i+1] = 0.f;
		MenuColorData[i+2] = 0.f;
	}		
	
	///////// Menu Selected Shade Data
	{
		int i = 144;
		MenuData[i] = 0.f;
		MenuData[i+1] = -1.f;
		MenuData[i+2] = 0.f;
		MenuColorData[i] = 1.f;
		MenuColorData[i+1] = 1.f;
		MenuColorData[i+2] = 1.f;
	}
	for(int i = 147; i <= 147 + 20*3; i = i+3)
	{
		GLfloat theta  = ((i-147.f)/60.f*M_PI);
		MenuData[i] = -0.5f*cos(theta);
		MenuData[i+1] = -1.f + 0.75f*sin(theta);
		MenuData[i+2] = 0;
		MenuColorData[i] = 0.f;
		MenuColorData[i+1] = 0.f;
		MenuColorData[i+2] = 0.f;
	}

	for(int i = 210; i < 210 + 3*3 ; i=i+3)
	{
		MenuData[i] = 1.f;
		MenuData[i+1] = (i-210.f)/3.f - 1.f;
		MenuData[i+2] = 0.f;
		if(((i-210)/3)%2 == 0)
		{
			MenuColorData[i] = 1.f;
			MenuColorData[i+1] = 1.f;
			MenuColorData[i+2] = 1.f;
		}
		else
		{
			MenuColorData[i] = 0.f;
			MenuColorData[i+1] = 0.f;
			MenuColorData[i+2] = 0.f;
		}
	}
}

