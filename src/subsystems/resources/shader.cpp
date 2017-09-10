#include "shader.h"

namespace MagusEngine
{
	Shader::Shader(const char* name)
	{
		/* Copy the name */
		strcpy_s(_name, name);
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

	bool Shader::Compile(char* vertexFile, char* fragmentFile)
	{
		const char* vertexFileBuffer;
		const char* fragmentFileBuffer;

		/* Load shader files into buffer */
		//vertexFileBuffer = LoadShaderSourceFile(vertexFile);
		//fragmentFileBuffer = LoadShaderSourceFile(fragmentFile);

		/* Create objects from low level renderer */
		_vertexShader = _lowLevelRenderer->CreateVertexShader();
		_fragmentShader = _lowLevelRenderer->CreateFragmentShader();

		/* Send shader source to low level renderer */
		_lowLevelRenderer->SetShaderSource(_vertexShader, &vertexFileBuffer);
		_lowLevelRenderer->SetShaderSource(_fragmentShader, &fragmentFileBuffer);

		/* Release memory for buffer now its been recieved by the gpu */
		delete[] vertexFileBuffer;
		vertexFileBuffer = 0;

		delete[] fragmentFileBuffer;
		fragmentFileBuffer = 0;

		/* Compile the shader source */
		_lowLevelRenderer->CompileShader(_vertexShader);
		_lowLevelRenderer->CompileShader(_fragmentShader);

		/* Create the shader project */
		_program = _lowLevelRenderer->CreateShaderProgram();

		/* Attach shaders to program */
		_lowLevelRenderer->AttachShader(_program, _vertexShader);
		_lowLevelRenderer->AttachShader(_program, _fragmentShader);

		/* Bind any attribute locations */
		_lowLevelRenderer->BindAttribute(_program, 0, "inputPosition");
		_lowLevelRenderer->BindAttribute(_program, 1, "inputColor");

		/* Link Shader */
		_lowLevelRenderer->LinkShaderProgram(_program);

		return true;
	}

	void Shader::OutputShaderErrorMessage(unsigned int shaderHandle)
	{
		int logSize;
		char* infoLog;


		// Get the size of the string containing the information log for the failed shader compilation message.
		_lowLevelRenderer->GetShaderLogLength(shaderHandle, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = new char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		_lowLevelRenderer->GetShaderInfoLog(shaderHandle, logSize, infoLog);

		printf("Shader Error:\n%s\n", infoLog);
	
		return;
	}

	void Shader::OutputLinkerErrorMessage(unsigned int programHandle)
	{
		int logSize;
		char* infoLog;


		// Get the size of the string containing the information log for the failed shader compilation message.
		_lowLevelRenderer->GetShaderLogLength(programHandle, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = new char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		_lowLevelRenderer->GetShaderProgramInfoLog(programHandle, logSize, infoLog);

		printf("Shader Program Error:\n%s\n", infoLog);

		return;
	}
}