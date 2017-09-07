#include "renderer_software.h"

namespace MagusEngine
{
	Renderer_Software::Renderer_Software()
	{

	}

	bool Renderer_Software::InitialiseExtensions()
	{
		return true;
	}

	bool Renderer_Software::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		/* Set class variables */
		_screenSizeWidth = screenWidth;
		_screenSizeHeight = screenHeight;
		_screenPixelDepth = screenDepth;

		/* Allocate data for front buffer */
		_framebuffer.Initialise(screenWidth, screenHeight, screenDepth);

		/* Initialise debug bitmap */
		_debugBitmap.Initialise(screenWidth, screenHeight);

		/* Initialise the scane buffer */
		_scanbuffer.Initialise(&_framebuffer);

		return true;
	}
	
	void Renderer_Software::Shutdown()
	{
	}

	void Renderer_Software::CompileShader()
	{

	}

	void Renderer_Software::DrawRectangle(int x, int y, int width, int height)
	{
		
	}

	void Renderer_Software::BeginScene(float red, float green, float blue, float alpha)
	{
		SR_Vertex minYVert = SR_Vertex(100, 100);
		SR_Vertex midYVert = SR_Vertex(150, 200);
		SR_Vertex maxYVert = SR_Vertex(80, 300);

		_framebuffer.Clear(red, green, blue, alpha);

		_scanbuffer.FillTriangle(minYVert, midYVert, maxYVert);
		
		_debugBitmap.Save((BYTE*)_framebuffer.GetData(), 32, 24, "C:\\Temp\\image.bmp");
		return;
	}


	void Renderer_Software::EndScene()
	{
		
		return;
	}
	
	
	void Renderer_Software::CheckError()
	{
	}


	void Renderer_Software::SaveBitmap()
	{
		
	}
}