#ifndef _FONT_H_
#define _FONT_H_

/* System Includes */
#include <string.h>

/* Local Project Include */
#include "../math/vector.h"
#include "color.h"
#include "texture.h"

namespace MagusEngine
{
	class Glyph
	{
	public:
		Glyph();

		/* Getters */
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();
		int GetXOffset();
		int GetYOffset();
		int GetXAdvance();
		Vector2f GetUVBL();
		Vector2f GetUVTL();
		Vector2f GetUVBR();
		Vector2f GetUVTR();

		/* Setters */
		void SetX(int x);
		void SetY(int y);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetXOffset(int xoffset);
		void SetYOffset(int yoffset);
		void SetXAdvance(int xadvance);
		void SetUVBL(Vector2f uv);
		void SetUVTL(Vector2f uv);
		void SetUVBR(Vector2f uv);
		void SetUVTR(Vector2f uv);

	private:
		int _x;
		int _y;
		int _width;
		int _height;
		int _xoffset;
		int _yoffset;
		int _xadvance;
		Vector2f _uvbottomleft;
		Vector2f _uvtopleft;
		Vector2f _uvbottomright;
		Vector2f _uvtopright;
	};

	class Font
	{
	public:
		Font(const char* name);

		bool InitialiseGlyphs(int count);

		/* Getters */
		char*		GetName();
		int			GetLineHeight();
		int			GetScaleW();
		int			GetScaleH();
		Texture*	GetTexture();
		Glyph*		GetGlyph(int index);
		
		/* Setters */		
		void SetLineHeight(int lineHeight);
		void SetScaleW(int scaleW);
		void SetScaleH(int scaleH);
		void SetTexture(Texture* texture);

	private:
		char _name[50];

		int _lineHeight;
		int _scaleW;
		int _scaleH;

		Texture* _texture;

		Glyph _glyphs[256];
	};
}

#endif