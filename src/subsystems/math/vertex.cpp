#include "vertex.h"

namespace MagusEngine
{

	Vertex::Vertex()
	{
		_x = 0.0f;
		_y = 0.0f;
	}

	Vertex::Vertex(float x, float y)
	{
		_x = x;
		_y = y;
	}

	float Vertex::GetX()
	{
		return _x;
	}

	float Vertex::GetY()
	{
		return _y;
	}

	void Vertex::SetX(float x)
	{
		_x = x;
	}

	void Vertex::SetY(float y)
	{
		_y = y;
	}

	float Vertex::TriangleArea(Vertex b, Vertex c)
	{
		float x1 = b.GetX() - _x;
		float y1 = b.GetY() - _y;

		float x2 = c.GetX() - _x;
		float y2 = c.GetY() - _y;

		return (x1 * y2 - x2 * y1);
	}
}