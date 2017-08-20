#ifndef _SYSTEM_WINDOWS_CLASS_H_
#define _SYSTEM_WINDOWS_CLASS_H_

#define WIN32_LEAN_AND_MEAN

/* includes */
#include "systemclass.h"
#include "../graphics/rendererclass.h"
#include "../input/inputclass.h"

/* system includes */
#include <windows.h>
#include <cstdio>

namespace MagusEngine
{
	class WindowsClass : public SystemClass
	{
	public:
		WindowsClass();
		
		bool Initialise();
		void Shutdown();
		void Run();
		
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		
	private:
		bool Frame();
		bool InitialiseWindows(RendererClass*, int&, int&);
		void ShutdownWindows();
		
	private:
		LPCWSTR m_applicationName;
		HINSTANCE m_hinstance;
		HWND m_hwnd;

		RendererClass* m_renderer;
		InputClass* m_input;
		GraphicsClass* m_graphics;
	};
	
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	static WindowsClass* ApplicationHandle = 0;
}

#endif