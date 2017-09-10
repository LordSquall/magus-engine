#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/* System Includes */
#include <string>

/* Local Project Include */
#include "texture.h"

namespace MagusEngine
{
	class Texture
	{
	public:
		Texture(const char* name);

		bool Initialise();

		void Shutdown();

	private:
		char _name[25];
	};
}

#endif