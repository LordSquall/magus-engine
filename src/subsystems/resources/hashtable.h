#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "texture.h"
#include "color.h"
#include "shader.h"
#include "material.h"
#include "font.h"
#include "mesh.h"

namespace MagusEngine
{
	class HashDataItem
	{
	public:
		char id[50];
	};
	
	class TextureDataItem: public HashDataItem
	{
	public:
		Texture* data;
	};

	class ColorDataItem : public HashDataItem
	{
	public:
		Color* data;
	};

	class ShaderDataItem : public HashDataItem
	{
	public:
		Shader* data;
	};

	class MaterialDataItem : public HashDataItem
	{
	public:
		Material* data;
	};

	class FontDataItem : public HashDataItem
	{
	public:
		Font* data;
	};

	class MeshDataItem : public HashDataItem
	{
	public:
		Mesh* data;
	};

	class HashTable
	{
	public:
		HashTable();

		void Initialise(int maxsize);

		void Insert(HashDataItem* item);

		HashDataItem* Get(int index);

		HashDataItem* Search(const char* name);

		/* Getters */
		int GetCount();
		int GetMaxCount();
				
	private:
		HashDataItem** _data;

		int _maxsize;
		int _dataCount;
	};
}

#endif