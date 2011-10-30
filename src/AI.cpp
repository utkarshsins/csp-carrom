#include <iostream>
#include<thread>
#include"AI.h"
#include"Main.h"
#include"AIStatus.h"
#include "Physics.h"
#include "Players.h"
#include "Mouse.h"
#include<unistd.h>

#define edge_half 0.95
#define CORNER_RADIUS (4.5f/2.f/74.f)

bool IsLegal(float CenterX, float VelocityY)
{
	if(fabs(CenterX) < PLACEMENTWIDTH)
		if(VelocityY >= 0.0)
			return true;
			
	return false;
}

bool CheckPath(int i, float M, float C, float CenterUp, float CenterDown)
{
	for(int j = 1; j < 6; j++)
	{
		float CenterX = coins[j].CenterX*cos(turn_rotation/180.f*M_PI) - coins[j].CenterY*sin(turn_rotation/180.f*M_PI);
		float CenterY = coins[j].CenterX*sin(turn_rotation/180.f*M_PI) + coins[j].CenterY*cos(turn_rotation/180.f*M_PI);

		if(j == i || coins[j].scored != 0)
			continue;
		else if(fabs((CenterX*M + C - CenterY) / sqrt(1.0 + M*M)) <= coins[j].radius + coins[0].radius && CenterY <= CenterUp && CenterY >= CenterDown)
		{
			if(DebugStatus::IsDebugOn(4))
			{
			std::cout << "AI VERBOSE: Fail for Coin " << j << " CenterX = " << CenterX << ", CenterY = " << CenterY << ", Distance = " << fabs((CenterX*M + C - CenterY) / sqrt(1.0 + M*M)) << std::endl;
			std::cout << "AI VERBOSE: Required Distance = " << coins[j].radius + coins[0].radius << std::endl;
			}
			return false;
		}
		if(DebugStatus::IsDebugOn(4))
			std::cout << "AI VERBOSE: Tested Coin " << j << ", CenterX = " << CenterX << ", CenterY = " << CenterY << ", Distance = " << fabs((CenterX*M + C - CenterY) / sqrt(1.0 + M*M)) <<  std::endl;
	}

	return true;
}

