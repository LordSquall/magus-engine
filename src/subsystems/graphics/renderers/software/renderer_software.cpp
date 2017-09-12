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

	void Renderer_Software::DrawRectangle(int x, int y, int width, int height)
	{
		
	}

	void Renderer_Software::BeginScene(float red, float green, float blue, float alpha)
	{
		_framebuffer.Clear(red, green, blue, alpha);

		return;
	}
	
	void Renderer_Software::EndScene()
	{
		
		_debugBitmap.Save((BYTE*)_framebuffer.GetData(), 32, 24, "C:\\Temp\\image.bmp");
		return;
	}
	
	void Renderer_Software::CheckError()
	{
	}

	/* Data Loading API */
	unsigned int Renderer_Software::GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount)
	{
		return 0;
	}

	unsigned int Renderer_Software::DrawBuffers(unsigned int bufferHandle)
	{
		return 0;
	}

	void Renderer_Software::SetCurrentModelMatrix(Matrix4f* matrix)
	{
		return;
	}

	void Renderer_Software::SetMaterial(Material* material)
	{
		return;
	}

	/* Shader API */
	void Renderer_Software::CompileShaderObject(Shader* shader)
	{
		return;
	}

	void Renderer_Software::SetCurrentShader(Shader* shader)
	{
		return;
	}

	/* Texture API */
	void Renderer_Software::CreateTexture(Texture* texture)
	{

	}

	void Renderer_Software::SaveBitmap()
	{
		
	}
}