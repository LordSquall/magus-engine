#ifndef _SYSTEM_LINUX_CLASS_H_
#define _SYSTEM_LINUX_CLASS_H_

/* includes */
#include "os_interface.h"
#include "../graphics/renderer_interface.h"
#include "../input/input.h"

/* system includes */
#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

namespace MagusEngine
{
	class OS_Linux : public OS_Interface
	{
	public:
		OS_Linux();
		
	/* OS_Interface - Functions */
		bool Initialise();
		void Shutdown();
		Renderer_Interface* GetLowLevelRenderer();
		
	
		void Run();

		bool InitialiseX11(int screenWidth, int screenHeight);
		
		Display* getDisplay();
		Window getWindow();
		XVisualInfo* getVisualInfo();
		
		
	private:
		Renderer_Interface* 	 _lowLevelRenderer;
		Input*		 			_input;
		
		Display*					m_display;
		Window						m_root;
		GLint						m_attributes[5];
		XVisualInfo*				m_visualInfo;
		Colormap					m_colormap;
		XSetWindowAttributes		m_setWindowsAttributes;
		Window						m_window;
		GLXContext					m_glContext;
		XWindowAttributes			m_windowAttributes;
		XEvent						m_xEvent;
	};
}

#endif