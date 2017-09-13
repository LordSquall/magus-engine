#include "renderer_windows_initialise_visitor.h"

#include "../../graphic2d.h"


namespace MagusEngine
{
	Renderer_Windows_Initialise_Visitor::Renderer_Windows_Initialise_Visitor()
	{
		_lowLevelRenderer = 0;
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

	void Renderer_Windows_Initialise_Visitor::PreVisit(SceneNode* sceneNode) {}
	void Renderer_Windows_Initialise_Visitor::Visit(SceneNode* sceneNode)
	{
		printf("[Windows Init Visitor]\tVisit Scene Node\n");
	}
	void Renderer_Windows_Initialise_Visitor::PostVisit(SceneNode* sceneNode) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Component* component) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Component* component)
	{
		printf("[Windows Init Visitor]\tVisit Component\n");
	}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Component* component) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Graphic2D* graphic2D) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Graphic2D* graphic2D)
	{
		int vertexBufferLength; 
		int indicesBufferLength;

		Drawable* d = graphic2D->GetDrawable();
		d->Build(&_vertexBuildBuffer[0], &vertexBufferLength, &_indicesBuildBuffer[0], &indicesBufferLength);

		graphic2D->GetRenderDataHandle()->vertexlength = vertexBufferLength;
		graphic2D->GetRenderDataHandle()->vertexhandle = _lowLevelRenderer->GenerateVertexBuffer(&_vertexBuildBuffer[0], vertexBufferLength);

		graphic2D->GetRenderDataHandle()->indexlength = indicesBufferLength;
		graphic2D->GetRenderDataHandle()->indexhandle = _lowLevelRenderer->GenerateIndicesBuffer(&_indicesBuildBuffer[0], indicesBufferLength);
	}

	void Renderer_Windows_Initialise_Visitor::PostVisit(Graphic2D* graphic2D) {}
	
	/* Getters */
	Renderer_Interface* Renderer_Windows_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}