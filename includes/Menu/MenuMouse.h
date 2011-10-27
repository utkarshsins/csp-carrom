#ifndef __MENUMOUSE__
#define __MENUMOUSE__
#include <iostream>
#include "Main.h"

#include "Network/Status.h"

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
		
		static void SetMenuSelected(int button, int state, int x, int y)
		{
			if(button == GLUT_LEFT_BUTTON)
				for(int i = 0; i<5; i++)
					if(IsMouseOnMenuButton(i))
						MenuSelected = i;
					else if(IsMouseOnDebugButton(i) && state == GLUT_DOWN)
						DebugStatus::ChangeDebugStatus(i);

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

	private:
		static int MouseX, MouseY;
		static int MenuSelected;
		static bool BlinkingCursorOn;
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
