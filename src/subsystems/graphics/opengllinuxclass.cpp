#include "opengllinuxclass.h"

#include "../systems/LinuxClass.h"

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
		
		m_glContext = glXCreateContext(linuxSystem->getDisplay(), linuxSystem->getVisualInfo(), NULL, GL_TRUE);
		glXMakeCurrent(linuxSystem->getDisplay(), linuxSystem->getWindow(), m_glContext);

		return true;
	}

	void OpenGLLinuxClass::Shutdown()
	{
		return;
	}

	void OpenGLLinuxClass::BeginScene(float red, float green, float blue, float alpha)
	{
		return;
	}


	void OpenGLLinuxClass::EndScene()
	{
		return;
	}
}