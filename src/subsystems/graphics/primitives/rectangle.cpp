#include "rectangle.h"

#include "../../scenemanagement/visitor.h"

namespace MagusEngine
{
	Rectangle::Rectangle()
	{
		_x = 0.0f;
		_y = 0.0f;
		_width = 0.0f;
		_height = 0.0f;
	}

	Rectangle::Rectangle(float x, float y, float width, float height)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
	}

	/* Drawable Functions */
	void Rectangle::Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData)
	{
		/* default the drawable data */
		fillData->enabled = false;
		fillData->vertexstart = 0;
		fillData->vertexlength = 0;
		fillData->vertexhandle = 0;
		fillData->indexstart = 0;
		fillData->indexlength = 0;
		fillData->indexhandle = 0;

		/* Path variables for drawing calculations */
		unsigned int pointCnt = 4;

		/* Build Points */
		Vector4f points[] = { 
			{ _x,			_y			 , 0.0f, 1.0f},
			{ _x,			_y + _height , 0.0f, 1.0f},
			{ _x + _width,	_y + _height , 0.0f, 1.0f},
			{ _x + _width,	_y			 , 0.0f, 1.0f}
		};


		/* Build vertex buffer */
		vbuffer[0] = Vertex(Vector4f(_x, _y, 0.0f, 1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(), Vector2f(0.0f, 1.0f));
		vbuffer[1] = Vertex(Vector4f(_x, _y + _height, 0.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(), Vector2f(0.0f, 0.0f));
		vbuffer[2] = Vertex(Vector4f(_x + _width, _y, 0.0f, 1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(), Vector2f(1.0f, 1.0f));
		vbuffer[3] = Vertex(Vector4f(_x + _width, _y + _height, 0.0f, 1.0f), Vector4f(1.0f, 1.0f, 1.0f, 1.0f), Vector2f(), Vector2f(1.0f, 0.0f));
		
		/* Build indicies buffer */
		ibuffer[0] = 0;
		ibuffer[1] = 1;
		ibuffer[2] = 2;
		ibuffer[3] = 1;
		ibuffer[4] = 2;
		ibuffer[5] = 3;

		/* Calculate stroke for rectangle */

		int vertcounter = 4;
		int indexcounter = 6;
		for (int i = 0; i < pointCnt; i++)
		{
			bool closingPoint = (i == pointCnt - 1);

			Vector4f* ptA;
			Vector4f* ptB;
			Vector4f* ptC;

			/* If closing edge, use different points */
			if (closingPoint)
			{
				ptA = &points[i];
				ptB = &points[0];
				ptC = &points[1];
			}
			else
			{
				ptA = &points[i];
				ptB = &points[i + 1];
				ptC = &points[i + 2];
			}

			Vector2f cornerpos;
			Vector2f cornerneg;
			VG::CalculateCornerPoint(ptA, ptB, ptC, &cornerpos, &cornerneg);

			Vector2f deltapos = Vector2f(ptB->y - ptA->y, -(ptB->x - ptA->x));
			Vector2f deltaneg = Vector2f(-(ptB->y - ptA->y), ptB->x - ptA->x);

			deltapos.Normalise();
			deltaneg.Normalise();

			/* Segement vertices*/
			vbuffer[vertcounter    ] = Vertex(*ptA, Vector4f(1.0f, 0.0f, 0.0f, 1.0f), deltapos, Vector2f(0.0f, 1.0f));
			vbuffer[vertcounter + 1] = Vertex(*ptA, Vector4f(0.0f, 1.0f, 0.0f, 1.0f), deltaneg, Vector2f(0.0f, 0.0f));
			vbuffer[vertcounter + 2] = Vertex(*ptB, Vector4f(0.0f, 0.0f, 1.0f, 1.0f), deltapos, Vector2f(1.0f, 1.0f));
			vbuffer[vertcounter + 3] = Vertex(*ptB, Vector4f(1.0f, 1.0f, 1.0f, 1.0f), deltaneg, Vector2f(1.0f, 0.0f));

			/* Corner vertices */
			vbuffer[vertcounter + 4] = Vertex(*ptB, Vector4f(1.0f, 1.0f, 1.0f, 1.0f), cornerpos, Vector2f(1.0f, 0.0f));

			/* Segement indices */
			ibuffer[indexcounter    ] = (i * 5);
			ibuffer[indexcounter + 1] = (i * 5) + 1;
			ibuffer[indexcounter + 2] = (i * 5) + 2;
			ibuffer[indexcounter + 3] = (i * 5) + 1;
			ibuffer[indexcounter + 4] = (i * 5) + 2;
			ibuffer[indexcounter + 5] = (i * 5) + 3;

			/* Corner indices */
			ibuffer[indexcounter + 6] = (i * 5) + 2;
			ibuffer[indexcounter + 7] = (i * 5) + 3;
			ibuffer[indexcounter + 8] = (i * 5) + 4;

			if (closingPoint)
			{
				ibuffer[indexcounter + 9] = (i * 5) + 4;
				ibuffer[indexcounter + 10] = 0;
				ibuffer[indexcounter + 11] = 1;
			}
			else
			{
				ibuffer[indexcounter + 9] = (i * 5) + 3;
				ibuffer[indexcounter + 10] = (i * 5) + 4;
				ibuffer[indexcounter + 11] = (i * 5) + 5;
			}

			vertcounter += 5;
			indexcounter += 12;
		}

		/* Configure buffer data */
		fillData->enabled = true;
		fillData->vertexstart = 0;
		fillData->vertexlength = 4;
		fillData->vertexmax = 4;
		fillData->indexstart = 0;
		fillData->indexlength = 6;
		fillData->indexmax = 6;

		strokeData->enabled = true;
		strokeData->vertexstart = 4;
		strokeData->vertexlength = vertcounter;
		strokeData->vertexmax = vertcounter;
		strokeData->indexstart = 6;
		strokeData->indexlength = indexcounter;
		strokeData->indexmax = indexcounter;
	}
	
	void Rectangle::PreDraw(Visitor* visitor)
	{
		visitor->PreVisit(this);
	}

	void Rectangle::PostDraw(Visitor* visitor)
	{
		visitor->PostVisit(this);
	}

	/* Visitable Functions */
	void Rectangle::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
	}

	/* Getters */
	float Rectangle::GetX() { return _x; }
	float Rectangle::GetY() { return _y; }
	float Rectangle::GetWidth() { return _width; }
	float Rectangle::GetHeight() { return _height; }

	/* Setters */
	void Rectangle::SetX(float x) { _x = x; }
	void Rectangle::SetY(float y) { _y = y; }
	void Rectangle::SetWidth(float width) { _width = width; }
	void Rectangle::SetHeight(float height) { _height = height; }
}