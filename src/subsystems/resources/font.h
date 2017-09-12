#ifndef _FONT_H_
#define _FONT_H_

/* System Includes */
#include <string>

/* Local Project Include */
#include "color.h"
#include "texture.h"

namespace MagusEngine
{
	class Glyph
	{
	public:
		Glyph();
	};

	class Font
	{
	public:
		Font(int id, const char* name);

		bool InitialiseGlyphs(int count);

		/* Getters */
		char*		GetName();
		int			GetId();

		
		/* Setters */

	private:
		int	 _id;
		char _name[50];

		Glyph* _glyphs;
	};
}

#endif