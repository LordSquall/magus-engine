#include "renderer_software_initialise_visitor.h"

namespace MagusEngine
{
	Renderer_Software_Initialise_Visitor::Renderer_Software_Initialise_Visitor()
	{
		_lowLevelRenderer = 0;
	}

	/* Visitor Functions */
	bool Renderer_Software_Initialise_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
	{
		_lowLevelRenderer = lowlevelRenderer;
		_resources = resources;

		return true;
	}

	void Renderer_Software_Initialise_Visitor::Visit(SceneNode* sceneNode)
	{
		printf("[Software Init Visitor]\tVisit Scene Node\n");
	}

	void Renderer_Software_Initialise_Visitor::Visit(Component* component)
	{
		printf("[Software Init Visitor]\tVisit Component\n");
	}

	void Renderer_Software_Initialise_Visitor::Visit(Graphic2D* graphic2D)
	{
		printf("[Software Init Visitor]\tVisit Graphic2D\n");
	}

	/* Getters */
	Renderer_Interface* Renderer_Software_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}