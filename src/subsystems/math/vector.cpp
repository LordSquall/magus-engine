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

	float Vector2f::Length()
	{
		return sqrt((_x * _x) + (_y * _y));
	}

	void Vector2f::Normalise()
	{
		float length = Length();

		_x = _x / length;
		_y = _y / length;
	}

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
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	Vector4f::Vector4f(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
}