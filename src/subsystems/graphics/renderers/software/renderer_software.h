#ifndef _RENDERER_SOFTWARE_H_
#define _RENDERER_SOFTWARE_H_

#include "../renderer_interface.h"
#include "../../../resources/shader.h"
#include "../../../resources/texture.h"
#include "../../../../frameworkconfig.h"
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

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();		
		
		void DrawRectangle(int x, int y, int width, int height);

		void CheckError();

		/* Data Loading API */
		unsigned int GenerateVertexBuffer(Vertex* vertices, VBO_Structure* vbodata);
		unsigned int GenerateIndicesBuffer(unsigned int* indices, VBO_Structure* vbodata);
		unsigned int UpdateVertexBuffer(VBO_Structure* bufferData, Vertex* vertices, unsigned int vertexStart, unsigned int vertexCount);
		unsigned int UpdateIndicesBuffer(VBO_Structure* bufferData, unsigned int* indices, unsigned int indicesStart, unsigned int indicesCount);

		unsigned int DrawBuffers(VBO_Structure* bufferData, RenderDrawCallType type);
		void SetCurrentModelMatrix(Matrix4f* matrix);
		void SetCurrentProjectionMatrix(Matrix4f* matrix);
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

		/* Debug functions */
		void SaveBitmap();

		Byte* GetFramebufferData();
		
	private:
		SR_Framebuffer _framebuffer;

		SR_Scanbuffer _scanbuffer;
		
		int _screenSizeWidth;
		int _screenSizeHeight;
		float _screenPixelDepth;
		
		Matrix4f* _modelMatrix;
		Matrix4f* _projectionMatix;

		/* Memory Pools */
		unsigned int _vboMemoryPoolLimit;
		Vertex* _vboMemoryPool;
		unsigned int _vboMemoryPoolUsed;

		unsigned int _iboMemoryPoolLimit;
		unsigned int* _iboMemoryPool;
		unsigned int _iboMemoryPoolUsed;

		/* Memory Tables */
		unsigned int _vboMemoryTableLimit;
		MemoryBuffer* _vboMemoryTable;
		unsigned int _vboMemoryTableUsed;

		unsigned int _iboMemoryTableLimit;
		MemoryBuffer* _iboMemoryTable;
		unsigned int _iboMemoryTableUsed;

	};
}

#endif