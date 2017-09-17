#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/* System Includes */
#include <string>

/* Local Project Include */
#include "../logging/logger.h"
#include "texture.h"

typedef char Byte;

namespace MagusEngine
{
	class Texture
	{
	public:
		Texture();

		Texture(const char* name, int width, int height);

		bool Initialise(unsigned int pixelSize);

		bool LoadPixelData(Byte* data, unsigned int pixelSize);

		void Shutdown();

		/* Getters */
		char* GetName();
		int GetWidth();
		int GetHeight();
		Byte* GetData();
		unsigned int GetRenderDataHandle();

		/* Setters */
		void SetName(const char* name);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetData(Byte* data);
		void SetRenderDataHandle(unsigned int handle);

	private:
		char _name[25];

		int	_width;
		int _height;
		Byte* _data;

		unsigned int _renderDataHandle;
	};
}

#endif