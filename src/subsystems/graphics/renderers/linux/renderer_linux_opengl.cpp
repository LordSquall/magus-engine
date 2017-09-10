#include "renderer_linux_opengl.h"

#include "../os/os_linux.h"

namespace MagusEngine
{
	Renderer_Linux_OpenGL::Renderer_Linux_OpenGL()
	{

	}

	bool Renderer_Linux_OpenGL::InitialiseExtensions()
	{
		return true;
	}

	bool Renderer_Linux_OpenGL::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		OS_Linux* os = (OS_Linux*)system;
		
		_os = system;
		
		printf("foobar 1\n");
		m_glContext = glXCreateContext(os->getDisplay(), os->getVisualInfo(), NULL, GL_TRUE);
		
		printf("foobar 2\n");
		glXMakeCurrent(os->getDisplay(), os->getWindow(), m_glContext);
		
		printf("foobar 3\n");
		return true;
	}
	
	void Renderer_Linux_OpenGL::Shutdown()
	{
	}

	void Renderer_Linux_OpenGL::DrawRectangle(int x, int y, int width, int height)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glEnd();
	}

	void Renderer_Linux_OpenGL::BeginScene(float red, float green, float blue, float alpha)
	{
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return;
	}


	void Renderer_Linux_OpenGL::EndScene()
	{
		OS_Linux* os = (OS_Linux*)_os;
		glXSwapBuffers(os->getDisplay(), os->getWindow());
		return;
	}
	
	
	void Renderer_Linux_OpenGL::CheckError()
	{
		// check OpenGL error
		GLenum err = glGetError();

		if (err != GL_NO_ERROR)
		{
			switch (err)
			{
			case GL_INVALID_ENUM:
				printf("GL Error: Invalid Enum\n");
				break;
			case GL_INVALID_VALUE:
				printf("GL Error: Invalid Value\n");
				break;
			case GL_INVALID_OPERATION:
				printf("GL Error: Invalid Operation\n");
				break;
			case GL_STACK_OVERFLOW:
				printf("GL Error: Stack Overflow\n");
				break;
			case GL_STACK_UNDERFLOW:
				printf("GL Error: Stack Underflow\n");
				break;
			case GL_OUT_OF_MEMORY:
				printf("GL Error: Out of Memory\n");
				break;
			}
		}
	}
}