#include "graphics_blender.h"

namespace MagusEngine
{
	Graphics_Blender::Graphics_Blender()
	{

	}

	bool Graphics_Blender::Initialise(Renderer_Interface* hardwareRenderer, Renderer_Interface* softwareRenderer, int screenWidth, int screenHeight)
	{
		_hardwareRenderer = (Renderer_Windows_OpenGL*)hardwareRenderer;
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
		vertices[1] = Vertex(0.0f, (float)screenHeight, 0.0, 0.0f, 0.0f, 0.0f, 1.0f);
		vertices[1].SetU(0.0f);
		vertices[1].SetV(0.0f);
		vertices[2] = Vertex((float)screenWidth, 0.0f, 0.0, 0.0f, 0.0f, 0.0f, 1.0f);
		vertices[2].SetU(1.0f);
		vertices[2].SetV(1.0f);
		vertices[3] = Vertex((float)screenWidth, (float)screenHeight, 0.0, 0.0f, 0.0f, 0.0f, 1.0f);
		vertices[3].SetU(1.0f);
		vertices[3].SetV(0.0f);

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

	bool Graphics_Blender::Render()
	{
		/* Update texture info */
		_texture.SetData(_softwareRenderer->GetFramebufferData());

		_hardwareRenderer->CheckError();
		_hardwareRenderer->SetTexture(&_texture);
		_hardwareRenderer->CheckError();
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _texture.GetWidth(), _texture.GetHeight(), GL_BGRA, GL_UNSIGNED_BYTE, _texture.GetData());


		Matrix4f tempProjection = Matrix4f();
		tempProjection.BuildIdentity();
		
		int location = glGetUniformLocation(_hardwareRenderer->GetShader()->GetProgramHandle(), "modelMatrix");
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, tempProjection.GetData());

		_hardwareRenderer->CheckError();
		_hardwareRenderer->DrawBuffers(&_vbo, RenderDrawCallType::FILL_2D);

		_hardwareRenderer->CheckError();

		return true;
	}
}