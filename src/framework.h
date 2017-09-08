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

#include "subsystems/graphics/graphics.h"

namespace MagusEngine
{
	class Framework
	{
	public:
		Framework();

		bool Initialise(char* dataDirectory);
		bool Frame();
		void Shutdown();

		bool ProcessDataDirectory(const char* dataDirectory);

	private:
		FrameworkConfig _config;
		OS_Interface*	_os;
		Graphics		_graphics;

		std::vector<SceneNode*>		_uaScenes;

	private:
		int CountUAFiles(const char* directory);
		
		bool ProcessEngineConfig(const char* filename);

		bool ProcessUA(const char* filename);

		SceneNode* ProcessSceneNode(tinyxml2::XMLElement* element);
	};
}
#endif
