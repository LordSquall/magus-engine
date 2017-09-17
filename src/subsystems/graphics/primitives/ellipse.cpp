#include "ellipse.h"

#include "../../scenemanagement/visitor.h"

namespace MagusEngine
{
	Ellipse::Ellipse()
	{
		_x = 0.0f;
		_y = 0.0f;
		_rx = 0.0f;
		_ry = 0.0f;
	}

	Ellipse::Ellipse(float x, float y, float rx, float ry)
	{
		_x = x;
		_y = y;
		_rx = rx;
		_ry = ry;
	}

	/* Drawable Functions */
	void Ellipse::Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData)
	{
		/* default the drawable data */
		fillData->enabled = false;
		fillData->vertexstart = 0;
		fillData->vertexlength = 0;
		fillData->vertexhandle = 0;
		fillData->indexstart = 0;
		fillData->indexlength = 0;
		fillData->indexhandle = 0;



		/* Build vertex buffer */
		
		/* Draw Initial point */
		
		//vbuffer[0].SetX(_x);
		//vbuffer[0].SetY(_y);
		//vbuffer[0].SetZ(0.0f);
		//vbuffer[0].SetW(0.0f); 

		//vbuffer[0].SetR(1.0f);
		//vbuffer[0].SetG(0.0f);
		//vbuffer[0].SetB(0.0f);
		//vbuffer[0].SetA(1.0f);

		//vbuffer[0].SetU(0.0f);
		//vbuffer[0].SetV(1.0f);

		//vbuffer[1].SetX(_x);
		//vbuffer[1].SetY(_y +  _height);
		//vbuffer[1].SetZ(0.0f);
		//vbuffer[1].SetW(1.0f);

		//vbuffer[1].SetR(0.0f);
		//vbuffer[1].SetG(1.0f);
		//vbuffer[1].SetB(0.0f);
		//vbuffer[1].SetA(1.0f);

		//vbuffer[1].SetU(0.0f);
		//vbuffer[1].SetV(0.0f);

		//vbuffer[2].SetX(_x + _width);
		//vbuffer[2].SetY(_y);
		//vbuffer[2].SetZ(0.0f);
		//vbuffer[2].SetW(1.0f);

		//vbuffer[2].SetR(0.0f);
		//vbuffer[2].SetG(0.0f);
		//vbuffer[2].SetB(1.0f);
		//vbuffer[2].SetA(1.0f);

		//vbuffer[2].SetU(1.0f);
		//vbuffer[2].SetV(1.0f);

		//vbuffer[3].SetX(_x + _width);
		//vbuffer[3].SetY(_y + _height);
		//vbuffer[3].SetZ(0.0f);
		//vbuffer[3].SetW(1.0f);
		//
		//vbuffer[3].SetR(1.0f);
		//vbuffer[3].SetG(0.0f);
		//vbuffer[3].SetB(1.0f);
		//vbuffer[3].SetA(1.0f);

		//vbuffer[3].SetU(1.0f);
		//vbuffer[3].SetV(0.0f);

		///* Build indicies buffer */
		//ibuffer[0] = 0;
		//ibuffer[1] = 1;
		//ibuffer[2] = 2;
		//ibuffer[3] = 1;
		//ibuffer[4] = 2;
		//ibuffer[5] = 3;

		///* Set buffer lengths */
		//*vbufferLength = 0;
		//*ibufferLength = 0;
	}
	
	void Ellipse::PreDraw(Visitor* visitor)
	{
		visitor->PreVisit(this);
	}

	void Ellipse::PostDraw(Visitor* visitor)
	{
		visitor->PostVisit(this);
	}

	/* Visitable Functions */
	void Ellipse::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
	}

	/* Getters */
	float Ellipse::GetX() { return _x; }
	float Ellipse::GetY() { return _y; }
	float Ellipse::GetRX() { return _rx; }
	float Ellipse::GetRY() { return _ry; }

	/* Setters */
	void Ellipse::SetX(float x) { _x = x; }
	void Ellipse::SetY(float y) { _y = y; }
	void Ellipse::SetRX(float rx) { _rx = rx; }
	void Ellipse::SetRY(float ry) { _ry = ry; }
}