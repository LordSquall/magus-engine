#include "graphics_visitor.h"


namespace MagusEngine
{
	GraphicsVisitor::GraphicsVisitor()
	{
		_levellevelRenderer = 0;
	}

	void GraphicsVisitor::Initialise(Renderer_Interface* lowlevelRenderer)
	{
		lowlevelRenderer = lowlevelRenderer;
	}

	void GraphicsVisitor::Visit(SceneNode* sceneNode)
	{
		printf("Visiting Scene Node: %s\n", sceneNode->GetName());
	}
}