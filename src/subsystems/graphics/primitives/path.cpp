#include "path.h"

#include "../../scenemanagement/visitor.h"

#include "../../external/poly2tri/poly2tri.h"

namespace MagusEngine
{
	Path::Path(const char* pointString)
	{
		char input[10000];

		strcpy_s(input, pointString);

		char * pch;
		float x, y;
		pch = strtok(input, ",");
		while (pch != NULL)
		{

			pch = strtok(NULL, ",");

			if (strcmp(pch, "E") == 0)
				break;

			x = atof(pch);

			pch = strtok(NULL, ",");
			y = atof(pch);

			_points.push_back(new p2t::Point(x, y));
		}

	}

	/* Drawable Functions */
	void Path::Build(Vertex* vbuffer, int* vbufferLength, unsigned int* ibuffer, int* ibufferLength)
	{
		p2t::CDT poly2Tri(_points);

		poly2Tri.Triangulate();

		std::vector<p2t::Triangle*> triangles = poly2Tri.GetTriangles();

		for (int x = 0; x < triangles.size(); x++)
		{
			p2t::Triangle* tri = triangles.at(x);

			for (int y = 0; y < 3; y++)
			{
				vbuffer[(x * 3) + y].SetX(tri->GetPoint(y)->x);
				vbuffer[(x * 3) + y].SetY(tri->GetPoint(y)->y);
				vbuffer[(x * 3) + y].SetZ(0.0f);
				vbuffer[(x * 3) + y].SetW(1.0f);

				vbuffer[(x * 3) + y].SetR(1.0f);
				vbuffer[(x * 3) + y].SetG(0.0f);
				vbuffer[(x * 3) + y].SetB(0.0f);
				vbuffer[(x * 3) + y].SetA(1.0f);

				vbuffer[(x * 3) + y].SetU(0.0f);
				vbuffer[(x * 3) + y].SetV(1.0f);

				*vbufferLength += 1;

				ibuffer[(x * 3) + y] = (x * 3) + y;

				*ibufferLength += 1;
			}
		}

		*vbufferLength = triangles.size() * 3;
		*ibufferLength = triangles.size() * 3;
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