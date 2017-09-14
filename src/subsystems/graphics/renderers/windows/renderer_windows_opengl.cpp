#include "renderer_windows_opengl.h"


namespace MagusEngine
{
	Renderer_Windows_OpenGL::Renderer_Windows_OpenGL()
	{
		_deviceContext = 0;
		_renderingContext = 0;
	}

	bool Renderer_Windows_OpenGL::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize GLAD\n");
			return false;
		}

		_CurrentTexture = 0;
		_CurrentMaterial = 0;
		_CurrentShader = 0;
		
		/* Generate vao */
		glGenVertexArrays(1, &_vao);
		
		glBindVertexArray(_vao);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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


		glUseProgram(_CurrentShader->GetProgramHandle());
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

	}
	
	void Renderer_Windows_OpenGL::CheckError()
	{
		CheckOpenGLError();
	}

	/* Data Loading API */
	unsigned int Renderer_Windows_OpenGL::GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount)
	{
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		CheckError();

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);
		CheckError();
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(0);	
		glEnableVertexAttribArray(1);
		CheckError();
		return VBO;
	}

	unsigned int Renderer_Windows_OpenGL::GenerateIndicesBuffer(unsigned int* indices, unsigned int indicesCount)
	{
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		CheckError();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex) * indicesCount, indices, GL_STATIC_DRAW);
		CheckError();

		return EBO;
	}

	unsigned int Renderer_Windows_OpenGL::DrawBuffers(VBO_Structure* bufferData)
	{
		unsigned int location;
		Matrix4f tempMat = Matrix4f();
		tempMat.BuildIdentity();

		Matrix4f tempProjection = Matrix4f();
		tempProjection.BuildOrthographic(0.0f, 800.0f, 600.0f, 0.0f,  1.0f, -1.0f);

		CheckError();
		glUseProgram(_CurrentShader->GetProgramHandle());

		location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "projectionMatrix");
		if(location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, tempProjection.GetData());

		CheckError();
		glBindBuffer(GL_ARRAY_BUFFER, bufferData->vertexhandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferData->indexhandle);

		CheckError();
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		CheckError();
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));

		CheckError();
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));

		CheckError();
		glEnableVertexAttribArray(0);	

		CheckError(); 
		glEnableVertexAttribArray(1);

		CheckError();
		glEnableVertexAttribArray(2);

		CheckError();
		glDrawElements(GL_TRIANGLES, bufferData->indexlength, GL_UNSIGNED_INT, 0);


		CheckError();
		return 0;
	}

	void Renderer_Windows_OpenGL::SetCurrentModelMatrix(Matrix4f* matrix)
	{
		CheckError();
		int location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "modelMatrix");
		CheckError();
		if(location == -1)
		{
			return;
		}
		glUniformMatrix4fv(location, 1, false, matrix->GetData());
		CheckError();
	}

	void Renderer_Windows_OpenGL::SetMaterial(Material* material)
	{
		int location = 0;

		/* Set Current Material */
		_CurrentMaterial = material;

		/* Set current color */
		if(material->GetColor() != NULL)
		{
			location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "color");
			if(location == -1)
			{
				return;
			}
			glUniform4fv(location, 1, (float*)material->GetColor());
		}
		
		/* Set texture */
		SetTexture(material->GetTexture());

		return;
	}

	void Renderer_Windows_OpenGL::SetTexture(Texture* texture)
	{
		/* Set Current Texture */
		_CurrentTexture = texture;

		if (texture != NULL)
		{
			/* Bind the texture */
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->GetRenderDataHandle());

			int location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "uni_textureEnabled");
			glUniform1i(location, 1);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 1);
			int location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "uni_textureEnabled");
			glUniform1i(location, 0);
		}

	}

	/* Shader API */
	void Renderer_Windows_OpenGL::CompileShaderObject(Shader* shader)
	{
		int success;
		char infoLog[512];

		/* GL required const pointers */
		const GLchar* vertexsource =  shader->GetVertexSrc();
		const GLchar* fragmentsource =  shader->GetFragmentSrc();

		/* Vertex Shader */
		shader->SetVertexHandle(glCreateShader(GL_VERTEX_SHADER));

		glShaderSource(shader->GetVertexHandle(), 1, &vertexsource, NULL);
		glCompileShader(shader->GetVertexHandle());

		/* Check for vertex shader compile errors */
		glGetShaderiv(shader->GetVertexHandle(), GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader->GetVertexHandle(), 512, NULL, infoLog);
			printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
			printf("%s", infoLog);
		}

		/* Fragment Shader */
		shader->SetFragmentHandle(glCreateShader(GL_FRAGMENT_SHADER));

		glShaderSource(shader->GetFragmentHandle(), 1, &fragmentsource, NULL);
		glCompileShader(shader->GetFragmentHandle());

		/* Check for fragment shader compile errors */
		glGetShaderiv(shader->GetFragmentHandle(), GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader->GetFragmentHandle(), 512, NULL, infoLog);
			printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
			printf("%s", infoLog);
		}

		/* Link shaders */
		shader->SetProgramHandle(glCreateProgram());

		/* Attach shaders to program */
		glAttachShader(shader->GetProgramHandle(), shader->GetVertexHandle());
		glAttachShader(shader->GetProgramHandle(), shader->GetFragmentHandle());
		glLinkProgram(shader->GetProgramHandle());

		/* Check for linking errors */
		glGetProgramiv(shader->GetProgramHandle(), GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader->GetProgramHandle(), 512, NULL, infoLog);
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
			printf("%s", infoLog);
		}

		/* Delete shader as program is complete */
		glDeleteShader(shader->GetVertexHandle());
		glDeleteShader(shader->GetFragmentHandle());

		/* Set as the current shader */
		_CurrentShader = shader;
	}

	void Renderer_Windows_OpenGL::SetCurrentShader(Shader* shader)
	{
		_CurrentShader = shader;
		glUseProgram(shader->GetProgramHandle());
	}


	/* Texture API */
	void Renderer_Windows_OpenGL::CreateTexture(Texture* texture)
	{
		unsigned int TB;
		glGenTextures(1, &TB);
		glBindTexture(GL_TEXTURE_2D, TB);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0,  GL_RGBA, GL_UNSIGNED_BYTE, texture->GetData());

		texture->SetRenderDataHandle(TB);
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
}