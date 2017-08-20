#include "graphicsclass.h"

namespace MagusEngine
{
	GraphicsClass::GraphicsClass()
	{
		m_renderer = 0;
	}

	bool GraphicsClass::Initialise(RendererClass* renderer)
	{
		m_renderer = renderer;
		return true;
	}


	void GraphicsClass::Shutdown()
	{
		m_renderer = 0;
		return;
	}

	bool GraphicsClass::Frame()
	{
		bool result;

		// Render the graphics scene.
		result = Render();
		if (!result)
		{
			return false;
		}
		return true;
	}


	bool GraphicsClass::Render()
	{
		// Clear the buffers to begin the scene.
		m_renderer->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

		// Present the rendered scene to the screen.
		m_renderer->EndScene();

		return true;
	}
}