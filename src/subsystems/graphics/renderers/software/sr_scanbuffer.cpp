#include "sr_scanbuffer.h"

namespace MagusEngine
{
	
	SR_Scanbuffer::SR_Scanbuffer()
	{

	}

	void SR_Scanbuffer::Initialise(int screenWidth, int screenHeight, SR_Framebuffer* frame)
	{
		_frame = frame;

		_screenWidth = (float)screenWidth;
		_screenHeight = (float)screenHeight;
	}

	void SR_Scanbuffer::DrawTriangle(Vertex v1, Vertex v2, Vertex v3, Material* material, Texture* texture)
	{

		_verticesClipList[0] = v1;
		_verticesClipList[1] = v2;
		_verticesClipList[2] = v3;

		_verticesClipListCount = 3;
		_auxillaryClipListCount = 0;
		
		if(ClipPolygonAxis(_verticesClipList, &_verticesClipListCount, _auxillaryClipList, &_auxillaryClipListCount, 0) &&
			ClipPolygonAxis(_verticesClipList, &_verticesClipListCount, _auxillaryClipList, &_auxillaryClipListCount, 1) &&
			ClipPolygonAxis(_verticesClipList, &_verticesClipListCount, _auxillaryClipList, &_auxillaryClipListCount, 2))
		{
			Vertex initVert = _verticesClipList[0];

			for(int i = 1; i < _verticesClipListCount - 1; i++)
			{
				FillTriangle(initVert, _verticesClipList[i], _verticesClipList[i+1], material,  texture);
			}
		}
	}
	
	bool SR_Scanbuffer::ClipPolygonAxis(Vertex* vertices, int* vertexCount, Vertex* auxillary, int* auxillaryCnt,  int componentIndex)
	{
		int result = 0;
		result = ClipPolygonComponent(vertices, vertexCount, componentIndex, 1.0f, auxillary, auxillaryCnt);

		if(result == 0)
		{
			return false;
		}

		result = ClipPolygonComponent(auxillary, vertexCount, componentIndex, -1.0f, vertices, auxillaryCnt);

		if(result == 0)
			return false;

		return true;

	}

	int SR_Scanbuffer::ClipPolygonComponent(Vertex* vertices, int* vertexCnt, int componentIndex, float componentFactor, Vertex* result, int* resultCnt)
	{
		int res = 0;
		Vertex previousVertex = vertices[*vertexCnt-1];
		float previousComponent = previousVertex.GetIndex(componentIndex) * componentFactor;
		bool previousInside = previousComponent <= previousVertex.GetPosition()->w;

		for(int i = 0; i < *vertexCnt; i++)
		{
			Vertex currentVertex = vertices[i];
			float currentComponent = currentVertex.GetIndex(componentIndex) * componentFactor;
			bool currentInside = currentComponent <= currentVertex.GetPosition()->w;

			if(currentInside ^ previousInside)
			{
				float lerpAmt  = (previousVertex.GetPosition()->w - previousComponent) / ((previousVertex.GetPosition()->w - previousComponent) - (currentVertex.GetPosition()->w - currentComponent));

				previousVertex.Lerp(currentVertex, lerpAmt);
			}

			if(currentInside)
			{
				result[*resultCnt] = currentVertex; 
				(*resultCnt)++;
				res++;
			}

			previousVertex = currentVertex;
			previousComponent = currentComponent;
			previousInside = currentInside;
		}

		return res;
	}

	void SR_Scanbuffer::FillTriangle(Vertex v1, Vertex v2, Vertex v3, Material* material, Texture* texture)
	{
		_currentMaterial = material;
		_currentTexture = texture;

		/* Convert vertices to screen space */
		Matrix4f screenSpace;
		screenSpace.BuildScreenSpaceTransform(_screenWidth / 2.0f, _screenHeight / 2.0f);
		Vertex minY = v1.Transform(screenSpace).PrespectiveDivide();
		Vertex midY = v2.Transform(screenSpace).PrespectiveDivide();
		Vertex maxY = v3.Transform(screenSpace).PrespectiveDivide();

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

		ScanTriangle(minY, midY, maxY, minY.TriangleAreaTimesTwo(maxY, midY) >= 0.0f);

	}

	void SR_Scanbuffer::ScanTriangle(Vertex minYVert, Vertex midYVert, Vertex maxYVert, bool side)
	{
		SR_Varier colorVarier = SR_Varier(&minYVert, &midYVert, &maxYVert);

		SR_Edge topToBottom =		SR_Edge(colorVarier, &minYVert, &maxYVert, 0);
		SR_Edge topToMiddle =		SR_Edge(colorVarier, &minYVert, &midYVert, 0);
		SR_Edge middleToBottom =	SR_Edge(colorVarier, &midYVert, &maxYVert, 1);


		ScanEdge(&colorVarier, &topToBottom, &topToMiddle, side);
		ScanEdge(&colorVarier, &topToBottom, &middleToBottom, side);
	}


	void SR_Scanbuffer::ScanEdge(SR_Varier* colorVarier, SR_Edge* e1, SR_Edge* e2, bool side)
	{
		SR_Edge* left = e1;
		SR_Edge* right = e2;

		if (side)
		{
			SR_Edge* temp = left;
			left = right;
			right = temp;
		}

		int yStart = (int)e2->GetYStart();
		int yEnd = (int)e2->GetYEnd();
		for (int x = yStart; x < yEnd; x++)
		{
			DrawScanLine(colorVarier, left, right, x);
			left->Step();
			right->Step();
		}
	}

	void SR_Scanbuffer::DrawScanLine(SR_Varier* colorVarier, SR_Edge* left, SR_Edge* right, int j)
	{
		int xMin = (int)ceil(left->GetX());
		int xMax = (int)ceil(right->GetX());
		float xPrestep = xMin - left->GetX();

		Vector4f color = left->GetColor() + ((*colorVarier->GetColorXStep()) * xPrestep);
		Vector2f uv = left->GetUV() + ((*colorVarier->GetUVXStep()) * xPrestep);


		for (int i = xMin; i < xMax; i++)
		{
			if (_currentTexture != NULL)
			{
				int srcX = (int)(uv.x * (_currentTexture->GetWidth() - 1) + 0.5f);
				int srcY = (int)(uv.y * (_currentTexture->GetHeight() - 1) + 0.5f);

				_frame->CopyPixel(i, j, (float)srcX, (float)srcY, _currentTexture);
				uv = uv + (*colorVarier->GetUVXStep());
			}
			else if (_currentMaterial->GetTexture() != NULL)
			{
				Texture* texture = _currentMaterial->GetTexture();

				int srcX = (int)(uv.x * (texture->GetWidth() - 1) + 0.5f);
				int srcY = (int)(uv.y * (texture->GetHeight() - 1) + 0.5f);

				_frame->CopyPixel(i, j, (float)srcX, (float)srcY, texture);
				uv = uv + (*colorVarier->GetUVXStep());
			} 
			else if (_currentMaterial->GetColor1() != NULL)
			{

				Color* color = _currentMaterial->GetColor1();

				_frame->DrawPixel(i, j, color->GetR(), color->GetG(), color->GetB(), color->GetA());
			}
			else
			{

				_frame->DrawPixel(i, j, color.x, color.y, color.z, 1.0f);
				color = color + (*colorVarier->GetColorXStep());
			}
		
		}
	}
}