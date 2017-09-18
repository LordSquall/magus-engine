#include "graphics_visitor.h"


namespace MagusEngine
{
	GraphicsVisitor::GraphicsVisitor()
	{
		_lowLevelRenderer = 0;
	}

	bool GraphicsVisitor::Initialise(Renderer_Interface* lowlevelRenderer)
	{
		lowlevelRenderer = lowlevelRenderer;
		return true;
	}

	void GraphicsVisitor::Visit(SceneNode* sceneNode)
	{
;
	}

	void GraphicsVisitor::Visit(Component* component)
	{

	}

	void GraphicsVisitor::Visit(Graphic2D* graphic2D)
	{

		//_lowLevelRenderer->DrawBuffer(graphic2D);
	}
}