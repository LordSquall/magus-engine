#include "renderer_windows_initialise_visitor.h"

#include "../../../scenemanagement/scenenode.h"
#include "../../graphic2d.h"
#include "../../graphic3d.h"


namespace MagusEngine
{
	Renderer_Windows_Initialise_Visitor::Renderer_Windows_Initialise_Visitor()
	{
		_lowLevelRenderer = 0;

		_buildCritical = false;
	}

	/* Visitor Functions */
	bool Renderer_Windows_Initialise_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources, Camera* camera, Matrix4f* projection2D, Matrix4f* projection3D)
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
		/* Software rendering only occurs on non-critical components */
		if (_buildCritical == false)
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

	void Renderer_Windows_Initialise_Visitor::PreVisit(Graphic3D* graphic3d) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Graphic3D* graphic3d)
	{	
		/* Software rendering only occurs on non-critical components */
		if (_buildCritical == false)
		{
			VBO_Structure vboData;

			/* Use the attached drawable to build the geometry data */
			Drawable* d = graphic3d->GetDrawable();

			/* Get renferences to GHandles of the graphics object */
			VBO_Structure* gHandle = graphic3d->GetDataHandle();

			d->Build(&_vertexBuildBuffer[0], &_indicesBuildBuffer[0], &vboData, NULL);

			/* Genearte fill vertex data for the low level renderer */
			gHandle->enabled = vboData.enabled;
			gHandle->vertexstart = vboData.vertexstart;
			gHandle->vertexlength = vboData.vertexlength;
			gHandle->vertexmax = vboData.vertexmax;
			gHandle->vertexhandle = _lowLevelRenderer->GenerateVertexBuffer(&_vertexBuildBuffer[0], gHandle);

			/* Genearte fill index data for the low level renderer */
			gHandle->indexstart = vboData.indexstart;
			gHandle->indexlength = vboData.indexlength;
			gHandle->indexmax = vboData.indexmax;
			gHandle->indexhandle = _lowLevelRenderer->GenerateIndicesBuffer(&_indicesBuildBuffer[0], gHandle);

		}
	}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Graphic3D* graphic3d) {}

	void Renderer_Windows_Initialise_Visitor::PreVisit(Model* model) {}
	void Renderer_Windows_Initialise_Visitor::Visit(Model* model) {}
	void Renderer_Windows_Initialise_Visitor::PostVisit(Model* model) {}

	/* Getters */
	Renderer_Interface* Renderer_Windows_Initialise_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}