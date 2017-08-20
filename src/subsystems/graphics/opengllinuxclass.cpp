#include "opengllinuxclass.h"

namespace MagusEngine
{
	OpenGLLinuxClass::OpenGLLinuxClass()
	{

	}

	bool OpenGLLinuxClass::InitialiseExtensions()
	{
		return true;
	}

	bool OpenGLLinuxClass::Initialise(int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
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

		m_glContext = glXCreateContext(m_display, m_visualInfo, NULL, GL_TRUE);
		glXMakeCurrent(m_display, m_window, m_glContext);

		return true;
	}

	void OpenGLLinuxClass::Shutdown()
	{
		return;
	}

	void OpenGLLinuxClass::BeginScene(float red, float green, float blue, float alpha)
	{
		return;
	}


	void OpenGLLinuxClass::EndScene()
	{
		return;
	}
}