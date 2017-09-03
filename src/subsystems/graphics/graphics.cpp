#include "graphics.h"

namespace MagusEngine
{
	Graphics::Graphics()
	{
		_os = 0;
	}

	bool Graphics::Initialise(OS_Interface* os)
	{
		_os = os;

		/* Initialise Graphics Subsystems */

		/* Low level renderer */
		_lowLevelRenderer = os->GetLowLevelRenderer();

		/* Create basic test scene */
		/*m_rootNode = new SceneNodeClass();
		if (m_rootNode != NULL)
		{
			m_rootNode->Initialise();
		}*/

		return true;
	}


	void Graphics::Shutdown()
	{
		_os = 0;
		_lowLevelRenderer = 0;

		return;
	}

	bool Graphics::Frame()
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


	bool Graphics::Render()
	{
		// Clear the buffers to begin the scene.
		_lowLevelRenderer->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	
		// Present the rendered scene to the screen.
		_lowLevelRenderer->EndScene();

		return true;
	}
}