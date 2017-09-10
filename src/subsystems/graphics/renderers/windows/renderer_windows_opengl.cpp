#include "renderer_windows_opengl.h"


namespace MagusEngine
{
	Renderer_Windows_OpenGL::Renderer_Windows_OpenGL()
	{
		_deviceContext = 0;
		_renderingContext = 0;
	}

	bool Renderer_Windows_OpenGL::InitialiseExtensions()
	{
		
		return true;
	}

	bool Renderer_Windows_OpenGL::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize GLAD\n");
			return -1;
		}

		return true;
	}

	void Renderer_Windows_OpenGL::Shutdown()
	{
		// Release the rendering context.
		if (_renderingContext)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_renderingContext);
			_renderingContext = 0;
		}

		// Release the device context.
		if (_deviceContext)
		{
			//ReleaseDC(hwnd, m_deviceContext);
			_deviceContext = 0;
		}

		return;
	}

	void Renderer_Windows_OpenGL::BeginScene(float red, float green, float blue, float alpha)
	{
		// Set the color to clear the screen to.
		glClearColor(red, green, blue, alpha);

		// Clear the screen and depth buffer.
		glClear(GL_COLOR_BUFFER_BIT);

		return;
	}

	void Renderer_Windows_OpenGL::EndScene()
	{
		// Present the back buffer to the screen since rendering is complete.
	//	SwapBuffers(_deviceContext);

		return;
	}

	void Renderer_Windows_OpenGL::DrawRectangle(int x, int y, int width, int height)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3f(1.0f, 0.0f, 00.0f);

		glBegin(GL_TRIANGLES);
		glVertex3f(-50.0f, 50.0f, 0.0f);
		glVertex3f(-50.0f, -50.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, 0.0f);
		glEnd();
	}
	
	void Renderer_Windows_OpenGL::CheckError()
	{
		CheckOpenGLError();
	}

	/* Data Loading API */
	unsigned int Renderer_Windows_OpenGL::GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount)
	{
		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		return VAO;
	}

	unsigned int Renderer_Windows_OpenGL::DrawBuffers(unsigned int bufferHandle)
	{
		CheckError();
		glUseProgram(_currentShader->GetProgramHandle());

		CheckError();
		glBindVertexArray(bufferHandle); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		CheckError();
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//CheckError();
		return 0;
	}

	/* Shader API */
	void Renderer_Windows_OpenGL::CompileShaderObject(Shader* shader)
	{

		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec2 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
			"}\0";
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";


		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		}
		// fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
		}
		// link shaders
		int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		shader->SetProgramHandle(shaderProgram);

		_currentShader = shader;

		//int status;
		//CheckError();
		///* Create objects from low level renderer */
		//shader->SetVertexHandle(CreateVertexShader());
		//shader->SetFragmentHandle(CreateFragmentShader());
		//CheckError();
		///* Send shader source to low level renderer */
		//SetShaderSource(shader->GetVertexHandle(), shader->GetVertexSrc());
		//SetShaderSource(shader->GetFragmentHandle(), shader->GetFragmentSrc());
		//CheckError();
		///* Compile the shader source */
		//CompileShader(shader->GetVertexHandle());
		//CompileShader(shader->GetFragmentHandle());

		//CheckError();

		///* Check for compile errors in shaders */
		//glGetShaderiv(shader->GetVertexHandle(), GL_COMPILE_STATUS, &status);
		//if(!status)
		//	OutputShaderErrorMessage(shader->GetVertexHandle());

		//CheckError();

		//glGetShaderiv(shader->GetFragmentHandle(), GL_COMPILE_STATUS, &status);
		//if (!status)
		//	OutputShaderErrorMessage(shader->GetFragmentHandle());

		//CheckError();

		///* Create the shader project */
		//shader->SetProgramHandle(CreateShaderProgram());

		//CheckError();

		///* Attach shaders to program */
		//AttachShader(shader->GetProgramHandle(), shader->GetVertexHandle());
		//CheckError();
		//AttachShader(shader->GetProgramHandle(), shader->GetFragmentHandle());
		//CheckError();

		///* Link Shader */
		//LinkShaderProgram(shader->GetProgramHandle());

		///* Check for Linkers Errors */
		//glGetProgramiv(shader->GetProgramHandle(), GL_LINK_STATUS, &status);
		//if (!status)
		//	OutputLinkerErrorMessage(shader->GetFragmentHandle());


		//CheckError();
		//glUseProgram(shader->GetProgramHandle());

		//CheckError();
		//_currentShader = shader;

	}

	unsigned int Renderer_Windows_OpenGL::CreateVertexShader()
	{
		return glCreateShader(GL_VERTEX_SHADER);
	}

	unsigned int Renderer_Windows_OpenGL::CreateFragmentShader()
	{
		return glCreateShader(GL_FRAGMENT_SHADER);
	}

	void Renderer_Windows_OpenGL::SetShaderSource(unsigned int shaderHandle, char* source)
	{
		const char* src = source;
		glShaderSource(shaderHandle, 1, &src, NULL);
	}

	void Renderer_Windows_OpenGL::CompileShader(unsigned int shaderHandle)
	{
		glCompileShader(shaderHandle);
	}
	
	unsigned int Renderer_Windows_OpenGL::CreateShaderProgram()
	{
		return glCreateProgram();
	}
	
	void Renderer_Windows_OpenGL::AttachShader(unsigned int programHandle, unsigned int shaderHandle)
	{
		glAttachShader(programHandle, shaderHandle);
	}
	
	void Renderer_Windows_OpenGL::BindAttribute(unsigned int programHandle, unsigned int index, const char* name)
	{
		glBindAttribLocation(programHandle, index, name);
	}
	
	void Renderer_Windows_OpenGL::LinkShaderProgram(unsigned int programHandle)
	{
		glLinkProgram(programHandle);
	}

	void Renderer_Windows_OpenGL::GetShaderLogLength(unsigned int shaderHandle, int* length)
	{
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, length);
	}

	void Renderer_Windows_OpenGL::GetShaderInfoLog(unsigned int shaderHandle, int size, char* logBuffer)
	{
		glGetShaderInfoLog(shaderHandle, size, NULL, logBuffer);
	}

	void Renderer_Windows_OpenGL::GetShaderProgramInfoLog(unsigned int programHandle, int size, char* logBuffer)
	{
		glGetProgramInfoLog(programHandle, size, NULL, logBuffer);
	}


	bool Renderer_Windows_OpenGL::LoadExtensionList()
	{
		return true;
	}


	void Renderer_Windows_OpenGL::CheckOpenGLError()
	{
		// check OpenGL error
		GLenum err = glGetError();

		if (err != GL_NO_ERROR)
		{
			switch (err)
			{
			case GL_INVALID_ENUM:
				printf("GL Error: Invalid Enum\n");
				break;
			case GL_INVALID_VALUE:
				printf("GL Error: Invalid Value\n");
				break;
			case GL_INVALID_OPERATION:
				printf("GL Error: Invalid Operation\n");
				break;
			case GL_STACK_OVERFLOW:
				printf("GL Error: Stack Overflow\n");
				break;
			case GL_STACK_UNDERFLOW:
				printf("GL Error: Stack Underflow\n");
				break;
			case GL_OUT_OF_MEMORY:
				printf("GL Error: Out of Memory\n");
				break;
			}
		}
	}

	void Renderer_Windows_OpenGL::OutputShaderErrorMessage(unsigned int shaderHandle)
	{
		int logSize;
		char* infoLog;


		// Get the size of the string containing the information log for the failed shader compilation message.
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = new char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		GetShaderInfoLog(shaderHandle, logSize, infoLog);

		printf("Shader Error:\n%s\n", infoLog);

		return;
	}

	void Renderer_Windows_OpenGL::OutputLinkerErrorMessage(unsigned int programHandle)
	{
		int logSize;
		char* infoLog;


		// Get the size of the string containing the information log for the failed shader compilation message.
		glGetShaderiv(programHandle, GL_INFO_LOG_LENGTH, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = new char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		GetShaderProgramInfoLog(programHandle, logSize, infoLog);

		printf("Shader Program Error:\n%s\n", infoLog);

		return;
	}
}