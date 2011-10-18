#include<thread>
#include"AI.h"
#include"Main.h"

void AIStriker()
{
//	getchar();
//	Random Comment
	setCenter();
	printf("st_x : %f st_y : %f\n\n\n",coins[0].VelocityX,coins[0].VelocityY);
	//getchar();
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

//bool pathClear(float x, float y)
//{
//
//	float a=coins[0].CenterX;
//	float b=coins[0].CenterY;
//	while(a-x>=0.002||b-y>=0.002)
//		for(int i=1;i<6;i++)
//		{
//			if(distance(a,b,x,y)<=coins[0].radius+coins[i].radius)
//			{
//				return false;
//			}
//			a+=0.001*(x-coins[0].CenterX);
//			b+=0.001*(y-coins[0].CenterY);
//		}	
//	return true;
//}

void setCenter()
{
	float adjustment=0;

	while(adjustment<=PLACEMENTWIDTH)
	{
		coins[0].CenterX=(sin(turn_rotation*M_PI/180))*SHIFT*-1+cos(turn_rotation*M_PI/180)*adjustment;
		coins[0].CenterY=(cos(turn_rotation*M_PI/180))*SHIFT*-1+sin(turn_rotation*M_PI/180)*adjustment;

		Render();

		for(int i=5;i>=1;i--)
		{
			if(tryCoin(i)==true)
			{
				return;
			}
		}
		adjustment+=0.01;
	}

	adjustment=0;

	while(adjustment>=-PLACEMENTWIDTH)
	{
		coins[0].CenterX=(sin(turn_rotation*M_PI/180))*SHIFT*-1+cos(turn_rotation*M_PI/180)*adjustment;
		coins[0].CenterY=(cos(turn_rotation*M_PI/180))*SHIFT*-1+sin(turn_rotation*M_PI/180)*adjustment;

		Render();

		for(int i=5;i>=1;i--)
		{
			if(tryCoin(i)==true)
			{
				return;
			}
		}
		adjustment-=0.01;
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
	float width=0.95;
	float factor_x=(diff_x*width-coins[i].CenterX);
	float factor_y=(diff_y*width-coins[i].CenterY);

	float length=sqrt(factor_x*factor_x+factor_y*factor_y);
	factor_x/=length;
	factor_y/=length;


	float x=diff_x*width;
	float y=diff_y*width;

	float a=coins[i].CenterX;
	float b=coins[i].CenterY;
	while(fabs(a-x)>=0.002||fabs(b-y)>=0.002)
	{
		for(int j=1;j<6;j++)
		{
			if(j==i||coins[j].scored!=0)
				continue;
//			printf("distance: %f\n",distance(a,b,x,y));
//			printf("%d",i);
			if(distance(a,b,coins[j].CenterX,coins[j].CenterY)<=coins[i].radius+coins[j].radius)
			{
				printf("yoyohoho");
				return false;
			}
		}
		a+=0.001*(x-coins[i].CenterX);
		b+=0.001*(y-coins[i].CenterY);
//		printf("\n");
	}

	x=coins[i].CenterX-(coins[i].radius+coins[0].radius)*factor_x;
	y=coins[i].CenterY-(coins[i].radius+coins[0].radius)*factor_y;

	a=coins[0].CenterX;
	b=coins[0].CenterY;
	while(fabs(a-x)>=0.002||fabs(b-y)>=0.002)
	{
		for(int j=1;j<6;j++)
		{
			if(j==i)
				continue;
//			printf("distance: %f\n",distance(a,b,x,y));
//			printf("%d",i);
			if(distance(a,b,coins[j].CenterX,coins[j].CenterY)<=coins[0].radius+coins[j].radius)
			{
				return false;
			}
		}
		a+=0.001*(x-coins[0].CenterX);
		b+=0.001*(y-coins[0].CenterY);
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

//	printf("%f\n",sqrt(x_squared+y_squared));
	return sqrt(x_squared+y_squared);
}
