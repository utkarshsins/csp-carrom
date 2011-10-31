#include "Players.h"

CarromCoin coins[6];

int player=-1;

GLboolean coin_pocketed=true;

int Players::PlayerFileID[4] = { -1, -1, -1, -1 };
int Players::PlayerTurn = 0;
int Players::MaxPlayers = 0;
int Players::MyNumberOfPlayers = 1;
int Players::MyPlayerIDs[4] = { -1, -1, -1, -1 };
int Players::ServerFileID = -1;

int Players::PlayerScore[4] = { 0, 0, 0, 0 };