bool TryCoinUtkarsh(int i)
{
	if(DebugStatus::IsDebugOn(4))
	std::cout << "AI VERBOSE: Trying for Coin " << i << std::endl;

		float CenterX = coins[i].CenterX*cos(turn_rotation/180.f*M_PI) - coins[i].CenterY*sin(turn_rotation/180.f*M_PI);
		float CenterY = coins[i].CenterX*sin(turn_rotation/180.f*M_PI) + coins[i].CenterY*cos(turn_rotation/180.f*M_PI);


	if(DebugStatus::IsDebugOn(4))
		std::cout << "AI VERBOSE: Coin CenterX = " << CenterX << ", CenterY = " << CenterY << std::endl;

	for(int j = 0; j < 4; j++)
	{
		float CornerCenterX = corners[j].CenterX*cos(turn_rotation/180.f*M_PI) - corners[j].CenterY*sin(turn_rotation/180.f*M_PI);
		float CornerCenterY = corners[j].CenterX*sin(turn_rotation/180.f*M_PI) + corners[j].CenterY*cos(turn_rotation/180.f*M_PI);

		std::cout << "RUKO: " << CornerCenterX << ", " << CornerCenterY << ", " << corners[j].CenterX << ", " << corners[j].CenterY << ", " << turn_rotation << std::endl;
		if(CornerCenterY < 0.0)
			continue;
			
		float Theta = -GetTheta((CornerCenterX - CenterX), (CornerCenterY - CenterY), 1.0, 0.0);

		float StrikerCenterX = CenterX - (coins[i].radius+corners[j].radius)*cos(Theta);
		float StrikerCenterY = CenterY - (coins[i].radius+corners[j].radius)*sin(Theta);

		float M = tan(Theta);
		float InitialStrikerCenterX = StrikerCenterX - (StrikerCenterY - (-0.66f))/M;
		float InitialStrikerCenterY = -0.66f;

		float InitialStrikerCenterXLeft = InitialStrikerCenterX;
		float InitialStrikerCenterXRight = InitialStrikerCenterX;

//		int n;
//		std::cin >> n;


		float C = CornerCenterY - M*CornerCenterX;
		
		if(DebugStatus::IsDebugOn(4))
		{
			std::cout << "AI VERBOSE: Trying corner " << i << std::endl;
			std::cout << "AI VERBOSE: Corner " << i << " CenterX = " << CornerCenterX << ", CenterY = " << CornerCenterY << std::endl;
			std::cout << "AI VERBOSE: Corner-Coin Theta = " << Theta/M_PI*180.f << std::endl;
			std::cout << "AI VERBOSE: Proposed Striker CenterX = " << StrikerCenterX << ", CenterY = " << StrikerCenterY << std::endl;
			std::cout << "AI VERBOSE: Initial Striker CenterX = " << -coins[0].CenterX << ", CenterY = " << -coins[0].CenterY << std::endl;
			std::cout << "AI VERBOSE: Generating line Y = MX + C " << std::endl;
			std::cout << "AI VERBOSE: Y = " << M << "X ";
			if(C > 0.0)
				std::cout << " + ";
			std::cout << C << std::endl;
		}

//		std::cin >> n;
		
		if(CheckPath(i, M, C, CornerCenterY, CenterY))
		for(float adjustment = 0.01; ;)
		{
			if(InitialStrikerCenterXLeft >= -PLACEMENTWIDTH)
			{
				float ThetaDash = -GetTheta((StrikerCenterX - InitialStrikerCenterXLeft), (StrikerCenterY - InitialStrikerCenterY), 1.0, 0);
				float MDash = tan(ThetaDash);
				float CDash = StrikerCenterY - MDash*StrikerCenterX;
		
				if(DebugStatus::IsDebugOn(4))
				{
					std::cout << "AI VERBOSE: Initial Proposed Striker CenterX = " << InitialStrikerCenterXLeft << ", CenterY = " << InitialStrikerCenterY << std::endl;
					std::cout << "AI VERBOSE: ThetaDash = " << ThetaDash*180.f/M_PI << std::endl;
					std::cout << "AI VERBOSE: Line II: Y = " << MDash << "X ";
					if(CDash > 0.0)
						std::cout << " + ";
					std::cout << CDash << std::endl;
				}
		

				coins[0].CenterX = InitialStrikerCenterXLeft * cos(-turn_rotation/180.f*M_PI) -InitialStrikerCenterY * sin(-turn_rotation/180.f*M_PI) ;
				coins[0].CenterY = InitialStrikerCenterXLeft * sin(-turn_rotation/180.f*M_PI) +    InitialStrikerCenterY * cos(-turn_rotation/180.f*M_PI);
//				RenderGame();

				if(CheckPath(i, MDash, CDash, StrikerCenterY, InitialStrikerCenterY) && IsLegal(InitialStrikerCenterXLeft, sin(ThetaDash)))
				{	
					if(DebugStatus::IsDebugOn(4))
						std::cout << "AI VERBOSE: Path Clear" << std::endl;
					coins[0].VelocityX = 1.5 * cos(ThetaDash) * cos(-turn_rotation/180.f*M_PI) - 1.5 * sin(ThetaDash) * sin(-turn_rotation/180.f*M_PI);//Max = 1.3
					coins[0].VelocityY = 1.5 * cos(ThetaDash) * sin(-turn_rotation/180.f*M_PI) + 1.5 * sin(ThetaDash) * cos(-turn_rotation/180.f*M_PI);
					return true;
					break;
				}
				InitialStrikerCenterXLeft = InitialStrikerCenterXLeft - adjustment;
				
//				int n;
//				std::cin >> n;
			}
			if(InitialStrikerCenterXRight <= PLACEMENTWIDTH)
			{

				float ThetaDash = -GetTheta((StrikerCenterX - InitialStrikerCenterXRight), (StrikerCenterY - InitialStrikerCenterY), 1.0, 0);
				
				float MDash = tan(ThetaDash);
				float CDash = StrikerCenterY - MDash*StrikerCenterX;
		
				if(DebugStatus::IsDebugOn(4))
				{
					std::cout << "AI VERBOSE: Initial Proposed Striker CenterX = " << InitialStrikerCenterXRight << ", CenterY = " << InitialStrikerCenterY << std::endl;
					std::cout << "AI VERBOSE: Generating line Y = MX + C " << std::endl;
					std::cout << "AI VERBOSE: ThetaDash = " << ThetaDash*180.f/M_PI << std::endl;
					std::cout << "AI VERBOSE: Line II: Y = " << MDash << "X ";
					if(CDash > 0.0)
						std::cout << " + ";
					std::cout << CDash << std::endl;
				}
				
				coins[0].CenterX = InitialStrikerCenterXRight * cos(-turn_rotation/180.f*M_PI) -InitialStrikerCenterY * sin(-turn_rotation/180.f*M_PI) ;
				coins[0].CenterY = InitialStrikerCenterXRight * sin(-turn_rotation/180.f*M_PI) + InitialStrikerCenterY * cos(-turn_rotation/180.f*M_PI);
//				RenderGame();

				if(CheckPath(i, MDash, CDash, StrikerCenterY, InitialStrikerCenterY) && IsLegal(InitialStrikerCenterXRight, sin(ThetaDash)))
				{	
					if(DebugStatus::IsDebugOn(4))
						std::cout << "AI VERBOSE: Path Clear" << std::endl;
					coins[0].VelocityX = 1.5 * cos(ThetaDash) * cos(-turn_rotation/180.f*M_PI) - 1.5 * sin(ThetaDash) * sin(-turn_rotation/180.f*M_PI);//Max = 1.3
					coins[0].VelocityY = 1.5 * cos(ThetaDash) * sin(-turn_rotation/180.f*M_PI) + 1.5 * sin(ThetaDash) * cos(-turn_rotation/180.f*M_PI);
					return true;
					break;
				}
				InitialStrikerCenterXRight = InitialStrikerCenterXRight + adjustment;
				
//				int n;
//				std::cin >> n;
			}
			if(InitialStrikerCenterXLeft < -PLACEMENTWIDTH && InitialStrikerCenterXRight > PLACEMENTWIDTH)
				break;


//			int n;
//			std::cin >> n;
		}

	}

//	int n;
//	std::cin >> n;
	return false;
}
		

