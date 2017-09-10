#include "texture.h"

namespace MagusEngine
{
	Texture::Texture(const char* name)
	{
		/* Copy the name */
		strcpy_s(_name, name);
	}

	bool Texture::Initialise()
	{

		return true;
	}

	void Texture::Shutdown()
	{
		
	}

}