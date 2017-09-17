#include "vertex.h"

namespace MagusEngine
{

	Vertex::Vertex()
	{
		_position	= Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
		_color		= Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
		_extrude	= Vector2f(0.0f, 0.0f);
		_uv			= Vector2f(0.0f, 0.0f);
	}

	Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a)
	{
		_position	= Vector4f(x, y, z, 1.0f);
		_color		= Vector4f(r, g, b, a);
		_extrude	= Vector2f(0.0f, 0.0f);
		_uv			= Vector2f(0.0f, 0.0f);
	}

	Vertex::Vertex(Vector4f position, Vector4f color, Vector2f extrude, Vector2f uv)
	{
		_position = position;
		_color = color;
		_extrude = extrude;
		_uv = uv;
	}

	Vector4f* Vertex::GetPosition() { return &_position; }
	Vector4f* Vertex::GetColor() { return &_color; }
	Vector2f* Vertex::GetExtrude() { return &_extrude; }
	Vector2f* Vertex::GetUV() { return &_uv; }

	float Vertex::GetX() { return _position.x; }
	float Vertex::GetY() { return _position.y; }
	float Vertex::GetZ() { return _position.z; }
	float Vertex::GetW() { return _position.w; }

	float Vertex::GetR() { return _color.x; }
	float Vertex::GetG() { return _color.y; }
	float Vertex::GetB() { return _color.z; }
	float Vertex::GetA() { return _color.w; }

	float Vertex::GetU() { return _uv.x; }
	float Vertex::GetV() { return _uv.y; }

	void Vertex::SetPosition(float x, float y, float z, float w)
	{ 
		_position.x = x;
		_position.y = y;
		_position.z = z;
		_position.w = w;
	}

	void Vertex::SetColor(float r, float g, float b, float a)
	{
		_color.x = r;
		_color.y = g;
		_color.z = b;
		_color.w = a;
	}

	void Vertex::SetExtrude(float x, float y)
	{
		_extrude.x = x;
		_extrude.y = y;
	}

	void Vertex::SetUV(float u, float v)
	{
		_uv.x = u;
		_uv.y = v;
	}

	void Vertex::SetX(float x) { _position.x = x; }
	void Vertex::SetY(float y) { _position.y = y; }
	void Vertex::SetZ(float z) { _position.z = z; }
	void Vertex::SetW(float w) { _position.w = w; }

	void Vertex::SetR(float r) { _color.x = r; }
	void Vertex::SetG(float g) { _color.y = g; }
	void Vertex::SetB(float b) { _color.z = b; }
	void Vertex::SetA(float a) { _color.w = a; }

	void Vertex::SetU(float u) { _uv.x = u; }
	void Vertex::SetV(float v) { _uv.y = v; }

	Vertex Vertex::Transform(Matrix4f matrix)
	{
		return Vertex(matrix * _position, _color, _extrude, _uv);
	}

	Vertex Vertex::PrespectiveDivide()
	{
		return Vertex(
			Vector4f(_position.x / _position.w, _position.y / _position.w, _position.z / _position.w, _position.w),
			_color,
			_extrude,
			_uv);
	}

	float Vertex::TriangleAreaTimesTwo(Vertex b, Vertex c)
	{
		float x1 = b.GetX() - _position.x;
		float y1 = b.GetY() - _position.y;

		float x2 = c.GetX() - _position.x;
		float y2 = c.GetY() - _position.y;

		return (x1 * y2 - x2 * y1);
	}


	Vertex Vertex::Lerp(Vertex other, float lerpAmt)
	{
		return Vertex();

	}


	float Vertex::GetIndex(int index)
	{
		switch (index)
		{
		case 0: return GetX();
		case 1: return GetY();
		case 2: return GetZ();
		case 3: return GetW();
		}


		return 0.0f;
	}
}