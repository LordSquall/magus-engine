#include "renderer_software_initialise_visitor.h"

#include "../../graphic2d.h"

namespace MagusEngine
{
	Renderer_Software_Initialise_Visitor::Renderer_Software_Initialise_Visitor(Renderer_Software* software)
	{
		_lowLevelRenderer = 0;
		_softwareRenderer = software;
	}

	/* Visitor Functions */
	bool Renderer_Software_Initialise_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
	{
		_lowLevelRenderer = lowlevelRenderer;
		_resources = resources;

		return true;
	}

	void Renderer_Software_Initialise_Visitor::PreVisit(SceneNode* sceneNode) {}
	void Renderer_Software_Initialise_Visitor::Visit(SceneNode* sceneNode)
	{
		printf("[Software Init Visitor]\tVisit Scene Node\n");
	}
	void Renderer_Software_Initialise_Visitor::PostVisit(SceneNode* sceneNode) {}

	void Renderer_Software_Initialise_Visitor::PreVisit(Component* component) {}
	void Renderer_Software_Initialise_Visitor::Visit(Component* component)
	{
		printf("[Software Init Visitor]\tVisit Component\n");
	}
	void Renderer_Software_Initialise_Visitor::PostVisit(Component* component) {}

	void Renderer_Software_Initialise_Visitor::PreVisit(Graphic2D* graphic2D) {}
	void Renderer_Software_Initialise_Visitor::Visit(Graphic2D* graphic2D)
	{
		printf("[Software Init Visitor]\tVisit Graphic2D\n");
		Drawable* d = graphic2D->GetDrawable();

		printf("[Software Init Visitor]\tBuild Vertex Buffer\n");

		//d->Build(&_vertexBuildBuffer[0]);

	}
	void Renderer_Software_Initialise_Visitor::PostVisit(Graphic2D* graphic2D) {}

	/* Getters */
	Renderer_Interface* Renderer_Software_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}