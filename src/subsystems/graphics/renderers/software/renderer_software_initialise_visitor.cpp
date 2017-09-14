#include "renderer_software_initialise_visitor.h"

#include "../../../scenemanagement/scenenode.h"
#include "../../graphic2d.h"

namespace MagusEngine
{
	Renderer_Software_Initialise_Visitor::Renderer_Software_Initialise_Visitor(Renderer_Software* software)
	{
		_lowLevelRenderer = 0;
		_softwareRenderer = software;

		_buildCritical = false;
	}

	/* Visitor Functions */
	bool Renderer_Software_Initialise_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
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

	void Renderer_Software_Initialise_Visitor::PreVisit(SceneNode* sceneNode)
	{
		_buildCritical = sceneNode->IsCritical();
	}

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
		if (_buildCritical == true)
		{
			int vertexBufferLength;
			int indicesBufferLength;

			Drawable* d = graphic2D->GetDrawable();
			d->Build(&_vertexBuildBuffer[0], &vertexBufferLength, &_indicesBuildBuffer[0], &indicesBufferLength);

			graphic2D->GetSWRenderDataHandle()->vertexlength = vertexBufferLength;
			graphic2D->GetSWRenderDataHandle()->vertexhandle = _lowLevelRenderer->GenerateVertexBuffer(&_vertexBuildBuffer[0], vertexBufferLength);

			graphic2D->GetSWRenderDataHandle()->indexlength = indicesBufferLength;
			graphic2D->GetSWRenderDataHandle()->indexhandle = _lowLevelRenderer->GenerateIndicesBuffer(&_indicesBuildBuffer[0], indicesBufferLength);
		}
	}
	void Renderer_Software_Initialise_Visitor::PostVisit(Graphic2D* graphic2D) {}

	void Renderer_Software_Initialise_Visitor::PreVisit(Rectangle* rectangle) {}
	void Renderer_Software_Initialise_Visitor::Visit(Rectangle* rectangle) {}
	void Renderer_Software_Initialise_Visitor::PostVisit(Rectangle* rectangle) {}

	void Renderer_Software_Initialise_Visitor::PreVisit(Line* line) {}
	void Renderer_Software_Initialise_Visitor::Visit(Line* line) {}
	void Renderer_Software_Initialise_Visitor::PostVisit(Line* line) {}

	void Renderer_Software_Initialise_Visitor::PreVisit(Text* text) {}
	void Renderer_Software_Initialise_Visitor::Visit(Text* text) {}
	void Renderer_Software_Initialise_Visitor::PostVisit(Text* text) {}

	/* Getters */
	Renderer_Interface* Renderer_Software_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}