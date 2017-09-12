#ifndef _RESOURCES_H_
#define _RESOURCES_H_

/* System Includes */
#include <Windows.h>

/* Local Project Include */
#include "texture.h"
#include "shader.h"
#include "color.h"
#include "material.h"
#include "font.h"
#include "../external/tinydir/tinydir.h"
#include "../external/lodepng/lodepng.h"
#include "../scenemanagement/visitable.h"

namespace MagusEngine
{
	class Resources
	{
	public:
		Resources();

		bool Initialise(unsigned int textureMax, unsigned int shaderMax, unsigned int colorMax, unsigned int materialMax, unsigned int fontMax);

		bool AddTextureFromFile(const char* name, const char* path);

		bool AddShaderFromFile(const char* name, const char* vertexpath, const char* fragmentPath);

		bool AddFontFromFile(const char* name, const char* path);

		bool AddColor(int id, const char* name, float r, float g, float b, float a);

		bool AddMaterial(Material* material);

		/* Shader Functions */
		unsigned int GetShaderCount();
		Shader* GetShader(unsigned int index);

		/* Texture Functions */
		unsigned int GetTextureCount();
		Texture* GetTexture(unsigned int index);

		/* Color Functions */
		unsigned int GetColorCount();
		Color* GetColor(unsigned int index);

		/* Material Functions */
		unsigned int GetMaterialCount();
		Material* GetMaterial(unsigned int index);

		/* Font Functions */
		unsigned int GetFontCount();
		Font* GetFont(unsigned int index);

		/* Setters */
		void SetRootPath(const char* path);

		/* Getters */
		char* GetRootPath();

	private:
		char _rootPath[255];

		Texture** _textures;
		unsigned int _textureMaxCount;
		unsigned int _textureCount;

		Color** _colors;
		unsigned int _colorMaxCount;
		unsigned int _colorCount;

		Material** _materials;
		unsigned int _materialMaxCount;
		unsigned int _materialCount;

		Shader** _shaders;
		unsigned int _shaderMaxCount;
		unsigned int _shaderCount;

		Font** _fonts;
		unsigned int _fontMaxCount;
		unsigned int _fontCount;

	private:
		Texture* LoadBmp(const char* name, const char* path);
		Texture* LoadPng(const char* name, const char* path);

		static const char *GetFileExt(const char *filename) {
			const char *dot = strrchr(filename, '.');
			if(!dot || dot == filename) return "";
				return dot + 1;
		}

	};
}
#endif