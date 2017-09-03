#include "opengllinuxclass.h"

#include "../systems/linuxclass.h"

namespace MagusEngine
{
	OpenGLLinuxClass::OpenGLLinuxClass()
	{

	}

	bool OpenGLLinuxClass::InitialiseExtensions()
	{
		return true;
	}

	bool OpenGLLinuxClass::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		LinuxClass* linuxSystem = (LinuxClass*)system;
		
		
		
		printf("foobar 1\n");
		m_glContext = glXCreateContext(linuxSystem->getDisplay(), linuxSystem->getVisualInfo(), NULL, GL_TRUE);
		
		printf("foobar 2\n");
		glXMakeCurrent(linuxSystem->getDisplay(), linuxSystem->getWindow(), m_glContext);
		
		printf("foobar 3\n");
		return true;
	}

	void OpenGLLinuxClass::Shutdown()
	{
		return;
	}

	void OpenGLLinuxClass::BeginScene(float red, float green, float blue, float alpha)
	{
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}


	void OpenGLLinuxClass::EndScene()
	{
		return;
	}
	
	void OpenGLLinuxClass::DrawRectangle(int x, int y, int width, int height)
	{
		CheckOpenGLError();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, 0.5);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glEnd();
	}
	
	void OpenGLLinuxClass::CheckOpenGLError()
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