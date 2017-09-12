#ifndef _RENDERER_SOFTWARE_H_
#define _RENDERER_SOFTWARE_H_

#include "../renderer_interface.h"
#include "../../../resources/shader.h"
#include "../../../resources/texture.h"
#include "sr_bitmap.h"
#include "sr_framebuffer.h"
#include "sr_scanbuffer.h"

typedef char Byte;

namespace MagusEngine
{
	class Renderer_Software : public Renderer_Interface
	{
	public:
		Renderer_Software();

		bool Initialise(void*, int, int, float, float, bool);
		bool InitialiseExtensions();

		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();		
		
		void DrawRectangle(int x, int y, int width, int height);

		void CheckError();

		/* Data Loading API */
		unsigned int GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount);
		unsigned int DrawBuffers(unsigned int bufferHandle);
		void SetCurrentModelMatrix(Matrix4f* matrix);
		void SetMaterial(Material* material);

		/* Shader API */		
		void CompileShaderObject(Shader* shader);
		void SetCurrentShader(Shader* shader);

		/* Texture API */
		void CreateTexture(Texture* texture);
		
		/* Debug functions */
		void SaveBitmap();
		
	private:
		SR_Framebuffer _framebuffer;

		SR_Scanbuffer _scanbuffer;
		
		int _screenSizeWidth;
		int _screenSizeHeight;
		float _screenPixelDepth;

		SR_Bitmap _debugBitmap;

	};
}

#endif