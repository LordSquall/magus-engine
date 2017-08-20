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
}