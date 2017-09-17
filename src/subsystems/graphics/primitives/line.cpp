#include "line.h"

#include "../../scenemanagement/visitor.h"

namespace MagusEngine
{
	Line::Line()
	{
		_x1 = 0.0f;
		_y1 = 0.0f;
		_x2 = 0.0f;
		_y2 = 0.0f;
	}

	Line::Line(float x1, float y1, float x2, float y2)
	{
		_x1 = x1;
		_y1 = y1;
		_x2 = x2;
		_y2 = y2;
	}

	/* Drawable Functions */
	void Line::Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData)
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
			{ _x1, _y1, 0.0f, 1.0f },
			{ _x2, _y2, 0.0f, 1.0f }
		};

		/* calculate normal */
		Vector2f deltapos = Vector2f(_y2 - _y1, -(_x2 - _x1));
		Vector2f deltaneg = Vector2f(-(_y2 - _y1), _x2 - _x1);

		deltapos.Normalise();
		deltaneg.Normalise();
		
		/* Segement vertices*/
		vbuffer[0] = Vertex(points[0], Vector4f(1.0f, 0.0f, 0.0f, 1.0f), deltapos, Vector2f(0.0f, 1.0f));
		vbuffer[1] = Vertex(points[0], Vector4f(0.0f, 1.0f, 0.0f, 1.0f), deltaneg, Vector2f(0.0f, 0.0f));
		vbuffer[2] = Vertex(points[1], Vector4f(0.0f, 0.0f, 1.0f, 1.0f), deltapos, Vector2f(1.0f, 1.0f));
		vbuffer[3] = Vertex(points[1], Vector4f(1.0f, 1.0f, 1.0f, 1.0f), deltaneg, Vector2f(1.0f, 0.0f));

		/* Build indicies buffer */
		ibuffer[0] = 0;
		ibuffer[1] = 1;
		ibuffer[2] = 2;
		ibuffer[3] = 1;
		ibuffer[4] = 2;
		ibuffer[5] = 3;

		/* Set buffer lengths */
		fillData->enabled = false;
		fillData->vertexstart = 0;
		fillData->vertexlength = 0;
		fillData->vertexmax = 0;
		fillData->indexstart = 0;
		fillData->indexlength = 0;
		fillData->indexmax = 0;

		strokeData->enabled = true;
		strokeData->vertexstart = 0;
		strokeData->vertexlength = 4;
		strokeData->vertexmax = 4;
		strokeData->indexstart = 0;
		strokeData->indexlength = 6;
		strokeData->indexmax = 6;
	}

	void Line::PreDraw(Visitor* visitor)
	{
		visitor->PreVisit(this);
	}

	void Line::PostDraw(Visitor* visitor)
	{
		visitor->PostVisit(this);
	}

	/* Visitable Functions */
	void Line::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
	}

	/* Getters */
	float Line::GetX1() { return _x1; }
	float Line::GetY1() { return _y1; }
	float Line::GetX2() { return _x2; }
	float Line::GetY2() { return _y2; }
	float Line::GetWidth() { return _width; }

	/* Setters */
	void Line::SetX1(float x) { _x1 = x; }
	void Line::SetY1(float y) { _y1 = y; }
	void Line::SetX2(float x) { _x2 = x; }
	void Line::SetY2(float y) { _y2 = y; }
	void Line::SetWidth(float width) { _width = width; }

}