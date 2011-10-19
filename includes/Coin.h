#ifndef __CarromCoin__
#define __CarromCoin__
#include "Carrom.h"

#define CARROMCOIN_MASS 5.25f
#define CARROMSTRIKER_MASS 10.f
class CarromCoin
{
	public:
		CarromCoin();
		GLfloat CenterX;
		GLfloat CenterY;
		GLfloat CenterZ;
		GLfloat VelocityX;
		GLfloat VelocityY;
		GLfloat VelocityZ;
		GLfloat CoinMass;
		bool IsQueen;
		bool IsWhite;
		bool Collided;
		bool IsStriker;
		void DrawCoin();
		void SetXY(GLfloat, GLfloat);
		int CoinID;
		GLfloat radius;

		int scored;
};
#endif 
