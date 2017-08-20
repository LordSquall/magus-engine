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

		bool Initialise(void*, int, int, float, float, bool);
		bool InitialiseExtensions();

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();

	private:
		GLXContext					m_glContext;
	};
}

#endif