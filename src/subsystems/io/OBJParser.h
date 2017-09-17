#ifndef _OBJ_PARSER_H_
#define _OBJ_PARSER_H_

/* System Includes */

/* Local Project Includes */
#include "../math/vector.h"
#include "../resources/Mesh.h"

namespace MagusEngine
{
	class Resources;

	class OBJParser
	{
	public:
		static Mesh* ParseOBJFile(const char* filename, const char* name, Resources* resources);
	};
}

#endif