#include "sr_edge.h"

namespace MagusEngine
{
	
	SR_Edge::SR_Edge(SR_Varier varier, Vertex* start, Vertex* end, int index)
	{
		/* Initilaise variables */
		_x = 0.0f;
		_xStep = 0.0f;
		_yStart = 0.0f;
		_yEnd = 0.0f;

		_yStart = (int)ceil(start->GetY()); 
		_yEnd = (int)ceil(end->GetY());

		float yD = end->GetY() - start->GetY();
		float xD = end->GetX() - start->GetX();

		float yPrestep = _yStart - start->GetY();

		_xStep = xD / yD;
		
		_x = start->GetX() + yPrestep * _xStep;
		float xPrestep = _x - start->GetX();

		_color = (*varier.GetColor(index)) +
			(*varier.GetColorYStep()) * yPrestep +
			(*varier.GetColorXStep()) * xPrestep;

		_colorStep = (*varier.GetColorYStep()) + (*varier.GetColorXStep()) * _xStep;

		_uv = (*varier.GetUV(index)) +
			(*varier.GetUVYStep()) * yPrestep +
			(*varier.GetUVXStep()) * xPrestep;

		_uvStep = (*varier.GetUVYStep()) + (*varier.GetUVXStep()) * _xStep;


	}
	
	void SR_Edge::Step()
	{
		_x += _xStep;
		_color = _color + _colorStep;
		_uv = _uv + _uvStep;
	}


	/* Getters */
	float SR_Edge::GetX() { return _x; }
	float SR_Edge::GetYStart() { return _yStart; }
	float SR_Edge::GetYEnd() { return _yEnd; }
	Vector4f SR_Edge::GetColor() { return _color; }
	Vector2f SR_Edge::GetUV() { return _uv; }
}