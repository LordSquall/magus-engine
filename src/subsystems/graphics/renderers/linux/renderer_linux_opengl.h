#ifndef _OPENGL_CLASS_H_
#define _OPENGL_CLASS_H_

#include "../renderer_interface.h"

#include<stdio.h>
#include<stdlib.h>

#define GL_GLEXT_PROTOTYPES

#include<X11/X.h>
#include<X11/Xlib.h>

#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include<GL/gl.h>
#include<GL/glext.h>

#include "../../../math/matrix.h"
#include "../../../resources/shader.h"
#include "../../../resources/texture.h"
#include "../../../resources/color.h"
#include "../../../resources/material.h"

namespace MagusEngine
{
	class Renderer_Linux_OpenGL : public Renderer_Interface
	{
	public:
		Renderer_Linux_OpenGL();

		bool Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync);

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();
		
		
		void DrawRectangle(int x, int y, int width, int height);

		void CheckError();
		
		/* Drawing API */
		unsigned int GenerateVertexBuffer(Vertex* vertices, VBO_Structure* vbodata);
		unsigned int GenerateIndicesBuffer(unsigned int* indices, VBO_Structure* vbodata);
		unsigned int UpdateVertexBuffer(VBO_Structure* bufferData, Vertex* vertices, unsigned int vertexStart, unsigned int vertexCount);
		unsigned int UpdateIndicesBuffer(VBO_Structure* bufferData, unsigned int* indices, unsigned int indicesStart, unsigned int indicesCount);

		unsigned int DrawBuffers(VBO_Structure* bufferData, RenderDrawCallType type);
		void SetCurrentModelMatrix(Matrix4f* matrix);
		void SetCurrentProjectionMatrix(Matrix4f* matrix);
		void SetCurrentViewMatrix(Matrix4f* matrix);
		void SetMaterial(Material* material);
		void SetTexture(Texture* texture);

		/* Shader API */
		void CompileShaderObject(Shader* shader);
		void SetCurrentShader(Shader* shader);
		
		/* Texture API */
		void CreateTexture(Texture* texture);

		/* Filter API */
		void ActivateFilter(VBO_Structure* bufferData);
		void DeactivateFilter(VBO_Structure* bufferData);

		void CheckOpenGLError();
		
	private:
		void*						_os;
		GLXContext					m_glContext;
		
		GLuint						_vao;
		
		Matrix4f*					_projectionMatrix;
	};
}

#endif