#include"Physics.h"
#include"Main.h"

#define CORNER_RADIUS (4.5f/2.f/74.0f)
#define ERROR_ACCOMODATION	0.005
#define ERROR_ACCOMODATION_1 (ERROR_ACCOMODATION+coins[index].radius)

CarromCoin corners[4];
#define edge_half 0.95

#define friction 0.3
#define physics_factor 0.024
#define pocketing_factor 1.3

bool engagePhysics()
{
	int counter=0;
	bool run_again=false;
	for(int i=-1;i<=1;i+=2)
		for(int j=-1;j<=1;j+=2, counter++)
		{
			corners[counter].CenterX=i*(edge_half-CORNER_RADIUS);
			corners[counter].CenterY=j*(edge_half-CORNER_RADIUS);
			corners[counter].radius=CORNER_RADIUS;
		}
	for(int i=0;i<6;i++)
	{
		if((coins[i].VelocityX>0.0?coins[i].VelocityX:-coins[i].VelocityX)+(coins[i].VelocityY>0?coins[i].VelocityY:0-coins[i].VelocityY)<=0.0001)
		{
			continue;
		}
		else
			run_again=true;
		float _sin=coins[i].VelocityX/sqrt(coins[i].VelocityX*coins[i].VelocityX+coins[i].VelocityY*coins[i].VelocityY);
		float _cos=coins[i].VelocityY/sqrt(coins[i].VelocityX*coins[i].VelocityX+coins[i].VelocityY*coins[i].VelocityY);

		coins[i].CenterX+=coins[i].VelocityX*physics_factor;
		float tem=coins[i].VelocityX;
		coins[i].VelocityX-=(friction*physics_factor)*_sin;
		if(coins[i].VelocityX*tem<0)
			coins[i].VelocityX=0;

		coins[i].CenterY+=coins[i].VelocityY*physics_factor;
		tem=coins[i].VelocityY;
		coins[i].VelocityY-=(friction*physics_factor)*_cos;
		if(coins[i].VelocityY*tem<0)
			coins[i].VelocityY=0;
	}	
	
		std::thread t0 (checkCollision, 0);
		std::thread t1 (checkCollision, 1);
		std::thread t2 (checkCollision, 2);
		std::thread t3 (checkCollision, 3);
		std::thread t4 (checkCollision, 4);
		std::thread t5 (checkCollision, 5);

		t0.join();
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();

		for(int i=0; i<6; i++)
			coins[i].Collided = false;
		
	if(run_again)
		return true;
	else
		return false;		
}

float distance(CarromCoin a, CarromCoin b)
{
	float a_x=a.CenterX;
	float b_x=b.CenterX;

	float x_squared=(a_x-b_x)*(a_x-b_x);

	float a_y=a.CenterY;
	float b_y=b.CenterY;

	float y_squared=(a_y-b_y)*(a_y-b_y);

	return sqrt(x_squared+y_squared);
}

float GetTheta(float VectorAX, float VectorAY, float VectorBX, float VectorBY)
{
	float DotProduct, LengthA, LengthB, Result;
	
	DotProduct = (VectorAX*VectorBX) + (VectorAY*VectorBY);
	LengthA = sqrt(VectorAX*VectorAX +VectorAY*VectorAY);
	LengthB = sqrt(VectorBX*VectorBX +VectorBY*VectorBY);
	
	float CosTheta = DotProduct / LengthA / LengthB;
	
	if(CosTheta > 1.0)
		CosTheta = 1.0;
	else if(CosTheta < -1.0)
		CosTheta = -1.0;
		
		
	Result = acos(CosTheta);
	
	if(LengthA == 0.0 || LengthB == 0.0)
		return 0.0;
		
	if(	VectorAX*VectorBY - VectorBX*VectorAY < 0.0 )
		Result = -Result;
		
	return Result;
}
	
