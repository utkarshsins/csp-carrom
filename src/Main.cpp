#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include"Main.h"
#include"BMPLoader.h"
#include"Mouse.h"
#include"AI.h"

#define PI M_PI
float position=3;
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
//GLfloat pivotPos[3]={0,0,0};
GLfloat  fixate_translate[3];

GLfloat cameraPos[3]={0,-1.0*ALPHA,1.125*ALPHA};
GLfloat cameraLook[3]={(0-cameraPos[0])/PERSP_ZOOM,(0-cameraPos[1])/PERSP_ZOOM,0};
GLfloat persp_rot=0;
GLfloat pointer_angle=0;
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
void ReshapeFunction(int w, int h)
{
	windowX=w;
	windowY=h;
	glViewport(0,0,w,h);
	setCamera();
}
void setCamera()
{
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
	coins[0].DrawCoin();
}

void Render(void)
{
	frame++;
//	printf("%d\n",camera_movable);
//	printf("Camera Set: %f, %f, %f \n", cameraPos[0], cameraPos[1], cameraPos[2]);
//	printf("coin 0 center x: %f\n",coins[0].CenterX);
//	printf("TOTAL_ROT=%f,sin=%f,cos=%f\n",turn_rotation,sin(turn_rotation*PI/180),cos(turn_rotation*PI/180));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,0.7);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();

//	glutSolidSphere(0.1,3,3);
	glRotated(turn_rotation, 0,0,1);

	if(camera_movable)
		glTranslated(0-coins[0].CenterX,0-coins[0].CenterY,COIN_HEIGHT);
	else
		glTranslated(fixate_translate[0],fixate_translate[1],COIN_HEIGHT);
//	printf("%f\n",turn_rotation);

	glRotated(turn_animation,0,0,1);
	DrawCarromBoard();

	for(int i=0;i<6;i++)
		if(coins[i].scored==0)
			coins[i].DrawCoin();

	if(striker_lock)
		drawPointer();
	glutSwapBuffers();
}

void playTurn()
{
	
	camera_movable=false;

	fixate_translate[0]=-coins[0].CenterX;
	fixate_translate[1]=-coins[0].CenterY;
	
	coins[0].VelocityX=sin(((0-pointer_angle+turn_rotation)/180)*PI);
	coins[0].VelocityY=cos(((0-pointer_angle+turn_rotation)/180)*PI);

	goTop();
	std::thread t(engagePhysics,0);
	t.detach();
	striker_lock=false;
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

//	pivotPos[0]=coins[0].CenterX;
//	pivotPos[1]=coins[0].CenterY;
//	fly back to perspective

	goPersp();
//	getchar();
	if(player==2)
		AIStriker();

	//	for(int i=0;i<3;i++)
//	{
//		cameraPos[i]=1+0*pivotPos[i];
//		to_look[i]=cameraLook[i];
//	}
////	cameraPos[0]=0;
////	cameraPos[1]=-1*ALPHA;
////	cameraPos[2]=+1.125*ALPHA;
//	to_look[0]+=pivotPos[0];
////	cameraLook[0]=-cameraPos[0]/PERSP_ZOOM;
////	cameraLook[1]=-cameraPos[1]/PERSP_ZOOM;
////	cameraLook[2]=0;

//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,0,1);
//	getchar();
//	printf("Camera Set: %f, %f, %f \n", cameraPos[0], cameraPos[1], cameraPos[2]);
//	printf("Look Set: %f, %f, %f \n", cameraLook[0], cameraLook[1], cameraLook[2]);
//
//	camera_movable=true;
//	Render();
//	getchar();
}
void drawPointer()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(0,0,COIN_HEIGHT);
	glRotated(pointer_angle, 0,0,1);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,1.25);
	glEnd();

	glPopMatrix();
}

void doStuff();

void idle()
{
	glutPostRedisplay();
}

