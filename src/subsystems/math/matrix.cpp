#include "matrix.h"

namespace MagusEngine
{
	Matrix2f::Matrix2f() { };

	float Matrix2f::Get(int i, int j) { return _m[i][j]; }
	void Matrix2f::Set(int i, int j, float v) { _m[i][j] = v; }

	void Matrix2f::SetIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;
	}




	Matrix3f::Matrix3f() { };

	float Matrix3f::Get(int i, int j) { return _m[i][j]; }
	void Matrix3f::Set(int i, int j, float v) { _m[i][j] = v; }

	void Matrix3f::SetIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;	_m[0][2] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;	_m[1][2] = 0.0f;
		_m[2][0] = 0.0f;	_m[2][1] = 0.0f;	_m[2][2] = 1.0f;
	}



	Matrix4f::Matrix4f() { };

	float Matrix4f::Get(int i, int j) { return _m[i][j]; }
	void Matrix4f::Set(int i, int j, float v) { _m[i][j] = v; }

	void Matrix4f::SetIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;	_m[0][2] = 0.0f;	_m[0][3] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;	_m[1][2] = 0.0f;	_m[1][3] = 0.0f;
		_m[2][0] = 0.0f;	_m[2][1] = 0.0f;	_m[2][2] = 1.0f;	_m[2][3] = 0.0f;
		_m[3][0] = 0.0f;	_m[3][1] = 0.0f;	_m[3][2] = 0.0f;	_m[3][3] = 1.0f;
	}
}