void checkCollision(int index)
{
	if(coins[index].scored!=0)
		return;
	for(int i=0;i<6;i++)
	{
		if(i>=index)
			break;
		if(coins[i].scored!=0)
			continue;
		if(distance(coins[index],coins[i])<coins[index].radius+coins[i].radius)
		{
		if(DebugStatus::IsDebugOn(2))
		{
			std::cout << "VERBOSE PHYSICS: Collision Occurred " << std::endl;
			std::cout << "VERBOSE PHYSICS: index Center X = " << coins[index].CenterX << ", Y = " << coins[index].CenterY << std::endl;
			std::cout << "VERBOSE PHYSICS: I Center X = " << coins[i].CenterX << ", Y = " << coins[i].CenterY << std::endl;
			std::cout << "VERBOSE PHYSICS: index Velocity X = " << coins[index].VelocityX << ", Y = " << coins[index].VelocityY << std::endl;
			std::cout << "VERBOSE PHYSICS: I Velocity X = " << coins[i].VelocityX << ", Y = " << coins[i].VelocityY << std::endl;
		}
			
			float RelativeCenterX = coins[index].CenterX - coins[i].CenterX;
			float RelativeCenterY = coins[index].CenterY - coins[i].CenterY;
			float RelativeDistance = sqrt(RelativeCenterX*RelativeCenterX + RelativeCenterY*RelativeCenterY);
						
			float VelocityA = sqrt(coins[index].VelocityX*coins[index].VelocityX + coins[index].VelocityY*coins[index].VelocityY);
			float VelocityB = sqrt(coins[i].VelocityX*coins[i].VelocityX + coins[i].VelocityY*coins[i].VelocityY);
						
			float ThetaA = GetTheta(RelativeCenterX, RelativeCenterY, coins[index].VelocityX, coins[index].VelocityY);
			float ThetaB = GetTheta(RelativeCenterX, RelativeCenterY, coins[i].VelocityX, coins[i].VelocityY);
			float ThetaPosition = GetTheta(1.0, 0.0, RelativeCenterX, RelativeCenterY);
			
			float Vat = VelocityA*sin(ThetaA);
			float Vbt = VelocityB*sin(ThetaB);
			
			float Van = VelocityA*cos(ThetaA);
			float Vbn = VelocityB*cos(ThetaB);
			
			float e = 0.8;
			
			float Vand = (coins[index].CoinMass*Van + coins[i].CoinMass*(Vbn*(1.0+e) - e*Van))/(coins[index].CoinMass+coins[i].CoinMass);
			float Vbnd = e*(Van - Vbn) + Vand;
			
						
			coins[index].VelocityX = coins[index].VelocityX - (Van-Vand)*cos(ThetaPosition);
			coins[index].VelocityY = coins[index].VelocityY - (Van-Vand)*sin(ThetaPosition);
			coins[i].VelocityX = coins[i].VelocityX - (Vbn-Vbnd)*cos(ThetaPosition);
			coins[i].VelocityY = coins[i].VelocityY - (Vbn-Vbnd)*sin(ThetaPosition);
			
			
		if(DebugStatus::IsDebugOn(2))
		{
			std::cout << "VERBOSE PHYSICS: Relative Center X = " << RelativeCenterX << ", Y = " << RelativeCenterY << ", Distance = " << RelativeDistance << std::endl;			
			std::cout << "VERBOSE PHYSICS: Velocity index = " << VelocityA << ", i = " << VelocityB << std::endl;		
			std::cout << "VERBOSE PHYSICS: ThetaA = " << ThetaA/M_PI*180.f << ", ThetaB = " << ThetaB/M_PI*180.f << std::endl;			
			std::cout << "VERBOSE PHYSICS: ThetaPosition = " << ThetaPosition/M_PI*180.f << std::endl;
			std::cout << "VERBOSE PHYSICS: Van = " << Van << ", Vbn = " << Vbn << std::endl;
			
			std::cout << "VERBOSE PHYSICS: index Velocity X = " << coins[index].VelocityX << ", Y = " << coins[index].VelocityY << std::endl;
			std::cout << "VERBOSE PHYSICS: Vand = " << Vand << ", Vbnd = " << Vbnd << std::endl;
			std::cout << "VERBOSE PHYSICS: I Velocity X = " << coins[i].VelocityX << ", Y = " << coins[i].VelocityY << std::endl;
		}
			
			coins[i].CenterX+=coins[i].VelocityX*physics_factor;
			coins[i].CenterY+=coins[i].VelocityY*physics_factor;
			coins[index].CenterX+=coins[index].VelocityX*physics_factor;
			coins[index].CenterY+=coins[index].VelocityY*physics_factor;
		}
	}

	for(int i=0;i<4;i++)
	{
		if(distance(coins[index],corners[i])<2*CORNER_RADIUS+5*ERROR_ACCOMODATION)
		{
			coins[index].scored=player;
			coins[index].VelocityX*=0;
			coins[index].VelocityY*=0;
			if(DebugStatus::IsDebugOn(2))
				printf("VERBOSE PHYSICS: Scored I guess. %f, %f, %f;\n", corners[i].CenterY, corners[i].CenterX, CORNER_RADIUS+ERROR_ACCOMODATION );
			coin_pocketed=true;
			return;
		}
	}

	if(coins[index].CenterX>=0.95-ERROR_ACCOMODATION_1||coins[index].CenterX<=-0.95+ERROR_ACCOMODATION_1)
	{
		coins[index].VelocityX*=-1;
		coins[index].CenterX+=coins[index].VelocityX*physics_factor;
	}

	if(coins[index].CenterY>=0.95-ERROR_ACCOMODATION_1||coins[index].CenterY<=-0.95+ERROR_ACCOMODATION_1)
	{
		coins[index].VelocityY*=-1;
		coins[index].CenterY+=coins[index].VelocityY*physics_factor;
	}

	return;
}
