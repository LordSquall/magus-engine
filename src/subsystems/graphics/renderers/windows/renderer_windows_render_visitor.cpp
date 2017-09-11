#include "renderer_windows_render_visitor.h"

#include "../../../scenemanagement/scenenode.h"
#include "../../graphic2d.h"

namespace MagusEngine
{
	Renderer_Windows_Render_Visitor::Renderer_Windows_Render_Visitor()
	{
		_lowLevelRenderer = 0;
		_matrixStackHead = 0;
	}

	/* Visitor Functions */
	bool Renderer_Windows_Render_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
	{
		_lowLevelRenderer = lowlevelRenderer;
		_resources = resources;

		/* Add a identify to matric to the top of the stack*/
		_matrixStack[_matrixStackHead] = Matrix4f();
		_matrixStackHead++;

		return true;
	}

	void Renderer_Windows_Render_Visitor::PreVisit(SceneNode* sceneNode) 
	{
		/* Build model Matrix */
		Matrix4f translation = Matrix4f();
		Matrix4f rotation = Matrix4f();
		Matrix4f scale = Matrix4f();
		Matrix4f model = Matrix4f();

		translation.BuildTranslation(sceneNode->GetPosition());
		rotation.BuildRotation(sceneNode->GetRotation());
		scale.BuildScale(sceneNode->GetScale());

		model = _matrixStack[_matrixStackHead-1] * (scale * translation * rotation);
		_matrixStack[_matrixStackHead] = model;
		_matrixStackHead++;
	}

	void Renderer_Windows_Render_Visitor::Visit(SceneNode* sceneNode){}
	
	void Renderer_Windows_Render_Visitor::PostVisit(SceneNode* sceneNode) 
	{
		_matrixStackHead--;
	}
	
	void Renderer_Windows_Render_Visitor::PreVisit(Component* component) {}
	void Renderer_Windows_Render_Visitor::Visit(Component* component)
	{
	}
	void Renderer_Windows_Render_Visitor::PostVisit(Component* component) {}

	void Renderer_Windows_Render_Visitor::PreVisit(Graphic2D* graphic2D) 
	{
		_lowLevelRenderer->SetCurrentModelMatrix(&_matrixStack[_matrixStackHead-1]);
	}
	void Renderer_Windows_Render_Visitor::Visit(Graphic2D* graphic2D)
	{
		_lowLevelRenderer->SetMaterial(graphic2D->GetMaterial());

		_lowLevelRenderer->DrawBuffers(graphic2D->GetRenderDataHandle());
	}
	void Renderer_Windows_Render_Visitor::PostVisit(Graphic2D* graphic2D) {}

	/* Getters */
	Renderer_Interface* Renderer_Windows_Render_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}