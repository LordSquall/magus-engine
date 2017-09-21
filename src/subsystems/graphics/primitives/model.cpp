#include "model.h"

#include "../../scenemanagement/visitor.h"

namespace MagusEngine
{
	Model::Model()
	{
		_mesh = NULL;
	}

	Model::Model(Mesh* mesh)
	{
		_mesh = mesh;
	}

	/* Drawable Functions */
	void Model::Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData)
	{
		/* default the drawable data */
		fillData->enabled = false;
		fillData->vertexstart = 0;
		fillData->vertexlength = 0;
		fillData->vertexhandle = 0;
		fillData->vertexmax = 0;
		fillData->indexstart = 0;
		fillData->indexlength = 0;
		fillData->indexhandle = 0;
		fillData->indexmax = 0;

		/* Populate the vertex buffer */
		for (int i = 0; i < _mesh->GetVertexCount(); i++)
		{
			vbuffer[i].SetX(_mesh->GetVertices()[i].GetX());
			vbuffer[i].SetY(_mesh->GetVertices()[i].GetY());
			vbuffer[i].SetZ(_mesh->GetVertices()[i].GetZ());
			vbuffer[i].SetW(1.0f);

			vbuffer[i].SetExtrude(0.0f, 0.0f);
			vbuffer[i].SetColor(0.0f, 0.0f, 0.0f, 0.0f);
			vbuffer[i].SetNormal(0.0f, 0.0f, 0.0f);

			printf("VERTEX: x:%.2f y:%.2f z:%.2f w:%.2f\n",
				vbuffer[i].GetX(),
				vbuffer[i].GetY(),
				vbuffer[i].GetZ(),
				vbuffer[i].GetW());
		}

		/* Populate the indices buffer */
		for (int i = 0; i < _mesh->GetIndicesCount(); i++)
		{
			ibuffer[i] = (_mesh->GetIndices()[i]);
		}

		/* Configure buffer data */
		fillData->enabled = true;
		fillData->vertexstart = 0;
		fillData->vertexlength = _mesh->GetVertexCount();
		fillData->vertexmax = _mesh->GetVertexCount();
		fillData->indexstart = 0;
		fillData->indexlength = _mesh->GetIndicesCount();
		fillData->indexmax = _mesh->GetIndicesCount();
	}
	
	void Model::PreDraw(Visitor* visitor)
	{
		visitor->PreVisit(this);
	}

	void Model::PostDraw(Visitor* visitor)
	{
		visitor->PostVisit(this);
	}

	/* Visitable Functions */
	void Model::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
	}

	/* Getters */
	Mesh* Model::GetMesh() { return _mesh; }
	
	/* Setters */
	void Model::SetMesh(Mesh* mesh) { _mesh = mesh; }
}