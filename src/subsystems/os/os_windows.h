#ifndef _SYSTEM_WINDOWS_CLASS_H_
#define _SYSTEM_WINDOWS_CLASS_H_

/* OS Defines */
#define WIN32_LEAN_AND_MEAN

/* system includes */
#include <glad\glad.h>
#include <GLFW\glfw3.h>

/* includes */
#include "os_interface.h"
#include "../graphics/renderers/windows/renderer_windows_initialise_visitor.h"
#include "../graphics/renderers/windows/renderer_windows_render_visitor.h"
#include "../graphics/renderers/renderer_interface.h"
#include "../input/input.h"


namespace MagusEngine
{
	class OS : public OS_Interface
	{
	public:
		OS();
		
		/* OS_Interface - Functions */
		bool Initialise(FrameworkConfig* config, Resources* resources);
		void Shutdown();
		void Run();
		Renderer_Interface* GetLowLevelRenderer();
		Visitor* GetLowLevelRendererInitialisationVisitor();
		Visitor* GetLowLevelRendererRenderVisitor();
		
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		
	private:
		bool Frame();
		bool InitialiseWindows(Renderer_Interface*, int&, int&);
		void ShutdownWindows();

		static void ErrorCallback(int error, const char* description);
		
	private:
		FrameworkConfig* _config;
		Resources*		 _resources;

		Renderer_Interface* _lowLevelRenderer;
		Visitor*			_lowLevelRendererInitialisationVisitor;
		Visitor*			_lowLevelRendererRenderVisitor;
		Input*				_input;
	};
	
	static OS* ApplicationHandle = 0;
}

#endif