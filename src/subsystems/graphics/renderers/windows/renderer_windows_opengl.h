#ifndef _OPENGLWINDOWS_CLASS_H_
#define _OPENGLWINDOWS_CLASS_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../renderer_interface.h"

#include "../../../math/matrix.h"
#include "../../../resources/shader.h"
#include "../../../resources/texture.h"

#pragma comment(lib, "opengl32.lib")

namespace MagusEngine
{
	class Renderer_Windows_OpenGL : public Renderer_Interface
	{
	public:
		Renderer_Windows_OpenGL();

		bool Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync);
		bool InitialiseExtensions();

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();

		void DrawRectangle(int x, int y, int width, int height);

		void CheckError();

		/* Drawing API */
		unsigned int GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount);
		unsigned int DrawBuffers(unsigned int bufferHandle);

		/* Shader API */
		void CompileShaderObject(Shader* shader);
		unsigned int CreateVertexShader();
		unsigned int CreateFragmentShader();
		void SetShaderSource(unsigned int shaderHandle, char* source);
		void CompileShader(unsigned int shaderHandle);
		unsigned int CreateShaderProgram();
		void AttachShader(unsigned int programHandle, unsigned int shaderHandle);
		void BindAttribute(unsigned int programHandle, unsigned int index, const char* name);
		void LinkShaderProgram(unsigned int programHandle);
		void GetShaderLogLength(unsigned int programHandle, int* length);
		void GetShaderInfoLog(unsigned int programHandle, int size, char* logBuffer);
		void GetShaderProgramInfoLog(unsigned int programHandle, int size, char* logBuffer);


		void CheckOpenGLError();

		void OutputShaderErrorMessage(unsigned int shaderHandle);
		void OutputLinkerErrorMessage(unsigned int programHandle);

	private:
		bool LoadExtensionList();

	private:
		HDC		_deviceContext;
		HGLRC	_renderingContext;

		Shader* _currentShader;

		unsigned int _vao;


		float	_worldMatrix[16];
		float	_projectionMatrix[16];
		char	_videoCardDescription[128];

	};
}

#endif