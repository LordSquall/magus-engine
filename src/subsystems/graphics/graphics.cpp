#include "graphics.h"

#ifdef _WIN32
#include "renderers/windows/graphics_blender.h"
#include "renderers/windows/renderer_windows_opengl.h"
#else
#include "renderers/linux/graphics_blender.h"
#include "renderers/linux/renderer_linux_opengl.h"
#endif

#include "renderers/software/renderer_software_initialise_visitor.h"
#include "renderers/software/renderer_software_render_visitor.h"
#include "renderers/software/renderer_software.h"

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

		GLFWmonitor* monitor = NULL;

		if (config->fullscreen == true)
		{
			monitor = glfwGetPrimaryMonitor();
		}

		_window = glfwCreateWindow(_config->width, _config->height, _config->title, monitor, NULL);
		if (_window == NULL)
		{
			LOGERROR("Failed to create GLFW window");
			glfwTerminate();
			return false;
		}

		glfwSetKeyCallback(_window, &key_callback);
		glfwMakeContextCurrent(_window);
		glfwSwapInterval(0);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		/* Low level Hardware renderer, provided by the OS */
		_lowLevelHardwareRenderer = os->GetLowLevelRenderer();
		/* Once windows is ready we can initilase the low level renderer */
		_lowLevelHardwareRenderer->Initialise(this, _config->width, _config->height, 1000.0f, -1.0f, false);

		_lowLevelSoftwareRenderer = new Renderer_Software(_config);
		_lowLevelSoftwareRenderer->Initialise(os, _config->width, _config->height,  0.0f, 10000.0f, false);

		_2DProjectionMatrix.BuildOrthographic(0.0f, (float)config->width, (float)config->height, 0.0f, 1.0f, -1.0f);

		_3DProjectionMatrix.BuildPerspective(90.0f, (float)config->width / (float)config->height, 0.1f, 100.0f);

		_camera.Initialise(Vector3f(0.0f, 0.0f, -1000.0f), Vector3f(0.0f, 0.0f, 0.0f));

		return true;
	}


	bool Graphics::Shutdown()
	{
		_os = 0;
		_lowLevelHardwareRenderer = 0;
		_lowLevelSoftwareRenderer = 0;

		return true;
	}

	void Graphics::AddScene(SceneNode* sceneNode)
	{
		_rootScene.AddChild(sceneNode);
	}


	SceneNode* Graphics::GetRootSceneNode() { return &_rootScene; }

	bool Graphics::InitialiseFrame()
	{
		/* retrieve hardware path visitors */
		_hardwareInitialiseVisitor = _os->GetLowLevelRendererInitialisationVisitor();

		_hardwareInitialiseVisitor->Initialise(_lowLevelHardwareRenderer, _resources, &_camera,  &_2DProjectionMatrix, &_3DProjectionMatrix);

		_hardwareRenderVisitor = _os->GetLowLevelRendererRenderVisitor();

		_hardwareRenderVisitor->Initialise(_lowLevelHardwareRenderer, _resources, &_camera, &_2DProjectionMatrix, &_3DProjectionMatrix);

		/* Initialise software path visitors */
		_softwareInitialiseVisitor = new Renderer_Software_Initialise_Visitor((Renderer_Software*)_lowLevelSoftwareRenderer);

		_softwareInitialiseVisitor->Initialise(_lowLevelSoftwareRenderer, _resources, &_camera,  &_2DProjectionMatrix, &_3DProjectionMatrix);

		_softwareRenderVisitor = new Renderer_Software_Render_Visitor();
		
		_softwareRenderVisitor->Initialise(_lowLevelSoftwareRenderer, _resources, &_camera, &_2DProjectionMatrix, &_3DProjectionMatrix);

		_graphicsBlender = new Graphics_Blender();

		_graphicsBlender->Initialise(_lowLevelHardwareRenderer, _lowLevelSoftwareRenderer, _config->width, _config->height);

		_rootScene.Accept(_hardwareInitialiseVisitor);

		_rootScene.Accept(_softwareInitialiseVisitor);

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

		result = !(bool)glfwWindowShouldClose(_window);

		return result;
	}


	bool Graphics::Render()
	{
		if(_config->hardwareRendererEnabled == true)
		{
			/* Begin Hardware Renderer scene */
			_lowLevelHardwareRenderer->BeginScene(0.2f, 0.3f, 0.3f, 1.0f);

			/* Walk the scene using the hardware visitor */
			_rootScene.Accept(_hardwareRenderVisitor);

			/* End the Hardware Renderer scene */
			_lowLevelHardwareRenderer->EndScene();
			
		}

		if(_config->softwareRendererEnabled == true)
		{
		
			_lowLevelSoftwareRenderer->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);

			_rootScene.Accept(_softwareRenderVisitor);

			_lowLevelSoftwareRenderer->EndScene();
		}
		
		if(_config->gpuBlend == true)
		{
			_graphicsBlender->Render(_2DProjectionMatrix, *_camera.GetViewMatrix());
		}

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


	void Graphics::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, TRUE);
	}
}