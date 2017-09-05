/* Header Guards */
#ifndef _OS_INTERFACE_H_
#define _OS_INTERFACE_H_

/* Temp includes - Will be configurable by file later on... */
#define FULL_SCREEN false
#define VSYNC_ENABLED false 
#define SCREEN_DEPTH 1000.0f
#define SCREEN_NEAR 0.1f

/* System Includes */

/* Local Project Includes */
#include "../graphics/renderer_interface.h"

namespace MagusEngine
{
	/*
		Name: OS_Interface
		Type: Interface
		Purpose: Details all the characteristics of a portable platform
	*/
	class OS_Interface
	{
	public:

		/* Called by the engine - initialise any operating system and windowing structures*/
		virtual bool Initialise() = 0;

		/* Called by the engine - shutdown and clean up any memory allocated by the operating system and windowing */
		virtual void Shutdown() = 0;

		/* Return a valid low level renderer interface */
		virtual Renderer_Interface* GetLowLevelRenderer() = 0;
	};
}

#endif