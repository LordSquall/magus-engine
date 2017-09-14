#include "graphics_blender.h"

namespace MagusEngine
{
	Graphics_Blender::Graphics_Blender()
	{

	}

	bool Graphics_Blender::Initialise(Renderer_Interface* hardwareRenderer, Renderer_Interface* softwareRenderer)
	{
		_hardwareRenderer = (Renderer_Windows_OpenGL*)hardwareRenderer;
		_softwareRenderer = (Renderer_Software*)softwareRenderer;

		/* Create a texture */
		_texture.SetName("Software Texture");
		_texture.SetWidth(800);
		_texture.SetHeight(600);
		_texture.SetData(0);

		_hardwareRenderer->CreateTexture(&_texture);

		/* Build VBO */
		Vertex vertices[4];
		vertices[0] = Vertex(0.0f, 0.0f, 0.0);
		vertices[0].SetU(0.0f);
		vertices[0].SetV(1.0f);
		vertices[1] = Vertex(0.0f, 600.0f, 0.0);
		vertices[1].SetU(0.0f);
		vertices[1].SetV(0.0f);
		vertices[2] = Vertex(800.0f, 0.0f, 0.0);
		vertices[2].SetU(1.0f);
		vertices[2].SetV(1.0f);
		vertices[3] = Vertex(800.0f, 600.0f, 0.0);
		vertices[3].SetU(1.0f);
		vertices[3].SetV(0.0f);

		unsigned int indicies[6];
		indicies[0] = 0;
		indicies[1] = 1;
		indicies[2] = 2;
		indicies[3] = 1;
		indicies[4] = 2;
		indicies[5] = 3;

		_vbo.vertexhandle = _hardwareRenderer->GenerateVertexBuffer(vertices, 4);
		_vbo.vertexlength = 4;
		_vbo.indexhandle = _hardwareRenderer->GenerateIndicesBuffer(indicies, 6);
		_vbo.indexlength = 6;

		return true;
	}

	bool Graphics_Blender::Render()
	{
		/* Update texture info */
		_texture.SetData(_softwareRenderer->GetFramebufferData());

		_hardwareRenderer->CheckError();
		glBindTexture(GL_TEXTURE_2D, _texture.GetRenderDataHandle());

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
		_hardwareRenderer->DrawBuffers(&_vbo);

		_hardwareRenderer->CheckError();

		return true;
	}
}