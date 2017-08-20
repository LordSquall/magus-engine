#include "opengllinuxclass.h"

namespace MagusEngine
{
	OpenGLLinuxClass::OpenGLLinuxClass()
	{

	}

	bool OpenGLLinuxClass::InitialiseExtensions()
	{
		return true;
	}

	bool OpenGLLinuxClass::Initialise(int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
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