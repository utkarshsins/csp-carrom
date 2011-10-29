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

#include "Client.h"

#define SERVER_PORT 1234

#define LETMEJOIN 0
#define WELCOME 1
#define PLAYERTURN 2
#define STRIKERSTATUS 3
#define ROOMFULL 4
#define LEFTROOM 5

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


void ProcessData(int FileID, CarromNetworkStruct Reply)
{
	
//int Players::PlayerFileID[4] = { -1 };
std::cout << "YO Processing";

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

	CarromNetworkStruct ToSend;
	ProcessData(ClientSocketFileDescriptor, ToSend);

}
