/* includes */
#include "os_windows.h"

#include "../graphics/renderers/windows/renderer_windows_opengl.h"

namespace MagusEngine
{
	OS::OS()
	{
		_lowLevelRenderer = 0;
	}
	
	bool OS::Initialise(FrameworkConfig* config, Resources* resources)
	{
		int screenWidth, screenHeight;
		bool result;

		/* Save reference to config */
		_config = config;
		_resources = resources;

		// Initialize the width and height of the screen to zero.
		screenWidth = 0;
		screenHeight = 0;


		// Create the OpenGL Windows Specific object.
		_lowLevelRenderer = new Renderer_Windows_OpenGL();
		if (!_lowLevelRenderer)
		{
			return false;
		}
		
		// Create the window the application will be using and also initialize OpenGL.
		result = InitialiseWindows(_lowLevelRenderer, screenWidth, screenHeight);
		if (!result)
		{
			//MessageBox(_hwnd, "Could not initialize the window.", "Error", MB_OK);
			return false;
		}
		
		return true;
	}
	
	void OS::Shutdown()
	{
		
		// Release the Low Level Renderer object.
		if (_lowLevelRenderer)
		{
			_lowLevelRenderer->Shutdown();
			delete _lowLevelRenderer;
			_lowLevelRenderer = 0;
		}

		// Shutdown the window.
		ShutdownWindows();

		return;
	}
	
	void OS::Run()
	{
		//MSG msg;
		//bool done, result;


		//// Initialize the message structure.
		//ZeroMemory(&msg, sizeof(MSG));
		//
		//// Loop until there is a quit message from the window or the user.
		//done = false;
		//while(!done)
		//{
		//	// Handle the windows messages.
		//	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//	{
		//		TranslateMessage(&msg);
		//		DispatchMessage(&msg);
		//	}

		//	// If windows signals to end the application then exit out.
		//	if(msg.message == WM_QUIT)
		//	{
		//		done = true;
		//	}
		//	else
		//	{
		//		// Otherwise do the frame processing.
		//		result = Frame();
		//		if(!result)
		//		{
		//			done = true;
		//		}
		//	}

		//}

		return;
	}

	Renderer_Interface* OS::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}

	Visitor* OS::GetLowLevelRendererInitialisationVisitor()
	{
		return new Renderer_Windows_Initialise_Visitor();
	}

	Visitor* OS::GetLowLevelRendererRenderVisitor()
	{
		return new Renderer_Windows_Render_Visitor();
	}

	bool OS::Frame()
	{
		//// Check if the user pressed escape and wants to exit the application.
		//if (m_input->IsKeyDown(VK_ESCAPE))
		//{
		//	return false;
		//}

		//// Do the frame processing for the graphics object.
		//result = m_graphics->Frame();
		//if (!result)
		//{
		//	return false;
		//}

		return true;
	}


	void OS::ShutdownWindows()
	{
		
	}

	LRESULT CALLBACK OS::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		switch (umsg)
		{
			// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			//m_input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
		//	m_input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
		}
	}

	bool OS::InitialiseWindows(Renderer_Interface* renderer, int& screenWidth, int& screenHeight)
	{
		//glfwInit();

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwSetErrorCallback(OS::ErrorCallback);

		//GLFWwindow* window = glfwCreateWindow(_config->width, _config->height, _config->title, NULL, NULL);
		//if (window == NULL)
		//{
		//	printf("Failed to create GLFW window");
		//	glfwTerminate();
		//	return -1;
		//}
		//glfwMakeContextCurrent(window);
		////glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		return true;
	}

	void OS::ErrorCallback(int error, const char* description)
	{
		printf(description);
	}
}