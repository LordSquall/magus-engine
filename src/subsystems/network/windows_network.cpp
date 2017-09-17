#include "windows_network.h"

namespace MagusEngine
{
	bool Network::EstablishUDP(int port)
	{
		/* Initialise networking */
		LOGINFO("Initialising Winsock");
		if (WSAStartup(MAKEWORD(2, 2), &_wsa) != 0)
		{
			return false;
		}

		/* Open Sockets to related port */
		_socket = socket(AF_INET, SOCK_DGRAM, 0);
		if (_socket == SOCKET_ERROR)
		{
			LOGERROR("Unable to open Socket\n");
			return false;
		}

		/* Setup address structure */
		memset((char *)&_socketAddr, 0, sizeof(_socketAddr));
		_socketAddr.sin_family = AF_INET;
		_socketAddr.sin_port = htons(port);
		_socketAddr.sin_addr.S_un.S_addr = INADDR_ANY;

		/* Bind IP Port */
		if (bind(_socket, (struct sockaddr *)&_socketAddr, sizeof(_socketAddr)) == SOCKET_ERROR)
		{
			LOGERROR("ERROR: Bind failed with error code : %d", WSAGetLastError());
			return false;
		}
	}

	bool Network::StartRecieve()
	{
		/* Create Threads for each sensor */
		std::thread* thread = new std::thread(&Network::StartAsync, this);

		return true;
	}

	bool Network::StartAsync()
	{


		bool running = true;
		int recievedLength = 0;

		struct timeval read_timeout;
		read_timeout.tv_sec = 0;
		read_timeout.tv_usec = 1;

		/* Set the time for the receive function */
		setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&read_timeout, sizeof(read_timeout));

		while (running)
		{
			/* Clear the buffer by filling null, it might have previously received data */
			memset(_buf, '\0', 255);

			/* Reset the recieved length */
			recievedLength = sizeof(_socketOtherAddr);

			/* try to receive some data */
			if ((recievedLength = recvfrom(_socket, _buf, 255, 0, (struct sockaddr *) &_socketOtherAddr, &recievedLength)) == SOCKET_ERROR)
			{
				LOGERROR("recvfrom() failed with error code : %d", WSAGetLastError());
				return false;
			}

			/* Update data models */
			_datamodel->GetAltitudeDM()->Update(_buf);
		}

		return true;
	}
}