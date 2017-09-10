#include "renderer_software_render_visitor.h"

namespace MagusEngine
{
	Renderer_Software_Render_Visitor::Renderer_Software_Render_Visitor()
	{
		_lowLevelRenderer = 0;
	}

	/* Visitor Functions */
	bool Renderer_Software_Render_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
	{
		_lowLevelRenderer = lowlevelRenderer;
		_resources = resources;
		return true;
	}

	void Renderer_Software_Render_Visitor::Visit(SceneNode* sceneNode)
	{
		printf("[Windows Render Visitor]\tVisit Scene Node\n");
	}

	void Renderer_Software_Render_Visitor::Visit(Component* component)
	{
		printf("[Windows Render Visitor]\tVisit Component\n");
	}

	void Renderer_Software_Render_Visitor::Visit(Graphic2D* graphic2D)
	{
		printf("[Windows Render Visitor]\tVisit Graphic2D\n");
	}

	/* Getters */
	Renderer_Interface* Renderer_Software_Render_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}