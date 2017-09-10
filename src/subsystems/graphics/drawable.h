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
		virtual int Build(Vertex* buffer) = 0;
	};
}

#endif
