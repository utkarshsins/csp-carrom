#ifndef __MENUBUTTONH__
#define __MENUBUTTONH__
#include "Carrom.h"
#include "Network/Status.h"

extern GLfloat MenuData[2000];
extern GLfloat MenuColorData[2000];
extern GLfloat MenuTextureData[2000];

void ReshapeFunctionMenu(int, int);
void MenuInit();
void MenuDataInit();

void UpdateTheme();

#endif
