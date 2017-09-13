#include "text.h"

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

		for (int i = 0; i < length; i++)
		{
			/* Build vertex buffer */
			vbuffer[(i * 4)].SetX(_x + (i * 20.0f));
			vbuffer[(i * 4)].SetY(_y);
			vbuffer[(i * 4)].SetU(0.0f);
			vbuffer[(i * 4)].SetV(1.0f);

			vbuffer[(i * 4) + 1].SetX(_x + (i * 20.0f));
			vbuffer[(i * 4) + 1].SetY(_y + 50.0f);
			vbuffer[(i * 4) + 1].SetU(0.0f);
			vbuffer[(i * 4) + 1].SetV(0.0f);

			vbuffer[(i * 4) + 2].SetX(_x + (i * 20.0f) + 10.0f);
			vbuffer[(i * 4) + 2].SetY(_y);
			vbuffer[(i * 4) + 2].SetU(1.0f);
			vbuffer[(i * 4) + 2].SetV(1.0f);

			vbuffer[(i * 4) + 3].SetX(_x + (i * 20.0f) + 10.0f);
			vbuffer[(i * 4) + 3].SetY(_y + 50.0f);
			vbuffer[(i * 4) + 3].SetU(1.0f);
			vbuffer[(i * 4) + 3].SetV(0.0f);

			/* Build indicies buffer */
			ibuffer[(i * 6) + 0] = (i * 6) + 0;
			ibuffer[(i * 6) + 1] = (i * 6) + 1;
			ibuffer[(i * 6) + 2] = (i * 6) + 2;
			ibuffer[(i * 6) + 3] = (i * 6) + 1;
			ibuffer[(i * 6) + 4] = (i * 6) + 2;
			ibuffer[(i * 6) + 5] = (i * 6) + 3;

			vertCount += 4;
			indicesCount += 6;
		}

		/* Set buffer lengths */
		*vbufferLength = vertCount;
		*ibufferLength = indicesCount;
	}

	/* Getters */
	float Text::GetX() { return _x; }
	float Text::GetY() { return _y; }
	const char* Text::GetContent() { return _content; }

	/* Setters */
	void Text::SetX(float x) { _x = x; }
	void Text::SetY(float y) { _y = y; }
	void Text::SetContent(const char* content) {
		strcpy_s(_content, content);
	}
}