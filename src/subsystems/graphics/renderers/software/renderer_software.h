#ifndef _RENDERER_SOFTWARE_H_
#define _RENDERER_SOFTWARE_H_

#include "../renderer_interface.h"
#include "../../../resources/shader.h"
#include "../../../resources/texture.h"
#include "../../../../frameworkconfig.h"
#include "sr_bitmap.h"
#include "sr_framebuffer.h"
#include "sr_scanbuffer.h"

typedef char Byte;

namespace MagusEngine
{
	struct MemoryBuffer
	{
		void* start;
		void* end;
	};

	class Renderer_Software : public Renderer_Interface
	{
	public:
		Renderer_Software(FrameworkConfig* config);

		bool Initialise(void*, int, int, float, float, bool);
		bool InitialiseExtensions();

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();		
		
		void DrawRectangle(int x, int y, int width, int height);

		void CheckError();

		/* Data Loading API */
		unsigned int GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount);
		unsigned int GenerateIndicesBuffer(unsigned int* indices, unsigned int indicesCount);

		unsigned int DrawBuffers(VBO_Structure* bufferData);
		void SetCurrentModelMatrix(Matrix4f* matrix);
		void SetMaterial(Material* material);
		void SetTexture(Texture* texture);

		/* Shader API */		
		void CompileShaderObject(Shader* shader);
		void SetCurrentShader(Shader* shader);

		/* Texture API */
		void CreateTexture(Texture* texture);
		
		/* Debug functions */
		void SaveBitmap();

		Byte* GetFramebufferData();
		
	private:
		SR_Framebuffer _framebuffer;

		SR_Scanbuffer _scanbuffer;
		
		int _screenSizeWidth;
		int _screenSizeHeight;
		float _screenPixelDepth;

		SR_Bitmap _debugBitmap;

		Matrix4f* _modelMatrix;

		unsigned int _vboMemoryLimit;
		Vertex* _vboMemory;
		Vertex* _vboMemoryHead;

		unsigned int _iboMemoryLimit;
		unsigned int* _iboMemory;
		unsigned int* _iboMemoryHead;

		unsigned int _vboMemoryBufferTableLimit;
		MemoryBuffer* _vboMemoryBufferTable;
		unsigned int _vboMemoryBufferCount;

		unsigned int _iboMemoryBufferTableLimit;
		MemoryBuffer* _iboMemoryBufferTable;
		unsigned int _iboMemoryBufferCount;

	};
}

#endif