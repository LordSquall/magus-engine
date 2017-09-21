#include "mesh.h"

namespace MagusEngine
{
	Mesh::Mesh()
	{
		strcpy(_name, "unknown");
	}

	Mesh::Mesh(const char* name)
	{
		/* Copy the name */
		strcpy(_name, name);
	}


	void Mesh::Initialise(unsigned int vertexCount, unsigned int indicesCount)
	{
		_vertices = (Vertex*)malloc(sizeof(Vertex)*vertexCount);
		_verticesCount = vertexCount;

		_indices = (unsigned int*)malloc(sizeof(unsigned int)*indicesCount);
		_indicesCount = indicesCount;
	}

	/* Getters */
	char* Mesh::GetName() { return _name; }
	Vertex* Mesh::GetVertices() { return _vertices; }
	unsigned int Mesh::GetVertexCount() { return _verticesCount; };
	unsigned int* Mesh::GetIndices() { return _indices; }
	unsigned int Mesh::GetIndicesCount() { return _indicesCount; }

	/* Setters */
	void Mesh::SetName(const char* name) { strcmp(_name, name); }
}