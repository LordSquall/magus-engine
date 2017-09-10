#ifndef _SHADER_H_
#define _SHADER_H_

/* System Includes */
#include <fstream>
#include "../graphics/renderers/renderer_interface.h"

namespace MagusEngine
{
	class Shader
	{
	public:
		Shader(const char* name);

		bool Initialise(Renderer_Interface* lowlevelRenderer);
		bool InitailiseVertexSourceBuffer(unsigned int size);
		bool InitailiseFragmentSourceBuffer(unsigned int size);

		void OutputShaderErrorMessage(unsigned int);
		void OutputLinkerErrorMessage(unsigned int);

		void Shutdown();

		/* Getters */
		char* GetName();
		unsigned int GetProgramHandle();
		unsigned int GetVertexHandle();
		unsigned int GetFragmentHandle();
		char* GetVertexSrc();
		char* GetFragmentSrc();

		/* Setters */
		void SetProgramHandle(unsigned int programHandle);
		void SetVertexHandle(unsigned int vertexHandle);
		void SetFragmentHandle(unsigned int fragmentHandle);

	private:
		char _name[255];
		unsigned int _program;
		unsigned int _vertexShader;
		unsigned int _fragmentShader;
	
		char* _vertexShaderSrc;
		char* _fragmentShaderSrc;

		Renderer_Interface* _lowLevelRenderer;
	};
}

#endif