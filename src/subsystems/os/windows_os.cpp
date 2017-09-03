/* includes */
#include "windowsclass.h"

#include "../graphics/openglwindowsclass.h"

namespace MagusEngine
{
	WindowsClass::WindowsClass()
	{
		m_renderer = 0;
		m_graphics = 0;
	}
	
	bool WindowsClass::Initialise()
	{
		int screenWidth, screenHeight;
		bool result;


		// Initialize the width and height of the screen to zero.
		screenWidth = 0;
		screenHeight = 0;

		// Create the OpenGL Windows Specific object.
		m_renderer = new OpenGLWindowsClass();
		if (!m_renderer)
		{
			return false;
		}

		// Create the window the application will be using and also initialize OpenGL.
		result = InitialiseWindows(m_renderer, screenWidth, screenHeight);
		if (!result)
		{
			MessageBox(m_hwnd, "Could not initialize the window.", "Error", MB_OK);
			return false;
		}

		// Create the input object.  This object will be used to handle reading the input from the user.
		m_input = new InputClass;
		if (!m_input)
		{
			return false;
		}

		// Initialize the input object.
		m_input->Initialise();

		// Create the graphics object.  This object will handle rendering all the graphics for this application.
		m_graphics = new GraphicsClass;
		if (!m_graphics)
		{
			return false;
		}

		// Initialize the graphics object.
		result = m_graphics->Initialise(m_renderer);
		if (!result)
		{
			return false;
		}

		return true;
	}
	
	void WindowsClass::Shutdown()
	{
		// Release the graphics object.
		if (m_graphics)
		{
			//m_graphics->Shutdown();
			delete m_graphics;
			m_graphics = 0;
		}

		// Release the input object.
		if (m_input)
		{
			delete m_input;
			m_input = 0;
		}

		// Release the OpenGL object.
		if (m_renderer)
		{
			m_renderer->Shutdown();
			delete m_renderer;
			m_renderer = 0;
		}

		// Shutdown the window.
		ShutdownWindows();

		return;
	}
	
	void WindowsClass::Run()
	{
		MSG msg;
		bool done, result;


		// Initialize the message structure.
		ZeroMemory(&msg, sizeof(MSG));
		
		// Loop until there is a quit message from the window or the user.
		done = false;
		while(!done)
		{
			// Handle the windows messages.
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// If windows signals to end the application then exit out.
			if(msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				// Otherwise do the frame processing.
				result = Frame();
				if(!result)
				{
					done = true;
				}
			}

		}

		return;
	}
	
	bool WindowsClass::Frame()
	{
		bool result;

		// Check if the user pressed escape and wants to exit the application.
		if (m_input->IsKeyDown(VK_ESCAPE))
		{
			return false;
		}

		// Do the frame processing for the graphics object.
		result = m_graphics->Frame();
		if (!result)
		{
			return false;
		}

		return true;
	}
	
	void WindowsClass::ShutdownWindows()
	{
		
	}

	LRESULT CALLBACK WindowsClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		switch (umsg)
		{
			// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			m_input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
		}
	}

	bool WindowsClass::InitialiseWindows(RendererClass* renderer, int& screenWidth, int& screenHeight)
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;
		bool result;

		// Get an external pointer to this object.	
		ApplicationHandle = this;

		// Get the instance of this application.
		m_hinstance = GetModuleHandle(NULL);

		// Give the application a name.
		m_applicationName = L"Engine";

		// Setup the windows class with default settings.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = (LPCSTR)m_applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the window class.
		RegisterClassEx(&wc);

		// Create a temporary window for the OpenGL extension setup.
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)m_applicationName, (LPCSTR)m_applicationName, WS_POPUP,
			0, 0, 640, 480, NULL, NULL, m_hinstance, NULL);
		if (m_hwnd == NULL)
		{
			return false;
		}

		// Don't show the window.
		ShowWindow(m_hwnd, SW_HIDE);

		// Initialize a temporary OpenGL window and load the OpenGL extensions.
		renderer->m_windowSystemHandle = m_hwnd;
		result = renderer->InitialiseExtensions();
		if (!result)
		{
			MessageBox(m_hwnd, "Could not initialize the OpenGL extensions.", "Error", MB_OK);
			return false;
		}

		// Release the temporary window now that the extensions have been initialized.
		DestroyWindow(m_hwnd);
		m_hwnd = NULL;

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
			screenWidth = 800;
			screenHeight = 600;

			// Place the window in the middle of the screen.
			posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
		}

		// Create the window with the screen settings and get the handle to it.
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)m_applicationName, (LPCSTR)m_applicationName, WS_POPUP,
			posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);
		if (m_hwnd == NULL)
		{
			return false;
		}

		// Initialize OpenGL now that the window has been created.
		renderer->m_windowSystemHandle = m_hwnd;
		result = renderer->Initialise(this, screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);
		if (!result)
		{
			MessageBox(m_hwnd, "Could not initialize OpenGL, check if video card supports OpenGL 4.0.", "Error", MB_OK);
			return false;
		}

		// Bring the window up on the screen and set it as main focus.
		ShowWindow(m_hwnd, SW_SHOW);
		SetForegroundWindow(m_hwnd);
		SetFocus(m_hwnd);

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