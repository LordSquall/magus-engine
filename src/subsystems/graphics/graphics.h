#ifndef _GRAPHICS_CLASS_H_
#define _GRAPHICS_CLASS_H_

/* System Includes */
#include <thread>
#include <GLFW\glfw3.h>

/* Local Project Includes */
#include "..\os\os_interface.h"
#include "renderers\renderer_interface.h"
#include "renderers\software\renderer_software.h"
#include "renderers\software\renderer_software_initialise_visitor.h"
#include "renderers\software\renderer_software_render_visitor.h"
#include "..\scenemanagement\scenenode.h"
#include "graphics_visitor.h"
#include "..\resources\resources.h"

namespace MagusEngine
{
	class Graphics
	{
	public:
		Graphics();

		bool Initialise(OS_Interface* os, Resources* resources, FrameworkConfig* _config, int maxSceneCount);
		void Shutdown();

		bool InitialiseFrame();
		bool Frame();

		void AddScene(SceneNode* sceneNode);

	private:
		bool Render();

		bool SoftwareRender();

	private:
		OS_Interface*		_os;
		Resources*			_resources;
		FrameworkConfig*	_config;
		GLFWwindow*			_window;

		Renderer_Interface* _lowLevelHardwareRenderer;
		Renderer_Interface*	_lowLevelSoftwareRenderer;
	
		Visitor*			_hardwareInitialiseVisitor;
		Visitor*			_softwareInitialiseVisitor;

		Visitor*			_hardwareRenderVisitor;
		Visitor*			_softwareRenderVisitor;

		SceneNode			_rootScene;

		std::thread			_hardwareRendererThread;
		std::thread			_softwareRendererThread;
	};
}

#endif