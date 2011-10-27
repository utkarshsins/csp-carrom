#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include"Main.h"
#include"BMPLoader.h"
#include"Mouse.h"
#include"AI.h"

#define PI M_PI
#define CAMERA_Y -0.6*ALPHA
#define CAMERA_Z 1.2*ALPHA

float position=3;
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
//GLfloat pivotPos[3]={0,0,0};
GLfloat  fixate_translate[3];

GLfloat cameraPos[3]={0,CAMERA_Y,CAMERA_Z};
GLfloat cameraLook[3]={(0-cameraPos[0])/PERSP_ZOOM,(0-cameraPos[1])/PERSP_ZOOM,0};
GLfloat persp_rot=0;
GLfloat pointer_angle=0,pointer_length;
GLfloat turn_rotation=0, turn_animation=0;
GLfloat last_x=0,last_y=0;
GLboolean coin_pocketed=false;

int mouseX,mouseY, windowX, windowY;
std::mutex m;
//int rot=0;
int dir=1;
int player=1;
int total_players=2;
int frame=0;

CarromCoin coins[6];

GLboolean moving,adjusting, striker_lock=false,camera_movable=true;

void ReshapeFunctionGame(int w, int h)
{
	glutSetWindow(GAMEWINDOW);
	glViewport(0, 0, w, h);
}

void ReshapeFunction(int w, int h)
{
	std::cout << "Window width = "<< w << ", height = "<< h <<std::endl;
	windowX=w;
	windowY=h - 250;

	glutSetWindow(MENUWINDOW);
	glutReshapeWindow(w, 250);

	glutSetWindow(GAMEWINDOW);
	glutReshapeWindow(w, h-250);

	setCamera();
}
void setCamera()
{
	glutSetWindow(GAMEWINDOW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)(windowX)/windowY,0.5,300);
	for(int i=0;i<2;i++)
		cameraLook[i]=-cameraPos[i]/PERSP_ZOOM;
	cameraLook[2]=0;
	gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook)/*(0-cameraPos[0])/PERSP_ZOOM,(0-cameraPos[1])/PERSP_ZOOM*/,0,0,1);
	glRotated(persp_rot,0,0,1);
}

void drawStriker()
{
	glutSetWindow(GAMEWINDOW);
	coins[0].DrawCoin();
}

void RenderGame(void)
{
	glutSetWindow(GAMEWINDOW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,0.7);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();

	glRotated(turn_rotation, 0,0,1);

	if(camera_movable)
		glTranslated(0-coins[0].CenterX,0-coins[0].CenterY,COIN_HEIGHT);
	else
		glTranslated(fixate_translate[0],fixate_translate[1],COIN_HEIGHT);

	glRotated(turn_animation,0,0,1);
	DrawCarromBoard();

	for(int i=0;i<6;i++)
		if(coins[i].scored==0)
			coins[i].DrawCoin();

//	DrawMenuButton();

	if(striker_lock)
		drawPointer();
	glutSwapBuffers();
}

void nextTurn()
{
	striker_lock=false;

	if(!coin_pocketed)
	{
		player++;
		if(player==total_players+1)
			player=1;
		rotateCam(180);
	}

	coin_pocketed=false;

	coins[0].CenterX=-SHIFT*sin(turn_rotation*PI/180);
	coins[0].CenterY=-SHIFT*cos(turn_rotation*PI/180);

//	if(player==2)
//		AIStriker();
//	else
		goPersp();
}

void drawPointer()
{
	glutSetWindow(GAMEWINDOW);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(0,0,COIN_HEIGHT);
	glRotated(pointer_angle, 0,0,1);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,pointer_length);
	glEnd();

	glPopMatrix();
}

void idle()
{
	glutSetWindow(GAMEWINDOW);
	glutPostRedisplay();
}

void rotateCam(int requirement)
{
	glutSetWindow(GAMEWINDOW);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0-coins[0].CenterX,0-coins[0].CenterY,COIN_HEIGHT);
	GLdouble rotate=8.0;
	while(rotate>0.00001&&((turn_animation))<=requirement-0.3)
	{
		turn_animation+=(rotate);
		rotate*=(int)turn_animation%requirement>requirement*0.8?0.97:0.96;
		RenderGame();
	}

	turn_rotation+=requirement;
	turn_animation=0;
}

