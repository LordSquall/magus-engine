#include "framework.h"

namespace MagusEngine
{
	Framework::Framework()
	{

	}

	bool Framework::Initialise()
	{
		/* Create the os subsystem depending on current platform */
#ifdef _WIN32
		_os = new OS_Windows();
#else
		_os = new OS_Linux();
#endif

		/* Initialise the os */
		if (_os->Initialise() == FALSE)
		{
			printf("Error: Unable to Initialise OS SubSystem!\n");
			return false;
		}

		/* Initialise the graphics subsystem */
		_graphics.Initialise(_os);

		
		return true;
	}

	bool Framework::Frame()
	{
		/* Input Frame */

		/* Graphics Frame */
		_graphics.Frame();

		return true;
	}

	void Framework::Shutdown()
	{

	}
}