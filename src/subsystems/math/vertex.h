#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef char Byte;

namespace MagusEngine
{
	class Vertex
	{
	public:
		Vertex();
		Vertex(float x, float y, float u, float v);

		float GetX();
		float GetY();
		
		float GetU();
		float GetV();

		void SetX(float x);
		void SetY(float y);
		
		void SetU(float u);
		void SetV(float v);

		float TriangleArea(Vertex b, Vertex c);

	private:
		float _x;
		float _y;
		
		float _u;
		float _v;
	};
}

#endif