#include "matrix.h"

namespace MagusEngine
{
	Matrix2f::Matrix2f() { };

	float Matrix2f::Get(int i, int j) { return _m[i][j]; }
	void Matrix2f::Set(int i, int j, float v) { _m[i][j] = v; }

	void Matrix2f::BuildIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;
	}




	Matrix3f::Matrix3f() { };

	float Matrix3f::Get(int i, int j) { return _m[i][j]; }
	void Matrix3f::Set(int i, int j, float v) { _m[i][j] = v; }

	void Matrix3f::BuildIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;	_m[0][2] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;	_m[1][2] = 0.0f;
		_m[2][0] = 0.0f;	_m[2][1] = 0.0f;	_m[2][2] = 1.0f;
	}



	Matrix4f::Matrix4f() { };

	float Matrix4f::Get(int i, int j) { return _m[i][j]; }
	void Matrix4f::Set(int i, int j, float v) { _m[i][j] = v; }



	float* Matrix4f::GetData() { return &_m[0][0]; }

	void Matrix4f::BuildIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;	_m[0][2] = 0.0f;	_m[0][3] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;	_m[1][2] = 0.0f;	_m[1][3] = 0.0f;
		_m[2][0] = 0.0f;	_m[2][1] = 0.0f;	_m[2][2] = 1.0f;	_m[2][3] = 0.0f;
		_m[3][0] = 0.0f;	_m[3][1] = 0.0f;	_m[3][2] = 0.0f;	_m[3][3] = 1.0f;
	}

	void Matrix4f::BuildOrthographic(float left, float right, float top, float bottom, float far, float near)
	{
		float width = right - left;
		float height = top - bottom;
		float depth = far - near;

		_m[0][0] = 2.00f / width; 	_m[0][1] = 0.0f;			_m[0][2] = 0.0f;			_m[0][3] = -(right + left) / width;
		_m[1][0] = 0.0f;			_m[1][1] = 2.0f / height;	_m[1][2] = 0.0f;			_m[1][3] = -(top + bottom) / height;
		_m[2][0] = 0.0f;			_m[2][1] = 0.0f;			_m[2][2] = 2.0f / depth;	_m[2][3] = -(far + near) / depth;
		_m[3][0] = 0.0f;			_m[3][1] = 0.0f;			_m[3][2] = 0.0f;			_m[3][3] = 1.0f;
	}

	void Matrix4f::BuildPerspective(float fov, float ratio, float znear, float zfar)
	{
		float t = tan(fov / 2.0f);
		float zr = znear - zfar;

		_m[0][0] = 1.0f / (t * ratio); 	_m[0][1] = 0.0f;		_m[0][2] = 0.0f;					_m[0][3] = 0.0f;
		_m[1][0] = 0.0f;				_m[1][1] = 1.0f / t;	_m[1][2] = 0.0f;					_m[1][3] = 0.0f;
		_m[2][0] = 0.0f;				_m[2][1] = 0.0f;		_m[2][2] = (-znear - zfar) / zr; 	_m[2][3] = 2.0f * zfar * znear / zr;
		_m[3][0] = 0.0f;				_m[3][1] = 0.0f;		_m[3][2] = 0.0f;					_m[3][3] = 1.0f;
	}
}