void rotateCam(int requirement)
{
//	getchar();

	glMatrixMode(GL_MODELVIEW);
//	printf("\n\n\n\n%f\n",turn_animation);
	glLoadIdentity();
	glTranslated(0-coins[0].CenterX,0-coins[0].CenterY,COIN_HEIGHT);
	GLdouble rotate=8.0;
//	float total=0;
	while(rotate>0.00001&&((turn_animation))<=requirement-0.3)
	{
//		glRotated(rotate,0,0,1);
		turn_animation+=(rotate);
//		printf("%f  %f\n",rotate, total);
		rotate*=(int)turn_animation%requirement>requirement*0.8?0.97:0.96;
		Render();
	}

//	getchar();

	turn_rotation+=requirement;
	turn_animation=0;
//	glRotated(180-turn_animation,0,0,1);
//	Render();

//	getchar();
}

//void goTop()
//{
//	bool sin0=(-0.00001<=sin(turn_rotation*PI/180))&&(sin(turn_rotation*PI/180)<=0.00001);
//	bool cos0=(-0.00001<=cos(turn_rotation*PI/180))&&(cos(turn_rotation*PI/180)<=0.00001);
//	float angle=turn_rotation*PI/180;
//
//	printf("bools sin:%d cos:%d\n",sin0,cos0);
//
//	float camX,camY;
//	if(sin0)
//	{
//		camX=coins[0].CenterX;
//		camY=coins[0].CenterY;
//	}
//	else
//	{
//		camX=-coins[0].CenterY;
//		camY=coins[0].CenterX;
//	}
//
//	if(cos(angle)<=-0.99||sin(angle)<=-0.99)
//	{
//		camX*=-1;
//		camY*=-1;
//	}
//	cameraLook[0]=cameraPos[0]=-camX;
//	cameraLook[1]=cameraPos[1]=-camY;
//	cameraLook[2]=0;
//	cameraPos[2]=3;
//
//	persp_rot=0;
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45,(float)(windowX)/windowY,0.5,300);
//	gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,1,0);
//
//	Render();
//}


void goTop()
{
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
//	cameraLook[0]=cameraPos[0]=-camX;
//	cameraLook[1]=cameraPos[1]=-camY;
//	cameraLook[2]=0;
//	cameraPos[2]=3;

	float to_rotate=persp_rot;
//	for(int i=0;i<3;i++)
//	{
//		persp_rot-=to_rotate/3.f;
//		setCamera();
//		Render();
//	}

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
//		getchar();

		for(int j=0;j<3;j++)
		{
			cameraPos[j]-=(to_fly[j]/gradiant);
			cameraLook[j]-=(to_look[j]/gradiant);
		}

		persp_rot-=to_rotate/gradiant;
//		cameraPos[1]=-camY;///gradiant;
//		cameraLook[1]=-camY;///gradiant;
//		setCamera();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,(float)(windowX)/windowY,0.5,300);
		gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,1,0);//cameraPos[0],SHIFT*(i+1)/gradiant,0,0,1,0);
//		glRotated(persp_rot*(gradiant-1-i)/gradiant,0,0,1);

		Render();
	}
}

