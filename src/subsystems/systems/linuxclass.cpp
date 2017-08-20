/* includes */
#include "linuxclass.h"

#include "../graphics/opengllinuxclass.h"

namespace MagusEngine
{
	LinuxClass::LinuxClass()
	{
		m_renderer = 0;
		m_graphics = 0;
	}
	
	bool LinuxClass::Initialise()
	{
		int screenWidth, screenHeight;
		bool result;


		// Initialize the width and height of the screen to zero.
		screenWidth = 0;
		screenHeight = 0;

		// Create the OpenGL Linux Specific object.
		m_renderer = new OpenGLLinuxClass();
		if (!m_renderer)
		{
			return false;
		}

		// Create the window the application will be using and also initialize OpenGL.
		//result = InitialiseWindows(m_renderer, screenWidth, screenHeight);
		//if (!result)
		//{
		////	MessageBox(m_hwnd, "Could not initialize the window.", "Error", MB_OK);
		//	return false;
		//}

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
	
	void LinuxClass::Shutdown()
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

		return;
	}
	
	void LinuxClass::Run()
	{
		//MSG msg;
		bool done, result;


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

}