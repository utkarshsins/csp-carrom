#include "Coin.h"


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

	void CarromCoin::DrawCoin()
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		if(IsStriker)
			glBindTexture(GL_TEXTURE_2D, textureID[5]);
		else if(IsQueen)
			glBindTexture(GL_TEXTURE_2D, textureID[4]);
		else if(IsWhite)
			glBindTexture(GL_TEXTURE_2D, textureID[2]);
		else
			glBindTexture(GL_TEXTURE_2D, textureID[3]);
		
		if(scored == 0)
		{
			glTranslatef(0*1.f + CenterX, 0*1.f + CenterY, 0.f);
			
			glScaled(radius/COIN_RADIUS,radius/COIN_RADIUS,1);
			glDrawElements(GL_POLYGON, 40, GL_UNSIGNED_INT, CarromCoinFace);
			glDrawElements(GL_POLYGON, 40, GL_UNSIGNED_INT, CarromCoinFace + 40);
			glDrawArrays(GL_QUAD_STRIP, 984 / 3, 80);
		}
		else
		{
			glTranslatef(0*1.f + CenterX, 0*1.f + CenterY, CenterZ);
			glEnable (GL_FOG);
			
			glDrawElements(GL_POLYGON, 40, GL_UNSIGNED_INT, CarromCoinFace);
			glDrawElements(GL_POLYGON, 40, GL_UNSIGNED_INT, CarromCoinFace + 40);
			glDrawArrays(GL_QUAD_STRIP, 984 / 3, 80);
			
			glDisable(GL_FOG);
			
			VelocityX = 0.f;
			VelocityY = 0.f;
			
			if(CenterZ < -(0.8f*2.f/74.f)*7.f/10.f)
			{
				VelocityZ = 0.0f;
				CenterZ = -(0.8f*2.f/74.f)*1.1f;
			}
			else
				CenterZ = CenterZ - VelocityZ;
		}				
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	void CarromCoin::SetXY(GLfloat x, GLfloat y)
	{
		CenterX = x;
		CenterY = y;
	}
