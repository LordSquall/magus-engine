#ifndef _RENDERER_STRUCTURES_H_
#define _RENDERER_STRUCTURES_H_

/* System Include */

/* Local Project Includes */

namespace MagusEngine
{
	typedef struct VBO_Structure
	{
		bool enabled;

		unsigned int vertexhandle;
		unsigned int vertexstart;
		unsigned int vertexlength;
		unsigned int vertexmax;

		unsigned int indexhandle;
		unsigned int indexstart;
		unsigned int indexlength;
		unsigned int indexmax;
	}VBO_Structure;

	typedef struct DrawableData
	{
		/* Fill Data */
		unsigned int fillVertexStart;
		unsigned int fillVertexLength;
		unsigned int fillIndexStart;
		unsigned int fillIndexLength;

	}DrawableData;

}

#endif