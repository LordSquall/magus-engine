#ifndef _WINDOWS_NETWORK_H_
#define _WINDOWS_NETWORK_H_

/* Local Project Includes */
#include "network_interface.h"

/* System Includes */
#include <winsock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <atomic>

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