void SetCenterUtkarsh()
{
	if(DebugStatus::IsDebugOn(4))
		std::cout << "AI VERBOSE: Utkarsh AI" << std::endl;

	for(int i = 1; i < 6; i++)
		if(coins[i].scored==0)
			if(TryCoinUtkarsh(i))
				break;

	if(coins[0].VelocityX != 0.0 && coins[0].VelocityY != 0.0)
	{
		float CenterX = coins[0].CenterX;
		coins[0].CenterX = 0.0;
	
		float adjustment;
		if(CenterX < 0.0)
			adjustment = -0.01;
		else
			adjustment = 0.01;

		for(; fabs(coins[0].CenterX - CenterX) >= 0.01 ; coins[0].CenterX = coins[0].CenterX + adjustment)
			RenderGame();

		coins[0].CenterX = CenterX;
	}
	
	std::cout << "RUKO: " << std::endl;
	for(int i = 0; i < 6; i++)
		std::cout << "RUKO: Coin " << i << " (" << coins[i].CenterX << ", " << coins[i].CenterY << ")" << std::endl;

//	int n;
//	std::cin >> n;
	
}

void CornersInit()
{
	int counter=0;
	for(int i=-1;i<=1;i+=2)
		for(int j=-1;j<=1;j+=2, counter++)
		{
			corners[counter].CenterX=i*(edge_half-CORNER_RADIUS);
			corners[counter].CenterY=j*(edge_half-CORNER_RADIUS);
			corners[counter].radius=CORNER_RADIUS;
		}
}

