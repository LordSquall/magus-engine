#ifndef _LINUX_NETWORK_H_
#define _LINUX_NETWORK_H_

/* Local Project Includes */
#include "network_interface.h"

/* System Includes */
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread>

namespace MagusEngine
{
	class Network : public Network_Interface
	{
	public:
		bool EstablishUDP(int port);
		bool StartRecieve();

		bool StartAsync();

	private:
		WSADATA _wsa;
	protected:
		int _socket;
		struct sockaddr_in _socketAddr;
		struct sockaddr_in _socketOtherAddr;
		Byte _buf[255];
		
	};
}

#endif