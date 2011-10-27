#include "Menu/MenuMouse.h"

int MenuMouse::MouseX = -1;
int MenuMouse::MouseY = -1;
int MenuMouse::MenuSelected = 0;

bool MenuMouse::BlinkingCursorOn = false;

bool DebugStatus::DebugStatusValue[5] = { false };
bool MenuMouse::MouseDown = false;
