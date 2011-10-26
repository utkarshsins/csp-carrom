#ifndef __MENURENDERH__
#define __MENURENDERH__
#include "Carrom.h"
#include "Main.h"
#include <GL/freeglut.h>
#include "Network/Status.h"

void MenuGlInit();
void DrawMenuButton();
void DrawMenuFrame();

void DrawGameMenu();

void DrawNetwork();

void DrawConnectToBox();

void WriteText(const char *, GLfloat, GLfloat);
#endif
