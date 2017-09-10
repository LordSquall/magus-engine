#include "graphics.h"

namespace MagusEngine
{
	Graphics::Graphics()
	{
		_os = 0;
	}

	bool Graphics::Initialise(OS_Interface* os, Resources* resources, FrameworkConfig* config, int maxSceneCount)
	{
		_os = os;
		_resources = resources;
		_config = config;

		//_softwareRendererThread = std::thread(&Graphics::SoftwareRender, this);

		_rootScene.Initialise("Root Node", maxSceneCount);

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwSetErrorCallback(OS::ErrorCallback);

		_window = glfwCreateWindow(_config->width, _config->height, _config->title, NULL, NULL);
		if (_window == NULL)
		{
			printf("Failed to create GLFW window");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(_window);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


		/* Low level Hardware renderer, provided by the OS */
		_lowLevelHardwareRenderer = os->GetLowLevelRenderer();
		/* Once windows is ready we can initilase the low level renderer */
		_lowLevelHardwareRenderer->Initialise(this, _config->width, _config->height, 1000.0f, -1.0f, false);

		_lowLevelSoftwareRenderer = new Renderer_Software();
		_lowLevelSoftwareRenderer->Initialise(os, 800, 600, 0, 10000, false);

		
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
		_hardwareInitialiseVisitor->Initialise(_lowLevelHardwareRenderer, _resources);
		_hardwareRenderVisitor = _os->GetLowLevelRendererRenderVisitor();
		_hardwareRenderVisitor->Initialise(_lowLevelHardwareRenderer, _resources);
		
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


		glfwSwapBuffers(_window);
		glfwPollEvents();

		return glfwWindowShouldClose(_window);
	}


	bool Graphics::Render()
	{
		/* Begin Hardware Renderer scene */
		_lowLevelHardwareRenderer->BeginScene(0.2f, 0.3f, 0.3f, 1.0f);

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