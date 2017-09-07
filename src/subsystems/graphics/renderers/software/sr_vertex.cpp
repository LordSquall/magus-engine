#include "sr_vertex.h"

namespace MagusEngine
{
	
	SR_Vertex::SR_Vertex(float x, float y)
	{
		_x = x;
		_y = y;
	}

	float SR_Vertex::GetX()
	{
		return _x;
	}

	float SR_Vertex::GetY()
	{
		return _y;
	}

	void SR_Vertex::SetX(float x)
	{
		_x = x;
	}

	void SR_Vertex::SetY(float y)
	{
		_y = y;
	}

	float SR_Vertex::TriangleArea(SR_Vertex b, SR_Vertex c)
	{
		float x1 = b.GetX() - _x;
		float y1 = b.GetY() - _y;

		float x2 = c.GetX() - _x;
		float y2 = c.GetY() - _y;

		return (x1 * y2 - x2 * y1);
	}
}