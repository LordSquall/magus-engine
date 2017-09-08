#ifndef _SYSTEM_WINDOWS_CLASS_H_
#define _SYSTEM_WINDOWS_CLASS_H_

/* OS Defines */
#define WIN32_LEAN_AND_MEAN

/* includes */
#include "os_interface.h"

#include "../graphics/renderers/renderer_interface.h"
#include "../input/input.h"

/* system includes */
#include <windows.h>
#include <cstdio>

namespace MagusEngine
{
	class OS : public OS_Interface
	{
	public:
		OS();
		
		/* OS_Interface - Functions */
		bool Initialise(FrameworkConfig* config);
		void Shutdown();
		void Run();
		Renderer_Interface* GetLowLevelRenderer();
		
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		
	private:
		bool Frame();
		bool InitialiseWindows(Renderer_Interface*, int&, int&);
		void ShutdownWindows();
		
	private:
		FrameworkConfig* _config;

		HINSTANCE	_hinstance;
		HWND		_hwnd;

		Renderer_Interface* _lowLevelRenderer;
		Input*				_input;
	};
	
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	static OS* ApplicationHandle = 0;
}

#endif