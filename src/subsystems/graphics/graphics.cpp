#include "graphics.h"

namespace MagusEngine
{
	Graphics::Graphics()
	{
		_os = 0;
	}

	bool Graphics::Initialise(OS_Interface* os, Resources* resources, int maxSceneCount)
	{
		_os = os;
		_resources = resources;

		/* Low level Hardware renderer, provided by the OS */
		_lowLevelHardwareRenderer = os->GetLowLevelRenderer();
		_lowLevelHardwareRenderer->Initialise(os, 800, 600, 0, 10000, false);

		_lowLevelSoftwareRenderer = new Renderer_Software();
		_lowLevelSoftwareRenderer->Initialise(os, 800, 600, 0, 10000, false );

		//_softwareRendererThread = std::thread(&Graphics::SoftwareRender, this);

		_rootScene.Initialise("Root Node", maxSceneCount);
		
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

	bool Graphics::InitialiseFrame()
	{
		/* retrieve hardware path visitors */
		_hardwareInitialiseVisitor = _os->GetLowLevelRendererInitialisationVisitor();
		_hardwareRenderVisitor = _os->GetLowLevelRendererRenderVisitor();
		
		/* Initialise software path visitors */
		_softwareInitialiseVisitor = new Renderer_Software_Initialise_Visitor();
		_softwareInitialiseVisitor->Initialise(_lowLevelSoftwareRenderer, _resources);

		_softwareRenderVisitor = new Renderer_Software_Render_Visitor();
		_softwareRenderVisitor->Initialise(_lowLevelSoftwareRenderer, _resources);

		_rootScene.Accept(_hardwareInitialiseVisitor);

		return true;
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

		_rootScene.Accept(_hardwareRenderVisitor);

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