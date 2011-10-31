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

#include "Main.h"
#include "Client.h"
#include "Players.h"

#define SERVER_PORT 1234

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

int PlayerID;

void StartGame()
{
	NextTurnBoolean = true;
}

void ProcessData(int FileID, CarromNetworkStruct Reply)
{
	std::cout << "NETWORK VERBOSE: YO Processing, ReplyStatusCode = " << Reply.StatusCode << std::endl;
	if(Reply.StatusCode == LETMEJOIN)
	{
		write(FileID, &Reply, sizeof(Reply));
		std::cout << "NETWORK VERBOSE: Written LetMeJoin, Reading" << std::endl;
		read(FileID, &Reply, sizeof(Reply));
		ProcessData(FileID, Reply);
	}
	else if(Reply.StatusCode == WELCOME)
	{
		PlayerID = Reply.ValueA;
		std::cout << "NETWORK VERBOSE: Connection accepted. I am PlayerID ";
	
		for(int i = 0; i < Players::MyNumberOfPlayers ; i++)
		{
			Players::MyPlayerIDs[i] = PlayerID + i;
			std::cout << PlayerID + i << ", ";
		}

		std::cout << std::endl;

		read(FileID, &Reply, sizeof(Reply));
		ProcessData(FileID, Reply);
	}		
	else if(Reply.StatusCode == STARTINGGAME)
	{
		std::cout << "NETWORK VERBOSE: Server requests the game to be started" << std::endl;
		if(Reply.ValueC == -1)
			Players::SetMaxPlayers(2);
		else if(Reply.ValueD == -1)
			Players::SetMaxPlayers(3);
		else
			Players::SetMaxPlayers(4);

		Players::AddPlayer(1, Reply.ValueA);
		Players::AddPlayer(1, Reply.ValueB);
		Players::AddPlayer(1, Reply.ValueC);
		Players::AddPlayer(1, Reply.ValueD);


		std::cout << "NETWORK VERBOSE: Added players data" << std::endl;
		StartGame();
	}
}

int ClientSocketFileDescriptor;

void StartClient(const char IpToConnect[])
{
	struct sockaddr_in ServerAddress;
	struct hostent *Server;

	ClientSocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	std::cout << "NETWORK VERBOSE: Starting Client. Connecting to " << IpToConnect << std::endl;
	
	if(ClientSocketFileDescriptor < 0)
		error("Socket Not Opening");

	Server = gethostbyname(IpToConnect);

	if(Server == NULL)
	{
		std::cout << "NETWORK VERBOSE: No such Host found, Check again. The code is probably wrong. Nah its not" << std::endl;
		return;
	}

	bzero((char *) &ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	bcopy((char *)Server->h_addr, (char *)&ServerAddress.sin_addr.s_addr, Server->h_length);
	ServerAddress.sin_port = htons(SERVER_PORT);

	if(connect(ClientSocketFileDescriptor, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0)
		error("Cannot Connect");
	
	Players::ServerFileID = ClientSocketFileDescriptor;
	ProcessData(ClientSocketFileDescriptor, Initialize(LETMEJOIN, Players::MyNumberOfPlayers, 0, 0, 0));
		
	std::cout << "Reached here" << std::endl;

}

