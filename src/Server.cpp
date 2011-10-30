#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>

#include<thread>

#include "Players.h"
#include "Physics.h"
#define ALPHA 2
#define SHIFT 0.33*ALPHA

#define SERVER_PORT 1234

#define LETMEJOIN 0
#define WELCOME 1
#define PLAYERTURN 2
#define STRIKERSTATUS 3
#define ROOMFULL 4
#define LEFTROOM 5
#define STARTINGGAME 6
#define ISAI 7
#define ISCLIENT 8
#define ISNONE 9
#define DONESIM 10

typedef struct	{
	int StatusCode;
	float ValueA;
	float ValueB;
	float ValueC;
	float ValueD;
}CarromNetworkStruct;

CarromNetworkStruct Initialize(int Status, float A, float B, float C, float D)
{
	CarromNetworkStruct ToReturn;
	ToReturn.StatusCode = Status;
	ToReturn.ValueA = A;
	ToReturn.ValueB = B;
	ToReturn.ValueC = C;
	ToReturn.ValueD = D;
	
	return ToReturn;
}


void error(const char *msg)
{
	perror(msg);
}

void NextTurn()
{
	int FileIDPlayerTurn = Players::ReturnFileIDByPlayerID(Players::ReturnPlayerTurn());
	CarromNetworkStruct TurnData;
	std::cout << "Reading from " << FileIDPlayerTurn << " for TurnData" << std::endl;
	read(FileIDPlayerTurn, &TurnData, sizeof(TurnData));
	std::cout << "Recieved Turn Data " << TurnData.StatusCode << std::endl;

	if(TurnData.StatusCode == STRIKERSTATUS)
	{
		std::cout	<< "Recieved Turn Data (Striker): "
				<< "CenterX: " << TurnData.ValueA
				<< ", CenterY: " << TurnData.ValueB
				<< ", VelocityX: " << TurnData.ValueC
				<< ", VelocityY: " << TurnData.ValueD
				<< std::endl;
		for(int i = 0; i < Players::ReturnMaxPlayers() ; i++)
		{
			if(Players::ReturnFileIDByPlayerID(Players::ReturnPlayerTurn()) != Players::ReturnFileIDByPlayerID(i))
			{
				std::cout << "Writing Data to PlayerID " << i << " on FileID " << Players::ReturnFileIDByPlayerID(i) << std::endl;
				write(Players::ReturnFileIDByPlayerID(i), &TurnData, sizeof(TurnData));
			}
		}//Write to Rest

		coins[0].CenterX = TurnData.ValueA;
		coins[0].CenterY = TurnData.ValueB;
		coins[0].VelocityX = TurnData.ValueC;
		coins[0].VelocityY = TurnData.ValueD;

		while(engagePhysics());		//Process and Simulate
		std::cout << "Simulated" << std::endl;
		for(int i = 0 ; i < 6 ; i++)
			std::cout	<< "Coin " << i 
					<< " CenterX= " << coins[i].CenterX
					<<", CenterY= " << coins[i].CenterY
					<<", VelocityX = " << coins[i].VelocityX
					<<", VelocityY = " << coins[i].VelocityY
					<< std::endl;
	}
	
	if(!coin_pocketed)
		Players::ChangePlayerTurn();
	coin_pocketed = false;
	NextTurn();
}

void CoinsInit()
{		
	coins[0].SetXY(0,0-SHIFT);
	coins[0].IsStriker = true;
	coins[0].CoinMass = CARROMSTRIKER_MASS;
	coins[0].radius=COIN_RADIUS*1.2;

	coins[2].IsWhite=true;
	coins[2].SetXY(-0.25,-0.25);
	coins[1].IsWhite=true;
	coins[1].SetXY(-0.4, 0);

	coins[4].SetXY(-0.4, 0.3);
	coins[3].SetXY(0.4, 0.5);

	coins[5].IsQueen=true;
}

void StartGame()
{
	std::cout << "Starting Game " << std::endl;
	for(int i = 0; i < 4; i++)
		if(Players::ReturnFileIDByPlayerID(i) != 0 && Players::ReturnFileIDByPlayerID(i) != -1)
		{		
			CarromNetworkStruct StartingGame = Initialize(STARTINGGAME, Players::ReturnFileIDByPlayerID(0), Players::ReturnFileIDByPlayerID(1), Players::ReturnFileIDByPlayerID(2), Players::ReturnFileIDByPlayerID(3));
			write(Players::ReturnFileIDByPlayerID(i), &StartingGame, sizeof(StartingGame));
		}
		
	CoinsInit();
	NextTurn();
}

