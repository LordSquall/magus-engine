#ifndef _MATRIX_H_
#define _MATRIX_H_

/* System Includes */
#include <math.h>

/* Local Projection Includes */
#include "vector.h"

#define PI 3.14159265359f

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
		
		float m[2][2];
	};

	class Matrix3f
	{
	public:
		Matrix3f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		void BuildIdentity();

		float m[3][3];
	};

	class Matrix4f
	{
	public:
		Matrix4f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		float* GetData();

		void BuildIdentity();
		
		void BuildTranslation(float x, float y, float z);
		void BuildTranslation(Vector3f* vec);
		void BuildRotation(float x, float y, float z);
		void BuildRotation(Vector3f* vec);
		void BuildScale(float x, float y, float z);
		void BuildScale(Vector3f* vec);

		void BuildOrthographic(float left, float right, float top, float bottom, float znear, float zfar);
		void BuildPerspective(float fov, float aspectRatio, float znear, float zfar);

		Matrix4f operator*(const Matrix4f& b);

		float m[4][4];
	};

	

}

#endif