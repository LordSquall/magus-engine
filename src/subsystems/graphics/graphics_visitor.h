#ifndef _GRAPHICS_VISITOR_H_
#define _GRAPHICS_VISITOR_H_

/* System Includes */
#include <thread>

/* Local Project Includes */
#include "../scenemanagement/visitor.h"
#include "../scenemanagement/scenenode.h"
#include "../scenemanagement/component.h"

#include "../graphics/graphic2d.h"

namespace MagusEngine
{
	class GraphicsVisitor : public Visitor
	{
	public:
		GraphicsVisitor();

		bool Initialise(Renderer_Interface* lowlevelRenderer);

		void Visit(SceneNode* sceneNode);
		void Visit(Component* component);

		void Visit(Graphic2D* graphic2D);

	private:
		Renderer_Interface*		_lowLevelRenderer;
	};
}

#endif