void ProcessData(int FileID, CarromNetworkStruct Reply)
{
	std::cout << "YO Processing " << Reply.StatusCode << std::endl;
	if(Reply.StatusCode == LETMEJOIN)
	{
		std::cout << "Request for Join... NumberOfPlayers = " << Players::ReturnNumberOfPlayers() << std::endl;
		int PlayerID = Players::AddPlayer(Reply.ValueA, FileID);
		CarromNetworkStruct Return;
		if(PlayerID == -1)
			Return = Initialize(ROOMFULL, 0, 0, 0, 0);
		else
			Return = Initialize(WELCOME, PlayerID, 0, 0, 0);
		
		write(FileID, &Return, sizeof(Return));
		
		std::cout << "Player Added" << std::endl;
		if(PlayerID != -1 && Players::ReturnNumberOfPlayers() == Players::ReturnMaxPlayers())
			StartGame();
	}
		
//int Players::PlayerFileID[4] = { -1 };

}


void StartServer(int Thread)
{
	socklen_t ClientAddressSize;

	struct sockaddr_in ServerAddress;
	struct sockaddr_in ClientAddress;
	
	int ServerListenSocketFileDescriptor, ServerReturnSocketFileDescriptor;
	
	ServerListenSocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(ServerListenSocketFileDescriptor < 0)
		error("Cannot Open Socket");

	bzero((char *) &ServerAddress, sizeof(ServerAddress));

	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = INADDR_ANY;
	ServerAddress.sin_port = htons(SERVER_PORT);

	bind(ServerListenSocketFileDescriptor, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress));
	listen(ServerListenSocketFileDescriptor, 5); //5 is maximum permitted

	ClientAddressSize = sizeof(ClientAddress);

		std::cout 	<< "=======================================================" << std::endl
				<< "Carrom CSP301 Assignment 3 Dedicated Server" << std::endl
				<< "Harshal Bidasaria (2010CS50283) , Utkarsh (2010CS50299)" << std::endl
				<< "=======================================================" << std::endl;
	while(Players::ReturnMaxPlayers() != 2 && Players::ReturnMaxPlayers() != 4)
	{
		int MaxPlayers;
		std::cout	<< "Enter the number of players in the game: " ;
		std::cin	>> MaxPlayers;
		Players::SetMaxPlayers(MaxPlayers);
	}
	/*
	while(((AIPlayers < 0 || AIPlayers > 1) && Players::ReturnMaxPlayers() == 2) || ((AIPlayers < 0 || AIPlayers > 3) && Players::ReturnMaxPlayers() == 4))
	{
		std::cout	<< "Enter the number of AI Players to be provided by Server: " ;
		std::cin	>> AIPlayers;
	}
	
	Players::AddAI(AIPlayers);
	*/

	std::cout	<< "Server Started and is listening on Port " << SERVER_PORT << std::endl;
				
	for(ServerReturnSocketFileDescriptor = accept(ServerListenSocketFileDescriptor, (struct sockaddr *) &ClientAddress, &ClientAddressSize);;ServerReturnSocketFileDescriptor = accept(ServerListenSocketFileDescriptor, (struct sockaddr *) &ClientAddress, &ClientAddressSize))
	{
		CarromNetworkStruct ServerStruct;
		if(ServerReturnSocketFileDescriptor < 0)
			error("Error in Accepting Connection");
	
		std::cout << "Connection Established from IP " << inet_ntoa(ClientAddress.sin_addr) << std::endl;
			
		if(read(ServerReturnSocketFileDescriptor, &ServerStruct, sizeof(ServerStruct)) < 0)
			error("Server cannot read");

		std::thread ServerThread (ProcessData, ServerReturnSocketFileDescriptor, ServerStruct);
		ServerThread.detach();
		std::cout << "Thread separated" << std::endl;

//			close(ServerReturnSocketFileDescriptor); //was initially listen
			//Do stuff with ReturnSocketFileDescriptor
		
//		else 
	}
	close(ServerListenSocketFileDescriptor);
}

int main()
{
	StartServer(0);
	return 0;
}
