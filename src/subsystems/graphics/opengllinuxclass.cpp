#include "openglclass.h"

namespace MagusEngine
{
	OpenGLClass::OpenGLClass()
	{

	}

	bool OpenGLClass::InitialiseExtensions()
	{
		return true;
	}

	bool OpenGLClass::Initialise(int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		return true;
	}

	void OpenGLClass::Shutdown()
	{
		return;
	}

	void OpenGLClass::BeginScene(float red, float green, float blue, float alpha)
	{
		return;
	}


	void OpenGLClass::EndScene()
	{
		return;
	}

}