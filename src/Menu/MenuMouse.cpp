#include "Menu/MenuMouse.h"

int MenuMouse::MouseX = -1;
int MenuMouse::MouseY = -1;
int MenuMouse::MenuSelected = 0;

bool MenuMouse::BlinkingCursorOn = false;

bool DebugStatus::DebugStatusValue[5] = { true , true, true, true, true};
bool MenuMouse::MouseDown = false;
bool MenuMouse::Wireframe = false;
