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
		_framebuffer.Clear(red, green, blue, alpha);

		_framebuffer.DrawPixel(100, 100, 0.0, 0.0, 1.0, 1.0);
		_framebuffer.DrawPixel(101, 100, 0.0, 0.0, 1.0, 1.0);
		_framebuffer.DrawPixel(102, 100, 0.0, 0.0, 1.0, 1.0);
		_framebuffer.DrawPixel(103, 100, 0.0, 0.0, 1.0, 1.0);
		_framebuffer.DrawPixel(104, 100, 0.0, 0.0, 1.0, 1.0);
		_framebuffer.DrawPixel(105, 100, 0.0, 0.0, 1.0, 1.0);
		_framebuffer.DrawPixel(106, 100, 0.0, 0.0, 1.0, 1.0);
		_framebuffer.DrawPixel(107, 100, 0.0, 0.0, 1.0, 1.0);

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