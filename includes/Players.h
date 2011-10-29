#ifndef __PLAYERSH__
#define __PLAYERSH__

#include "Coin.h"

extern CarromCoin coins[6];
extern int player;
extern GLboolean coin_pocketed;

class Players
{
	public:
		static int ReturnPlayerIDByFileID(int FileID)
		{
			for(int i = 0; i < 4; i++)
				if(PlayerFileID[i] == FileID)
					return i;
					
			return -1;
		}
		
		static int ReturnNumberOfPlayers()
		{
			for(int i = 0; i < 4; i++)
				if(PlayerFileID[i] == -1)
					return i;
					
			return 4;
		}
				
		static int ReturnFileIDByPlayerID(int PlayerID)
		{
			return PlayerFileID[PlayerID];
		}
		
		static int AddPlayer(int FileID)
		{
			int NumberOfPlayers = ReturnNumberOfPlayers();
			if(NumberOfPlayers == 4)
				return -1;
			else
			{
				PlayerFileID[NumberOfPlayers] = FileID;
				return NumberOfPlayers;
			}
		}
		
	private:
		static int PlayerFileID[4];
};

#endif
