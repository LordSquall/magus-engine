#include "rectangle.h"

namespace MagusEngine
{
	Rectangle::Rectangle()
	{
		_x = 0.0f;
		_y = 0.0f;
		_width = 0.0f;
		_height = 0.0f;
	}

	Rectangle::Rectangle(float x, float y, float width, float height)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
	}

	/* Drawable Functions */
	int Rectangle::Build(Vertex* buffer)
	{
		buffer[0].SetX(_x);
		buffer[0].SetY(_y);
		buffer[0].SetU(0.0f);
		buffer[0].SetV(1.0f);

		buffer[1].SetX(_x);
		buffer[1].SetY(_y +  _height);
		buffer[1].SetU(0.0f);
		buffer[1].SetV(0.0f);

		buffer[2].SetX(_x + _width);
		buffer[2].SetY(_y);
		buffer[2].SetU(1.0f);
		buffer[2].SetV(1.0f);

		buffer[3].SetX(_x + _width);
		buffer[3].SetY(_y + _height);
		buffer[3].SetU(1.0f);
		buffer[3].SetV(0.0f);

		return 4;

	}

	/* Getters */
	float Rectangle::GetX() { return _x; }
	float Rectangle::GetY() { return _y; }
	float Rectangle::GetWidth() { return _width; }
	float Rectangle::GetHeight() { return _height; }

	/* Setters */
	void Rectangle::SetX(float x) { _x = x; }
	void Rectangle::SetY(float y) { _y = y; }
	void Rectangle::SetWidth(float width) { _width = width; }
	void Rectangle::SetHeight(float height) { _height = height; }
}