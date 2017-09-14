#include "text.h"

#include "../../scenemanagement/visitor.h"

namespace MagusEngine
{
	Text::Text()
	{
		_x = 0.0f;
		_y = 0.0f;

		strcpy_s(_content, "UNKNOWN");
	}

	Text::Text(float x, float y, const char* content)
	{
		_x = x;
		_y = y;
		strcpy_s(_content, content);
	}

	/* Drawable Functions */
	void Text::Build(Vertex* vbuffer, int* vbufferLength, unsigned int* ibuffer, int* ibufferLength)
	{
		int length = strlen(_content);

		int vertCount = 0;
		int indicesCount = 0;

		float xcursor = 0.0f;

		for (int i = 0; i < length; i++)
		{
			Glyph* g = _font->GetGlyph(_content[i]);

			/* Build vertex buffer */
			vbuffer[(i * 4) + 0].SetX(xcursor);
			vbuffer[(i * 4) + 0].SetY(_y);
			vbuffer[(i * 4) + 0].SetU(g->GetUVBL().x);
			vbuffer[(i * 4) + 0].SetV(g->GetUVBL().y);

			vbuffer[(i * 4) + 1].SetX(xcursor);
			vbuffer[(i * 4) + 1].SetY(_y + g->GetHeight());
			vbuffer[(i * 4) + 1].SetU(g->GetUVTL().x);
			vbuffer[(i * 4) + 1].SetV(g->GetUVTL().y);

			vbuffer[(i * 4) + 2].SetX(xcursor + (g->GetWidth()));
			vbuffer[(i * 4) + 2].SetY(_y);
			vbuffer[(i * 4) + 2].SetU(g->GetUVBR().x);
			vbuffer[(i * 4) + 2].SetV(g->GetUVBR().y);

			vbuffer[(i * 4) + 3].SetX(xcursor + (g->GetWidth()));
			vbuffer[(i * 4) + 3].SetY(_y + g->GetHeight());
			vbuffer[(i * 4) + 3].SetU(g->GetUVTR().x);
			vbuffer[(i * 4) + 3].SetV(g->GetUVTR().y);

			/* Build indicies buffer */
			ibuffer[indicesCount + 0] = vertCount + 0;
			ibuffer[indicesCount + 1] = vertCount + 1;
			ibuffer[indicesCount + 2] = vertCount + 2;
			ibuffer[indicesCount + 3] = vertCount + 1;
			ibuffer[indicesCount + 4] = vertCount + 2;
			ibuffer[indicesCount + 5] = vertCount + 3;

			vertCount += 4;
			indicesCount += 6;

			xcursor += g->GetXAdvance();
		}

		/* Set buffer lengths */
		*vbufferLength = vertCount;
		*ibufferLength = indicesCount;
	}
	
	void Text::PreDraw(Visitor* visitor)
	{
		visitor->PreVisit(this);
	}
	
	void Text::PostDraw(Visitor* visitor)
	{
		visitor->PostVisit(this);
	}

	/* Visitable Functions */
	void Text::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
	}

	/* Getters */
	float Text::GetX() { return _x; }
	float Text::GetY() { return _y; }
	const char* Text::GetContent() { return _content; }
	Font* Text::GetFont() { return _font; }

	/* Setters */
	void Text::SetX(float x) { _x = x; }
	void Text::SetY(float y) { _y = y; }
	void Text::SetContent(const char* content) { strcpy_s(_content, content); }
	void Text::SetFont(Font* font) { _font = font; }
}