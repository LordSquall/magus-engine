#ifndef _SYSTEM_WINDOWS_CLASS_H_
#define _SYSTEM_WINDOWS_CLASS_H_

/* OS Defines */
#define WIN32_LEAN_AND_MEAN

/* includes */
#include "os_interface.h"

#include "../graphics/renderer_interface.h"
#include "../input/input.h"

/* system includes */
#include <windows.h>
#include <cstdio>

namespace MagusEngine
{
	class OS_Windows : public OS_Interface
	{
	public:
		OS_Windows();
		
		/* OS_Interface - Functions */
		bool Initialise();
		void Shutdown();
		void Run();
		Renderer_Interface* GetLowLevelRenderer();
		
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		
	private:
		bool Frame();
		bool InitialiseWindows(Renderer_Interface*, int&, int&);
		void ShutdownWindows();
		
	private:
		LPCWSTR m_applicationName;
		HINSTANCE m_hinstance;
		HWND m_hwnd;

		Renderer_Interface* _lowLevelRenderer;
		Input* _input;
	};
	
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	static OS_Windows* ApplicationHandle = 0;
}

#endif