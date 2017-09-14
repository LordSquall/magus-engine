#include "sr_varier.h"

namespace MagusEngine
{
	
	SR_Varier::SR_Varier(Vertex* start, Vertex* mid, Vertex* end)
	{
		_colors[0] = *start->GetColor();
		_colors[1] = *mid->GetColor();
		_colors[2] = *end->GetColor();

		_uv[0] = *start->GetUV();
		_uv[1] = *mid->GetUV();
		_uv[2] = *end->GetUV();

		float oneOverdx = 1.0f /
			(((mid->GetX() - end->GetX()) *
			(start->GetY() - end->GetY())) -
			((start->GetX() - end->GetX()) *
			(mid->GetY() - end->GetY())));

		float oneOverdy = -oneOverdx;

		_colorXStep = 
			(((_colors[1] - _colors[2]) *
			(start->GetY() - end->GetY())) - 
			((_colors[0] - _colors[2]) *
			(mid->GetY() - end->GetY()))) * oneOverdx;

		_colorYStep = 
			(((_colors[1] - _colors[2]) *
			(start->GetX() - end->GetX())) -
			((_colors[0] - _colors[2]) *
			(mid->GetX() - end->GetX()))) * oneOverdy;

		_uvXStep =
			(((_uv[1] - _uv[2]) *
			(start->GetY() - end->GetY())) -
			((_uv[0] - _uv[2]) *
			(mid->GetY() - end->GetY()))) * oneOverdx;

		_uvYStep =
			(((_uv[1] - _uv[2]) *
			(start->GetX() - end->GetX())) -
			((_uv[0] - _uv[2]) *
			(mid->GetX() - end->GetX()))) * oneOverdy;

	}

	/* Getters */
	Vector4f* SR_Varier::GetColor(int index) { return &_colors[index]; }
	Vector4f* SR_Varier::GetColorXStep() { return &_colorXStep; }
	Vector4f* SR_Varier::GetColorYStep() { return &_colorYStep; }

	Vector2f* SR_Varier::GetUV(int index) { return &_uv[index]; }
	Vector2f* SR_Varier::GetUVXStep() { return &_uvXStep; }
	Vector2f* SR_Varier::GetUVYStep() { return &_uvYStep; }
}