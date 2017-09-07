#ifndef _SR_VERTEX_H_
#define _SR_VERTEX_H_

typedef char Byte;

namespace MagusEngine
{
	class SR_Vertex
	{
	public:
		SR_Vertex(float x, float y);

		float GetX();
		float GetY();

		void SetX(float x);
		void SetY(float y);

		float TriangleArea(SR_Vertex b, SR_Vertex c);

	private:
		float _x;
		float _y;
	};
}

#endif