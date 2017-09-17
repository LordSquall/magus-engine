#ifndef _PATH_H_
#define _PATH_H_

/* System Includes */

/* Local Project Includes */
#include "../../external/poly2tri/poly2tri.h"
#include "../drawable.h"

namespace MagusEngine
{
	/*
	Name:  Path
	Type: Class
	Purpose: Represents a Path Shape
	*/
	class Path : public Drawable
	{
	public:
		/*
		Default contstructor
		*/
		Path(const char* pointString);

		/* Drawable Functions */
		void Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData);
		void PreDraw(Visitor* visitor);
		void PostDraw(Visitor* visitor);

		/* Visitable Functions */
		void Accept(Visitor* visitor);

		/* Getters */

		/* Setters */


	private:
		std::vector<p2t::Point*> _points;
	};
}

#endif
