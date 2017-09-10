#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

/* System includes */
#include <vector>
#include <thread>
#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>

/* Local project includes */
#include "subsystems/external/tinydir/tinydir.h"
#include "subsystems/external/tinyxml2/tinyxml2.h"
#include "frameworkconfig.h"
#include "subsystems/os/os_interface.h"
#ifdef _WIN32
#include "subsystems/os/os_windows.h"
#else
#include "subsystems/os/os_linux.h"
#endif
#include "subsystems/resources/resources.h"
#include "subsystems/graphics/graphics.h"
#include "subsystems/io/UA.h"
#include "subsystems/io/UAParser.h"

namespace MagusEngine
{
	class Framework
	{
	public:
		Framework();

		bool Initialise(char* configfilePath);
		bool Frame();
		void Shutdown();

		bool ProcessUADataDirectory(const char* uadir);

	private:
		FrameworkConfig _config;
		OS_Interface*	_os;
		Graphics		_graphics;
		Resources		_resources;

		UA**			_uas;
		int				_maxUACount;
		int				_uaCount;

	private:
		bool ProcessEngineConfig(const char* filename);

		unsigned int _textureCount;
		unsigned int _shaderCount;
	};
}
#endif
