#include "vertex.h"

namespace MagusEngine
{

	Vertex::Vertex()
	{
		_position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Vertex::Vertex(float x, float y, float z)
	{
		_position = Vector4f(x, y, z, 1.0f);

		_u = 0.0f;
		_v = 0.0f;
	}

	Vertex::Vertex(Vector4f vector)
	{
		_position = vector;

		_u = 0.0f;
		_v = 0.0f;
	}

	float Vertex::GetX() { return _position.x; }
	float Vertex::GetY() { return _position.y; }
	float Vertex::GetZ() { return _position.z; }
	float Vertex::GetW() { return _position.w; }

	float Vertex::GetU() { return _u; }
	float Vertex::GetV() { return _v; }

	void Vertex::SetX(float x) { _position.x = x; }
	void Vertex::SetY(float y) { _position.y = y; }
	void Vertex::SetZ(float z) { _position.z = z; }
	void Vertex::SetW(float w) { _position.w = w; }
	void Vertex::SetU(float u) { _u = u; }
	void Vertex::SetV(float v) { _v = v; }

	Vertex Vertex::Transform(Matrix4f matrix)
	{
		return Vertex(matrix * _position);
	}

	Vertex Vertex::PrespectiveDivide()
	{
		return Vertex(_position.x / _position.w, _position.y / _position.w, _position.z / _position.w);
	}

	float Vertex::TriangleAreaTimesTwo(Vertex b, Vertex c)
	{
		float x1 = b.GetX() - _position.x;
		float y1 = b.GetY() - _position.y;

		float x2 = c.GetX() - _position.x;
		float y2 = c.GetY() - _position.y;

		return (x1 * y2 - x2 * y1);
	}
}