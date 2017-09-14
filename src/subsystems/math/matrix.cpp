#include "matrix.h"

namespace MagusEngine
{
	Matrix2f::Matrix2f() { BuildIdentity(); };

	float Matrix2f::Get(int i, int j) { return m[i][j]; }
	void Matrix2f::Set(int i, int j, float v) { m[i][j] = v; }

	void Matrix2f::BuildIdentity()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;
	}




	Matrix3f::Matrix3f() { BuildIdentity(); };

	float Matrix3f::Get(int i, int j) { return m[i][j]; }
	void Matrix3f::Set(int i, int j, float v) { m[i][j] = v; }

	void Matrix3f::BuildIdentity()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;
	}



	Matrix4f::Matrix4f() { BuildIdentity(); };

	float Matrix4f::Get(int i, int j) { return m[i][j]; }
	void Matrix4f::Set(int i, int j, float v) { m[i][j] = v; }



	float* Matrix4f::GetData() { return &m[0][0]; }

	void Matrix4f::BuildIdentity()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0.0f;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;
	}

	void Matrix4f::BuildTranslation(float x, float y, float z)
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = x;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = y;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = z;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;
	}

	void Matrix4f::BuildTranslation(Vector3f* vec)
	{
		BuildTranslation(vec->GetX(), vec->GetY(), vec->GetZ());
	}

	void Matrix4f::BuildRotation(float x, float y, float z)
	{
		float xRads = (x * (float)PI) / 180.0f;
		float yRads = (y * (float)PI) / 180.0f;
		float zRads = (z * (float)PI) / 180.0f;

		float cx = cos(xRads);
		float sx = sin(xRads);
		float cy = cos(yRads);
		float sy = sin(yRads);
		float cz = cos(zRads);
		float sz = sin(zRads);

		m[0][0] = cy * cz;	m[0][1] = (cz * sx * sy) - (cx * sz);	m[0][2] = (cx * cz * sy) + (sx * sz);	m[0][3] = 0.0f;
		m[1][0] = cy * sz;	m[1][1] = (cx * cz) + (sx * sy * sz);	m[1][2] = (cx * sy * sz) - (cz * sx);	m[1][3] = 0.0f;
		m[2][0] = -sy;		m[2][1] = cy * sx;						m[2][2] = cx * cy;						m[2][3] = 0.0f;
		m[3][0] = 0.0f;		m[3][1] = 0.0f;							m[3][2] = 0.0f;							m[3][3] = 1.0f;
	}

	void Matrix4f::BuildRotation(Vector3f* vec)
	{
		BuildRotation(vec->GetX(), vec->GetY(), vec->GetZ());
	}

	void Matrix4f::BuildScale(float x, float y, float z)
	{
		m[0][0] = x;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = y;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = z;	m[2][3] = 0.0f;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;
	}

	void Matrix4f::BuildScale(Vector3f* vec)
	{
		BuildScale(vec->GetX(), vec->GetY(), vec->GetZ());
	}

	void Matrix4f::BuildOrthographic(float left, float right, float top, float bottom, float znear, float zfar)
	{
		float width = right - left;
		float height = top - bottom;
		float depth = zfar - znear;

		m[0][0] = 2.00f / width; 	m[0][1] = 0.0f;				m[0][2] = 0.0f;				m[0][3] = -(right + left) / width;
		m[1][0] = 0.0f;				m[1][1] = 2.0f / height;	m[1][2] = 0.0f;				m[1][3] = -(top + bottom) / height;
		m[2][0] = 0.0f;				m[2][1] = 0.0f;				m[2][2] = -2.0f / depth;	m[2][3] = -(zfar + znear) / depth;
		m[3][0] = 0.0f;				m[3][1] = 0.0f;				m[3][2] = 0.0f;				m[3][3] = 1.0f;
	}

	void Matrix4f::BuildPerspective(float fov, float ratio, float znear, float zfar)
	{
		float t = tan(fov / 2.0f);
		float zr = znear - zfar;

		m[0][0] = 1.0f / (t * ratio); 	m[0][1] = 0.0f;		m[0][2] = 0.0f;					m[0][3] = 0.0f;
		m[1][0] = 0.0f;				m[1][1] = 1.0f / t;	m[1][2] = 0.0f;					m[1][3] = 0.0f;
		m[2][0] = 0.0f;				m[2][1] = 0.0f;		m[2][2] = (-znear - zfar) / zr; 	m[2][3] = 2.0f * zfar * znear / zr;
		m[3][0] = 0.0f;				m[3][1] = 0.0f;		m[3][2] = 0.0f;					m[3][3] = 1.0f;
	}


	void Matrix4f::BuildScreenSpaceTransform(float halfwidth, float halfheight)
	{
		m[0][0] = halfwidth;	m[0][1] = 0.0f;			m[0][2] = 0.0f;		m[0][3] = halfwidth;
		m[1][0] = 0.0f;			m[1][1] = -halfheight;	m[1][2] = 0.0f;		m[1][3] = halfheight;
		m[2][0] = 0.0f;			m[2][1] = 0.0f;			m[2][2] = 1.0f;		m[2][3] = 0.0f;
		m[3][0] = 0.0f;			m[3][1] = 0.0f;			m[3][2] = 0.0f;		m[3][3] = 1.0f;
	}

	Matrix4f Matrix4f::operator*(const Matrix4f& b)
	{
		Matrix4f t = Matrix4f();
		
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				t.Set(i, j, m[i][0] * b.m[0][j] +
							m[i][1] * b.m[1][j] +
							m[i][2] * b.m[2][j] +
							m[i][3] * b.m[3][j]);
			}	
		}

		return t;
	}

	Vector4f Matrix4f::operator*(const Vector4f& b)
	{
		
		return Vector4f(
			(m[0][0] * b.x) + (m[0][1] * b.y) + (m[0][2] * b.z) + (m[0][3] * b.w),
			(m[1][0] * b.x) + (m[1][1] * b.y) + (m[1][2] * b.z) + (m[1][3] * b.w),
			(m[2][0] * b.x) + (m[2][1] * b.y) + (m[2][2] * b.z) + (m[2][3] * b.w),
			(m[3][0] * b.x) + (m[3][1] * b.y) + (m[3][2] * b.z) + (m[3][3] * b.w)		
		);
	}
}