#ifndef _VISITOR_H_
#define _VISITOR_H_

/* System Includes */
#include <stdio.h>

/* Local Project Includes */
#include "../graphics/renderers/renderer_interface.h"
#include "../resources/resources.h"

namespace MagusEngine
{
	class SceneNode;
	class Component;
	class Graphic2D;
	
	class Visitor
	{
	public:
		virtual bool Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources) = 0;

		virtual void PreVisit(SceneNode* sceneNode) = 0;
		virtual void Visit(SceneNode* sceneNode) = 0;
		virtual void PostVisit(SceneNode* sceneNode) = 0;

		virtual void PreVisit(Component* component) = 0;
		virtual void Visit(Component* component) = 0;
		virtual void PostVisit(Component* component) = 0;

		virtual void PreVisit(Graphic2D* graphic2d) = 0;
		virtual void Visit(Graphic2D* graphic2d) = 0;
		virtual void PostVisit(Graphic2D* graphic2d) = 0;

	};
}

#endif