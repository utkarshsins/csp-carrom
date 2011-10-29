#include "CoinServer.h"


CarromCoin::CarromCoin()
	{
		CarromCoin::CoinID = 0;
		CarromCoin::CenterX = 0.f;
		CarromCoin::CenterY = 0.f;
		CarromCoin::CenterZ = 0.f;
		CarromCoin::VelocityX = 0.f;
		CarromCoin::VelocityY = 0.f;
		CarromCoin::VelocityZ = 0.0005f;
		CarromCoin::CoinMass = CARROMCOIN_MASS;
		CarromCoin::IsWhite = false;
		CarromCoin::IsQueen = false;
		CarromCoin::radius=COIN_RADIUS;
		CarromCoin::scored=0;
		CarromCoin::Collided = false;
		CarromCoin::IsStriker = false;
	}

	void CarromCoin::SetXY(GLfloat x, GLfloat y)
	{
		CenterX = x;
		CenterY = y;
	}
