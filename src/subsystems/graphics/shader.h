#ifndef _SHADER_H_
#define _SHADER_H_

#include "../graphics/renderer_interface.h"

namespace MagusEngine
{
	class Shader
	{
	public:
		Shader();

	private:
		unsigned int _program;
		unsigned int _vertexShader;
		unsigned int _fragmentShader;
	};
}

#endif