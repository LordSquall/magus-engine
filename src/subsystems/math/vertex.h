#ifndef _VERTEX_H_
#define _VERTEX_H_

/* Local Project Includes */
#include "vector.h"
#include "matrix.h"

typedef char Byte;

namespace MagusEngine
{
	class Vertex
	{
	public:
		Vertex();
		Vertex(float x, float y, float z);
		Vertex(Vector4f vector);

		float GetX();
		float GetY();
		float GetZ();
		float GetW();
		
		float GetU();
		float GetV();

		void SetX(float x);
		void SetY(float y);
		void SetZ(float x);
		void SetW(float y);
		
		void SetU(float u);
		void SetV(float v);

		float TriangleAreaTimesTwo(Vertex b, Vertex c);

		Vertex Transform(Matrix4f matrix);
		Vertex PrespectiveDivide();

	private:
		Vector4f _position;
		
		float _u;
		float _v;
	};
}

#endif