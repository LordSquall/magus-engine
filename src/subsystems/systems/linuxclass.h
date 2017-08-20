#ifndef _SYSTEM_LINUX_CLASS_H_
#define _SYSTEM_LINUX_CLASS_H_

/* includes */
#include "systemclass.h"
#include "../graphics/rendererclass.h"
#include "../input/inputclass.h"

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
	class LinuxClass : public SystemClass
	{
	public:
		LinuxClass();
		
		bool Initialise();
		void Shutdown();
		void Run();
		
		bool InitialiseX11(int screenWidth, int screenHeight);
		
		Display* getDisplay();
		Window* getWindow();
		XVisualInfo* getVisualInfo();
		
		
	private:
		RendererClass* m_renderer;
		InputClass* m_input;
		GraphicsClass* m_graphics;
		
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