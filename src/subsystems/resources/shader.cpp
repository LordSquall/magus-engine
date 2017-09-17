#include "shader.h"

namespace MagusEngine
{
	Shader::Shader(const char* name)
	{
		/* Copy the name */
		strcpy(_name, name);
	}

	bool Shader::Initialise(Renderer_Interface* lowLevelRenderer)
	{
		/* Initialise Variables */
		_lowLevelRenderer	= lowLevelRenderer;
		_program			= 0;
		_vertexShader		= 0;
		_fragmentShader		= 0;

		return true;
	}

	bool Shader::InitailiseVertexSourceBuffer(unsigned int size)
	{
		_vertexShaderSrc = (char*)malloc(sizeof(char) * size);

		if (_vertexShaderSrc == NULL)
		{
			return false;
		}
		return true;
	}

	bool Shader::InitailiseFragmentSourceBuffer(unsigned int size)
	{
		_fragmentShaderSrc = (char*)malloc(sizeof(char) * size);

		if (_fragmentShaderSrc == NULL)
		{
			return false;
		}
		return true;
	}

	/* Getters */
	char* Shader::GetName() { return _name; }
	unsigned int Shader::GetProgramHandle() { return _program; }
	unsigned int Shader::GetVertexHandle() { return _vertexShader; }
	unsigned int Shader::GetFragmentHandle() { return _fragmentShader; }
	char* Shader::GetVertexSrc() { return _vertexShaderSrc; }
	char* Shader::GetFragmentSrc() { return _fragmentShaderSrc; }

	/* Setters */
	void Shader::SetProgramHandle(unsigned int programHandle) { _program = programHandle; }
	void Shader::SetVertexHandle(unsigned int vertexHandle) { _vertexShader = vertexHandle; }
	void Shader::SetFragmentHandle(unsigned int fragmentHandle) { _fragmentShader = fragmentHandle; }
}