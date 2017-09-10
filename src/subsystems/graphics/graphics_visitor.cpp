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
		printf("Visiting Scene Node: %s\n", sceneNode->GetName());
	}

	void GraphicsVisitor::Visit(Component* component)
	{
		printf("Visiting Component\n");
	}

	void GraphicsVisitor::Visit(Graphic2D* graphic2D)
	{
		printf("Visiting Graphic2D\n");

		//_lowLevelRenderer->DrawBuffer(graphic2D);
	}
}