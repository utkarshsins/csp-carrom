#ifndef __MENUMOUSE__
#define __MENUMOUSE__
#include <iostream>
#include "Main.h"
#include "Players.h"
#include "Network/Status.h"
#include "Menu/Theme.h"

class DebugStatus
{
	public:
		static void ChangeDebugStatus(int i)
		{
			DebugStatusValue[i] = !DebugStatusValue[i];
		}

		static bool IsDebugOn(int i)
		{
			return DebugStatusValue[i];
		}

	private:
		static bool DebugStatusValue[5];
};

class MenuMouse {
	public:
		static int MouseMenuX(int x)
		{
			MouseX = x;
			return MouseX;
		}
		static int MouseMenuX()
		{
			return MouseX;
		}
		static int MouseMenuY(int y)
		{
			MouseY = y;
			return MouseY;
		}
		static int MouseMenuY()
		{
			return MouseY;
		}

		static void MouseMenuFunction(int x, int y)
		{
			MouseMenuX(x);
			MouseMenuY(y);	
			if(MouseDown)
				SetMenuSelected(GLUT_LEFT_BUTTON, GLUT_DOWN, x, y);
			glutPostRedisplay();
		}
		
		static bool IsMouseOnMenuButton(int i)
		{
			if(MouseY >= 5 && MouseY <= 5+50)
				if(MouseX >= 5+(windowX-10)*i/5.f && MouseX <= 5+(windowX-10.f)*(i+1)/5.f)
					return true;
			return false;
		}
		
		static bool IsMenuSelected(int i)
		{
			if(i==MenuSelected)
				return true;
			return false;
		}

		static bool IsMouseOnDebugButton(int i)
		{
			if(IsMenuSelected(1))
				if(MouseY >= 60 && MouseY <= 240)
					if(MouseX >= 5+(windowX-10)*i/5.f && MouseX <= 5+(windowX-10.f)*(i+1)/5.f)
						return true;
			return false;
		}
		
		static bool IsMouseOnSettings(int i)
		{
			if(IsMenuSelected(3))
				if(MouseY >= 60 && MouseY <= 240)
					if(MouseX >= 5+(windowX-10)*i/5.f && MouseX <= 5+(windowX-10.f)*(i+1)/5.f)
						return true;
			return false;
		}
	
		static bool IsMouseOnLocalPlayers(int i)
		{
			if(IsMouseOnSettings(0))
				if(MouseY >= 105 && MouseY <= 150)
					if(MouseX >= 5+(windowX-10)*i/5.f/4.f && MouseX <= 5+(windowX-10)*(i+1)/5.f/4.f)
						return true;
			return false;
		}
		
		static bool IsMouseOnWireframe()
		{
			if(IsMouseOnSettings(0))
				if(MouseY >= 150 && MouseY <= 240)
					if(MouseX >= 5 && MouseX <= 5+(windowX-10)/5.f)
						return true;
			return false;
		}
			
				
		static bool IsMouseOnRGB(int state)
		{
			int i;
			if(IsMenuSelected(2) && state == GLUT_DOWN)
			{
				if(MouseX >= 5+(windowX-10)/3.f && MouseX <= 5+(windowX-10)*2.f/3.f)
					if(MouseY >= 60 && MouseY <=240)
					{
						GLfloat mid = windowX / 2.f;
						mid = mid + (windowX-10.f) / 9.f / 2.f;
						GLfloat MouseRGBX = ((MouseX - mid)/(windowX*2.f/25.f) + 1.f)/2.f;
						MouseRGBX = MouseRGBX * 255;
						
						if(MouseRGBX < 0)
							MouseRGBX = 0;
						else if(MouseRGBX > 255)
							MouseRGBX = 255;
	
						if(MouseY >= 60 && MouseY <120)
							i = 0;
						else if(MouseY >=120 && MouseY <180)
							i = 1;
						else
							i = 2;

						Theme::ChangeRGB(i, MouseRGBX);
					}
			}
			return false;
		}

		static void SetMenuSelected(int button, int state, int x, int y)
		{
			if(button == GLUT_LEFT_BUTTON)
			{
				for(int i = 0; i<5; i++)
					if(IsMouseOnMenuButton(i))
						MenuSelected = i;
					else if(IsMouseOnDebugButton(i) && state == GLUT_DOWN)
						DebugStatus::ChangeDebugStatus(i);
				IsMouseOnRGB(state);
				for(int i = 0; i < 4; i++)
					if(IsMouseOnLocalPlayers(i))
						Players::MyNumberOfPlayers = i+1;
				
				if(IsMouseOnWireframe() && state == GLUT_DOWN)
				{
					Wireframe = !Wireframe;
					glutSetWindow(GAMEWINDOW);
					glutPostRedisplay();
					glutSetWindow(MENUWINDOW);
				}
			}

			if(state == GLUT_DOWN)
				MouseDown = true;
			else
				MouseDown = false;

			glutSetWindow(MENUWINDOW);
			glutPostRedisplay();
		}

		static void CursorDisplayChange(int i)
		{
			glutSetWindow(MENUWINDOW);
			BlinkingCursorOn = !BlinkingCursorOn;

			glutTimerFunc(1000, MenuMouse::CursorDisplayChange, 0);
			glutPostRedisplay();
		}

		static bool IsCursorOn()
		{
			return BlinkingCursorOn;
		}
		
		static bool IsWireframeOn()
		{
			return Wireframe;
		}

	private:
		static int MouseX, MouseY;
		static int MenuSelected;
		static bool BlinkingCursorOn;
		static bool MouseDown;
		static bool Wireframe;
};

class MenuKeyboard
{
	public:
		static void KeyPress(unsigned char key, int x, int y)
		{
			char *NetIP = NetworkStatus::ReturnNetworkIP();
			int PositionToInsert = strlen(NetIP);

			if(key == 8)
				if(PositionToInsert>0)
					NetIP[PositionToInsert-1] = '\0';
				else;
			else if(key == 13)
				std::cout << "Pressed Enter. Change State." << std::endl;
			else if(PositionToInsert < 15)
				NetIP[PositionToInsert] = key;

			glutSetWindow(MENUWINDOW);
			glutPostRedisplay();
			//NetworkStatus::ChangeIP(NetIP);
		}
};


#endif
