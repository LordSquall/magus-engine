#ifndef _SR_MATRIX_H_
#define _SR_MATRIX_H_

typedef char Byte;

namespace MagusEngine
{
	class SR_Matrix2f
	{
	public:
		SR_Matrix2f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		void SetIdentity();
		
	private:
		float _m[2][2];
	};

	class SR_Matrix3f
	{
	public:
		SR_Matrix3f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		void SetIdentity();

	private:
		float _m[3][3];
	};

	class SR_Matrix4f
	{
	public:
		SR_Matrix4f();

		float Get(int i, int j);
		void Set(int i, int j, float v);

		void SetIdentity();

	private:
		float _m[4][4];
	};

	

}

#endif