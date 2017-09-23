#include "graphics_blender.h"

namespace MagusEngine
{
	Graphics_Blender::Graphics_Blender()
	{

	}

	bool Graphics_Blender::Initialise(Renderer_Interface* hardwareRenderer, Renderer_Interface* softwareRenderer, int screenWidth, int screenHeight)
	{
		_hardwareRenderer = (Renderer_Linux_OpenGL*)hardwareRenderer;
		_softwareRenderer = (Renderer_Software*)softwareRenderer;

		/* Create a texture */
		_texture.SetName("Software Texture");
		_texture.SetWidth(screenWidth);
		_texture.SetHeight(screenHeight);
		_texture.SetData(0);

		_hardwareRenderer->CreateTexture(&_texture);

		/* Build VBO */
		VBO_Structure vbo;
		vbo.enabled = true;

		Vertex vertices[4];
		vertices[0] = Vertex(0.0f, 0.0f, 0.0, 0.0f, 0.0f, 0.0f, 1.0f);
		vertices[0].SetU(0.0f);
		vertices[0].SetV(1.0f);
		vertices[0].SetExtrude(0.0f, 0.0f);
		vertices[1] = Vertex(0.0f, (float)screenHeight, 0.0, 0.0f, 0.0f, 0.0f, 1.0f);
		vertices[1].SetU(0.0f);
		vertices[1].SetV(0.0f);
		vertices[1].SetExtrude(0.0f, 0.0f);
		vertices[2] = Vertex((float)screenWidth, 0.0f, 0.0, 0.0f, 0.0f, 0.0f, 1.0f);
		vertices[2].SetU(1.0f);
		vertices[2].SetV(1.0f);
		vertices[2].SetExtrude(0.0f, 0.0f);
		vertices[3] = Vertex((float)screenWidth, (float)screenHeight, 0.0, 0.0f, 0.0f, 0.0f, 1.0f);
		vertices[3].SetU(1.0f);
		vertices[3].SetV(0.0f);
		vertices[3].SetExtrude(0.0f, 0.0f);

		unsigned int indicies[6];
		indicies[0] = 0;
		indicies[1] = 1;
		indicies[2] = 2;
		indicies[3] = 1;
		indicies[4] = 2;
		indicies[5] = 3;


		_vbo.vertexstart = 0;
		_vbo.vertexmax = 4;
		_vbo.vertexlength = 4;
		_vbo.vertexhandle = _hardwareRenderer->GenerateVertexBuffer(vertices, &_vbo);

		_vbo.indexstart = 0;
		_vbo.indexmax = 6;
		_vbo.indexlength = 6;
		_vbo.indexhandle = _hardwareRenderer->GenerateIndicesBuffer(indicies, &_vbo);
		
		
		return true;
	}

	bool Graphics_Blender::Render(Matrix4f projection, Matrix4f viewMatrix)
	{
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		_texture.SetData(_softwareRenderer->GetFramebufferData());

		//_bitmap.Save(_texture.GetData(), 32, 0, "temp.bmp");

		_hardwareRenderer->CheckError();
		_hardwareRenderer->SetTexture(&_texture);
		_hardwareRenderer->CheckError();
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _texture.GetWidth(), _texture.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, _texture.GetData());

		Matrix4f indent;
		indent.BuildIdentity();

		int location = glGetUniformLocation(_hardwareRenderer->GetShader()->GetProgramHandle(), "blendmode");
		if (location == -1)
		{
			return false;
		}
		glUniform1i(location, 1);

		 location = glGetUniformLocation(_hardwareRenderer->GetShader()->GetProgramHandle(), "model");
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, indent.GetData());


		location = glGetUniformLocation(_hardwareRenderer->GetShader()->GetProgramHandle(), "projection");
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, projection.GetData());

		_hardwareRenderer->SetCurrentModelMatrix(&indent);

		_hardwareRenderer->CheckError();
		_hardwareRenderer->DrawBuffers(&_vbo, RenderDrawCallType::FILL_2D);

		_hardwareRenderer->CheckError();


		location = glGetUniformLocation(_hardwareRenderer->GetShader()->GetProgramHandle(), "blendmode");
		if (location == -1)
		{
			return false;
		}
		glUniform1i(location, 0);

		return true;
	}
}