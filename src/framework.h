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
#include "subsystems/resources/resources.h"
#include "subsystems/graphics/graphics.h"
#include "subsystems/io/SceneParser.h"
#include "subsystems/datamodel/datamodel.h"
#include "subsystems/behaviour/behaviour_visitor.h"
#include "subsystems/network/network_interface.h"

#ifdef _WIN32
#include "subsystems/os/os_windows.h"
#include "subsystems/network/windows_network.h"
#else
#include "subsystems/os/os_linux.h"
#include "subsystems/network/linux_network.h"
#endif

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
		FrameworkConfig		_config;
		OS_Interface*		_os;
		Graphics			_graphics;
		Resources			_resources;
		BehaviourVisitor*	_behaviourVisitor;
		DataModel			_dataModel;
		Network_Interface*	_network;

		Scene*			_scenes[MAX_SCENES];
		int				_sceneCount;

	private:
		bool ProcessEngineConfig(const char* filename);

		unsigned int _textureCount;
		unsigned int _shaderCount;
	};
}
#endif
