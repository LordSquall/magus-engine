#include "FontParser.h"

#include "../resources/resources.h"

namespace MagusEngine
{
	Font* FontParser::ParseFontFile(const char* filename, const char* name, Resources* resources)
	{
		Font* newFont = new Font(name);

		tinyxml2::XMLDocument doc;
		doc.LoadFile(filename);

		/* Get font element */
		tinyxml2::XMLElement* fontElement = doc.FirstChildElement("font");

		/* Check to make sure the root tag is font */
		if (fontElement != NULL)
		{
			/* pass each tag to build font */
			for (tinyxml2::XMLElement* e = fontElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
			{
				if (strcmp(e->Name(), "info") == 0)
				{
					ProcessInfoTag(e, newFont, resources);
				}
				else if (strcmp(e->Name(), "common") == 0)
				{
					ProcessCommonTag(e, newFont, resources);
				}
				else if (strcmp(e->Name(), "pages") == 0)
				{
					ProcessPagesTag(e, newFont, resources);
				}
				else if (strcmp(e->Name(), "chars") == 0)
				{
					ProcessCharsTag(e, newFont, resources);
				}
			}
		}
		return newFont;
	}

	void FontParser::ProcessInfoTag(tinyxml2::XMLElement* element, Font* font, Resources* resources)
	{
		/* To concerned with info properties at the moment... */
	}

	void FontParser::ProcessCommonTag(tinyxml2::XMLElement* element, Font* font, Resources* resources)
	{
		font->SetLineHeight(element->IntAttribute("lineHeight"));
		font->SetScaleW(element->IntAttribute("scaleW"));
		font->SetScaleH(element->IntAttribute("scaleH"));
	}

	void FontParser::ProcessPagesTag(tinyxml2::XMLElement* element, Font* font, Resources* resources)
	{
		/* pass each tag to build page */
		for (tinyxml2::XMLElement* e = element->FirstChildElement("page"); e != NULL; e = e->NextSiblingElement("page"))
		{
			/* Full path buffer */
			char fullPathBuffer[255];
			sprintf(fullPathBuffer, "/resources/fonts/%s.png", font->GetName());

			resources->AddTextureFromFile(font->GetName(), fullPathBuffer);

			/* Add font texture to font object */
			font->SetTexture(resources->GetTexture(font->GetName()));
		}
	}

	void FontParser::ProcessCharsTag(tinyxml2::XMLElement* element, Font* font, Resources* resources)
	{
		/* pass each tag to build glyphs */
		for (tinyxml2::XMLElement* e = element->FirstChildElement("char"); e != NULL; e = e->NextSiblingElement("char"))
		{
			ProcessGlyphTag(e, font, resources);
		}
	}

	void FontParser::ProcessGlyphTag(tinyxml2::XMLElement* element, Font* font, Resources* resources)
	{
		Glyph* g = font->GetGlyph(element->IntAttribute("id"));

		if (element->IntAttribute("id") == 72)
		{
			g->SetX(element->IntAttribute("x"));
			g->SetY(element->IntAttribute("y"));
		}

		g->SetX(element->IntAttribute("x"));
		g->SetY(element->IntAttribute("y"));
		g->SetWidth(element->IntAttribute("width"));
		g->SetHeight(element->IntAttribute("height"));
		g->SetXOffset(element->IntAttribute("xoffset"));
		g->SetYOffset(element->IntAttribute("yoffset"));
		g->SetXAdvance(element->IntAttribute("xadvance"));
		
		/* Calcualte UV for bottom right of glyph */
		Vector2f bl, tl, br, tr;

		bl.x = (((float)g->GetX() / (float)font->GetScaleW()));
		bl.y = (((float)g->GetY() + (float)g->GetHeight()) / (float)font->GetScaleH());

		tl.x = ((float)g->GetX() / (float)font->GetScaleW());
		tl.y = ((float)g->GetY() / (float)font->GetScaleH());

		br.x = (((float)g->GetX() + (float)g->GetWidth()) / (float)font->GetScaleW());
		br.y = (((float)g->GetY() + (float)g->GetHeight()) / (float)font->GetScaleH());

		tr.x = (((float)g->GetX() + (float)g->GetWidth()) / (float)font->GetScaleW());
		tr.y = ((float)g->GetY() / (float)font->GetScaleH());

		g->SetUVBL(bl);
		g->SetUVTL(tl);

		g->SetUVBR(br);
		g->SetUVTR(tr);

	}
}