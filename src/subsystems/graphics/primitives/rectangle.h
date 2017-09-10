#ifndef _MAGUS_RECTANGLE_H_
#define _MAGUS_RECTANGLE_H_

/* System Includes */

/* Local Project Includes */
#include "../drawable.h"

namespace MagusEngine
{
	/*
	Name:  Rectangle
	Type: Class
	Purpose: Represents a Rectangle Shape
	*/
	class Rectangle : public Drawable
	{
	public:
		/*
		Default contstructor
		*/
		Rectangle();

		Rectangle(float x, float y, float width, float height);

		/* Drawable Functions */
		int Build(Vertex* buffer);

		/* Getters */
		float GetX();
		float GetY();
		float GetWidth();
		float GetHeight();

		/* Setters */
		void SetX(float x);
		void SetY(float y);
		void SetWidth(float width);
		void SetHeight(float height);

	private:
		float _x;
		float _y;
		float _width;
		float _height;
	};
}

#endif