void goTop()
{
	glutSetWindow(GAMEWINDOW);
	bool sin0=(-0.00001<=sin(turn_rotation*PI/180))&&(sin(turn_rotation*PI/180)<=0.00001);
	bool cos0=(-0.00001<=cos(turn_rotation*PI/180))&&(cos(turn_rotation*PI/180)<=0.00001);
	float angle=turn_rotation*PI/180;

	printf("bools sin:%d cos:%d\n",sin0,cos0);

	float camX,camY;
	if(sin0)
	{
		camX=coins[0].CenterX;
		camY=coins[0].CenterY;
	}
	else
	{
		camX=-coins[0].CenterY;
		camY=coins[0].CenterX;
	}

	if(cos(angle)<=-0.99||sin(angle)<=-0.99)
	{
		camX*=-1;
		camY*=-1;
	}

	float to_rotate=persp_rot;

	glMatrixMode(GL_PROJECTION);

	float to_fly[3],to_look[3];

	to_fly[0]=cameraPos[0]+camX;
	to_look[0]=cameraLook[0]+camX;

	to_fly[1]=cameraPos[1]+camY;
	to_look[1]=cameraLook[1]+camY;

	to_fly[2]=cameraPos[2]-3;
	to_look[2]=cameraLook[2];

	float gradiant=10;
	for(int i=0;i<gradiant;i++)
	{
		for(int j=0;j<3;j++)
		{
			cameraPos[j]-=(to_fly[j]/gradiant);
			cameraLook[j]-=(to_look[j]/gradiant);
		}

		persp_rot-=to_rotate/gradiant;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,(float)(windowX)/windowY,0.5,300);
		gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,1,0);//cameraPos[0],SHIFT*(i+1)/gradiant,0,0,1,0);

		RenderGame();
	}
}

void goPersp()
{
	glutSetWindow(GAMEWINDOW);
	GLfloat to_look[3],to_fly[3];
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_movable=true;

	cameraPos[0]=cameraLook[0]=0;
	cameraPos[1]=cameraLook[1]=SHIFT;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)(windowX)/windowY,0.5,300);
	gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,1,0);//cameraPos[0],SHIFT*(i+1)/gradiant,0,0,1,0);

	RenderGame();
	to_fly[0]=cameraPos[0]-0;
	to_fly[1]=cameraPos[1]-CAMERA_Y;
	to_fly[2]=cameraPos[2]-CAMERA_Z;

	to_look[0]=0*cameraLook[0]+0;
	to_look[1]=cameraLook[1]+CAMERA_Y/PERSP_ZOOM;
	to_look[2]=cameraLook[2];

	int gradiant=30;//10;
	
	for(int i=0;i<gradiant;i++)
	{
		for(int j=0;j<3;j++)
		{
			cameraPos[j]-=to_fly[j]/gradiant;
			cameraLook[j]-=to_look[j]/gradiant;
		}
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		gluPerspective(45,(float)(windowX)/windowY,0.5,300);
		gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,(gradiant-i-1.0f)/gradiant,(i+1.0f)/gradiant);//cameraPos[0],SHIFT*(i+1)/gradiant,0,0,1,0);

		RenderGame();
	}

	camera_movable=true;
	RenderGame();
}

void key(unsigned char a, int b, int y)
{
}

void init(void)
{
	GLfloat light_position[] = { -1.0, -3.0, 4.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
//	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);


	CarromBaseGlInit();
	CarromBaseInit(ALPHA);	
	LoadCarromTextures();

	coins[0].SetXY(0,0-SHIFT);
	coins[0].IsStriker = true;
	coins[0].CoinMass = CARROMSTRIKER_MASS;
	coins[0].radius=COIN_RADIUS*1.2;

	coins[2].IsWhite=true;
	coins[2].SetXY(-0.25,-0.25);
	coins[1].IsWhite=true;
	coins[1].SetXY(-0.4, 0);

	coins[4].SetXY(-0.4, 0.3);
	coins[3].SetXY(0.4, 0.5);

	coins[5].IsQueen=true;

}

int main(int args, char *argv[])
{
	glutInit(&args, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutInitWindowSize(1280, 1024);
	glutInitWindowPosition(480, 300);
	
	glutCreateWindow(argv[0]);
//	glutFullScreen();
	glutReshapeFunc(ReshapeFunction);

	glutCreateSubWindow(glutGetWindow(), 0, 250, 1920, 500);	
	init();
	
	glutReshapeFunc(ReshapeFunctionGame);
	glutDisplayFunc(RenderGame);
	glutIdleFunc(idle);
	glutMotionFunc(moveCam);
	glutPassiveMotionFunc(stopCam);
	glutMouseFunc(MouseButton);
	glutKeyboardFunc(key);

	MenuInit();

	glutMainLoop();

	return 0;
}


