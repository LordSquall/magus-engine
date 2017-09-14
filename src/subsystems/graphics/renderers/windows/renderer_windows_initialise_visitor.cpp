#include "renderer_windows_initialise_visitor.h"

#include "../../../scenemanagement/scenenode.h"
#include "../../graphic2d.h"


namespace MagusEngine
{
	Renderer_Windows_Initialise_Visitor::Renderer_Windows_Initialise_Visitor()
	{
		_lowLevelRenderer = 0;

		_buildCritical = false;
	}

	/* Visitor Functions */
	bool Renderer_Windows_Initialise_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
	{
		_lowLevelRenderer = lowlevelRenderer;
		_resources = resources;

		/* Process any resources which require render specific modification */
		for (unsigned int i = 0; i < resources->GetShaderCount(); i++)
		{
			_lowLevelRenderer->CompileShaderObject(resources->GetShader(i));
		}

		for (unsigned int i = 0; i < resources->GetTextureCount(); i++)
		{
			_lowLevelRenderer->CreateTexture(resources->GetTexture(i));
		}

		return true;
	}

	void Renderer_Windows_Initialise_Visitor::PreVisit(SceneNode* sceneNode) 
	{
		_buildCritical = sceneNode->IsCritical();
	}

	void Renderer_Windows_Initialise_Visitor::Visit(SceneNode* sceneNode){}
	void Renderer_Windows_Initialise_Visitor::PostVisit(SceneNode* sceneNode) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Component* component) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Component* component){}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Component* component) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Graphic2D* graphic2D) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Graphic2D* graphic2D)
	{
		int vertexBufferLength; 
		int indicesBufferLength;

		if (_buildCritical == false)
		{
			Drawable* d = graphic2D->GetDrawable();
			d->Build(&_vertexBuildBuffer[0], &vertexBufferLength, &_indicesBuildBuffer[0], &indicesBufferLength);

			graphic2D->GetHWRenderDataHandle()->vertexlength = vertexBufferLength;
			graphic2D->GetHWRenderDataHandle()->vertexhandle = _lowLevelRenderer->GenerateVertexBuffer(&_vertexBuildBuffer[0], vertexBufferLength);

			graphic2D->GetHWRenderDataHandle()->indexlength = indicesBufferLength;
			graphic2D->GetHWRenderDataHandle()->indexhandle = _lowLevelRenderer->GenerateIndicesBuffer(&_indicesBuildBuffer[0], indicesBufferLength);
		}
	}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Graphic2D* graphic2D) {}
	
	void Renderer_Windows_Initialise_Visitor::PreVisit(Rectangle* rectangle) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Rectangle* rectangle) {}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Rectangle* rectangle) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Line* line) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Line* line) {}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Line* line) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Text* text) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Text* text) {}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Text* text) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Ellipse* ellipse) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Ellipse* ellipse) {}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Ellipse* ellipse) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Path* path) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Path* path) {}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Path* path) {}

	/* Getters */
	Renderer_Interface* Renderer_Windows_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}