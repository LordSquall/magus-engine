#ifndef _COMPONENT_H_
#define _COMPONENT_H_

/* System Includes */
#include <stdio.h>

/* Local Project Includes */
#include "visitor.h"
#include "visitable.h"

namespace MagusEngine
{
	/*
		Name: Component
		Type: Interface
		Purpose: A single visiable application on a scene graph
	*/
	class Component : public Visitable
	{
	public:

		/* Visitable Fucntions */
		virtual void Accept(Visitor* visitor) = 0;

		virtual void Initialise() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}

#endif