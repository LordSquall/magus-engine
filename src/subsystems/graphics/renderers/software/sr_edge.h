#ifndef _SR_EDGE_H_
#define _SR_EDGE_H_

/* System Includes */

/* Local Project Includes */
#include "sr_varier.h"
#include "../../../math/vertex.h"
#include "../../../math/vector.h"

typedef char Byte;

namespace MagusEngine
{
	class SR_Edge
	{
	public:
		SR_Edge(SR_Varier varier, Vertex* start, Vertex* end, int index);
		
		void Step();

		/* Getters */
		float GetX();
		float GetYStart();
		float GetYEnd();
		Vector4f GetColor();
		Vector2f GetUV();

	private:
		float _x;
		float _xStep;
		float _yStart;
		float _yEnd;
		Vector4f _color;
		Vector4f _colorStep;
		Vector2f _uv;
		Vector2f _uvStep;
	};
}

#endif