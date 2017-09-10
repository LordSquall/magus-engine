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
		for (int i = 0; i < resources->GetShaderCount(); i++)
		{
			_lowLevelRenderer->CompileShaderObject(resources->GetShader(i));
		}


		return true;
	}

	void Renderer_Windows_Initialise_Visitor::Visit(SceneNode* sceneNode)
	{
		printf("[Windows Init Visitor]\tVisit Scene Node\n");
	}

	void Renderer_Windows_Initialise_Visitor::Visit(Component* component)
	{
		printf("[Windows Init Visitor]\tVisit Component\n");
	}

	void Renderer_Windows_Initialise_Visitor::Visit(Graphic2D* graphic2D)
	{
		printf("[Windows Init Visitor]\tVisit Graphic2D\n");
		Drawable* d = graphic2D->GetDrawable();

		printf("[Windows Init Visitor]\tBuild Vertex Buffer\n");

		_vertexBuildBufferCount =  d->Build(&_vertexBuildBuffer[0]);

		printf("[Windows Init Visitor]\tGenerating GPU memory\n");
		graphic2D->SetRenderDataHandle(_lowLevelRenderer->GenerateVertexBuffer(&_vertexBuildBuffer[0], _vertexBuildBufferCount));
	}

	/* Getters */
	Renderer_Interface* Renderer_Windows_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}