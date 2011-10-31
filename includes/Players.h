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
//			std::cout << "Returning Number Of Players, Players IDs = ";
			for(int i = 0; i < 4; i++)
			{
//				std::cout << PlayerFileID[i] << ", ";
				if(PlayerFileID[i] == -1)
				{
//					std::cout << std::endl;
					return i;
				}
			}
			
//			std::cout << std::endl;
			return 4;
		}
				
		static int ReturnFileIDByPlayerID(int PlayerID)
		{
			return PlayerFileID[PlayerID];
		}
		
		static int AddPlayer(int number, int FileID)
		{
			int NumberOfPlayers = ReturnNumberOfPlayers();
			if(NumberOfPlayers + number > ReturnMaxPlayers())
			{
				std::cout << "GAME VERBOSE: Can't add, max players allowed is "<< ReturnMaxPlayers() << std::endl;
				std::cout << "GAME VERBOSE: NumberOfPlayers = " << NumberOfPlayers << std::endl;
				std::cout << "GAME VERBOSE: number = " << number << std::endl;
				return -1;
			}
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

		static bool IsNextTurnMine()
		{
			for(int i = 0; i < 4; i++)
				if(ReturnPlayerTurn() == MyPlayerIDs[i])
					return true;
			return false;
		}
	
		static int ServerFileID;
		static int MyNumberOfPlayers;
		static int MyPlayerIDs[4];
		static int PlayerScore[4]; // To Use this.. access Players::PlayerScore[i] from anywhere in the program
	private:
		static int PlayerFileID[4];
		static int PlayerTurn;
		static int MaxPlayers;
};

#endif
