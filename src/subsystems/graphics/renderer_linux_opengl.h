#ifndef _OPENGL_CLASS_H_
#define _OPENGL_CLASS_H_

#include "renderer_interface.h"

#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

namespace MagusEngine
{
	class Renderer_Linux_OpenGL : public Renderer_Interface
	{
	public:
		Renderer_Linux_OpenGL();

		bool Initialise(void*, int, int, float, float, bool);
		bool InitialiseExtensions();

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();
		
		
		void DrawRectangle(int x, int y, int width, int height);

		void CheckError();
		
	private:
		void*						_os;
		GLXContext					m_glContext;
	};
}

#endif