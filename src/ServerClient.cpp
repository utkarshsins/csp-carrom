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

#include "Main.h"

#define SERVER_PORT 1234

void error(const char *msg)
{
	perror(msg);
}

int ServerListenSocketFileDescriptor, ServerReturnSocketFileDescriptor;
int ClientSocketFileDescriptor[3];

typedef struct	{
	char Message[25];
	char IP[25];
	int SenderPlayerID;
	int RecieverPlayerID;
	int PlayersInRoom;
	int TimeStamp;
	int PlayerTurn;
	int CoinID;
	float CoinX;
	float CoinY;
	float CoinVelocityX;
	float CoinVelocityY;
	bool OfUse;
}CarromNetworkStruct;

int PlayersInRoom = 1;
int GlobalTimeStamp = 0;
int PlayerTurn = -1;
int MyID = 0;
CarromNetworkStruct ServerStruct;
CarromNetworkStruct ClientStruct[3];

void InitializeServerStruct(const char *Msg, const char *ip, int spid, int rpid, int tstamp, int coinid, float coinx, float coiny, float coinvx, float coinvy, bool use)
{
	strcpy(ServerStruct.Message, Msg);
	strcpy(ServerStruct.IP, ip);
	ServerStruct.SenderPlayerID = spid;
	ServerStruct.RecieverPlayerID = rpid;
	ServerStruct.PlayersInRoom = PlayersInRoom;
	ServerStruct.TimeStamp = tstamp;
	ServerStruct.PlayerTurn = PlayerTurn;
	ServerStruct.CoinID = coinid;
	ServerStruct.CoinX = coinx;
	ServerStruct.CoinY = coiny;
	ServerStruct.CoinVelocityX = coinvx;
	ServerStruct.CoinVelocityY = coinvy;
	ServerStruct.OfUse = use;
}

void InitializeClientStruct(int i, const char *Msg, const char *ip, int spid, int rpid, int tstamp, int coinid, float coinx, float coiny, float coinvx, float coinvy, bool use)
{
	strcpy(ClientStruct[i].Message, Msg);
	strcpy(ClientStruct[i].IP, ip); //Correct This
	ClientStruct[i].SenderPlayerID = spid;
	ClientStruct[i].RecieverPlayerID = rpid;
	ClientStruct[i].PlayersInRoom = PlayersInRoom;
	ClientStruct[i].TimeStamp = tstamp;
	ClientStruct[i].PlayerTurn = PlayerTurn;
	ClientStruct[i].CoinID = coinid;
	ClientStruct[i].CoinX = coinx;
	ClientStruct[i].CoinY = coiny;
        ClientStruct[i].CoinVelocityX = coinvx;
	ClientStruct[i].CoinVelocityY = coinvy;
	ClientStruct[i].OfUse = use;
}


bool ProcessData(CarromNetworkStruct StructToProcess)
{
	if(StructToProcess.OfUse)
		if(strcmp(StructToProcess.Message, "LetMeEnterRoom")==0)
		{
			printf("IP: %s, wants to enter the room.\n", StructToProcess.IP);
			if(PlayersInRoom == 4)
				printf("Room is already full.\n");
			else
			{
				PlayersInRoom++;
				printf("PlayerID: %d, Welcome In Room.\n", PlayersInRoom);
				GlobalTimeStamp++;
				return true;
				//Send Data in Return about allotment
				//Send Data to all about allotment
			}
		}
		else if(strcmp(StructToProcess.Message, "CoinPosition") == 0)
		{
			if(StructToProcess.TimeStamp == GlobalTimeStamp+1)
			{
				printf("Data Valid, from PlayerID:%d\n", StructToProcess.SenderPlayerID);
				if(StructToProcess.PlayerTurn == StructToProcess.SenderPlayerID)
				{
					coins[StructToProcess.CoinID].SetXY(StructToProcess.CoinX, StructToProcess.CoinY);
					coins[StructToProcess.CoinID].VelocityX  = StructToProcess.CoinVelocityX;
					coins[StructToProcess.CoinID].VelocityY  = StructToProcess.CoinVelocityY;
					printf("Coin Positions updated.\n");
					//Send Data to all
					GlobalTimeStamp++;
				}
				else
				{
					printf("Don't Cheat PlayerID:%d\n", StructToProcess.SenderPlayerID);
				}
				//Return Recieved
			}
		}
		else if(strcmp(StructToProcess.Message, "TurnChange") == 0)
		{
			printf("PlayerID:%d, Turn Finished.\n", StructToProcess.SenderPlayerID);
			printf("Next Turn, PlayerID:%d\n", StructToProcess.PlayerTurn);
			//Change Turn on Local Game
			GlobalTimeStamp++;
			PlayerTurn = StructToProcess.PlayerTurn;
		}
		else if(strcmp(StructToProcess.Message,"PlayerJoinedRoom") == 0)
		{
			if(StructToProcess.TimeStamp == GlobalTimeStamp+1)
			{
				printf("OK! Updating My Database.\n");
				//Take New Player Data
				GlobalTimeStamp++;
			}
		}
		else if(strcmp(StructToProcess.Message,"DataReceived") == 0)
		{
//			if(StructToProcess.TimeStamp == GlobalTimeStamp)
			{
				printf("Good Enough. Data was recieved on the other end.\n");
				return true;
			}
		}
		else if(strcmp(StructToProcess.Message,"StartGame") == 0)
		{
			//Start The Game
			GlobalTimeStamp++;
		}
		else
		{
			printf("Data Corrupt.\n");
		}
	else
	{
		GlobalTimeStamp++;
	}
	return false;
}

