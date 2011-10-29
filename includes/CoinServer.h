#ifndef __CarromCoinServer__
#define __CarromCoinServer__

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define COIN_RADIUS (3.1f/74.f)
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
		void SetXY(GLfloat, GLfloat);
		int CoinID;
		GLfloat radius;
		
		int scored;
};
#endif 
