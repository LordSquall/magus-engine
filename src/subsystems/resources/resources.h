#ifndef _RESOURCES_H_
#define _RESOURCES_H_

/* System Includes */
#include <Windows.h>

/* Local Project Include */
#include "../logging/logger.h"
#include "../io/FontParser.h"
#include "../io/OBJParser.h"
#include "hashtable.h"
#include "texture.h"
#include "shader.h"
#include "color.h"
#include "material.h"
#include "mesh.h"
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

		bool Initialise(unsigned int textureMax, unsigned int shaderMax, unsigned int colorMax, unsigned int materialMax, unsigned int fontMax, unsigned int meshMax);

		bool AddTextureFromFile(const char* name, const char* path);

		bool AddShaderFromFile(const char* name, const char* vertexpath, const char* fragmentPath);

		bool AddFontFromFile(const char* name, const char* path);

		bool AddMeshFromFile(const char* name, const char* path);
		
		/* Shader Functions */
		bool			AddShader(const char* name, Shader* shader);
		unsigned int	GetShaderCount();
		Shader*			GetShader(unsigned int index);
		Shader*			GetShader(const char* name);

		/* Texture Functions */
		bool			AddTexture(const char* name, Texture* texture);
		unsigned int	GetTextureCount();
		Texture*		GetTexture(unsigned int index);
		Texture*		GetTexture(const char* name);

		/* Color Functions */
		bool			AddColor(const char* name, Color* color);
		unsigned int	GetColorCount();
		Color*			GetColor(unsigned int index);
		Color*			GetColor(const char* name);

		/* Material Functions */
		bool			AddMaterial(const char* name, Material* material);
		unsigned int	GetMaterialCount();
		Material*		GetMaterial(unsigned int index);
		Material*		GetMaterial(const char* name);

		/* Font Functions */
		bool			AddFont(const char* name, Font* font);
		unsigned int	GetFontCount();
		Font*			GetFont(unsigned int index);
		Font*			GetFont(const char* name);
		
		/* Mesh Functions */
		bool			AddMesh(const char* name, Mesh* font);
		unsigned int	GetMeshCount();
		Mesh*			GetMesh(unsigned int index);
		Mesh*			GetMesh(const char* name);

		/* Setters */
		void SetRootPath(const char* path);

		/* Getters */
		char* GetRootPath();

	private:
		char _rootPath[255];

		HashTable _textureHashTable;
		HashTable _colorHashTable;
		HashTable _materialsHashTable;
		HashTable _shadersHashTable;
		HashTable _fontsHashTable;
		HashTable _meshHashTable;
	
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