/*
void goTop()
{
	printf("Entering\n");
	float to_fly[3], to_look[3], to_rotate=persp_rot;
//	getchar();
	int gradiant=10;
//	for(int i=0;i<3;i++)
//	{
////		to_fly[i]=cameraPos[i]+pivotPos[i];
//		to_look[i]=cameraLook[i];
//	}

	for(int i=0;i<3;i++)
	{
		persp_rot-=to_rotate/3.f;
		setCamera();
		Render();
	}
	getchar();
	bool sin0=-0.00001<=sin(turn_rotation*PI/180)&&sin(turn_rotation*PI/180)<=0.00001;

	to_fly[0]=(sin0?coins[0].CenterX:coins[0].CenterY);
	to_fly[1]=cameraPos[1]+((sin0)?(coins[0].CenterY):coins[0].CenterX);
	to_fly[2]=-3+cameraPos[2];

	printf("coin x %f; coin y %f\n",coins[0].CenterX,coins[0].CenterY);
	for(int i=0;i<3;i++)
	{
		printf("Cam pos,look %d : %f,%f\n",i, cameraPos[i],cameraLook[i]);
		printf("DIFF FOR %d is %f\n\n",i,(cameraPos[i]-to_fly[i]));
	}

	to_look[0]=sin0?(coins[0].CenterY):coins[0].CenterX;//*(1-1.0/PERSP_ZOOM);
	to_look[1]=cameraLook[1]+sin0?(co//ins[0].CenterX):coins[0].CenterY;
	to_look[2]=cameraLook[2];

	printf("to fly one %f\ncam1 %f\n",to_fly[1],cameraPos[1]);

	for(int i=0;i<gradiant;i++)
	{
		getchar();
		for(int j=0;j<3;j++)
		{
			cameraPos[j]-=to_fly[j]/gradiant;
			cameraLook[j]-=to_look[j]/gradiant;
		}

//		setCamera();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,(float)(windowX)/windowY,0.5,300);
		gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,1,0);//cameraPos[0],SHIFT*(i+1)/gradiant,0,0,1,0);
//		glRotated(persp_rot*(gradiant-1-i)/gradiant,0,0,1);

		Render();
	}
	printf("to fly zero %f\ncam0 %f\n",to_fly[0],cameraPos[0]);

//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45,(float)(windowX)/windowY,0.5,300);
//	if(-0.00001<=sin(turn_rotation*PI/180)&&sin(turn_rotation*PI/180)<=0.00001)
//		gluLookAt(-coins[0].CenterX,-coins[0].CenterY,3,-coins[0].CenterX,-coins[0].CenterY,0,0,1,0);
//	else
//		gluLookAt(-coins[0].CenterY,-coins[0].CenterX,3,coins[0].CenterY,-coins[0].CenterX,0,0,1,0);
	//basically coins orientation not the same as the cams, check it out

//	Render();
//	cameraPos[0]=to_fly[0];
//	cameraPos[1]=to_fly[1];

//	cameraLook[0]=to_look[0];
//	cameraLook[1]=to_look[1];

	persp_rot=0;
	getchar();
}

*/
void goPersp()
{
//	getchar();

	GLfloat to_look[3],to_fly[3];
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_movable=true;

	cameraPos[0]=cameraLook[0]=0;
	cameraPos[1]=cameraLook[1]=SHIFT;

//	cameraPos[0]-=fixate_translate[0]*cos((turn_rotation-90)*PI/180);
//	cameraLook[0]-=fixate_translate[0]*cos((turn_rotation-90)*PI/180);
//
//	cameraPos[0]-=fixate_translate[1]*-1*sin((turn_rotation-90)*PI/180);
//	cameraLook[0]-=fixate_translate[1]*-1*sin((turn_rotation-90)*PI/180);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)(windowX)/windowY,0.5,300);
	gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,1,0);//cameraPos[0],SHIFT*(i+1)/gradiant,0,0,1,0);

	Render();
//	getchar();

	//	for(int i=0;i<3;i++)
//	{
//		cameraPos[i]-=*fixate_translate[i];
//		cameraLook[i]-=fixate_translate[i];
//	}
	to_fly[0]=cameraPos[0]-0;
	to_fly[1]=cameraPos[1]+1*ALPHA;
	to_fly[2]=cameraPos[2]-1.125*ALPHA;

	to_look[0]=0*cameraLook[0]+0;
	to_look[1]=cameraLook[1]-ALPHA/PERSP_ZOOM;
	to_look[2]=cameraLook[2];

	int gradiant=30;//10;
	
