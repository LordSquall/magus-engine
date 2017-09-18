#include "renderer_linux_opengl.h"

#include "../../../os/os_linux.h"

//#include <GL/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace MagusEngine
{
	Renderer_Linux_OpenGL::Renderer_Linux_OpenGL()
	{

	}

	bool Renderer_Linux_OpenGL::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{

printf("foobar\n");
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("initialize GLAD\n");
			return false;
		}

		_CurrentTexture = 0;
		_CurrentMaterial = 0;
		_CurrentShader = 0;
		
		/* Generate vao */
		glGenVertexArrays(1, &_vao);
		
		CheckError();
		glBindVertexArray(_vao);
		CheckError();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		return true;
	}
	
	void Renderer_Linux_OpenGL::Shutdown()
	{
	}

	void Renderer_Linux_OpenGL::DrawRectangle(int x, int y, int width, int height)
	{

	}

	void Renderer_Linux_OpenGL::BeginScene(float red, float green, float blue, float alpha)
	{
		printf("Begin Scene 0\n");
		glClearColor(red, green, blue, alpha);
		
		printf("Begin Scene 1\n");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		printf("Begin Scene 2\n");
		return;
	}


	void Renderer_Linux_OpenGL::EndScene()
	{
		//OS* os = (OS*)_os;
		//glXSwapBuffers(os->getDisplay(), os->getWindow());
		return;
	}
	
	
	void Renderer_Linux_OpenGL::CheckError()
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
	
	/* Data Loading API */
	unsigned int Renderer_Linux_OpenGL::GenerateVertexBuffer(Vertex* vertices, VBO_Structure* vbodata)
	{
		
		unsigned int temp = 0;

		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		CheckError();
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vbodata->vertexmax, &vertices[vbodata->vertexstart], GL_STATIC_DRAW);
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		CheckError();
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		glEnableVertexAttribArray(0);	
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		glEnableVertexAttribArray(1);
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		glEnableVertexAttribArray(2);
		printf("DEBUG: Generate Vertex Buffer: %d\n", temp); temp++;
		CheckError();
		
		LOGINFO("Vertex Buffer Generated [%d]", VBO);
		return VBO;
	}

	unsigned int Renderer_Linux_OpenGL::GenerateIndicesBuffer(unsigned int* indices, VBO_Structure* vbodata)
	{		
		unsigned int temp = 0;

		printf("DEBUG: Generate Indices Buffer: %d\n", temp); temp++;
		unsigned int IBO;
		glGenBuffers(1, &IBO);
		printf("DEBUG: Generate Indices Buffer: %d\n", temp); temp++;
		CheckError();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		printf("DEBUG: Generate Indices Buffer: %d\n", temp); temp++;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vbodata->indexmax, &indices[vbodata->indexstart], GL_STATIC_DRAW);
		printf("DEBUG: Generate Indices Buffer: %d\n", temp); temp++;
		CheckError();

		
		LOGINFO("Index Buffer Generated [%d]", IBO);
		
		return IBO;
	}


	unsigned int Renderer_Linux_OpenGL::UpdateVertexBuffer(VBO_Structure* bufferData, Vertex* vertices, unsigned int vertexStart, unsigned int vertexCount)
	{
		CheckError();
		glBindBuffer(GL_ARRAY_BUFFER, bufferData->vertexhandle);
		CheckError();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertexCount, vertices);
		CheckError();

		return bufferData->vertexhandle;
	}
	
	unsigned int Renderer_Linux_OpenGL::UpdateIndicesBuffer(VBO_Structure* bufferData, unsigned int* indices, unsigned int indicesStart, unsigned int indicesCount)
	{
		CheckError();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferData->indexhandle);
		CheckError();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * indicesCount, indices);
		CheckError();
		return bufferData->indexhandle;
	}

	unsigned int Renderer_Linux_OpenGL::DrawBuffers(VBO_Structure* bufferData, RenderDrawCallType type)
	{
		unsigned int location;
		unsigned int temp = 0;

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "projectionMatrix");
		if(location == -1)
		{
			return false;
		}
		
		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		glUniformMatrix4fv(location, 1, false, _projectionMatrix->GetData());

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "uni_renderPassType");
		
		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		if (location == -1)
		{
			return false;
		}
		
		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		glUniform1i(location, type);

		CheckError();
		
		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		glBindBuffer(GL_ARRAY_BUFFER, bufferData->vertexhandle);
		
		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferData->indexhandle);

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		CheckError();
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		CheckError();
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		CheckError();
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		CheckError();
		glEnableVertexAttribArray(0);	

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		CheckError(); 
		glEnableVertexAttribArray(1);

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		CheckError();
		glEnableVertexAttribArray(2);

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;
		CheckError();
		glDrawElements(GL_TRIANGLES, bufferData->indexlength, GL_UNSIGNED_INT, 0);

		printf("DEBUG: Draw Buffers: %d\n", temp); temp++;

		CheckError();
		return 0;
	}

	void Renderer_Linux_OpenGL::SetCurrentModelMatrix(Matrix4f* matrix)
	{
		unsigned int temp = 0;
		printf("DEBUG: Set Current Model Matrix: %d\n", temp); temp++;
		CheckError();
		int location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "modelMatrix");
		CheckError();
		printf("DEBUG: Set Current Model Matrix: %d\n", temp); temp++;
		LOGINFO("Current Model Matrix Location: %d", location);
		if(location == -1)
		{
			return;
		}
		printf("DEBUG: Set Current Model Matrix: %d\n", temp); temp++;
		glUniformMatrix4fv(location, 1, false, matrix->GetData());
		CheckError();
		printf("DEBUG: Set Current Model Matrix: %d\n", temp); temp++;
	}

	
	void Renderer_Linux_OpenGL::SetCurrentProjectionMatrix(Matrix4f* matrix)
	{
		unsigned int temp = 0;
		printf("DEBUG: Set Current Projection Matrix: %d\n", temp); temp++;
		CheckError();
		int location = glGetUniformLocation(_CurrentShader->GetProgramHandle(), "projectionMatrix");
		CheckError();
		printf("DEBUG: Set Current Projection Matrix: %d\n", temp); temp++;
		if(location == -1)
		{
			return;
		}
		printf("DEBUG: Set Current Projection Matrix: %d\n", temp); temp++;
		glUniformMatrix4fv(location, 1, false, matrix->GetData());
		CheckError();
		printf("DEBUG: Set Current Projection Matrix: %d\n", temp); temp++;


		_projectionMatrix = matrix;
	}

	void Renderer_Linux_OpenGL::SetMaterial(Material* material)
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

	void Renderer_Linux_OpenGL::SetTexture(Texture* texture)
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
	void Renderer_Linux_OpenGL::CompileShaderObject(Shader* shader)
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

		LOGINFO("Shader Compiled Successfully");
		
		/* Set as the current shader */
		SetCurrentShader(shader);
	}

	void Renderer_Linux_OpenGL::SetCurrentShader(Shader* shader)
	{
		_CurrentShader = shader;
		glUseProgram(shader->GetProgramHandle());
		LOGINFO("Shader Set [%d]", shader->GetProgramHandle());
	}


	/* Texture API */
	void Renderer_Linux_OpenGL::CreateTexture(Texture* texture)
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
	void Renderer_Linux_OpenGL::ActivateFilter(VBO_Structure* bufferData)
	{
		/* Turn of the color buffers */
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		/* Enable stencil testing */
		glEnable(GL_STENCIL_TEST);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_INCR, GL_INCR, GL_INCR);
		glStencilMask(0xFF);

		//DrawBuffers(bufferData);

		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(0x00);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}

	void Renderer_Linux_OpenGL::DeactivateFilter(VBO_Structure* bufferData)
	{
		/* Turn of the color buffers */
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		/* Enable stencil testing */
		glEnable(GL_STENCIL_TEST);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_DECR, GL_DECR, GL_DECR);
		glStencilMask(0xFF);

		//DrawBuffers(bufferData);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(0x00);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		glDisable(GL_STENCIL_TEST);
	}
}
