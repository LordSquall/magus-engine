#ifndef _RENDERER_CLASS_H_
#define _RENDERER_CLASS_H_

namespace MagusEngine
{
	class RendererClass
	{
	public:
		RendererClass();

		virtual bool Initialise(int, int, float, float, bool) = 0;
		virtual bool InitialiseExtensions() = 0;

		virtual void Shutdown() = 0;

		virtual void BeginScene(float, float, float, float) = 0;
		virtual void EndScene() = 0;

	public:
		void* m_windowSystemHandle;
	};
}

#endif