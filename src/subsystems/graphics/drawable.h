#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

/* System Includes */

/* Local Project Includes */
#include "../scenemanagement/visitable.h"
#include "../math/vertex.h"

namespace MagusEngine
{
	class Drawable: public Visitable
	{
	public:
		virtual void Build(Vertex* vbuffer, int* vbufferLength, unsigned int* ibuffer, int* ibufferLength) = 0;

		virtual void PreDraw(Visitor* visitor) = 0;

		virtual void PostDraw(Visitor* visitor) = 0;

		virtual void Accept(Visitor* visitor) = 0;
	};
}

#endif
