#ifndef _SYSTEM_CLASS_H_
#define _SYSTEM_CLASS_H_

/* includes */
#include "../graphics/graphicsclass.h"
#include "../graphics/rendererclass.h"

namespace MagusEngine
{
	class SystemClass
	{
	public:
		SystemClass();
		
		virtual bool Initialise() = 0;
		virtual void Shutdown() = 0;
		
		virtual void Run() = 0;
	};
}

#endif