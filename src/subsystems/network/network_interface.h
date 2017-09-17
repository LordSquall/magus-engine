#ifndef _NETWORK_INTERFACE_H_
#define _NETWORK_INTERFACE_H_

/* Local Project Includes */
#include "../datamodel/datamodel.h"

namespace MagusEngine
{
	class Network_Interface
	{
	public:
		virtual bool EstablishUDP(int port) = 0;
		virtual bool StartRecieve() = 0;

		void SetDataModel(DataModel* datamodel);

	protected:
		DataModel* _datamodel;
	};
}

#endif