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
				<< "=======================================================" << std::endl
				<< "Server Started and is listening on Port " << SERVER_PORT << std::endl;
				
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

//			close(ServerReturnSocketFileDescriptor); //was initially listen
			//Do stuff with ReturnSocketFileDescriptor
		
//		else 
	}
//	close(ServerListenSocketFileDescriptor);
}

int main()
{
	StartServer(0);
	return 0;
}
