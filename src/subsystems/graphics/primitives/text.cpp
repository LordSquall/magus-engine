#include "text.h"

#include "../../scenemanagement/visitor.h"

namespace MagusEngine
{
	Text::Text()
	{
		_x = 0.0f;
		_y = 0.0f;

		strcpy(_content, "UNKNOWN");
	}

	Text::Text(float x, float y, const char* content)
	{
		_x = x;
		_y = y;
		strcpy(_content, content);
	}

	/* Drawable Functions */
	void Text::Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData)
	{
		/* default the drawable data */
		fillData->enabled = false;
		fillData->vertexstart = 0;
		fillData->vertexlength = 0;
		fillData->vertexhandle = 0;
		fillData->indexstart = 0;
		fillData->indexlength = 0;
		fillData->indexhandle = 0;

		int length = strlen(_content);

		int vertCount = 0;
		int indicesCount = 0;

		float xcursor = 0.0f;

		for (int i = 0; i < length; i++)
		{
			Glyph* g = _font->GetGlyph(_content[i]);

			/* Build vertex buffer */
			vbuffer[(i * 4) + 0] = Vertex(Vector4f(_x + xcursor					, _y				 , 0.0f, 1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector3f(), Vector2f(), Vector2f(g->GetUVBL().x, g->GetUVBL().y));
			vbuffer[(i * 4) + 1] = Vertex(Vector4f(_x + xcursor					, _y + g->GetHeight(), 0.0f, 1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector3f(), Vector2f(), Vector2f(g->GetUVTL().x, g->GetUVTL().y));
			vbuffer[(i * 4) + 2] = Vertex(Vector4f(_x + xcursor + g->GetWidth() , _y				 , 0.0f, 1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector3f(), Vector2f(), Vector2f(g->GetUVBR().x, g->GetUVBR().y));
			vbuffer[(i * 4) + 3] = Vertex(Vector4f(_x + xcursor + g->GetWidth() , _y + g->GetHeight(), 0.0f, 1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector3f(), Vector2f(), Vector2f(g->GetUVTR().x, g->GetUVTR().y));

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
		fillData->enabled = true;
		fillData->vertexstart = 0;
		fillData->vertexlength = vertCount;
		fillData->vertexmax = 100;
		fillData->indexstart = 0;
		fillData->indexlength = indicesCount;
		fillData->indexmax = 200;

		strokeData->enabled = false;
		strokeData->vertexstart = 0;
		strokeData->vertexlength = 0;
		strokeData->vertexmax = 0;
		strokeData->indexstart = 0;
		strokeData->indexlength = 0;
		strokeData->indexmax = 0;
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
	char* Text::GetContent() { return _content; }
	Font* Text::GetFont() { return _font; }

	/* Setters */
	void Text::SetX(float x) { _x = x; }
	void Text::SetY(float y) { _y = y; }
	void Text::SetContent(const char* content) { strcpy(_content, content); }
	void Text::SetFont(Font* font) { _font = font; }
}