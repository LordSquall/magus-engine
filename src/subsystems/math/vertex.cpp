#include "vertex.h"

namespace MagusEngine
{

	Vertex::Vertex()
	{
		_x = 0.0f;
		_y = 0.0f;
	}

	Vertex::Vertex(float x, float y, float u, float v)
	{
		_x = x;
		_y = y;
		_u = u;
		_v = v;
	}

	float Vertex::GetX()
	{
		return _x;
	}

	float Vertex::GetY()
	{
		return _y;
	}
	
	float Vertex::GetU()
	{
		return _u;
	}

	float Vertex::GetV()
	{
		return _v;
	}

	void Vertex::SetX(float x)
	{
		_x = x;
	}

	void Vertex::SetY(float y)
	{
		_y = y;
	}

	void Vertex::SetU(float u)
	{
		_u = u;
	}

	void Vertex::SetV(float v)
	{
		_v = v;
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