//	printf("Camera Original: %f, %f, %f \n", cameraPos[0], cameraPos[1], cameraPos[2]);
//	printf("Look Original: %f, %f, %f \n", cameraLook[0], cameraLook[1], cameraLook[2]);

	for(int i=0;i<gradiant;i++)
	{
//		printf("Camera Set: %f, %f, %f \n", cameraPos[0], cameraPos[1], cameraPos[2]);

//		getchar();
		for(int j=0;j<3;j++)
		{
			cameraPos[j]-=to_fly[j]/gradiant;
			cameraLook[j]-=to_look[j]/gradiant;
		}
		
//		getchar();
//		fixate_translate[0]-=(fixate_translate[0]-coins[0].CenterX);
//		fixate_translate[1]-=(fixate_translate[1]-coins[0].CenterY);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		gluPerspective(45,(float)(windowX)/windowY,0.5,300);
		gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,(gradiant-i-1.0f)/gradiant,(i+1.0f)/gradiant);//cameraPos[0],SHIFT*(i+1)/gradiant,0,0,1,0);
//		printf("%f,%f,%f\n",0.0,(gradiant-i-1.0f)/(float)gradiant,(i+1.0f)/(float)gradiant);

		Render();
	}

//	printf("Camera Later: %f, %f, %f \n", cameraPos[0], cameraPos[1], cameraPos[2]);
//	printf("Look Later: %f, %f, %f \n", cameraLook[0], cameraLook[1], cameraLook[2]);
//	getchar();
//	gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,0,1);
//	getchar();
	camera_movable=true;
	Render();
//	getchar();
}

void key(unsigned char a, int b, int y)
{

	if('s'=='s')
	{
		goTop();
		getchar();
//		rotateCam();
		engagePhysics(0);
//		nextTurn();
	}
}

void init(void)
{
	GLfloat light_position[] = { -1.0, -3.0, 4.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
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
//	pivotPos[0]=coins[0].CenterX;
//	pivotPos[1]=coins[0].CenterY;


	coins[2].IsWhite=true;
	coins[2].SetXY(-0.25,-0.25);
	coins[1].IsWhite=true;
	coins[1].SetXY(-0.4, 0);

	coins[4].SetXY(-0.4, 0.3);
	coins[3].SetXY(0.4, 0.5);

	coins[5].IsQueen=true;

//	glNewList(listID, GL_COMPILE);	
//	DrawCarromBoard();
//	glEndList();

}

void doStuff()
{
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslated(0,0,2);
	for(int i=1;i!=-10;i++)
	{
//		glutSolidCube(0.5);
		if(i==10000000){
			m.lock();
//			sleep(1);
//////			rot=(rot+1)%3000;
			m.unlock();
			i=0;
		}
//		printf("Give me something to break");
//		Render();
	}
}

void yoyo()
{
	do{
		printf("here");
		float error=0.02;
		coins[0].CenterX+=0.000002*dir;
		if(coins[0].CenterX+error>0.95||coins[0].CenterX-error<-0.95)
		{
			dir*=-1;

			coins[0].CenterX+=0.0003*dir;
		}
	}while(1==1);
}
void printFPS(int last_frames)
{
	printf("frame rate:%f fps\n",(frame-last_frames));
	printf("frame:%d\n",frame);
	glutTimerFunc(1000,printFPS,frame);
}
int main(int args, char *argv[])
{
	glutInit(&args, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(480, 300);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(ReshapeFunction);
	glutDisplayFunc(Render);
	glutIdleFunc(idle);
	glutMotionFunc(moveCam);
	glutPassiveMotionFunc(stopCam);
//	glutMouseWheelFunc(scroll);
	glutMouseFunc(MouseButton);
	glutKeyboardFunc(key);
//	glutTimerFunc(10,yoyo,0);
//	displayInit();
//	std::thread t(yoyo);
//	glutFullScreen();
	//printFPS(0);
	glutMainLoop();
//	t.join();
	return 0;
}


