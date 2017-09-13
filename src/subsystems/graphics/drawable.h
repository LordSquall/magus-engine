#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

/* System Includes */

/* Local Project Includes */
#include "../math/vertex.h"

namespace MagusEngine
{
	class Drawable
	{
	public:
		virtual void Build(Vertex* vbuffer, int* vbufferLength, unsigned int* ibuffer, int* ibufferLength) = 0;
	};
}

#endif
