#include "vector.h"

namespace MagusEngine
{
	Vector2f::Vector2f()
	{
		_x = 0.0f;
		_y = 0.0f;
	}

	Vector2f::Vector2f(float x, float y)
	{
		_x = x;
		_y = y;
	}

	float Vector2f::GetX() { return _x; }
	float Vector2f::GetY() {	return _y; }

	void Vector2f::SetX(float x) { _x = x; }
	void Vector2f::SetY(float y) { _y = y; }


	Vector3f::Vector3f()
	{
		_x = 0.0f;
		_y = 0.0f;
		_z = 0.0f;
	}

	Vector3f::Vector3f(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	float Vector3f::GetX() { return _x; }
	float Vector3f::GetY() { return _y; }
	float Vector3f::GetZ() { return _z; }

	void Vector3f::SetX(float x) { _x = x; }
	void Vector3f::SetY(float y) { _y = y; }
	void Vector3f::SetZ(float z) { _z = z; }


	Vector4f::Vector4f()
	{
		_x = 0.0f;
		_y = 0.0f;
		_z = 0.0f;
		_w = 0.0f;
	}

	Vector4f::Vector4f(float x, float y, float z, float w)
	{
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	float Vector4f::GetX() { return _x; }
	float Vector4f::GetY() { return _y; }
	float Vector4f::GetZ() { return _z; }
	float Vector4f::GetW() { return _w; }

	void Vector4f::SetX(float x) { _x = x; }
	void Vector4f::SetY(float y) { _y = y; }
	void Vector4f::SetZ(float z) { _z = z; }
	void Vector4f::SetW(float w) { _w = w; }
}