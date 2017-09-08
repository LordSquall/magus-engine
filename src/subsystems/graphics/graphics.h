#ifndef _GRAPHICS_CLASS_H_
#define _GRAPHICS_CLASS_H_

/* System Includes */
#include <thread>

/* Local Project Includes */
#include "..\os\os_interface.h"
#include "renderers\renderer_interface.h"
#include "renderers\renderer_software.h"
#include "..\scenemanagement\scenenode.h"
#include "graphics_visitor.h"

namespace MagusEngine
{
	class Graphics
	{
	public:
		Graphics();

		bool Initialise(OS_Interface* os);
		void Shutdown();
		bool Frame();

		void AddScene(SceneNode* sceneNode);

	private:
		bool Render();

		bool SoftwareRender();

	private:
		OS_Interface*		_os;
		
		Renderer_Interface* _lowLevelHardwareRenderer; 
		Renderer_Interface*	_lowLevelSoftwareRenderer;
	
		Visitor*			_GraphicsVisitor;

		SceneNode			_rootScene;

		std::thread			_hardwareRendererThread;
		std::thread			_softwareRendererThread;
	};
}

#endif