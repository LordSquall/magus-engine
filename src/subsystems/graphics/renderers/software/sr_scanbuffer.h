#ifndef _SR_SCANBUFFER_H_
#define _SR_SCANBUFFER_H_

/* Project Includes */
#include "sr_framebuffer.h"
#include "sr_vertex.h"

typedef char Byte;

namespace MagusEngine
{
	class SR_Scanbuffer
	{
	public:
		SR_Scanbuffer();

		void Initialise(SR_Framebuffer* frame);

		void Draw(int y, int min, int max);

		void FillShape(int yMin, int yMax);

		void FillTriangle(SR_Vertex v1, SR_Vertex v2, SR_Vertex v3);

		void ScanConvertLine(SR_Vertex minYVert, SR_Vertex maxYVert, int side);

		void ScanConvertTriangle(SR_Vertex minYVert, SR_Vertex midYVert, SR_Vertex maxYVert, int side);


	private:
		SR_Framebuffer* _frame;

		unsigned int* _buffer;
	};
}

#endif