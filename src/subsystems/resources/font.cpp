#include "font.h"

namespace MagusEngine
{
	/* Glyph Functions */

	Glyph::Glyph()
	{
		_x = 0;
		_y = 0;
		_width = 0;
		_height = 0;
		_xoffset = 0;
		_yoffset = 0;
		_xadvance = 0;
	}
	
	/* Getters */
	int Glyph::GetX() { return _x; }
	int Glyph::GetY() { return _y; }
	int Glyph::GetWidth() { return _width; }
	int Glyph::GetHeight() { return _height; }
	int Glyph::GetXOffset() { return _xoffset; }
	int Glyph::GetYOffset() { return _yoffset; }
	int Glyph::GetXAdvance() { return _xadvance; }
	Vector2f Glyph::GetUVBL() { return _uvbottomleft; }
	Vector2f Glyph::GetUVTL() { return _uvtopleft; }
	Vector2f Glyph::GetUVBR() { return _uvbottomright; }
	Vector2f Glyph::GetUVTR() { return _uvtopright; }

	/* Setters */
	void Glyph::SetX(int x) { _x = x; }
	void Glyph::SetY(int y) { _y = y; }
	void Glyph::SetWidth(int width) { _width = width; }
	void Glyph::SetHeight(int height) { _height = height; }
	void Glyph::SetXOffset(int xoffset) { _xoffset = xoffset; }
	void Glyph::SetYOffset(int yoffset) { _yoffset = yoffset; }
	void Glyph::SetXAdvance(int xadvance) { _xadvance = xadvance; }
	void Glyph::SetUVBL(Vector2f uv) { _uvbottomleft = uv; }
	void Glyph::SetUVTL(Vector2f uv) { _uvtopleft = uv; }
	void Glyph::SetUVBR(Vector2f uv) { _uvbottomright = uv; }
	void Glyph::SetUVTR(Vector2f uv) { _uvtopright = uv; }

	Font::Font(const char* name)
	{
		strcpy(_name, name);
	}

	bool Font::InitialiseGlyphs(int count)
	{
		return true;
	}

	/* Getters */
	char*		Font::GetName() { return _name; }
	int			Font::GetLineHeight() { return _lineHeight; }
	int			Font::GetScaleW() { return _scaleW; }
	int			Font::GetScaleH() { return _scaleH; }
	Texture*	Font::GetTexture() { return _texture; }
	Glyph*		Font::GetGlyph(int index) { return &_glyphs[index]; };
		
	/* Setters */
	void Font::SetLineHeight(int lineHeight) { _lineHeight = lineHeight; }
	void Font::SetScaleW(int scaleW) { _scaleW = scaleW; }
	void Font::SetScaleH(int scaleH) { _scaleH = scaleH; }
	void Font::SetTexture(Texture* texture) { _texture = texture; }

}