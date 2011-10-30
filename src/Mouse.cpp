#include"Main.h"
#include"Client.h"
#include"Mouse.h"
#include"Players.h"
#define PI M_PI

int pointer_y, pointer_x;
void MouseButton(int key, int direction, int x, int y)
{
	if(!camera_movable)
		return;

	if(key==GLUT_LEFT_BUTTON&&direction==GLUT_UP&&!moving&&!adjusting)
	{
		if(isMouseOnStriker(x,y))
		{
			if(striker_lock)
			{
				striker_lock=false;
				return;
			}
			
			striker_lock=true;
				pointer_angle=0*turn_rotation-persp_rot;
				pointer_y=y;
				pointer_x=x;
				setPointerLength(x,y);
		}

		else if(striker_lock)
		{
			playTurn();
		}
		
	}
	else if(key==3||key==4)
	{
		direction=key==3?-1:1;
		if(cameraPos[2]<0.5&&direction==-1||cameraPos[2]>4&&direction==1)
			return;
		int factor=3;
		for(int smoother=0;smoother<factor;smoother++)
		{
			for(int i=0;i<3;i++)
			{
				cameraPos[i]=cameraPos[i]*(1+0.03*direction/factor);
			}
			cameraPos[2]*=(1+0.07*direction/factor);
			setCamera();
			RenderGame();
		}
	}
	
	glutSetWindow(GAMEWINDOW);
	glutPostRedisplay();
}

void setPointerLength(int x, int y)
{
	pointer_length=(abs(pointer_x-x)+abs(pointer_y-y)*2)/200.0;
	if(pointer_length>1.3)
		pointer_length=1.3;
	else if(pointer_length<0.3)
		pointer_length=0.3;
}

bool isMouseOnStriker(int x, int y)
{
	GLint viewport[4];
	GLuint selection_buffer[5];

	glSelectBuffer(5, selection_buffer);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(x,viewport[3]-y, 13,13,viewport);
	gluPerspective(45, windowX/(float)windowY,0.5, 300);
	gluLookAt(EXPANDARR3(cameraPos),EXPANDARR3(cameraLook),0,0,1);

	glMatrixMode(GL_MODELVIEW);
	drawStriker();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();
	int hits=glRenderMode(GL_RENDER);

	if(hits!=0)
		return true;
	else return false;
}


void moveCam(int x, int y)
{
	if(!camera_movable)
		return;
	float offset=30, slwdown=0.1;
	if(moving)
	{
		glMatrixMode(GL_PROJECTION);
		GLfloat proposed_rotation=persp_rot+(x-mouseX)*slwdown;
		if(((int)proposed_rotation<60&&(int)proposed_rotation>-60))
			{
				glRotated((x-mouseX)*slwdown,0,0,1);
				persp_rot=proposed_rotation;
			}
		else
		{
			moving=false;
		}
	}

	else if(adjusting)
	{
			float degradation=1.0/500;
			float size=PLACEMENTWIDTH;

			float mouseMovement=(x-mouseX)*((mouseX-x)>0?mouseX-x:x-mouseX)*degradation;;
			
			coins[0].CenterX+=mouseMovement*cos(turn_rotation*PI/180);
			coins[0].CenterY-=mouseMovement*sin(turn_rotation*PI/180);
			
			if(-0.00001<=sin(turn_rotation*PI/180)&&sin(turn_rotation*PI/180)<=0.00001)
			{
				if(coins[0].CenterX<0-size)
					coins[0].CenterX=0-size;
				else if(coins[0].CenterX>size)
					coins[0].CenterX=size;
			}
			else
			{
				if(coins[0].CenterY<0-size)
					coins[0].CenterY=0-size;
				else if(coins[0].CenterY>size)
					coins[0].CenterY=size;
			}
	//		pivotPos[0]=coins[0].CenterX;			
//			coins[0].CenterX=pivotPos[0];
//			coins[0].CenterY=pivotPos[1];
	}
	else if(isMouseOnStriker(x,y))
	{
		adjusting=true;
	}
	else
	{
		moving=true;
	}
	mouseX=x;
	
	glutSetWindow(GAMEWINDOW);
	glutPostRedisplay();
}

void stopCam(int x, int y)
{
	if(striker_lock&&(!moving&&!adjusting))
	{
		pointer_angle-=(float)(mouseX-x)/((pointer_y-y)>2?(pointer_y-y):2);
		setPointerLength(x,y);		
		if(pointer_angle>90)
			pointer_angle=90;
		if(pointer_angle<-90)
			pointer_angle=-90;
	}

	moving=false;
	adjusting=false;

	mouseX=x;
	mouseY=y;
	
	glutSetWindow(GAMEWINDOW);
	glutPostRedisplay();
}

void SimulateGame(int arg)
{
	while(engagePhysics())
		RenderGame();

	if(!coin_pocketed)
		Players::ChangePlayerTurn();

        std::cout << "GAME VERBOSE: Simulated" << std::endl;
		for(int i = 0 ; i < 6 ; i++)
			std::cout       << "GAME VERBOSE: Coin " << i 
					<< " CenterX= " << coins[i].CenterX
					<<", CenterY= " << coins[i].CenterY
					<<", VelocityX = " << coins[i].VelocityX
					<<", VelocityY = " << coins[i].VelocityY
					<< std::endl;

	NextTurnBoolean = true;

//	nextTurn();
}	

void playTurn()
{	
	camera_movable=false;

	fixate_translate[0]=-coins[0].CenterX;
	fixate_translate[1]=-coins[0].CenterY;
	
	coins[0].VelocityX=sin(((0-pointer_angle+turn_rotation)/180)*PI)*pointer_length;
	coins[0].VelocityY=cos(((0-pointer_angle+turn_rotation)/180)*PI)*pointer_length;

	CarromNetworkStruct SendMyTurn = Initialize(STRIKERSTATUS, coins[0].CenterX, coins[0].CenterY, coins[0].VelocityX, coins[0].VelocityY);
	write(Players::ServerFileID, &SendMyTurn, sizeof(SendMyTurn));
	std::cout << "NETWORK VERBOSE: Written striker data to FileID " << Players::ServerFileID << std::endl;

	goTop();
	
	striker_lock=false;
	SimulateGame(0);	
}
