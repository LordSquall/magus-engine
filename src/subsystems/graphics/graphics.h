#ifndef _GRAPHICS_CLASS_H_
#define _GRAPHICS_CLASS_H_

/* Local Project Includes */
#include "../os/os_interface.h"
#include "renderer_interface.h"
#include "../scenemanagement/scenenode.h"

namespace MagusEngine
{
	class Graphics
	{
	public:
		Graphics();

		bool Initialise(OS_Interface* os);
		void Shutdown();
		bool Frame();

	private:
		bool Render();

	private:
		OS_Interface*		_os;
		Renderer_Interface* _lowLevelRenderer;
	};
}

#endif