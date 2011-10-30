#ifndef __PLAYERSH__
#define __PLAYERSH__

#include "Coin.h"
#include <iostream>

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
			std::cout << "Returning Number Of Players, Players IDs = ";
			for(int i = 0; i < 4; i++)
			{
				std::cout << PlayerFileID[i] << ", ";
				if(PlayerFileID[i] == -1)
					return i;
			}
			
			std::cout << std::endl;
			return 4;
		}
				
		static int ReturnFileIDByPlayerID(int PlayerID)
		{
			return PlayerFileID[PlayerID];
		}
		
		static int AddPlayer(int number, int FileID)
		{
			int NumberOfPlayers = ReturnNumberOfPlayers();
			if(NumberOfPlayers + number > 4)
				return -1;
			else
			{
				for(int i = NumberOfPlayers ; i < NumberOfPlayers + number ; i++)
					PlayerFileID[i] = FileID;
				return NumberOfPlayers;
			}
		}
	/*	
		static void AddAI(int i)
		{
			std::cout << "Adding AI" << std::endl;
			for(;i > 0; i--)
				AddPlayer(0);
		}
	*/	
		static int ReturnPlayerTurn()
		{
			return PlayerTurn;
		}
		
		static void ChangePlayerTurn()
		{
			PlayerTurn = (PlayerTurn + 1) % MaxPlayers;
		}
		
		static void SetMaxPlayers(int n)
		{
			MaxPlayers = n;
		}
		
		static int ReturnMaxPlayers()
		{
			return MaxPlayers;
		}
		
	private:
		static int PlayerFileID[4];
		static int PlayerTurn;
		static int MaxPlayers;
};

#endif
