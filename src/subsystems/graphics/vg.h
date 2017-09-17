#ifndef _VG_H_
#define _VG_H_

/* System Includes */

/* Local Project includes*/
#include "../math/vector.h"

namespace MagusEngine
{
	class VG
	{
	public:
		static void CalculateCornerPoint(Vector4f* ptA, Vector4f* ptB, Vector4f* ptC, Vector2f* pos, Vector2f* neg);
	};
}

#endif