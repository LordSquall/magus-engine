#ifndef _SR_VARIER_H_
#define _SR_VARIER_H_

/* System Includes */

/* Local Project Includes */
#include "../../../math/vertex.h"

typedef char Byte;

namespace MagusEngine
{
	class SR_Varier
	{
	public:
		SR_Varier(Vertex* start, Vertex* mid, Vertex* end);
		
		/* Getters */
		Vector4f* GetColor(int index);
		Vector4f* GetColorXStep();
		Vector4f* GetColorYStep();

		Vector2f* GetUV(int index);
		Vector2f* GetUVXStep();
		Vector2f* GetUVYStep();

	private:
		Vector4f _colors[3];
		Vector4f _colorXStep;
		Vector4f _colorYStep;

		Vector2f _uv[3];
		Vector2f _uvXStep;
		Vector2f _uvYStep;
	};
}

#endif