#include"Physics.h"
#include"Main.h"

#define CORNER_RADIUS (4.5f/2.f/74.0f)
#define ERROR_ACCOMODATION	0.005
#define ERROR_ACCOMODATION_1 (ERROR_ACCOMODATION+coins[index].radius)
#define VELX(a) coins[a].VelocityX
#define VELY(a) coins[a].VelocityY

CarromCoin corners[4];
float edge_half=0.95;

float friction=0.3;
float physics_factor=0.024;
float pocketing_factor = 1.3;

void engagePhysics(int arg)
{
//	printf("%f\n",coins[0].VelocityX);
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
		if((VELX(i)>0?VELX(i):0-VELX(i))+(VELY(i)>0?VELY(i):0-VELY(i))<=0.0001)
		{
			continue;
		}
		else
			run_again=true;
		float _sin=VELX(i)/sqrt(VELX(i)*VELX(i)+VELY(i)*VELY(i));
		float _cos=VELY(i)/sqrt(VELX(i)*VELX(i)+VELY(i)*VELY(i));

//		printf("sin:%f, cos:%f\n",_sin,_cos);
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

//		for(int i=0;i<6;i++)
//			checkCollision(i);
		for(int i=0; i<6; i++)
			coins[i].Collided = false;

//	printf("%d\n",run_again);
	if(run_again)
		glutTimerFunc(10,engagePhysics,0);
	else
		nextTurn();
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
		if(distance(coins[index],coins[i])<coins[index].radius+coins[i].radius+ERROR_ACCOMODATION)
		{
			
//			float VelocityYRelative = -(VELY(index)-VELY(i));
//			float VelocityXRelative = -(VELX(index)-VELX(i));
			float MomentumYRelative = -(coins[index].CoinMass*VELY(index)-coins[i].CoinMass*VELY(i));
			float MomentumXRelative = -(coins[index].CoinMass*VELX(index)-coins[i].CoinMass*VELX(i));
			
//			std::cout << "VelocityCompX = " << VelocityXRelative <<std::endl;
//			std::cout << "MomentumComponentX = " <<  MomentumXRelative << std::endl;
//			std::cout << "VelocityCompY = " << VelocityYRelative <<std::endl;
//			std::cout << "MomentumComponentY = " <<  MomentumYRelative << std::endl;
			
//			float NetRelativeVelocity = sqrt(VelocityYRelative*VelocityYRelative + VelocityXRelative*VelocityXRelative);
			float NetRelativeMomentum = sqrt(MomentumYRelative*MomentumYRelative + MomentumXRelative*MomentumXRelative);
			
			float tanthetah  = atan2 ((coins[index].CenterY - coins[i].CenterY),(coins[index].CenterX - coins[i].CenterX));
//			float tanthetahm  = atan2 ((coins[index].CoinMass*coins[index].CenterY - coins[i].CoinMass*coins[i].CenterY),(coins[index].CoinMass*coins[index].CenterX - coins[i].CoinMass*coins[i].CenterX));
			
//			std::cout << "VelocityTheta = " << tanthetah <<std::endl;
//			std::cout << "MomentumTheta = " <<  tanthetahm << std::endl;			
			
//			float ThetaHRelativeVelocity = atan2(VelocityYRelative , VelocityXRelative);
			float ThetaHRelativeMomentum = atan2(MomentumYRelative , MomentumXRelative);
			
			float ThetaMThetaR = tanthetah - ThetaHRelativeMomentum;
			
//			float JoiningVelocityComponent = NetRelativeVelocity*cos(ThetaMThetaR);
			float JoiningMomentumComponent = NetRelativeMomentum*cos(ThetaMThetaR);
			
//			float JoiningVelocityComponentY = JoiningVelocityComponent*sin(tanthetah);
//			float JoiningVelocityComponentX = JoiningVelocityComponent*cos(tanthetah);
			float JoiningMomentumComponentY = JoiningMomentumComponent*sin(tanthetah);
			float JoiningMomentumComponentX = JoiningMomentumComponent*cos(tanthetah);
			
//			VELX(index) = VELX(index) + JoiningVelocityComponentX;
//			VELX(i) = VELX(i) - JoiningVelocityComponentX;	
			
//			VELY(index) = VELY(index) + JoiningVelocityComponentY;
//			VELY(i) = VELY(i) - JoiningVelocityComponentY;				
	
//			std::cout << "JoiningVelocityCompX = " << JoiningVelocityComponentX <<std::endl;
//			std::cout << "JoiningMomentumComponentX = " <<  JoiningMomentumComponentX << std::endl;

			VELX(index) = VELX(index) + JoiningMomentumComponentX / coins[index].CoinMass;
			VELX(i) = VELX(i) - JoiningMomentumComponentX / coins[i].CoinMass;	
			
			VELY(index) = VELY(index) + JoiningMomentumComponentY / coins[index].CoinMass;
			VELY(i) = VELY(i) - JoiningMomentumComponentY / coins[i].CoinMass;		
		}
	}

	for(int i=0;i<4;i++)
	{
		if(distance(coins[index],corners[i])<2*CORNER_RADIUS+5*ERROR_ACCOMODATION)
		{
			coins[index].scored=player;
			coins[index].VelocityX*=0;
			coins[index].VelocityY*=0;
			printf("Scored I guess. %f, %f, %f;\n", corners[i].CenterY, corners[i].CenterX, CORNER_RADIUS+ERROR_ACCOMODATION );
			coin_pocketed=true;
			return;
		}
	}

	if(coins[index].CenterX>=0.95-ERROR_ACCOMODATION_1||coins[index].CenterX<=-0.95+ERROR_ACCOMODATION_1)
	{
		coins[index].VelocityX*=-1;
		coins[index].CenterX+=VELX(index)*physics_factor;
	}

	if(coins[index].CenterY>=0.95-ERROR_ACCOMODATION_1||coins[index].CenterY<=-0.95+ERROR_ACCOMODATION_1)
	{
		coins[index].VelocityY*=-1;
		coins[index].CenterY+=VELY(index)*physics_factor;
	}

	return;
}
