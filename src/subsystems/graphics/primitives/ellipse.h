#ifndef _ELLIPSE_H
#define _ELLIPSE_H

/* System Includes */

/* Local Project Includes */
#include "../drawable.h"

namespace MagusEngine
{
	/*
	Name:  Ellipse
	Type: Class
	Purpose: Represents a Ellipse Shape
	*/
	class Ellipse : public Drawable
	{
	public:
		/*
		Default contstructor
		*/
		Ellipse();

		Ellipse(float x, float y, float rx, float ry);

		/* Drawable Functions */
		void Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData);
		void PreDraw(Visitor* visitor);
		void PostDraw(Visitor* visitor);

		/* Visitable Functions */
		void Accept(Visitor* visitor);

		/* Getters */
		float GetX();
		float GetY();
		float GetRX();
		float GetRY();

		/* Setters */
		void SetX(float x);
		void SetY(float y);
		void SetRY(float ry);
		void SetRX(float rx);

	private:
		float _x;
		float _y;
		float _rx;
		float _ry;
	};
}

#endif
