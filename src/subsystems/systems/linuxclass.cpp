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
		screenWidth = 800;
		screenHeight = 600;

		// Create the OpenGL Linux Specific object.
		m_renderer = new OpenGLLinuxClass();
		if (!m_renderer)
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


		done = false;
		
		while(!done)
		{
			XNextEvent(m_display, &m_xEvent);
        
			if(m_xEvent.type == Expose) {
					//XGetWindowAttributes(m_display, m_window, &gwa);
					//glViewport(0, 0, gwa.width, gwa.height);
					
					m_renderer->BeginScene(1.0, 1.0, 0.0);
					
					m_renderer->EndScene();
					
					glXSwapBuffers(m_display, m_window);
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
	
	Display* LinuxClass::getDisplay(
	{
		return m_display;
	}
	
	Window* LinuxClass::getWindow()
	{
		return &m_window;
	}
	
	XVisualInfo* LinuxClass::getVisualInfo()
	{
		return m_visualInfo;
	}
		
	
	bool LinuxClass::InitialiseX11(int screenWidth, int screenHeight)
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

		m_colormap = XCreateColormap(m_display, m_root, m_visualInfo->visual, AllocNone);

		m_setWindowsAttributes.colormap = m_colormap;
		m_setWindowsAttributes.event_mask = ExposureMask | KeyPressMask;

		m_window = XCreateWindow(m_display, m_root, 0, 0, 600,  600, 0, m_visualInfo->depth, InputOutput, m_visualInfo->visual, CWColormap | CWEventMask,  &m_setWindowsAttributes);

		XMapWindow(m_display, m_window);
		XStoreName(m_display, m_window, "Magus Engine");

		
		return true;
		
	}

}