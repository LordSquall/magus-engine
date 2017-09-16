#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

/* Framework Defines */
#define MAX_SCENES 10

/* System includes */
#include <vector>
#include <thread>
#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>

/* Local project includes */
#include "subsystems/logging/logger.h"
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
#include "subsystems/io/SceneParser.h"

namespace MagusEngine
{
	class Framework
	{
	public:
		Framework();

		bool Initialise(char* configfilePath);
		bool Frame();
		bool Shutdown();

		bool ProcessUADataDirectory(const char* uadir);

	private:
		FrameworkConfig _config;
		OS_Interface*	_os;
		Graphics		_graphics;
		Resources		_resources;

		Scene*			_scenes[MAX_SCENES];
		int				_sceneCount;

	private:
		bool ProcessEngineConfig(const char* filename);

		unsigned int _textureCount;
		unsigned int _shaderCount;
	};
}
#endif
