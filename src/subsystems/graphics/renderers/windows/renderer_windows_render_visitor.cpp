#include "renderer_windows_render_visitor.h"

#include "../../../scenemanagement/scenenode.h"
#include "../../graphic2d.h"
#include "../../primitives/text.h"

namespace MagusEngine
{
	Renderer_Windows_Render_Visitor::Renderer_Windows_Render_Visitor()
	{
		_lowLevelRenderer = 0;
		_matrixStackHead = 0;

		_renderCritical = false;

		_cachedTexture = 0;
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

		/* Set the current material settings in the low level renderer */
		if(sceneNode->GetMaterial() != NULL)
			_lowLevelRenderer->SetMaterial(sceneNode->GetMaterial());

		_renderCritical = sceneNode->IsCritical();

	}

	void Renderer_Windows_Render_Visitor::Visit(SceneNode* sceneNode)
	{
		if(strcmp(sceneNode->GetName(), "testnode") == 0)
		{
			//sceneNode->SetRotation(0.0f, 0.0f, sceneNode->GetRotation()->GetZ() + 1.0f);
		}
	}
	
	void Renderer_Windows_Render_Visitor::PostVisit(SceneNode* sceneNode) 
	{
		if (sceneNode->GetMaterial() != NULL)
			_lowLevelRenderer->SetMaterial(sceneNode->GetMaterial());

		_matrixStackHead--;
	}
	
	void Renderer_Windows_Render_Visitor::PreVisit(Component* component) {}
	void Renderer_Windows_Render_Visitor::Visit(Component* component) {}
	void Renderer_Windows_Render_Visitor::PostVisit(Component* component) {}

	void Renderer_Windows_Render_Visitor::PreVisit(Graphic2D* graphic2D) 
	{
		_lowLevelRenderer->SetCurrentModelMatrix(&_matrixStack[_matrixStackHead-1]);
	}

	void Renderer_Windows_Render_Visitor::Visit(Graphic2D* graphic2D)
	{
		if(_renderCritical == false)
			_lowLevelRenderer->DrawBuffers(graphic2D->GetHWRenderDataHandle());
	}
	void Renderer_Windows_Render_Visitor::PostVisit(Graphic2D* graphic2D) {}

	void Renderer_Windows_Render_Visitor::PreVisit(Rectangle* rectangle) {}
	void Renderer_Windows_Render_Visitor::Visit(Rectangle* rectangle) {}
	void Renderer_Windows_Render_Visitor::PostVisit(Rectangle* rectangle) {}

	void Renderer_Windows_Render_Visitor::PreVisit(Line* line) {}
	void Renderer_Windows_Render_Visitor::Visit(Line* line) {}
	void Renderer_Windows_Render_Visitor::PostVisit(Line* line) {}

	void Renderer_Windows_Render_Visitor::PreVisit(Text* text) 
	{
		/* cache the current texture */
		_cachedTexture = _lowLevelRenderer->GetTexture();

		/* set the texture to the font texture */
		_lowLevelRenderer->SetTexture(text->GetFont()->GetTexture());
	}

	void Renderer_Windows_Render_Visitor::Visit(Text* text) {}
	void Renderer_Windows_Render_Visitor::PostVisit(Text* text)
	{
		/* set the renderer back to the cached texture */
		_lowLevelRenderer->SetTexture(_cachedTexture);
	}

	/* Getters */
	Renderer_Interface* Renderer_Windows_Render_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}