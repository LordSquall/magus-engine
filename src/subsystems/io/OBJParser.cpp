#include "OBJParser.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../external/tiny_obj_loader/tiny_obj_loader.h"

#include "../resources/resources.h"

namespace MagusEngine
{
	Mesh* OBJParser::ParseOBJFile(const char* filename, const char* name, Resources* resources)
	{
		Mesh* newMesh = new Mesh(name);

		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector<Vector3f> temp_vertices;
		std::vector<Vector2f> temp_uvs;
		std::vector<Vector3f> temp_normals;
		
		FILE* file;
		fopen_s(&file, filename, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			return false;
		}

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));

		while (res != EOF)
		{

			if (strcmp(lineHeader, "v") == 0) {
				Vector3f vertex;
				fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				Vector2f uv;
				fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				Vector3f normal;
				fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		}



		newMesh->Initialise(temp_vertices.size(), vertexIndices.size() * 3);

		/* Copy vertex data across to mesh */
		Vertex* vertices = newMesh->GetVertices();

		for (unsigned int i = 0; i < temp_vertices.size(); i++)
		{
			vertices->SetPosition(temp_vertices.at(i).x, temp_vertices.at(i).y, temp_vertices.at(i).z, 1.0f);
			vertices->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
			vertices->SetUV(temp_uvs.at(i).x, temp_uvs.at(i).y);
		}

		/* Copy indicies data across to mesh */
		unsigned int* indicies = newMesh->GetIndices();

		for (unsigned int i = 0; i < vertexIndices.size(); i += 3)
		{
			//indicies = vertexIndices
			//vertices->SetPosition(temp_vertices.at(i).x, temp_vertices.at(i).y, temp_vertices.at(i).z, 1.0f);
			//vertices->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
			//vertices->SetUV(0.0f, 0.0f);
		}

		return newMesh;
	}
}