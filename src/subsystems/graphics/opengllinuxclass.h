#ifndef _OPENGL_CLASS_H_
#define _OPENGL_CLASS_H_

#include "rendererclass.h"

namespace MagusEngine
{
	class OpenGLLinuxClass : public RendererClass
	{
	public:
		OpenGLClass();

		bool Initialise(int, int, float, float, bool);
		bool InitialiseExtensions();

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();

	private:
	

	public:

	};
}

#endif