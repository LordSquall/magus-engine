#ifndef _SR_SCANBUFFER_H_
#define _SR_SCANBUFFER_H_

/* System Includes */
#include <math.h>

/* Project Includes */
#include "sr_framebuffer.h"
#include "sr_edge.h"

#include "../../../resources/material.h"
#include "../../../math/vertex.h"

typedef char Byte;

namespace MagusEngine
{
	class SR_Scanbuffer
	{
	public:
		SR_Scanbuffer();

		void Initialise(SR_Framebuffer* frame);

		void FillTriangle(Vertex v1, Vertex v2, Vertex v3, Material* material);

		void ScanTriangle(Vertex minYVert, Vertex midYVert, Vertex maxYVert, bool side);

		void ScanEdge(SR_Varier* colorVarier, SR_Edge* e1, SR_Edge* e2, bool side);

		void DrawScanLine(SR_Varier* colorVarier, SR_Edge* left, SR_Edge* right, int j);

	private:
		SR_Framebuffer* _frame;

		Material* _currentMaterial;
	};
}

#endif