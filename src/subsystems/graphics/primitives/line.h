#ifndef _LINE_H_
#define _LINE_H_

/* System Includes */

/* Local Project Includes */
#include "../drawable.h"
#include "../../math/vector.h"

namespace MagusEngine
{
	/*
	Name:  Line
	Type: Class
	Purpose: Represents a Line Shape
	*/
	class Line : public Drawable
	{
	public:
		/*
		Default contstructor
		*/
		Line();

		Line(float x1, float y1, float x2, float y2);

		/* Drawable Functions */
		void Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData);
		void PreDraw(Visitor* visitor);
		void PostDraw(Visitor* visitor);

		/* Visitable Functions */
		void Accept(Visitor* visitor);

		/* Getters */
		float GetX1();
		float GetY1();
		float GetX2();
		float GetY2();
		float GetWidth();

		/* Setters */
		void SetX1(float x);
		void SetY1(float y);
		void SetX2(float x);
		void SetY2(float y);
		void SetWidth(float width);

	private:
		float _x1;
		float _y1;
		float _x2;
		float _y2;
		float _width;
	};
}

#endif
