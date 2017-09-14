#include "rectangle.h"

#include "../../scenemanagement/visitor.h"

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
	void Rectangle::Build(Vertex* vbuffer, int* vbufferLength, unsigned int* ibuffer, int* ibufferLength)
	{
		/* Build vertex buffer */
		vbuffer[0].SetX(_x);
		vbuffer[0].SetY(_y);
		vbuffer[0].SetZ(0.0f);
		vbuffer[0].SetW(1.0f); 

		vbuffer[0].SetR(1.0f);
		vbuffer[0].SetG(0.0f);
		vbuffer[0].SetB(0.0f);
		vbuffer[0].SetA(1.0f);

		vbuffer[0].SetU(0.0f);
		vbuffer[0].SetV(1.0f);

		vbuffer[1].SetX(_x);
		vbuffer[1].SetY(_y +  _height);
		vbuffer[1].SetZ(0.0f);
		vbuffer[1].SetW(1.0f);

		vbuffer[1].SetR(0.0f);
		vbuffer[1].SetG(1.0f);
		vbuffer[1].SetB(0.0f);
		vbuffer[1].SetA(1.0f);

		vbuffer[1].SetU(0.0f);
		vbuffer[1].SetV(0.0f);

		vbuffer[2].SetX(_x + _width);
		vbuffer[2].SetY(_y);
		vbuffer[2].SetZ(0.0f);
		vbuffer[2].SetW(1.0f);

		vbuffer[2].SetR(0.0f);
		vbuffer[2].SetG(0.0f);
		vbuffer[2].SetB(1.0f);
		vbuffer[2].SetA(1.0f);

		vbuffer[2].SetU(1.0f);
		vbuffer[2].SetV(1.0f);

		vbuffer[3].SetX(_x + _width);
		vbuffer[3].SetY(_y + _height);
		vbuffer[3].SetZ(0.0f);
		vbuffer[3].SetW(1.0f);
		
		vbuffer[3].SetR(1.0f);
		vbuffer[3].SetG(0.0f);
		vbuffer[3].SetB(1.0f);
		vbuffer[3].SetA(1.0f);

		vbuffer[3].SetU(1.0f);
		vbuffer[3].SetV(0.0f);

		/* Build indicies buffer */
		ibuffer[0] = 0;
		ibuffer[1] = 1;
		ibuffer[2] = 2;
		ibuffer[3] = 1;
		ibuffer[4] = 2;
		ibuffer[5] = 3;

		/* Set buffer lengths */
		*vbufferLength = 4;
		*ibufferLength = 6;
	}
	
	void Rectangle::PreDraw(Visitor* visitor)
	{
		visitor->PreVisit(this);
	}

	void Rectangle::PostDraw(Visitor* visitor)
	{
		visitor->PostVisit(this);
	}

	/* Visitable Functions */
	void Rectangle::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
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