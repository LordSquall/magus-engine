#ifndef _RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_

namespace MagusEngine
{
	class Renderer_Interface
	{
	public:
		virtual bool Initialise(void*, int, int, float, float, bool) = 0;
		virtual bool InitialiseExtensions() = 0;

		virtual void Shutdown() = 0;

		virtual void BeginScene(float, float, float, float) = 0;
		virtual void EndScene() = 0;

		virtual void CompileShader() = 0;

		virtual void CheckError() = 0;

		virtual void DrawRectangle(int x, int y, int width, int height) = 0;

	public:
		void* _windowSystemHandle;
	};
}

#endif