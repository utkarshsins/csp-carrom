#ifndef __AISTATUSH__
#define __AISTATUSH__

#define HUMAN 0
#define AIHARSHAL 1
#define AIUTKARSH 2

class AIStatus
{
	public:
		static int ReturnAIStatusOfPlayer(int i)
		{
			return PlayerAI[i];
		}

		static void ChangeAIStatusOfPlayer(int Player, int Status)
		{
			PlayerAI[Player] = Status;
		}

	public:
		static int PlayerAI[4];
};

#endif
