#ifndef __CLIENTH__
#define __CLIENTH__

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

CarromNetworkStruct Initialize(int , float, float, float, float);


void StartClient(const char IpToConnect[]);

#endif
