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
		Vertex minYVert = Vertex(100, 100);
		Vertex midYVert = Vertex(150, 200);
		Vertex maxYVert = Vertex(80, 300);

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

	/* Data Loading API */
	unsigned int Renderer_Software::GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount)
	{
		return 0;
	}

	unsigned int Renderer_Software::DrawBuffers(unsigned int bufferHandle)
	{
		return 0;
	}

	/* Shader API */
	void Renderer_Software::CompileShaderObject(Shader* shader)
	{
		return;
	}

	unsigned int Renderer_Software::CreateVertexShader()
	{
		return 0;
	}

	unsigned int Renderer_Software::CreateFragmentShader()
	{
		return 0;
	}

	void Renderer_Software::SetShaderSource(unsigned int shaderHandle, char* source)
	{
	}

	void Renderer_Software::CompileShader(unsigned int shaderHandle)
	{
	}

	unsigned int Renderer_Software::CreateShaderProgram()
	{
		return 0;
	}

	void Renderer_Software::AttachShader(unsigned int programHandle, unsigned int shaderHandle)
	{
	}

	void Renderer_Software::BindAttribute(unsigned int programHandle, unsigned int index, const char* name)
	{
	}

	void Renderer_Software::LinkShaderProgram(unsigned int programHandle)
	{
	}

	void Renderer_Software::GetShaderLogLength(unsigned int programHandle, int* length)
	{

	}

	void Renderer_Software::GetShaderInfoLog(unsigned int programHandle, int size, char* logBuffer)
	{

	}

	void Renderer_Software::GetShaderProgramInfoLog(unsigned int programHandle, int size, char* logBuffer)
	{

	}

	void Renderer_Software::SaveBitmap()
	{
		
	}
}