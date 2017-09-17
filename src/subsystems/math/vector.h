#ifndef _VECTOR_H_
#define _VECTOR_H_

/* System Includes */
#include <math.h>

typedef char Byte;

namespace MagusEngine
{
	class Vector2f
	{
	public:
		Vector2f();
		Vector2f(float x, float y);

		float Length();

		void Normalise();
		float Cross(Vector2f* other);

		Vector2f operator+(const Vector2f& b);
		Vector2f operator-(const Vector2f& b);
		Vector2f operator*(const Vector2f& b);
		Vector2f operator/(const Vector2f& b);

		Vector2f operator+(const float& b);
		Vector2f operator-(const float& b);
		Vector2f operator*(const float& b);
		Vector2f operator/(const float& b);

		float x;
		float y;
	};

	class Vector3f
	{
	public:

		Vector3f();
		Vector3f(float x, float y, float z);


		Vector3f operator+(const Vector3f& b);
		Vector3f operator-(const Vector3f& b);
		Vector3f operator*(const Vector3f& b);
		Vector3f operator/(const Vector3f& b);

		Vector3f operator+(const float& b);
		Vector3f operator-(const float& b);
		Vector3f operator*(const float& b);
		Vector3f operator/(const float& b);

		float x;
		float y;
		float z;
	};

	class Vector4f
	{
	public:
		Vector4f();
		Vector4f(float x, float y, float z, float w);

		Vector4f Lerp(Vector4f dest, float factor);

		Vector4f operator+(const Vector4f& b);
		Vector4f operator-(const Vector4f& b);
		Vector4f operator*(const Vector4f& b);
		Vector4f operator/(const Vector4f& b);

		Vector4f operator+(const float& b);
		Vector4f operator-(const float& b);
		Vector4f operator*(const float& b);
		Vector4f operator/(const float& b);

		float x;
		float y;
		float z;
		float w;
	};

}

#endif