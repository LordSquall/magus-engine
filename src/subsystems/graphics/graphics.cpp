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

		/* Low level Hardware renderer, provided by the OS */
		_lowLevelHardwareRenderer = os->GetLowLevelRenderer();
		_lowLevelHardwareRenderer->Initialise(os, 800, 600, 0, 10000, false);

		_lowLevelSoftwareRenderer = new Renderer_Software();
		_lowLevelSoftwareRenderer->Initialise(os, 800, 600, 0, 10000, false );

		_softwareRendererThread = std::thread(&Graphics::SoftwareRender, this);

		_GraphicsVisitor = new GraphicsVisitor();
		_GraphicsVisitor->Initialise(_lowLevelHardwareRenderer);

		_rootScene.Initialise("Root Node");
		
		return true;
	}


	void Graphics::Shutdown()
	{
		_os = 0;
		_lowLevelHardwareRenderer = 0;
		_lowLevelSoftwareRenderer = 0;

		return;
	}

	void Graphics::AddScene(SceneNode* sceneNode)
	{
		_rootScene.AddChild(sceneNode);
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
		/* Begin Hardware Renderer scene */
		_lowLevelHardwareRenderer->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

		_rootScene.Accept(_GraphicsVisitor);

		/* End the Hardware Renderer scene */
		_lowLevelHardwareRenderer->EndScene();
		
		return true;
	}

	bool Graphics::SoftwareRender()
	{
		while (true)
		{
			/* Begin the Software Renderer scene */
			_lowLevelSoftwareRenderer->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);

			/* End the Software Renderer scene*/
			_lowLevelSoftwareRenderer->EndScene();
		}

		return true;
	}
}