void StartServer(int Thread)
{
	int ForkProcessID;
	socklen_t ClientAddressSize;

	struct sockaddr_in ServerAddress;
	struct sockaddr_in ClientAddress;
	
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

//	for(;PlayersInRoom < 4;)
	{
		
		InitializeServerStruct("DataReceived", "", 0, 0, GlobalTimeStamp, 0, 0, 0, 0, 0, true);
		ServerReturnSocketFileDescriptor = accept(ServerListenSocketFileDescriptor, (struct sockaddr *) &ClientAddress, &ClientAddressSize);
		if(ServerReturnSocketFileDescriptor < 0)
			error("Error in Accepting Connection");
	
		ForkProcessID = fork();
		if(ForkProcessID < 0)
			error("You cannot fork, Use spoon");
		if(ForkProcessID == 0)
		{
			printf("Connection Established\n");
			
			if(read(ServerReturnSocketFileDescriptor, &ServerStruct, sizeof(ServerStruct)) < 0)
				error("Server cannot read");

			if(ProcessData(ServerStruct))
			{
				InitializeServerStruct("DataReceived", "", 0, PlayersInRoom, GlobalTimeStamp, 0, 0, 0, 0, 0, true);
				if(write(ServerReturnSocketFileDescriptor, &ServerStruct, sizeof(ServerStruct)) < 0)
					error("Tried to accept player, but error");
			}

//			close(ServerReturnSocketFileDescriptor); //was initially listen
			//Do stuff with ReturnSocketFileDescriptor
		}
//		else 
			close(ServerReturnSocketFileDescriptor);
	}
//	close(ServerListenSocketFileDescriptor);
}


void StartClient(int ClientID, char IpToConnect[])
{
	struct sockaddr_in ServerAddress;
	struct hostent *Server;

	ClientSocketFileDescriptor[ClientID] = socket(AF_INET, SOCK_STREAM, 0);

	if(ClientSocketFileDescriptor[ClientID] < 0)
		error("Socket Not Opening");

	Server = gethostbyname(IpToConnect);

	if(Server == NULL)
	{
		printf("No such Host found, Check again. The code is probably wrong. Nah its not\n");
		exit(0);
	}

	bzero((char *) &ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	bcopy((char *)Server->h_addr, (char *)&ServerAddress.sin_addr.s_addr, Server->h_length);
	ServerAddress.sin_port = htons(SERVER_PORT);

	if(connect(ClientSocketFileDescriptor[ClientID], (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0)
		error("Cannot Connect");

//	std::thread WritingThread(ClientWrite, 0);
//	WritingThread.detach();

//	for(;;) //Condiion Reuiqred
	for(;; std::cout << "Some problem. Connected, but no reply. Attempting again." << std::endl)
	{
		InitializeClientStruct(ClientID, "LetMeEnterRoom", "", 0, 0, 0, 0, 0, 0, 0, 0, true);
		if(write(ClientSocketFileDescriptor[ClientID], &ClientStruct[ClientID], sizeof(ClientStruct[ClientID])) < 0)
			error("Cannot write to Socket");
		
		InitializeClientStruct(ClientID, "", "", 0, 0, 0, 0, 0, 0, 0, 0, false);
		if(read(ClientSocketFileDescriptor[ClientID], &ClientStruct[ClientID], sizeof(ClientStruct[ClientID])) < 0)
			error("Cannot read from Socket");

		if(ProcessData(ClientStruct[ClientID]))
			break;

	}
	
//	close(ClientSocketFileDescriptor[ClientID]);
}

void SideChangeClient()
{
	for (int i = 1; i<6; i++)
	{
		InitializeClientStruct(0, "CoinPosition", "", MyID, 0, GlobalTimeStamp, i, coins[i].CenterX, coins[i].CenterY, coins[i].VelocityX, coins[i].VelocityY, true);
		write(ClientSocketFileDescriptor[0], &ClientStruct[0], sizeof(ClientStruct[0]));
		
		InitializeClientStruct(0, "", "", 0, 0, 0, 0, 0, 0, 0, 0, false);
		if(read(ClientSocketFileDescriptor[0], &ClientStruct[0], sizeof(ClientStruct[0])) < 0)
			error("Cannot read from Socket");
	
		ProcessData(ClientStruct[0]);
	}
	
	PlayerTurn = (PlayerTurn + 1)%PlayersInRoom;
}

void SideChangeServer()
{
	for (int i = 1; i<6; i++)
	{
		InitializeServerStruct("CoinPosition", "", MyID, 0, GlobalTimeStamp, i, coins[i].CenterX, coins[i].CenterY, coins[i].VelocityX, coins[i].VelocityY, true);
		write(ServerReturnSocketFileDescriptor, &ServerStruct, sizeof(ServerStruct));
		
		InitializeServerStruct("", "", 0, 0, 0, 0, 0, 0, 0, 0, false);
		if(read(ServerReturnSocketFileDescriptor, &ServerStruct, sizeof(ServerStruct)) < 0)
			error("Cannot read from Socket");
	
		ProcessData(ServerStruct);
	}
	
	PlayerTurn = (PlayerTurn + 1)%PlayersInRoom;
}

void StartP2P()
{
	char Command [25];
	bool CreateRoom = false;
	
	std::cout << "Simulating Game\n" << "Press N to create a New Room or Enter an IP to join an existing room: ";
	std::cin >> Command;
	
	if(strcmp(Command, "N") == 0 || strcmp(Command, "n") == 0)
		CreateRoom = true;

	if(CreateRoom)
	{
		std::cout << "Starting Server" << std::endl;
		std::thread Server(StartServer, 0);
		std::cout << "Waiting for users to join." << std::endl;
		Server.join();
		std::cout <<"Something Happened" <<std::endl;
	}
	else
	{
//		StartServer(0);
		StartClient(0, Command);
	}
}
/*
int main()
{
	StartP2P();
	return 0;
}*/
