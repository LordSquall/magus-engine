/* Header Guards */
#ifndef _SYSTEM_CLASS_H_
#define _SYSTEM_CLASS_H_

/* System Includes */

/* Local Project Includes */
#include "../graphics/graphicsclass.h"
#include "../graphics/rendererclass.h"

namespace MagusEngine
{
	/*
		Name: SystemClass
		Type: Interface
		Purpose: Details all the characteristics of a portable platform
	*/
	class SystemClass
	{
	public:

		/* Default Contructor */
		SystemClass();

		/* Called by the engine - initialise any operating system and windowing structures*/
		virtual bool Initialise() = 0;

		/* Called by the engine - shutdown and clean up any memory allocated by the operating system and windowing */
		virtual void Shutdown() = 0;
		
		/* Called by the engine - enter the primary application loop */
		virtual void Run() = 0;
	};
}

#endif