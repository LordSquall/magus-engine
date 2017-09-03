#ifndef _SHADER_CLASS_H_
#define _SHADER_CLASS_H_

#include "../graphics/rendererclass.h"

namespace MagusEngine
{
	class ShaderClass
	{
	public:
		ShaderClass();

		bool Initialise();
		void Shutdown();

		void SetAsActive(RendererClass* renderer);

	private:
		unsigned int _program;
		unsigned int _vertexShader;
		unsigned int _fragmentShader;
	};
}

#endif