#ifndef _GRAPHICS_VISITOR_H_
#define _GRAPHICS_VISITOR_H_

/* System Includes */
#include <thread>

/* Local Project Includes */
#include "visitor.h"
#include "../scenemanagement/scenenode.h"

namespace MagusEngine
{
	class GraphicsVisitor : public Visitor
	{
	public:
		GraphicsVisitor();

		void Initialise(Renderer_Interface* lowlevelRenderer);

		void Visit(SceneNode* sceneNode);

	private:
		Renderer_Interface*		_levellevelRenderer;
	};
}

#endif