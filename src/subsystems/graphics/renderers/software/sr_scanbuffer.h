#ifndef _SR_SCANBUFFER_H_
#define _SR_SCANBUFFER_H_

/* Project Includes */
#include "sr_framebuffer.h"

#include "../../../math/vertex.h"

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

		void FillTriangle(Vertex v1, Vertex v2, Vertex v3);

		void ScanConvertLine(Vertex minYVert, Vertex maxYVert, int side);

		void ScanConvertTriangle(Vertex minYVert, Vertex midYVert, Vertex maxYVert, int side);


	private:
		SR_Framebuffer* _frame;

		unsigned int* _buffer;
	};
}

#endif