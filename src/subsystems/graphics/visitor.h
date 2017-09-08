#ifndef _VISITOR_H_
#define _VISITOR_H_

/* Local Project Includes */
#include "renderers\renderer_interface.h"

namespace MagusEngine
{
	class SceneNode;
	
	class Visitor
	{
	public:
		virtual void Initialise(Renderer_Interface* lowlevelRenderer) = 0;

		virtual void Visit(SceneNode* sceneNode) = 0;
	};
}

#endif