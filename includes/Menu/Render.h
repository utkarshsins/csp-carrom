#ifndef __MENURENDERH__
#define __MENURENDERH__
#include "Carrom.h"
#include "Main.h"
#include <GL/freeglut.h>
#include "Network/Status.h"
#include "Menu/DebugMenu.h"
#include "Menu/Theme.h"


void MenuGlInit();
void DrawMenuButton();
void DrawMenuFrame();

void DrawGameMenu();
void DrawDebugMenu();
void DrawThemeMenu();

void DrawNetwork();

void DrawConnectToBox();
void DrawRightBorder();


void DrawRed();
void DrawBlue();
void DrawGreen();

void WriteText(const char *, GLfloat, GLfloat);
#endif
