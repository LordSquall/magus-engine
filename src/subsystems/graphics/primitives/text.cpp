#include "text.h"

namespace MagusEngine
{
	Text::Text()
	{
		_x = 0.0f;
		_y = 0.0f;
		_content = "UNKNOWN";
	}

	Text::Text(float x, float y, const char* content)
	{
		_x = x;
		_y = y;
		_content = content;
	}

	/* Drawable Functions */
	int Text::Build(Vertex* buffer)
	{
		buffer[0].SetX(_x);
		buffer[0].SetY(_y);
		buffer[0].SetU(0.0f);
		buffer[0].SetV(1.0f);

		buffer[1].SetX(_x);
		buffer[1].SetY(_y + 100.0f);
		buffer[1].SetU(0.0f);
		buffer[1].SetV(0.0f);

		buffer[2].SetX(_x + 100.0f);
		buffer[2].SetY(_y);
		buffer[2].SetU(1.0f);
		buffer[2].SetV(1.0f);

		buffer[3].SetX(_x + 100.0f);
		buffer[3].SetY(_y + 100.0f);
		buffer[3].SetU(1.0f);
		buffer[3].SetV(0.0f);

		return 4;

	}

	/* Getters */
	float Text::GetX() { return _x; }
	float Text::GetY() { return _y; }
	const char* Text::GetContent() { return _content; }

	/* Setters */
	void Text::SetX(float x) { _x = x; }
	void Text::SetY(float y) { _y = y; }
	void Text::SetContent(const char* content) { _content = content; }
}