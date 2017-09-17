#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

/* System Includes */

/* Local Project Includes */
#include "renderers/renderer_structures.h"
#include "vg.h"
#include "../scenemanagement/visitable.h"
#include "../math/vertex.h"

namespace MagusEngine
{
	class Drawable: public Visitable
	{
	public:
		virtual void Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData) = 0;
		
		virtual void PreDraw(Visitor* visitor) = 0;

		virtual void PostDraw(Visitor* visitor) = 0;

		virtual void Accept(Visitor* visitor) = 0;

		bool markUpdated;
	};
}

#endif
