#ifndef _RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_

/* System Include */

/* Local Project Includes */
#include "../../math/vertex.h"

namespace MagusEngine
{
	class Renderer_Interface
	{
	public:
		virtual bool Initialise(void*, int, int, float, float, bool) = 0;
		virtual bool InitialiseExtensions() = 0;

		virtual void Shutdown() = 0;

		virtual void BeginScene(float, float, float, float) = 0;
		virtual void EndScene() = 0;

		virtual void CheckError() = 0;

		virtual void DrawRectangle(int x, int y, int width, int height) = 0;

		/* Data Loading API*/
		virtual unsigned int GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount) = 0;
		virtual unsigned int DrawBuffers(unsigned int bufferHandle) = 0;

		/* Shader API */
		virtual unsigned int CreateVertexShader() = 0;
		virtual unsigned int CreateFragmentShader() = 0;
		virtual void SetShaderSource(unsigned int shaderHandle, const char** source) = 0;
		virtual void CompileShader(unsigned int shaderHandle) = 0;
		virtual unsigned int CreateShaderProgram() = 0;
		virtual void AttachShader(unsigned int programHandle, unsigned int shaderHandle) = 0;
		virtual void BindAttribute(unsigned int programHandle, unsigned int index, const char* name) = 0;
		virtual void LinkShaderProgram(unsigned int programHandle) = 0;
		virtual void GetShaderLogLength(unsigned int programHandle, int* length) = 0;
		virtual void GetShaderInfoLog(unsigned int programHandle, int size, char* logBuffer) = 0;
		virtual void GetShaderProgramInfoLog(unsigned int programHandle, int size, char* logBuffer) = 0;


	public:
		void* _windowSystemHandle;
	};
}

#endif