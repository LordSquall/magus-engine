/* includes */
#include "os_linux.h"

#include "../graphics/renderer_linux_opengl.h"

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


		// Initialize the width and height of the screen to zero.
		screenWidth = 800;
		screenHeight = 600;

		// Create the OpenGL Linux Specific object.
		_lowLevelRenderer = new Renderer_Linux_OpenGL();
		if (!_lowLevelRenderer)
		{
			return false;
		}

		// Create the window the application will be using and also initialize OpenGL.
		result = InitialiseX11(screenWidth, screenHeight);
		if (!result)
		{
			printf("Could not initialize the window.\n");
			return false;
		}
		
		_lowLevelRenderer->Initialise(this, screenWidth, screenHeight, 1000.0f, 0.1f, true);

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

		return;
	}
	
	void OS::Run()
	{
		bool done;

		done = false;
		
		
		printf("Entering Main Loop\n");
		
		while(!done)
		{
			XNextEvent(m_display, &m_xEvent);
        
			if(m_xEvent.type == Expose) {
					XGetWindowAttributes(m_display, m_window, &m_windowAttributes);
					//glViewport(0, 0, gwa.width, gwa.height);
					
					_lowLevelRenderer->BeginScene(1.0f, 1.0f, 0.0f, 1.0f);
					
					_lowLevelRenderer->EndScene();
			}
					
			else if(m_xEvent.type == KeyPress) {
				done = !done;
			}
		}		

		glXMakeCurrent(m_display, None, NULL);
		//glXDestroyContext(m_display, glc);
		XDestroyWindow(m_display, m_window);
		XCloseDisplay(m_display);
		exit(0);		
	
		return;
	}

	Renderer_Interface* OS::GetLowLevelRenderer()
	{
		return _lowLevelRenderer;
	}
	
	Display* OS::getDisplay()
	{
		return m_display;
	}
	
	Window OS::getWindow()
	{
		return m_window;
	}
	
	XVisualInfo* OS::getVisualInfo()
	{
		return m_visualInfo;
	}
		
	
	bool OS::InitialiseX11(int screenWidth, int screenHeight)
	{
		m_attributes[0] = GLX_RGBA;
		m_attributes[1] = GLX_DEPTH_SIZE;
		m_attributes[2] = 24;
		m_attributes[3] = GLX_DOUBLEBUFFER;
		m_attributes[4] = None;
		
		m_display = XOpenDisplay(NULL);

		if(m_display == NULL)
		{
			printf("Cannot connect to X Server \n");
			return false;
		}

		m_root = DefaultRootWindow(m_display);

		m_visualInfo = glXChooseVisual(m_display, 0, m_attributes);

		if(m_visualInfo == NULL)
		{
			printf("no appropriate visual found\n");
			return false;
		} else {
			printf("visual %p selected\n", (void*)m_visualInfo->visualid);
		}

		
		printf("Creating Color Map\n");
		m_colormap = XCreateColormap(m_display, m_root, m_visualInfo->visual, AllocNone);

		m_setWindowsAttributes.colormap = m_colormap;
		m_setWindowsAttributes.event_mask = ExposureMask | KeyPressMask;

		printf("Creating Window\n");
		m_window = XCreateWindow(m_display, m_root, 0, 0, 600,  600, 0, m_visualInfo->depth, InputOutput, m_visualInfo->visual, CWColormap | CWEventMask,  &m_setWindowsAttributes);

		
		printf("Mapping Window\n");
		XMapWindow(m_display, m_window);
		
		printf("Setting Window Name\n");
		XStoreName(m_display, m_window, "Magus Engine");

		
		return true;
		
	}

}