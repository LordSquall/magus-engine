#ifndef _SR_PIPELINE_H_
#define _SR_PIPELINE_H_

/* System Includes */

/* Local Project Includes */
#include "../../../math/vector.h"

typedef char Byte;

namespace MagusEngine
{
	class SR_Pipeline
	{
	public:
		static Vector4f VertexFunction();
		static Vector4f FragmentFunction();
	};
}

#endif