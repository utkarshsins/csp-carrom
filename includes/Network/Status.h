#ifndef __NETWORKSTATUSH__
#define __NETWORKSTATUSH__

#include  <string.h>
#include <stdlib.h>
class NetworkStatus
{
	public:
		static bool IsConnected()
		{
			if (ConnectionEstablished)
				return true;
			else 
				return false;
		}

		static char *ReturnNetworkIP()
		{
			return NetworkIP;
		}

		static void ChangeIP(const char NewIP[])
		{
			free(NetworkIP);
			NetworkIP = (char *) malloc ((strlen(NewIP)+1)*sizeof(char));
			strcpy(NetworkStatus::NetworkIP, NewIP);
		}

	private:
		static bool ConnectionEstablished;
		static char *NetworkIP;
};

#endif
