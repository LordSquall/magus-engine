#include "texture.h"

namespace MagusEngine
{
	Texture::Texture(const char* name, int width, int height)
	{
		/* Copy the name */
		strcpy_s(_name, name);

		_width = width;
		_height = height;
	}

	bool Texture::Initialise(unsigned int pixelSize)
	{
		/* allocate texture memory */
		_data = (Byte*)malloc(sizeof(Byte) * pixelSize);

		return true;
	}
	
	bool Texture::LoadPixelData(Byte* data, unsigned int pixelSize)
	{
		memcpy(_data, data, pixelSize);
		return true;
	}

	void Texture::Shutdown()
	{
		
	}

	/* Getters */
	char* Texture::GetName() { return _name; }
	int Texture::GetId() { return _id; }
	int Texture::GetWidth() { return _width; }
	int Texture::GetHeight() { return _height; }
	Byte* Texture::GetData() { return _data; }
	unsigned int Texture::GetRenderDataHandle() { return _renderDataHandle; }

	/* Setters */
	void Texture::SetRenderDataHandle(unsigned int handle) { _renderDataHandle = handle;}
}