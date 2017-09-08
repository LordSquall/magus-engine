/* includes */
#include "os_windows.h"

#include "../graphics/renderers/renderer_windows_opengl.h"

namespace MagusEngine
{
	OS::OS()
	{
		_lowLevelRenderer = 0;
	}
	
	bool OS::Initialise(FrameworkConfig* config)
	{
		int screenWidth, screenHeight;
		bool result;

		/* Save reference to config */
		_config = config;

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
			MessageBox(_hwnd, "Could not initialize the window.", "Error", MB_OK);
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
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;
		bool result;

		// Get an external pointer to this object.	
		ApplicationHandle = this;

		// Get the instance of this application.
		_hinstance = GetModuleHandle(NULL);

		// Setup the windows class with default settings.
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = _hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = (LPCSTR)_config->title;
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the window class.
		RegisterClassEx(&wc);

		// Create a temporary window for the OpenGL extension setup.
		_hwnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)_config->title, (LPCSTR)_config->title, WS_POPUP,
			0, 0, 640, 480, NULL, NULL, _hinstance, NULL);
		if (_hwnd == NULL)
		{
			return false;
		}

		// Don't show the window.
		ShowWindow(_hwnd, SW_HIDE);

		// Initialize a temporary OpenGL window and load the OpenGL extensions.
		renderer->_windowSystemHandle = _hwnd;
		result = renderer->InitialiseExtensions();
		if (!result)
		{
			MessageBox(_hwnd, "Could not initialize the OpenGL extensions.", "Error", MB_OK);
			return false;
		}

		// Release the temporary window now that the extensions have been initialized.
		DestroyWindow(_hwnd);
		_hwnd = NULL;

		// Determine the resolution of the clients desktop screen.
		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);

		// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
		if (FULL_SCREEN)
		{
			// If full screen set the screen to maximum size of the users desktop and 32bit.
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Change the display settings to full screen.
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			// Set the position of the window to the top left corner.
			posX = posY = 0;
		}
		else
		{
			// If windowed then set it to 800x600 resolution.
			screenWidth = _config->width;
			screenHeight = _config->height;

			// Place the window in the middle of the screen.
			posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
		}

		// Create the window with the screen settings and get the handle to it.
		_hwnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)_config->title, (LPCSTR)_config->title, WS_POPUP,
			posX, posY, screenWidth, screenHeight, NULL, NULL, _hinstance, NULL);
		if (_hwnd == NULL)
		{
			return false;
		}

		// Initialize OpenGL now that the window has been created.
		renderer->_windowSystemHandle = _hwnd;
		result = renderer->Initialise(this, screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);
		if (!result)
		{
			MessageBox(_hwnd, "Could not initialize OpenGL, check if video card supports OpenGL 4.0.", "Error", MB_OK);
			return false;
		}

		// Bring the window up on the screen and set it as main focus.
		ShowWindow(_hwnd, SW_SHOW);
		SetForegroundWindow(_hwnd);
		SetFocus(_hwnd);

		// Hide the mouse cursor.
		ShowCursor(false);

		return true;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		switch (umessage)
		{
			// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
		}
	}

}