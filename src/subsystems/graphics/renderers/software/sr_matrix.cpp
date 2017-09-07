#include "sr_matrix.h"

namespace MagusEngine
{
	SR_Matrix2f::SR_Matrix2f() { };

	float SR_Matrix2f::Get(int i, int j) { return _m[i][j]; }
	void SR_Matrix2f::Set(int i, int j, float v) { _m[i][j] = v; }

	void SR_Matrix2f::SetIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;
	}




	SR_Matrix3f::SR_Matrix3f() { };

	float SR_Matrix3f::Get(int i, int j) { return _m[i][j]; }
	void SR_Matrix3f::Set(int i, int j, float v) { _m[i][j] = v; }

	void SR_Matrix3f::SetIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;	_m[0][2] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;	_m[1][2] = 0.0f;
		_m[2][0] = 0.0f;	_m[2][1] = 0.0f;	_m[2][2] = 1.0f;
	}



	SR_Matrix4f::SR_Matrix4f() { };

	float SR_Matrix4f::Get(int i, int j) { return _m[i][j]; }
	void SR_Matrix4f::Set(int i, int j, float v) { _m[i][j] = v; }

	void SR_Matrix4f::SetIdentity()
	{
		_m[0][0] = 1.0f;	_m[0][1] = 0.0f;	_m[0][2] = 0.0f;	_m[0][3] = 0.0f;
		_m[1][0] = 0.0f;	_m[1][1] = 1.0f;	_m[1][2] = 0.0f;	_m[1][3] = 0.0f;
		_m[2][0] = 0.0f;	_m[2][1] = 0.0f;	_m[2][2] = 1.0f;	_m[2][3] = 0.0f;
		_m[3][0] = 0.0f;	_m[3][1] = 0.0f;	_m[3][2] = 0.0f;	_m[3][3] = 1.0f;
	}
}