#include "renderer_software_render_visitor.h"

#include "../../../scenemanagement/scenenode.h"
#include "../../graphic2d.h"
#include "../../primitives/text.h"

namespace MagusEngine
{
	Renderer_Software_Render_Visitor::Renderer_Software_Render_Visitor()
	{
		_lowLevelRenderer = 0;
		_matrixStackHead = 0;

		_cachedTexture = 0;
	}

	/* Visitor Functions */
	bool Renderer_Software_Render_Visitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources)
	{
		_lowLevelRenderer = lowlevelRenderer;
		_resources = resources;

		_renderCritical = false;

		/* Add a identify to matric to the top of the stack*/
		_matrixStack[_matrixStackHead] = Matrix4f();
		_matrixStackHead++;

		return true;
	}

	void Renderer_Software_Render_Visitor::PreVisit(SceneNode* sceneNode)
	{
		/* Build model Matrix */
		Matrix4f translation = Matrix4f();
		Matrix4f rotation = Matrix4f();
		Matrix4f scale = Matrix4f();
		Matrix4f model = Matrix4f();

		translation.BuildTranslation(sceneNode->GetPosition());
		rotation.BuildRotation(sceneNode->GetRotation());
		scale.BuildScale(sceneNode->GetScale());

		model = _matrixStack[_matrixStackHead - 1] * (scale * translation * rotation);
		_matrixStack[_matrixStackHead] = model;
		_matrixStackHead++;

		/* Set the current material settings in the low level renderer */
		if (sceneNode->GetMaterial() != NULL)
			_lowLevelRenderer->SetMaterial(sceneNode->GetMaterial());


		_renderCritical = sceneNode->IsCritical();
	}

	void Renderer_Software_Render_Visitor::Visit(SceneNode* sceneNode)
	{
		if (strcmp(sceneNode->GetName(), "testnode") == 0)
		{
			sceneNode->SetRotation(sceneNode->GetRotation()->x + 1.0f, 0.0f, 0.0f);
		}
	}
	void Renderer_Software_Render_Visitor::PostVisit(SceneNode* sceneNode)
	{
		if (sceneNode->GetMaterial() != NULL)
			_lowLevelRenderer->SetMaterial(sceneNode->GetMaterial());

		_matrixStackHead--;
	}

	void Renderer_Software_Render_Visitor::PreVisit(Component* component) {}
	void Renderer_Software_Render_Visitor::Visit(Component* component) { }
	void Renderer_Software_Render_Visitor::PostVisit(Component* component) {}

	void Renderer_Software_Render_Visitor::PreVisit(Graphic2D* graphic2D)
	{
		_lowLevelRenderer->SetCurrentModelMatrix(&_matrixStack[_matrixStackHead - 1]);
	}

	void Renderer_Software_Render_Visitor::Visit(Graphic2D* graphic2D)
	{
		if(_renderCritical)
		{
			/* Check incase update is required */
			if (graphic2D->updateRequired == true)
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
				fillGHandle->vertexhandle = _lowLevelRenderer->UpdateVertexBuffer(graphic2D->GetFillDataHandle(), &_vertexBuildBuffer[0], fillData.vertexstart, fillData.vertexlength);

				/* Genearte fill index data for the low level renderer */
				fillGHandle->indexstart = fillData.indexstart;
				fillGHandle->indexlength = fillData.indexlength;
				fillGHandle->indexhandle = _lowLevelRenderer->UpdateIndicesBuffer(graphic2D->GetFillDataHandle(), &_indicesBuildBuffer[0], fillData.indexstart, fillData.indexlength);

				/* Genearte stroke vertex data for the low level renderer */
				strokeGHandle->enabled = strokeData.enabled;
				strokeGHandle->vertexstart = strokeData.vertexstart;
				strokeGHandle->vertexlength = strokeData.vertexlength;
				strokeGHandle->vertexhandle = _lowLevelRenderer->UpdateVertexBuffer(graphic2D->GetStrokeDataHandle(), &_vertexBuildBuffer[0], strokeData.vertexstart, strokeData.vertexlength);

				/* Genearte stroke index data for the low level renderer */
				strokeGHandle->indexstart = strokeData.indexstart;
				strokeGHandle->indexlength = strokeData.indexlength;
				strokeGHandle->indexhandle = _lowLevelRenderer->UpdateIndicesBuffer(graphic2D->GetStrokeDataHandle(), &_indicesBuildBuffer[0], strokeData.indexstart, strokeData.indexlength);

				graphic2D->updateRequired = false;
			}

			/* Draw fill data */
			if (graphic2D->GetFillDataHandle()->enabled == true)
				if (_lowLevelRenderer->GetMaterial()->GetEnabledFill())
					_lowLevelRenderer->DrawBuffers(graphic2D->GetFillDataHandle(), RenderDrawCallType::FILL_2D);

			/* Draw stroke data */
			if (graphic2D->GetStrokeDataHandle()->enabled == true)
				if (_lowLevelRenderer->GetMaterial()->GetEnabledStroke())
					_lowLevelRenderer->DrawBuffers(graphic2D->GetStrokeDataHandle(), RenderDrawCallType::STROKE_2D);
		}
	}

	void Renderer_Software_Render_Visitor::PostVisit(Graphic2D* graphic2D) {}

	void Renderer_Software_Render_Visitor::PreVisit(Rectangle* rectangle) {}
	void Renderer_Software_Render_Visitor::Visit(Rectangle* rectangle) {}
	void Renderer_Software_Render_Visitor::PostVisit(Rectangle* rectangle) {}

	void Renderer_Software_Render_Visitor::PreVisit(Line* line) {}
	void Renderer_Software_Render_Visitor::Visit(Line* line) {}
	void Renderer_Software_Render_Visitor::PostVisit(Line* line) {}

	void Renderer_Software_Render_Visitor::PreVisit(Text* text) 
	{
		if (_renderCritical == true)
		{
			/* cache the current texture */
			_cachedTexture = _lowLevelRenderer->GetTexture();

			/* set the texture to the font texture */
			_lowLevelRenderer->SetTexture(text->GetFont()->GetTexture());
		}
	}

	void Renderer_Software_Render_Visitor::Visit(Text* text) {}
	void Renderer_Software_Render_Visitor::PostVisit(Text* text)
	{
		if (_renderCritical == true)
		{
			/* set the renderer back to the cached texture */
			_lowLevelRenderer->SetTexture(_cachedTexture);
		}
	}

	void Renderer_Software_Render_Visitor::PreVisit(Ellipse* ellipse) {}
	void Renderer_Software_Render_Visitor::Visit(Ellipse* ellipse) {}
	void Renderer_Software_Render_Visitor::PostVisit(Ellipse* ellipse) {}

	void Renderer_Software_Render_Visitor::PreVisit(Path* path) {}
	void Renderer_Software_Render_Visitor::Visit(Path* path) {}
	void Renderer_Software_Render_Visitor::PostVisit(Path* path) {}

	/* Getters */
	Renderer_Interface* Renderer_Software_Render_Visitor::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

}