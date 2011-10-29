#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<netdb.h>

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



//int Players::PlayerFileID[4] = { -1 };

int main()
{
	std::cout << "YO";
	return 0;
}
