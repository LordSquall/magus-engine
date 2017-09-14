#ifndef _MESH_H_
#define _MESH_H_

/* System Includes */
#include <string>

/* Local Project Include */
#include "../math/vertex.h"

typedef char Byte;

namespace MagusEngine
{
	class Mesh
	{
	public:
		Mesh();

		Mesh(const char* name);

		void Initialise(unsigned int vertexCount, unsigned int indicesCount);

		/* Getters */
		char* GetName();
		Vertex* GetVertices();
		unsigned int* GetIndices();

		/* Setters */
		void SetName(const char* name);

	private:
		char _name[25];

		Vertex* _vertices;
		unsigned int _verticesCount;

		unsigned int* _indices;
		unsigned int _indicesCount;
	};
}

#endif