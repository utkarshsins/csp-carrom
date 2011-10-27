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
void DrawDebugMenu();

void DrawNetwork();

void DrawConnectToBox();
void DrawRightBorder();

void DrawNetworkDebug();
void DrawGraphicsDebug();
void DrawPhysicsDebug();
void DrawGameDebug();
void DrawAIDebug();

void WriteText(const char *, GLfloat, GLfloat);
#endif
