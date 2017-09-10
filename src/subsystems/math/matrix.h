#ifndef _MATRIX_H_
#define _MATRIX_H_

/* System Includes */
#include <math.h>

typedef char Byte;

namespace MagusEngine
{
	class Matrix2f
	{
	public:
		Matrix2f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		void BuildIdentity();
		
	private:
		float _m[2][2];
	};

	class Matrix3f
	{
	public:
		Matrix3f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		void BuildIdentity();

	private:
		float _m[3][3];
	};

	class Matrix4f
	{
	public:
		Matrix4f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		float* GetData();

		void BuildIdentity();
		void BuildOrthographic(float left, float right, float top, float bottom, float far, float near);
		void BuildPerspective(float fov, float aspectRatio, float znear, float zfar);

	private:
		float _m[4][4];
	};

	

}

#endif