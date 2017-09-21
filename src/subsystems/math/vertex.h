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
		Vertex(float x, float y, float z, float r, float g, float b, float a);
		Vertex(Vector4f position, Vector4f color, Vector3f normal, Vector2f extrude, Vector2f uv);

		Vector4f* GetPosition();
		Vector4f* GetColor();
		Vector3f* GetNormal();
		Vector2f* GetExtrude();
		Vector2f* GetUV();

		float GetX();
		float GetY();
		float GetZ();
		float GetW();

		float GetR();
		float GetG();
		float GetB();
		float GetA();
		
		float GetNX();
		float GetNY();
		float GetNZ();

		float GetU();
		float GetV();

		void SetPosition(float x, float y, float z, float w);
		void SetColor(float r, float g, float b, float a);
		void SetNormal(float x, float y, float z);
		void SetExtrude(float x, float y);
		void SetUV(float u, float v);

		void SetX(float x);
		void SetY(float y);
		void SetZ(float x);
		void SetW(float y);

		void SetR(float r);
		void SetG(float g);
		void SetB(float b);
		void SetA(float a);
		
		void SetNX(float x);
		void SetNY(float y);
		void SetNZ(float x);

		void SetU(float u);
		void SetV(float v);

		float TriangleAreaTimesTwo(Vertex b, Vertex c);

		Vertex Transform(Matrix4f matrix);
		Vertex PrespectiveDivide();

		Vertex Lerp(Vertex other, float lerpAmt);

		float GetIndex(int index);

	private:
		Vector4f _position;
		Vector4f _color;
		Vector3f _normal;
		Vector2f _extrude;
		Vector2f _uv;
	};
}

#endif