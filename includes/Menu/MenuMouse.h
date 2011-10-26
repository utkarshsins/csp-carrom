#ifndef __MENUMOUSE__
#define __MENUMOUSE__
#include <iostream>
#include "Main.h"

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
		
		static void SetMenuSelected(int button, int state, int x, int y)
		{
			if(button == GLUT_LEFT_BUTTON)
				for(int i = 0; i<5; i++)
					if(IsMouseOnMenuButton(i))
						MenuSelected = i;
		}

	private:
		static int MouseX, MouseY;
		static int MenuSelected;
};

#endif
