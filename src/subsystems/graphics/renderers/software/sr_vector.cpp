#include "sr_vector.h"

namespace MagusEngine
{
	SR_Vector2f::SR_Vector2f(float x, float y)
	{
		_x = x;
		_y = y;
	}

	float SR_Vector2f::GetX() { return _x; }
	float SR_Vector2f::GetY() {	return _y; }

	void SR_Vector2f::SetX(float x) { _x = x; }
	void SR_Vector2f::SetY(float y) { _y = y; }



	SR_Vector3f::SR_Vector3f(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	float SR_Vector3f::GetX() { return _x; }
	float SR_Vector3f::GetY() { return _y; }
	float SR_Vector3f::GetZ() { return _z; }

	void SR_Vector3f::SetX(float x) { _x = x; }
	void SR_Vector3f::SetY(float y) { _y = y; }
	void SR_Vector3f::SetZ(float z) { _z = z; }



	SR_Vector4f::SR_Vector4f(float x, float y, float z, float w)
	{
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	float SR_Vector4f::GetX() { return _x; }
	float SR_Vector4f::GetY() { return _y; }
	float SR_Vector4f::GetZ() { return _z; }
	float SR_Vector4f::GetW() { return _w; }

	void SR_Vector4f::SetX(float x) { _x = x; }
	void SR_Vector4f::SetY(float y) { _y = y; }
	void SR_Vector4f::SetZ(float z) { _z = z; }
	void SR_Vector4f::SetW(float w) { _w = w; }
}