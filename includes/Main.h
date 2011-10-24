#include<GL/freeglut.h>
#include<stdio.h>
#include<cmath>
#include<thread>
#include<mutex>
#include <iostream>
#include"Carrom.h"
#include"Coin.h"
#include"Physics.h"
#define EXPANDARR3(arr) arr[0],arr[1],arr[2]
#define ALPHA 2
#define SHIFT 0.33*ALPHA
#define PERSP_ZOOM 2
#define PLACEMENTWIDTH 0.28*ALPHA

extern GLfloat cameraPos[3];
extern int mouseX,mouseY, windowX, windowY;
extern GLboolean moving,adjusting,striker_lock, camera_movable, coin_pocketed;
extern GLfloat persp_rot;
//extern GLfloat pivotPos[3];
extern GLfloat fixate_translate[3];
extern CarromCoin coins[6];
extern GLfloat cameraLook[3];
extern GLfloat pointer_angle, pointer_length;
extern int player;
extern GLfloat turn_rotation;
extern std::mutex m;

void setCamera();
void ReshapeFunction(int w, int h);
void Render(void);
void scroll(int arbit, int direction, int x, int y);
void idle();
void rotateCam(int);
void init(void);
int main(int args, char *argv[]);
void drawStriker();
void drawPointer();
void goTop();
void goPersp();
void nextTurn();
void drawDebug(float,float);
