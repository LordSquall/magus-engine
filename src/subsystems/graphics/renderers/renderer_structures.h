#ifndef _RENDERER_STRUCTURES_H_
#define _RENDERER_STRUCTURES_H_

/* System Include */

/* Local Project Includes */

namespace MagusEngine
{
	typedef struct VBO_Structure
	{
		unsigned int vertexhandle;
		unsigned int vertexlength;

		unsigned int indexhandle;
		unsigned int indexlength;
	}VBO_Structure;

	typedef struct DrawableData
	{
		VBO_Structure fill;
		VBO_Structure stroke;
	};

}

#endif