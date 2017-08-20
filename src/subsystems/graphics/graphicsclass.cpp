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

		/* Create basic test scene */
		m_rootNode = new SceneNodeClass();
		if (m_rootNode != NULL)
		{
			m_rootNode->Initialise();
		}

		return true;
	}


	void GraphicsClass::Shutdown()
	{
		if (m_rootNode != NULL)
		{
			m_rootNode->Shutdown();
			delete m_rootNode;
			m_rootNode = 0;
		}

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

		m_rootNode->Render(m_renderer);

		// Present the rendered scene to the screen.
		m_renderer->EndScene();

		return true;
	}
}