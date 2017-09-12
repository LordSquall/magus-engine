#include "font.h"

namespace MagusEngine
{
	Font::Font(int id, const char* name)
	{
		_id = id;
		strcpy_s(_name, name);
	}

	bool Font::InitialiseGlyphs(int count)
	{
		/* allocate memory for glyph data */
		_glyphs = (Glyph*)malloc(sizeof(Glyph));

		return true;
	}

	/* Getters */
	char*		Font::GetName() { return _name; }
	int			Font::GetId() { return _id; }
		
	/* Setters */

}