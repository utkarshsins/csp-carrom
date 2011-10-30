#include "Players.h"

CarromCoin coins[6];

int player=-1;

GLboolean coin_pocketed=false;

int Players::PlayerFileID[4] = { -1, -1, -1, -1 };
int Players::PlayerTurn = 0;
int Players::MaxPlayers = 0;
int Players::MyNumberOfPlayers = 0;
int Players::MyPlayerIDs[4] = { -1, -1, -1, -1 };
int Players::ServerFileID = -1;
