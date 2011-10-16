#include<thread>
#include"AI.h"
#include"Main.h"

void AIStriker()
{
	getchar();
	setCenter();
	printf("st_x : %f st_y : %f\n\n\n",coins[0].VelocityX,coins[0].VelocityY);
	getchar();
	striker_lock=true;
	//playTurn();	

	camera_movable=false;

	fixate_translate[0]=-coins[0].CenterX;
	fixate_translate[1]=-coins[0].CenterY;
	
	//coins[0].VelocityX=sin(((0-pointer_angle+turn_rotation)/180)*PI);
	//coins[0].VelocityY=cos(((0-pointer_angle+turn_rotation)/180)*PI);

	goTop();
	std::thread t(engagePhysics,0);
	t.detach();
	striker_lock=false;

//	goTop();
//	std::thread t(engagePhysics,0);
//	t.detach();
//	striker_lock=false;
//	engagePhysics(0);

//	engagePhysics(0);
}

bool pathClear(float x, float y)
{

	float a=coins[0].CenterX;
	float b=coins[0].CenterY;
	while(a-x>=0.002||b-y>=0.002)
		for(int i=1;i<6;i++)
		{
			if(distance(a,b,x,y)<=coins[0].radius+coins[i].radius)
			{
				return false;
			}
			a+=0.001*(x-coins[0].CenterX);
			b+=0.001*(y-coins[0].CenterY);
		}	
	return true;
}

void setCenter()
{
	float adjustment=0;

	while(adjustment<=PLACEMENTWIDTH)
	{
		coins[0].CenterX=(sin(turn_rotation*M_PI/180))*SHIFT*-1+cos(turn_rotation*M_PI/180)*adjustment;
		coins[0].CenterY=(cos(turn_rotation*M_PI/180))*SHIFT*-1+sin(turn_rotation*M_PI/180)*adjustment;

		for(int i=5;i>=1;i--)
		{
			if(tryCoin(i)==true)
			{
				return;
			}
		}
		adjustment+=0.001;
	}

	adjustment=0;

	while(adjustment>=-PLACEMENTWIDTH)
	{
		coins[0].CenterX=(sin(turn_rotation*M_PI/180))*SHIFT*-1+cos(turn_rotation*M_PI/180)*adjustment;
		coins[0].CenterY=(cos(turn_rotation*M_PI/180))*SHIFT*-1+sin(turn_rotation*M_PI/180)*adjustment;

		for(int i=5;i>=1;i--)
		{
			if(tryCoin(i)==true)
			{
				return;
			}
		}
		adjustment-=0.001;
	}
}

bool tryCoin(int i)
{

	if(coins[i].scored!=0)
		return false;
	float diff_x=coins[i].CenterX-coins[0].CenterX;
	float diff_y=coins[i].CenterY-coins[0].CenterY;

	if(diff_x<0)
		diff_x=-1;
	else
		diff_x=1;

	if(diff_y<0)
		diff_y=-1;
	else
		diff_y=1;

	float targetX, targetY;
	//Begin Target hit position of Striker Caluculations
	//OBSERVATION fail only on particular side of the board, also, fail when coin scored, and also looks like cant do if not at original
	float width=0.95*2;
	float factor_x=(diff_x*width/2-coins[i].CenterX);
	float factor_y=(diff_y*width/2-coins[i].CenterY);

	float length=sqrt(factor_x*factor_x+factor_y*factor_y);
	factor_x/=length;
	factor_y/=length;

	float x=coins[i].CenterX-(coins[i].radius+coins[0].radius)*factor_x;
	float y=coins[i].CenterY-(coins[i].radius+coins[0].radius)*factor_y;

	float a=coins[0].CenterX;
	float b=coins[0].CenterY;
	while(fabs(a-x)>=0.002||fabs(b-y)>=0.002)
	{
		for(int i=1;i<6;i++)
		{
//			printf("distance: %f\n",distance(a,b,x,y));
//			printf("%d",i);
			if(distance(a,b,coins[i].CenterX,coins[i].CenterY)<=coins[0].radius+coins[i].radius)
			{
				return false;
			}
			a+=0.001*(x-coins[0].CenterX);
			b+=0.001*(y-coins[0].CenterY);
		}
//		printf("\n");
	}
	printf("Try succesful for coin %d\ncenter coin - x:%f,y:%f\ntagert center - x:%f,y:%f\ncenter striker - x:%f,y:%f",i,coins[i].CenterX,coins[i].CenterY,x,y,coins[0].CenterX,coins[0].CenterY);
	coins[0].VelocityX=(x-coins[0].CenterX)/sqrt((x-coins[0].CenterX)*(x-coins[0].CenterX)+(y-coins[0].CenterY)*(y-coins[0].CenterY));	
	coins[0].VelocityY=(y-coins[0].CenterY)/sqrt((x-coins[0].CenterX)*(x-coins[0].CenterX)+(y-coins[0].CenterY)*(y-coins[0].CenterY));	
	return true;
}

float distance(float a, float b, float x, float y)
{
	float x_squared=(a-x)*(a-x);

	float y_squared=(b-y)*(b-y);

	return sqrt(x_squared+y_squared);
}
