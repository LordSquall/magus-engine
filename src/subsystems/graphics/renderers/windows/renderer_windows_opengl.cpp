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
			LOGERROR("Unable to Initialize GLAD\n");
			return false;
		}

		_CurrentTexture = 0;
		_CurrentMaterial = 0;
		_CurrentShader = 0;
		
		/* Generate vao */
		glGenVertexArrays(1, &_vao);
		
		glBindVertexArray(_vao);

		glDisable(GL_CULL_FACE);
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
	unsigned int Renderer_Windows_OpenGL::GenerateVertexBuffer(Vertex* vertices, VBO_Structure* vbodata)
	{
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		CheckError();

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vbodata->vertexmax, &vertices[vbodata->vertexstart], GL_STATIC_DRAW);
		CheckError();
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(11 * sizeof(float)));
		glEnableVertexAttribArray(0);	
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		CheckError();
		return VBO;
	}

	unsigned int Renderer_Windows_OpenGL::GenerateIndicesBuffer(unsigned int* indices, VBO_Structure* vbodata)
	{
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		CheckError();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vbodata->indexmax, &indices[vbodata->indexstart], GL_STATIC_DRAW);
		CheckError();

		return EBO;
	}

	unsigned int Renderer_Windows_OpenGL::UpdateVertexBuffer(VBO_Structure* bufferData, Vertex* vertices, unsigned int vertexStart, unsigned int vertexCount)
	{
		CheckError();
		glBindBuffer(GL_ARRAY_BUFFER, bufferData->vertexhandle);
		CheckError();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertexCount, vertices);
		CheckError();

		return bufferData->vertexhandle;
	}

	unsigned int Renderer_Windows_OpenGL::UpdateIndicesBuffer(VBO_Structure* bufferData, unsigned int* indices, unsigned int indicesStart, unsigned int indicesCount)
	{
		CheckError();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferData->indexhandle);
		CheckError();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * indicesCount, indices);
		CheckError();
		return bufferData->indexhandle;
	}

	unsigned int Renderer_Windows_OpenGL::DrawBuffers(VBO_Structure* bufferData, RenderDrawCallType type)
	{

		/* Build mvp matrix */
		Matrix4f mvp = (*_projectionMatrix) * (*_viewMatrix) * (*_modelMatrix);

		int location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "mvp");
		CheckError();
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, mvp.GetData());
		CheckError();

		location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "uni_renderPassType");
		if (location == -1)
		{
			return false;
		}
		glUniform1i(location, type);

		CheckError();
		glBindBuffer(GL_ARRAY_BUFFER, bufferData->vertexhandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferData->indexhandle);

		CheckError();
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		CheckError();
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));

		CheckError();
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));

		CheckError();
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(11 * sizeof(float)));

		CheckError();
		glEnableVertexAttribArray(0);	

		CheckError(); 
		glEnableVertexAttribArray(1);

		CheckError();
		glEnableVertexAttribArray(2);

		CheckError();
		glEnableVertexAttribArray(3);

		CheckError();
		glDrawElements(GL_TRIANGLES, bufferData->indexlength, GL_UNSIGNED_INT, 0);


		CheckError();
		return 0;
	}

	void Renderer_Windows_OpenGL::SetCurrentModelMatrix(Matrix4f* matrix)
	{
		_modelMatrix = matrix;
	}

	void Renderer_Windows_OpenGL::SetCurrentProjectionMatrix(Matrix4f* matrix)
	{
		_projectionMatrix = matrix;
	}

	void Renderer_Windows_OpenGL::SetCurrentViewMatrix(Matrix4f* matrix)
	{
		_viewMatrix = matrix;
	}

	void Renderer_Windows_OpenGL::SetMaterial(Material* material)
	{
		int location = 0;

		/* Set Current Material */
		_CurrentMaterial = material;

		/* Set current color */
		if(material->GetColor1() != NULL)
		{
			location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "color");
			if(location == -1)
			{
				return;
			}
			glUniform4fv(location, 1, (float*)material->GetColor1());
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
			LOGERROR("Vertex Shader Compilation failed: %s", infoLog);
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
			LOGERROR("Fragment Shader Compilation failed: %s", infoLog);
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
			LOGERROR("Shader Program Linkage failed: %s", infoLog);
		}

		/* Delete shader as program is complete */
		glDeleteShader(shader->GetVertexHandle());
		glDeleteShader(shader->GetFragmentHandle());

		LOGINFO("Shader Compiled Successfully");
		
		/* Set as the current shader */
		SetCurrentShader(shader);
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
		CheckError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		CheckError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		CheckError();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0,  GL_RGBA, GL_UNSIGNED_BYTE, texture->GetData());
		CheckError();
		texture->SetRenderDataHandle(TB);
	}

	/* Filter API */
	void Renderer_Windows_OpenGL::ActivateFilter(VBO_Structure* bufferData)
	{
		/* Turn of the color buffers */
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		/* Enable stencil testing */
		glEnable(GL_STENCIL_TEST);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_INCR, GL_INCR, GL_INCR);
		glStencilMask(0xFF);

		DrawBuffers(bufferData, RenderDrawCallType::STENCIL);

		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(0x00);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}

	void Renderer_Windows_OpenGL::DeactivateFilter(VBO_Structure* bufferData)
	{
		/* Turn of the color buffers */
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		/* Enable stencil testing */
		glEnable(GL_STENCIL_TEST);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_DECR, GL_DECR, GL_DECR);
		glStencilMask(0xFF);

		DrawBuffers(bufferData, RenderDrawCallType::STENCIL);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(0x00);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		glDisable(GL_STENCIL_TEST);
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
				LOGERROR("GL Error: Invalid Enum\n");
				break;
			case GL_INVALID_VALUE:
				LOGERROR("GL Error: Invalid Value\n");
				break;
			case GL_INVALID_OPERATION:
				LOGERROR("GL Error: Invalid Operation\n");
				break;
			case GL_STACK_OVERFLOW:
				LOGERROR("GL Error: Stack Overflow\n");
				break;
			case GL_STACK_UNDERFLOW:
				LOGERROR("GL Error: Stack Underflow\n");
				break;
			case GL_OUT_OF_MEMORY:
				LOGERROR("GL Error: Out of Memory\n");
				break;
			}
		}
	}
}