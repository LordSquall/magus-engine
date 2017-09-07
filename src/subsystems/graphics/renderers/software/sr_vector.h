#ifndef _SR_VECTOR_H_
#define _SR_VECTOR_H_

typedef char Byte;

namespace MagusEngine
{
	class SR_Vector2f
	{
	public:
		SR_Vector2f(float x, float y);

		float GetX();
		float GetY();

		void SetX(float x);
		void SetY(float y);
		
	private:
		float _x;
		float _y;
	};

	class SR_Vector3f
	{
	public:
		SR_Vector3f(float x, float y, float z);

		float GetX();
		float GetY();
		float GetZ();

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);

	private:
		float _x;
		float _y;
		float _z;
	};

	class SR_Vector4f
	{
	public:
		SR_Vector4f(float x, float y, float z, float w);

		float GetX();
		float GetY();
		float GetZ();
		float GetW();

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);
		void SetW(float w);

	private:
		float _x;
		float _y;
		float _z;
		float _w;
	};

}

#endif