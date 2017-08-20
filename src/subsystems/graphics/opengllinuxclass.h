#ifndef _OPENGL_CLASS_H_
#define _OPENGL_CLASS_H_

#include "rendererclass.h"


#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

namespace MagusEngine
{
	class OpenGLLinuxClass : public RendererClass
	{
	public:
		OpenGLLinuxClass();

		bool Initialise(int, int, float, float, bool);
		bool InitialiseExtensions();

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();

	private:
		Display*						m_display;
		Window						m_root;
		GLint							m_attributes[5];
		XVisualInfo*					m_visualInfo;
		Colormap						m_colormap;
		XSetWindowAttributes		m_setWindowsAttributes;
		Window						m_window;
		GLXContext					m_glContext;
		XWindowAttributes			m_windowAttributes;
		XEvent						m_xEvent;
	};
}

#endif