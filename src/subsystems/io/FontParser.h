#ifndef _FONT_PARSER_H_
#define _FONT_PARSER_H_

/* System Includes */

/* Local Project Includes */
#include "../external/tinyxml2/tinyxml2.h"
#include "../resources/font.h"

namespace MagusEngine
{
	class Resources;

	class FontParser
	{
	public:
		static Font* ParseFontFile(const char* filename, const char* name, Resources* resources);

		static void ProcessInfoTag(tinyxml2::XMLElement* element, Font* font, Resources* resources);
		
		static void ProcessCommonTag(tinyxml2::XMLElement* element, Font* font, Resources* resources);

		static void ProcessPagesTag(tinyxml2::XMLElement* element, Font* font, Resources* resources);

		static void ProcessCharsTag(tinyxml2::XMLElement* element, Font* font, Resources* resources);

		static void ProcessGlyphTag(tinyxml2::XMLElement* element, Font* font, Resources* resources);
	};
}

#endif