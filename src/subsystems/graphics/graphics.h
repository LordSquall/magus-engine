#ifndef _GRAPHICS_CLASS_H_
#define _GRAPHICS_CLASS_H_

/* Local Project Includes */
#include "rendererclass.h"
#include "../scenemanagement/scenenodeclass.h"

namespace MagusEngine
{
	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;

	class GraphicsClass
	{
	public:
		GraphicsClass();

		bool Initialise(RendererClass*);
		void Shutdown();
		bool Frame();

	private:
		bool Render();

	private:
		RendererClass* m_renderer;
	
		SceneNodeClass* m_rootNode;
	};
}

#endif