void AIStriker()
{
/*	
*/
//	striker_lock=true;
	
	CornersInit();
//	camera_movable = false;

	if(AIStatus::ReturnAIStatusOfPlayer(Players::ReturnPlayerTurn()) == AIUTKARSH)
		SetCenterUtkarsh();
	else
		setCenter();

	int n;
	std::cin >> n;

	camera_movable=false;

	fixate_translate[0]=-coins[0].CenterX;
	fixate_translate[1]=-coins[0].CenterY;

/*
	if(DebugStatus::IsDebugOn(4))
		printf("AI VERBOSE: st_x : %f st_y : %f\n\n\n",coins[0].VelocityX,coins[0].VelocityY);
*/

        CarromNetworkStruct SendMyTurn = Initialize(STRIKERSTATUS, coins[0].CenterX, coins[0].CenterY, coins[0].VelocityX, coins[0].VelocityY);
        write(Players::ServerFileID, &SendMyTurn, sizeof(SendMyTurn));
        std::cout << "NETWORK VERBOSE: Written striker data to FileID " << Players::ServerFileID << std::endl;

        goTop();

        striker_lock=false;
	SimulateGame(0);
//	striker_lock = false;
}

void setCenter()
{
	float adjustment=(rand()%10000-5000)/20000.0;
	float temp=adjustment;

	printf("%f\n",temp);

	while(adjustment<=PLACEMENTWIDTH)
	{
		coins[0].CenterX=(sin(turn_rotation*M_PI/180))*SHIFT*-1+cos(turn_rotation*M_PI/180)*adjustment;
		coins[0].CenterY=(cos(turn_rotation*M_PI/180))*SHIFT*-1+sin(turn_rotation*M_PI/180)*adjustment;

		RenderGame();

		for(int i=5;i>=1;i--)
		{
			if(tryCoin(i)==true)
			{
				return;
			}
		}
		adjustment+=0.01;
	}

	adjustment=temp;

	while(adjustment>=-PLACEMENTWIDTH)
	{
		coins[0].CenterX=(sin(turn_rotation*M_PI/180))*SHIFT*-1+cos(turn_rotation*M_PI/180)*adjustment;
		coins[0].CenterY=(cos(turn_rotation*M_PI/180))*SHIFT*-1+sin(turn_rotation*M_PI/180)*adjustment;

		RenderGame();

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

	//Begin Target hit position of Striker Caluculations
	//OBSERVATION fail only on particular side of the board, also, fail when coin scored, and also looks like cant do if not at original
	float width=0.95;
	float factor_x=(diff_x*width-coins[i].CenterX);
	float factor_y=(diff_y*width-coins[i].CenterY);

	float length=sqrt(factor_x*factor_x+factor_y*factor_y);
	factor_x/=length;
	factor_y/=length;


	float targetX=coins[i].CenterX-(coins[i].radius+coins[0].radius)*factor_x, targetY=coins[i].CenterY-(coins[i].radius+coins[0].radius)*factor_y;

	coins[0].VelocityX=(targetX-coins[0].CenterX)/sqrt((targetX-coins[0].CenterX)*(targetX-coins[0].CenterX)+(targetY-coins[0].CenterY)*(targetY-coins[0].CenterY));	
	coins[0].VelocityY=(targetY-coins[0].CenterY)/sqrt((targetX-coins[0].CenterX)*(targetX-coins[0].CenterX)+(targetY-coins[0].CenterY)*(targetY-coins[0].CenterY));	

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
			if(distance(a,b,coins[j].CenterX,coins[j].CenterY)<=coins[i].radius+coins[j].radius)
			{
				printf("AI VERBOSE: yoyohoho\n");
				return false;
			}
		}
		a+=0.001*(x-coins[i].CenterX);
		b+=0.001*(y-coins[i].CenterY);
	}

	x=targetX;
	y=targetY;

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


	if(DebugStatus::IsDebugOn(4))
		printf("AI VERBOSE: Try succesful for coin %d\ncenter coin - x:%f,y:%f\ntagert center - x:%f,y:%f\ncenter striker - x:%f,y:%f\n",i,coins[i].CenterX,coins[i].CenterY,x,y,coins[0].CenterX,coins[0].CenterY);
	return true;
}

float distance(float a, float b, float x, float y)
{
	float x_squared=(a-x)*(a-x);

	float y_squared=(b-y)*(b-y);

//	printf("%f\n",sqrt(x_squared+y_squared));
	return sqrt(x_squared+y_squared);
}
