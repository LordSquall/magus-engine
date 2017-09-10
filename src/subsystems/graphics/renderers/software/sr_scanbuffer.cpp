#include "sr_scanbuffer.h"

namespace MagusEngine
{
	
	SR_Scanbuffer::SR_Scanbuffer()
	{

	}

	void SR_Scanbuffer::Initialise(SR_Framebuffer* frame)
	{
		_frame = frame;

		_buffer = new unsigned int[_frame->GetHeight() * 2];
	}

	void SR_Scanbuffer::Draw(int y, int min, int max)
	{
		_buffer[y * 2] = min;
		_buffer[y * 2 + 1] = max;
	}

	void SR_Scanbuffer::FillShape(int yMin, int yMax)
	{
		for (int j = yMin; j < yMax; j++)
		{
			int xMin = _buffer[j * 2];
			int xMax = _buffer[j * 2 + 1];

			for (int i = xMin; i < xMax; i++)
			{
				_frame->DrawPixel(i, j, 0.0f, 1.0f, 0.0f, 1.0f);
			}
		}
	}


	void SR_Scanbuffer::FillTriangle(Vertex v1, Vertex v2, Vertex v3)
	{
		Vertex minY = v1;
		Vertex midY = v2;
		Vertex maxY = v3;

		if (maxY.GetY() < midY.GetY())
		{
			Vertex temp = maxY;
			maxY = midY;
			midY = temp;
		}

		if (midY.GetY() < minY.GetY())
		{
			Vertex temp = midY;
			midY = minY;
			minY = temp;
		}

		if (maxY.GetY() < midY.GetY())
		{
			Vertex temp = maxY;
			maxY = midY;
			midY = temp;
		}

		float area = minY.TriangleArea(maxY, midY);
		int dir = area >= 0 ? 1 : 0;

		ScanConvertTriangle(minY, midY, maxY, dir);
		FillShape((int)minY.GetY(), (int)maxY.GetY());
	}


	void SR_Scanbuffer::ScanConvertTriangle(Vertex minYVert, Vertex midYVert, Vertex maxYVert, int side)
	{
		ScanConvertLine(minYVert, maxYVert, 0 + side);
		ScanConvertLine(minYVert, midYVert, 1 - side);
		ScanConvertLine(midYVert, maxYVert, 1 - side);
	}

	void SR_Scanbuffer::ScanConvertLine(Vertex minYVert, Vertex maxYVert, int side)
	{
		int yS = (int)minYVert.GetY();
		int yE = (int)maxYVert.GetY();
		int xS = (int)minYVert.GetX();
		int xE = (int)maxYVert.GetX();

		int yD = yE - yS;
		int xD = xE - xS;

		if (yD <= 0)
			return;

		float xStep = (float)xD / (float)yD;
		float cursorX = (float)xS;

		for (int i = yS; i < yE; i++)
		{
			_buffer[i * 2 + side] = (int)cursorX;
			cursorX += xStep;
		}
	}
}