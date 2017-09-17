#include "path.h"

#include "../../scenemanagement/visitor.h"

#include "../../external/poly2tri/poly2tri.h"

namespace MagusEngine
{
	Path::Path(const char* pointString)
	{
		char input[10000];

		strcpy(input, pointString);

		char * pch;
		float x, y;
		pch = strtok(input, ",");
		while (pch != NULL)
		{

			pch = strtok(NULL, ",");

			if (strcmp(pch, "E") == 0)
				break;

			x = (float)atof(pch);

			pch = strtok(NULL, ",");
			y = (float)atof(pch);

			_points.push_back(new p2t::Point(x, y));
		}

	}

	/* Drawable Functions */
	void Path::Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData)
	{
		/* default the drawable data */
		fillData->enabled = false;
		fillData->vertexstart = 0;
		fillData->vertexlength = 0;
		fillData->vertexhandle = 0;
		fillData->indexstart = 0;
		fillData->indexlength = 0;
		fillData->indexhandle = 0;

		p2t::CDT poly2Tri(_points);

		poly2Tri.Triangulate();

		std::vector<p2t::Triangle*> triangles = poly2Tri.GetTriangles();

		for (unsigned int x = 0; x < triangles.size(); x++)
		{
			p2t::Triangle* tri = triangles.at(x);

			for (int y = 0; y < 3; y++)
			{
				vbuffer[(x * 3) + y] = Vertex(Vector4f((float)tri->GetPoint(y)->x, (float)tri->GetPoint(y)->y, 0.0f, 1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(), Vector2f(0.0f, 1.0f));

				ibuffer[(x * 3) + y] = (x * 3) + y;

			}
		}

		/* Configure buffer data */
		fillData->enabled = true;
		fillData->vertexstart = 0;
		fillData->vertexlength = triangles.size() * 3;
		fillData->vertexmax = triangles.size() * 3;
		fillData->indexstart = 0;
		fillData->indexlength = triangles.size() * 3;
		fillData->indexmax = triangles.size() * 3;

		strokeData->enabled = false;
		strokeData->vertexstart = 0;
		strokeData->vertexlength = 0;
		strokeData->vertexmax = 0;
		strokeData->indexstart = 0;
		strokeData->indexlength = 0;
		strokeData->indexmax = 0;
	}
	
	void Path::PreDraw(Visitor* visitor)
	{
		visitor->PreVisit(this);
	}

	void Path::PostDraw(Visitor* visitor)
	{
		visitor->PostVisit(this);
	}

	/* Visitable Functions */
	void Path::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
	}

	/* Getters */

	/* Setters */

}