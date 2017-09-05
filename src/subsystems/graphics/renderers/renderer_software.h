#ifndef _RENDERER_SOFTWARE_H_
#define _RENDERER_SOFTWARE_H_

#include "..\renderer_interface.h"
#include "software\sr_bitmap.h"
#include "software\sr_framebuffer.h"

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

		void CompileShader();
		
		
		void DrawRectangle(int x, int y, int width, int height);

		void CheckError();

		/* Debug functions */
		void SaveBitmap();
		
	private:
		SR_Framebuffer _framebuffer;
		
		unsigned int _screenSizeWidth;
		unsigned int _screenSizeHeight;
		unsigned int _screenPixelDepth;

		SR_Bitmap _debugBitmap;

	};
}

#endif