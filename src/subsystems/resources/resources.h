#ifndef _RESOURCES_H_
#define _RESOURCES_H_

/* System Includes */
#include <Windows.h>

/* Local Project Include */
#include "texture.h"
#include "shader.h"
#include "../scenemanagement/visitable.h"

namespace MagusEngine
{
	class Resources
	{
	public:
		Resources();

		bool Initialise(unsigned int textureMax, unsigned int shaderMax);

		bool AddTextureFromFile(const char* name, const char* path);

		bool AddShaderFromFile(const char* name, const char* vertexpath, const char* fragmentPath);

		/* Setters */
		void SetRootPath(const char* path);

		/* Getters */
		char* GetRootPath();

	private:
		char _rootPath[255];

		Texture** _textures;
		unsigned int _textureMaxCount;
		unsigned int _textureCount;

		Shader** _shaders;
		unsigned int _shaderMaxCount;
		unsigned int _shaderCount;
	};
}

#endif