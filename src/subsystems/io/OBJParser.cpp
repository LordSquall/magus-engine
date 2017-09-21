#include "OBJParser.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../external/tiny_obj_loader/tiny_obj_loader.h"

#include "../resources/resources.h"

namespace MagusEngine
{
	Mesh* OBJParser::ParseOBJFile(const char* filename, const char* name, Resources* resources)
	{
		Mesh* newMesh = new Mesh(name);
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename);

		if (result == false)
		{
			LOGERROR("Unable to load OBJ file: %s\n", err.c_str());
			return NULL;
		}

		/* Loop over shapes */
		for (size_t s = 0; s < shapes.size(); s++) {

			/* Get the current shape */
			tinyobj::shape_t* shape = &shapes[s];

			/* Get the number of faces */
			int faceCount = shape->mesh.num_face_vertices.size();

			size_t indexOffset = 0;


			/* Initialise mesh data - only 1 shape currently supported */
			newMesh->Initialise(faceCount * 3, faceCount * 3);

			int vertCounter = 0;

			/* Process each face */
			for (size_t f = 0; f < faceCount; f++) {
				
				/* Get the number of vertices in the next face */
				int faceVertCount = shape->mesh.num_face_vertices[f];
				
				/* Make sure the face is triangular */
				if (faceVertCount != 3)
				{
					LOGERROR("OBJ Parser does not support non triangluar faces");
					return NULL;
				}


				Vertex* vertex = &newMesh->GetVertices()[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < faceVertCount; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];

					/* Vertices */
					newMesh->GetVertices()[vertCounter].SetPosition(
						attrib.vertices[3 * idx.vertex_index + 0],
						attrib.vertices[3 * idx.vertex_index + 1],
						attrib.vertices[3 * idx.vertex_index + 2],
						1.0f);

					newMesh->GetVertices()[vertCounter].SetNormal(
						attrib.normals[3 * idx.normal_index + 0],
						attrib.normals[3 * idx.normal_index + 1],
						attrib.normals[3 * idx.normal_index + 2]);

					newMesh->GetVertices()[vertCounter].SetUV(
						attrib.texcoords[idx.texcoord_index + 0],
						attrib.texcoords[idx.texcoord_index + 1]);

					newMesh->GetVertices()[vertCounter].SetColor(1.0f, 0.0f, 0.0f, 1.0f);
					newMesh->GetVertices()[vertCounter].SetExtrude(0.0f, 0.0f);

					newMesh->GetIndices()[vertCounter] = vertCounter;

					printf("VERTEX: x:%.2f y:%.2f z:%.2f\n",
						newMesh->GetVertices()[vertCounter].GetX(),
						newMesh->GetVertices()[vertCounter].GetY(),
						newMesh->GetVertices()[vertCounter].GetZ());

					vertCounter++;
				}
				indexOffset += faceVertCount;
			}
		}

		return newMesh;
	}
}