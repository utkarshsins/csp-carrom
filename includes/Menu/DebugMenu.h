#ifndef __DEBUGMENUH__
#define __DEBUGMENUH__

#include "Carrom.h"
#include "Main.h"
#include <GL/freeglut.h>

void DrawNetworkDebug();
void DrawGraphicsDebug();
void DrawPhysicsDebug();
void DrawGameDebug();
void DrawAIDebug();
void CheckDebugSelected(int);
void DrawDebugTick(int);

#endif
