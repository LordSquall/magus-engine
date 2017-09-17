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
		/* Software rendering only occurs on critical components */
		if (_buildCritical == true)
		{
			VBO_Structure fillData;
			VBO_Structure strokeData;

			/* Use the attached drawable to build the geometry data */
			Drawable* d = graphic2D->GetDrawable();

			/* Get renferences to GHandles of the graphics object */
			VBO_Structure* fillGHandle = graphic2D->GetFillDataHandle();
			VBO_Structure* strokeGHandle = graphic2D->GetStrokeDataHandle();

			d->Build(&_vertexBuildBuffer[0], &_indicesBuildBuffer[0], &fillData, &strokeData);

			/* Genearte fill vertex data for the low level renderer */
			fillGHandle->enabled = fillData.enabled;
			fillGHandle->vertexstart = fillData.vertexstart;
			fillGHandle->vertexlength = fillData.vertexlength;
			fillGHandle->vertexmax = fillData.vertexmax;
			fillGHandle->vertexhandle = _lowLevelRenderer->GenerateVertexBuffer(&_vertexBuildBuffer[0], fillGHandle);
			
			/* Genearte fill index data for the low level renderer */
			fillGHandle->indexstart = fillData.indexstart;
			fillGHandle->indexlength = fillData.indexlength;
			fillGHandle->indexmax = fillData.indexmax;
			fillGHandle->indexhandle = _lowLevelRenderer->GenerateIndicesBuffer(&_indicesBuildBuffer[0], fillGHandle);

			/* Genearte stroke vertex data for the low level renderer */
			strokeGHandle->enabled = strokeData.enabled;
			strokeGHandle->vertexstart = strokeData.vertexstart;
			strokeGHandle->vertexlength = strokeData.vertexlength;
			strokeGHandle->vertexmax = strokeData.vertexmax;
			strokeGHandle->vertexhandle = _lowLevelRenderer->GenerateVertexBuffer(&_vertexBuildBuffer[0], strokeGHandle);

			/* Genearte stroke index data for the low level renderer */
			strokeGHandle->indexstart = strokeData.indexstart;
			strokeGHandle->indexlength = strokeData.indexlength;
			strokeGHandle->indexmax = strokeData.indexmax;
			strokeGHandle->indexhandle = _lowLevelRenderer->GenerateIndicesBuffer(&_indicesBuildBuffer[0], strokeGHandle);
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

	void Renderer_Software_Initialise_Visitor::PreVisit(Ellipse* ellipse) {}
	void Renderer_Software_Initialise_Visitor::Visit(Ellipse* ellipse) {}
	void Renderer_Software_Initialise_Visitor::PostVisit(Ellipse* ellipse) {}

	void Renderer_Software_Initialise_Visitor::PreVisit(Path* path) {}
	void Renderer_Software_Initialise_Visitor::Visit(Path* path) {}
	void Renderer_Software_Initialise_Visitor::PostVisit(Path* path) {}

	/* Getters */
	Renderer_Interface* Renderer_Software_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}