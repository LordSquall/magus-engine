#ifndef _VERTEX_H_
#define _VERTEX_H_

typedef char Byte;

namespace MagusEngine
{
	class Vertex
	{
	public:
		Vertex();
		Vertex(float x, float y);

		float GetX();
		float GetY();

		void SetX(float x);
		void SetY(float y);

		float TriangleArea(Vertex b, Vertex c);

	private:
		float _x;
		float _y;
	};
}

#endif