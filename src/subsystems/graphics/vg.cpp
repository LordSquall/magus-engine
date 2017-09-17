#include "vg.h"

namespace MagusEngine
{
	void VG::CalculateCornerPoint(Vector4f* ptA, Vector4f* ptB, Vector4f* ptC, Vector2f* pos, Vector2f* neg)
	{
		Vector2f seg1normal = Vector2f(ptB->y - ptA->y, ptB->x - ptA->x);
		Vector2f seg2normal = Vector2f(ptC->y - ptB->y, ptC->x - ptB->x);

		seg1normal.Normalise();
		seg2normal.Normalise();

		Vector2f resultPos = Vector2f(seg1normal.x + seg2normal.x, seg1normal.y + seg2normal.y);

		resultPos.Normalise();

		/*  Invret the sign of X */
		if (resultPos.x > 0.0)
		{
			pos->x = -fabs(resultPos.x);
		}
		else
		{
			pos->x = fabs(resultPos.x);
		}
		pos->y = resultPos.y;
	}
}