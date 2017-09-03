#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

/* System includes */
#include <stdio.h>

/* Local project includes */
#include "subsystems/os/os_interface.h"
#ifdef _WIN32
#include "subsystems/os/os_windows.h"
#else
#include "subsystems/os/os_linux.h"
#endif

#include "subsystems/graphics/graphics.h"

namespace MagusEngine
{
	class Framework
	{
	public:
		Framework();

		bool Initialise();
		bool Frame();
		void Shutdown();

	private:
		OS_Interface*	_os;
		Graphics		_graphics;
	};
}
#endif
