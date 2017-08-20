#ifndef _SYSTEM_LINUX_CLASS_H_
#define _SYSTEM_LINUX_CLASS_H_

/* includes */
#include "systemclass.h"
#include "../graphics/rendererclass.h"
#include "../input/inputclass.h"

/* system includes */
#include <cstdio>

namespace MagusEngine
{
	class LinuxClass : public SystemClass
	{
	public:
		LinuxClass();
		
		bool Initialise();
		void Shutdown();
		void Run();
		
	private:
		RendererClass* m_renderer;
		InputClass* m_input;
		GraphicsClass* m_graphics;
	};
}

#endif