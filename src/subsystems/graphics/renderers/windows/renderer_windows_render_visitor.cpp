#include "renderer_windows_render_visitor.h"

#include "../../graphic2d.h"

namespace MagusEngine
{
	Renderer_Windows_Render_Visitor::Renderer_Windows_Render_Visitor()
	{
		_lowLevelRenderer = 0;
	}

	/* Visitor Functions */
	bool Renderer_Windows_Render_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
	{
		_lowLevelRenderer = lowlevelRenderer;
		_resources = resources;

		return true;
	}

	void Renderer_Windows_Render_Visitor::Visit(SceneNode* sceneNode)
	{
	}

	void Renderer_Windows_Render_Visitor::Visit(Component* component)
	{
	}

	void Renderer_Windows_Render_Visitor::Visit(Graphic2D* graphic2D)
	{
		_lowLevelRenderer->DrawBuffers(graphic2D->GetRenderDataHandle());
	}

	/* Getters */
	Renderer_Interface* Renderer_Windows_Render_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}