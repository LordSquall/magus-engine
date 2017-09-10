#include "renderer_windows_opengl.h"

namespace MagusEngine
{
	Renderer_Windows_OpenGL::Renderer_Windows_OpenGL()
	{
		_deviceContext = 0;
		_renderingContext = 0;
	}

	bool Renderer_Windows_OpenGL::InitialiseExtensions()
	{
		HDC deviceContext;
		PIXELFORMATDESCRIPTOR pixelFormat;
		int error;
		HGLRC renderContext;
		bool result;


		// Get the device context for this window.
		deviceContext = GetDC((HWND)_windowSystemHandle);
		if (!deviceContext)
		{
			return false;
		}

		// Set a temporary default pixel format.
		error = SetPixelFormat(deviceContext, 1, &pixelFormat);
		if (error != 1)
		{
			return false;
		}

		// Create a temporary rendering context.
		renderContext = wglCreateContext(deviceContext);
		if (!renderContext)
		{
			return false;
		}

		// Set the temporary rendering context as the current rendering context for this window.
		error = wglMakeCurrent(deviceContext, renderContext);
		if (error != 1)
		{
			return false;
		}

		// Initialize the OpenGL extensions needed for this application.  Note that a temporary rendering context was needed to do so.
		result = LoadExtensionList();
		if (!result)
		{
			return false;
		}

		// Release the temporary rendering context now that the extensions have been loaded.
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(renderContext);
		renderContext = NULL;

		// Release the device context for this window.
		ReleaseDC((HWND)_windowSystemHandle, deviceContext);
		deviceContext = 0;

		return true;
	}

	bool Renderer_Windows_OpenGL::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		int attributeListInt[19];
		int pixelFormat[1];
		unsigned int formatCount;
		int result;
		PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
		int attributeList[5];
		float fieldOfView, screenAspect;
		char *vendorString, *rendererString;


		// Get the device context for this window.
		_deviceContext = GetDC((HWND)_windowSystemHandle);
		if (!_deviceContext)
		{
			return false;
		}

		// Support for OpenGL rendering.
		attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
		attributeListInt[1] = TRUE;

		// Support for rendering to a window.
		attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
		attributeListInt[3] = TRUE;

		// Support for hardware acceleration.
		attributeListInt[4] = WGL_ACCELERATION_ARB;
		attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

		// Support for 24bit color.
		attributeListInt[6] = WGL_COLOR_BITS_ARB;
		attributeListInt[7] = 24;

		// Support for 24 bit depth buffer.
		attributeListInt[8] = WGL_DEPTH_BITS_ARB;
		attributeListInt[9] = 24;

		// Support for double buffer.
		attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
		attributeListInt[11] = TRUE;

		// Support for swapping front and back buffer.
		attributeListInt[12] = WGL_SWAP_METHOD_ARB;
		attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

		// Support for the RGBA pixel type.
		attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
		attributeListInt[15] = WGL_TYPE_RGBA_ARB;

		// Support for a 8 bit stencil buffer.
		attributeListInt[16] = WGL_STENCIL_BITS_ARB;
		attributeListInt[17] = 8;

		// Null terminate the attribute list.
		attributeListInt[18] = 0;

		// Query for a pixel format that fits the attributes we want.
		result = wglChoosePixelFormatARB(_deviceContext, attributeListInt, NULL, 1, pixelFormat, &formatCount);
		if (result != 1)
		{
			return false;
		}

		// If the video card/display can handle our desired pixel format then we set it as the current one.
		result = SetPixelFormat(_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
		if (result != 1)
		{
			return false;
		}

		// Set the 4.0 version of OpenGL in the attribute list.
		attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
		attributeList[1] = 4;
		attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
		attributeList[3] = 0;

		// Null terminate the attribute list.
		attributeList[4] = 0;

		// Create a OpenGL 4.0 rendering context.
		_renderingContext = wglCreateContextAttribsARB(_deviceContext, 0, attributeList);
		if (_renderingContext == NULL)
		{
			return false;
		}

		// Set the rendering context to active.
		result = wglMakeCurrent(_deviceContext, _renderingContext);
		if (result != 1)
		{
			return false;
		}


		CheckOpenGLError();

		// Initialize the world/model matrix to the identity matrix.
		BuildIdentityMatrix(_worldMatrix);

		// Set the field of view and screen aspect ratio.
		fieldOfView = 3.14159265358979323846f / 4.0f;
		screenAspect = (float)screenWidth / (float)screenHeight;

		// Build the perspective projection matrix.
		BuildPerspectiveFovLHMatrix(_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

		// Get the name of the video card.
		vendorString = (char*)glGetString(GL_VENDOR);
		rendererString = (char*)glGetString(GL_RENDERER);

		// Store the video card name in a class member variable so it can be retrieved later.
		strcpy_s(_videoCardDescription, vendorString);
		strcat_s(_videoCardDescription, " - ");
		strcat_s(_videoCardDescription, rendererString);

		// Turn on or off the vertical sync depending on the input bool value.
		if (vsync)
		{
			result = wglSwapIntervalEXT(1);
		}
		else
		{
			result = wglSwapIntervalEXT(0);
		}

		// Check if vsync was set correctly.
		if (result != 1)
		{
			return false;
		}

		return true;
	}

	void Renderer_Windows_OpenGL::Shutdown()
	{
		// Release the rendering context.
		if (_renderingContext)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_renderingContext);
			_renderingContext = 0;
		}

		// Release the device context.
		if (_deviceContext)
		{
			//ReleaseDC(hwnd, m_deviceContext);
			_deviceContext = 0;
		}

		return;
	}

	void Renderer_Windows_OpenGL::BeginScene(float red, float green, float blue, float alpha)
	{
		// Set the color to clear the screen to.
		glClearColor(red, green, blue, alpha);

		// Clear the screen and depth buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return;
	}

	void Renderer_Windows_OpenGL::EndScene()
	{
		// Present the back buffer to the screen since rendering is complete.
		SwapBuffers(_deviceContext);

		glFinish();

		PAINTSTRUCT ps;
		RECT r;

		HWND handle = WindowFromDC(_deviceContext);

		GetClientRect(handle, &r);

		if (r.bottom == 0) {

			return;
		}

		HDC hdc = BeginPaint(handle, &ps);

		Rectangle(hdc, 50, 50, 200, 100);

		EndPaint(handle, &ps);

		return;
	}

	void Renderer_Windows_OpenGL::DrawRectangle(int x, int y, int width, int height)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3f(1.0f, 0.0f, 00.0f);

		glBegin(GL_TRIANGLES);
		glVertex3f(-50.0f, 50.0f, 0.0f);
		glVertex3f(-50.0f, -50.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, 0.0f);
		glEnd();
	}
	
	void Renderer_Windows_OpenGL::CheckError()
	{
		CheckOpenGLError();
	}

	/* Data Loading API */
	unsigned int Renderer_Windows_OpenGL::GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount)
	{
		/* Create VBO */
		GLuint vbo;
		glGenBuffers(1, &vbo);

		/* Bind Buffer */
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		/* Upload data to GPU */
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);

		return vbo;
	}

	unsigned int Renderer_Windows_OpenGL::DrawBuffers(unsigned int bufferHandle)
	{
		/* Bind Buffer */
		glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		return 0;
	}

	/* Shader API */
	unsigned int Renderer_Windows_OpenGL::CreateVertexShader()
	{
		return glCreateShader(GL_VERTEX_SHADER);
	}

	unsigned int Renderer_Windows_OpenGL::CreateFragmentShader()
	{
		return glCreateShader(GL_FRAGMENT_SHADER);
	}

	void Renderer_Windows_OpenGL::SetShaderSource(unsigned int shaderHandle, const char** source)
	{
		glShaderSource(shaderHandle, 1, source, NULL);
	}

	void Renderer_Windows_OpenGL::CompileShader(unsigned int shaderHandle)
	{
		glCompileShader(shaderHandle);
	}
	
	unsigned int Renderer_Windows_OpenGL::CreateShaderProgram()
	{
		return glCreateProgram();
	}
	
	void Renderer_Windows_OpenGL::AttachShader(unsigned int programHandle, unsigned int shaderHandle)
	{
		glAttachShader(programHandle, shaderHandle);
	}
	
	void Renderer_Windows_OpenGL::BindAttribute(unsigned int programHandle, unsigned int index, const char* name)
	{
		glBindAttribLocation(programHandle, index, name);
	}
	
	void Renderer_Windows_OpenGL::LinkShaderProgram(unsigned int programHandle)
	{
		glLinkProgram(programHandle);
	}

	void Renderer_Windows_OpenGL::GetShaderLogLength(unsigned int shaderHandle, int* length)
	{
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, length);
	}

	void Renderer_Windows_OpenGL::GetShaderInfoLog(unsigned int shaderHandle, int size, char* logBuffer)
	{
		glGetShaderInfoLog(shaderHandle, size, NULL, logBuffer);
	}

	void Renderer_Windows_OpenGL::GetShaderProgramInfoLog(unsigned int programHandle, int size, char* logBuffer)
	{
		glGetProgramInfoLog(programHandle, size, NULL, logBuffer);
	}


	bool Renderer_Windows_OpenGL::LoadExtensionList()
	{
		// Load the OpenGL extensions that this application will be using.
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
		if (!wglChoosePixelFormatARB)
		{
			return false;
		}

		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		if (!wglCreateContextAttribsARB)
		{
			return false;
		}

		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
		if (!wglSwapIntervalEXT)
		{
			return false;
		}

		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		if (!glAttachShader)
		{
			return false;
		}

		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		if (!glBindBuffer)
		{
			return false;
		}

		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		if (!glBindVertexArray)
		{
			return false;
		}

		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		if (!glBufferData)
		{
			return false;
		}

		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		if (!glCompileShader)
		{
			return false;
		}

		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		if (!glCreateProgram)
		{
			return false;
		}

		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		if (!glCreateShader)
		{
			return false;
		}

		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
		if (!glDeleteBuffers)
		{
			return false;
		}

		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
		if (!glDeleteProgram)
		{
			return false;
		}

		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
		if (!glDeleteShader)
		{
			return false;
		}

		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
		if (!glDeleteVertexArrays)
		{
			return false;
		}

		glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
		if (!glDetachShader)
		{
			return false;
		}

		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		if (!glEnableVertexAttribArray)
		{
			return false;
		}

		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		if (!glGenBuffers)
		{
			return false;
		}

		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		if (!glGenVertexArrays)
		{
			return false;
		}

		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
		if (!glGetAttribLocation)
		{
			return false;
		}

		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
		if (!glGetProgramInfoLog)
		{
			return false;
		}

		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
		if (!glGetProgramiv)
		{
			return false;
		}

		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
		if (!glGetShaderInfoLog)
		{
			return false;
		}

		glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
		if (!glGetShaderiv)
		{
			return false;
		}

		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		if (!glLinkProgram)
		{
			return false;
		}

		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		if (!glShaderSource)
		{
			return false;
		}

		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
		if (!glUseProgram)
		{
			return false;
		}

		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		if (!glVertexAttribPointer)
		{
			return false;
		}

		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
		if (!glBindAttribLocation)
		{
			return false;
		}

		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		if (!glGetUniformLocation)
		{
			return false;
		}

		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
		if (!glUniformMatrix4fv)
		{
			return false;
		}

		glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
		if (!glActiveTexture)
		{
			return false;
		}

		glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
		if (!glUniform1i)
		{
			return false;
		}

		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
		if (!glGenerateMipmap)
		{
			return false;
		}

		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
		if (!glDisableVertexAttribArray)
		{
			return false;
		}

		glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
		if (!glUniform3fv)
		{
			return false;
		}

		glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
		if (!glUniform4fv)
		{
			return false;
		}


		return true;
	}

	void Renderer_Windows_OpenGL::GetWorldMatrix(float* matrix)
	{
		matrix[0] = _worldMatrix[0];
		matrix[1] = _worldMatrix[1];
		matrix[2] = _worldMatrix[2];
		matrix[3] = _worldMatrix[3];

		matrix[4] = _worldMatrix[4];
		matrix[5] = _worldMatrix[5];
		matrix[6] = _worldMatrix[6];
		matrix[7] = _worldMatrix[7];

		matrix[8] = _worldMatrix[8];
		matrix[9] = _worldMatrix[9];
		matrix[10] = _worldMatrix[10];
		matrix[11] = _worldMatrix[11];

		matrix[12] = _worldMatrix[12];
		matrix[13] = _worldMatrix[13];
		matrix[14] = _worldMatrix[14];
		matrix[15] = _worldMatrix[15];

		return;
	}

	void Renderer_Windows_OpenGL::GetProjectionMatrix(float* matrix)
	{
		matrix[0] = _projectionMatrix[0];
		matrix[1] = _projectionMatrix[1];
		matrix[2] = _projectionMatrix[2];
		matrix[3] = _projectionMatrix[3];

		matrix[4] = _projectionMatrix[4];
		matrix[5] = _projectionMatrix[5];
		matrix[6] = _projectionMatrix[6];
		matrix[7] = _projectionMatrix[7];

		matrix[8] = _projectionMatrix[8];
		matrix[9] = _projectionMatrix[9];
		matrix[10] = _projectionMatrix[10];
		matrix[11] = _projectionMatrix[11];

		matrix[12] = _projectionMatrix[12];
		matrix[13] = _projectionMatrix[13];
		matrix[14] = _projectionMatrix[14];
		matrix[15] = _projectionMatrix[15];

		return;
	}

	void Renderer_Windows_OpenGL::GetVideoCardInfo(char* cardName)
	{
		strcpy_s(cardName, 128, _videoCardDescription);
		return;
	}

	void Renderer_Windows_OpenGL::BuildIdentityMatrix(float* matrix)
	{
		matrix[0] = 1.0f;
		matrix[1] = 0.0f;
		matrix[2] = 0.0f;
		matrix[3] = 0.0f;

		matrix[4] = 0.0f;
		matrix[5] = 1.0f;
		matrix[6] = 0.0f;
		matrix[7] = 0.0f;

		matrix[8] = 0.0f;
		matrix[9] = 0.0f;
		matrix[10] = 1.0f;
		matrix[11] = 0.0f;

		matrix[12] = 0.0f;
		matrix[13] = 0.0f;
		matrix[14] = 0.0f;
		matrix[15] = 1.0f;

		return;
	}

	void Renderer_Windows_OpenGL::BuildPerspectiveFovLHMatrix(float* matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth)
	{
		matrix[0] = 1.0f / (screenAspect * (float)tan(fieldOfView * 0.5f));
		matrix[1] = 0.0f;
		matrix[2] = 0.0f;
		matrix[3] = 0.0f;

		matrix[4] = 0.0f;
		matrix[5] = 1.0f / (float)tan(fieldOfView * 0.5f);
		matrix[6] = 0.0f;
		matrix[7] = 0.0f;

		matrix[8] = 0.0f;
		matrix[9] = 0.0f;
		matrix[10] = screenDepth / (screenDepth - screenNear);
		matrix[11] = 1.0f;

		matrix[12] = 0.0f;
		matrix[13] = 0.0f;
		matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
		matrix[15] = 0.0f;

		return;
	}

	void Renderer_Windows_OpenGL::MatrixRotationY(float* matrix, float angle)
	{
		matrix[0] = cosf(angle);
		matrix[1] = 0.0f;
		matrix[2] = -sinf(angle);
		matrix[3] = 0.0f;

		matrix[4] = 0.0f;
		matrix[5] = 1.0f;
		matrix[6] = 0.0f;
		matrix[7] = 0.0f;

		matrix[8] = sinf(angle);
		matrix[9] = 0.0f;
		matrix[10] = cosf(angle);
		matrix[11] = 0.0f;

		matrix[12] = 0.0f;
		matrix[13] = 0.0f;
		matrix[14] = 0.0f;
		matrix[15] = 1.0f;

		return;
	}

	void Renderer_Windows_OpenGL::MatrixTranslation(float* matrix, float x, float y, float z)
	{
		matrix[0] = 1.0f;
		matrix[1] = 0.0f;
		matrix[2] = 0.0f;
		matrix[3] = 0.0f;

		matrix[4] = 0.0f;
		matrix[5] = 1.0f;
		matrix[6] = 0.0f;
		matrix[7] = 0.0f;

		matrix[8] = 0.0f;
		matrix[9] = 0.0f;
		matrix[10] = 1.0f;
		matrix[11] = 0.0f;

		matrix[12] = x;
		matrix[13] = y;
		matrix[14] = z;
		matrix[15] = 1.0f;

		return;
	}

	void Renderer_Windows_OpenGL::MatrixMultiply(float* result, float* matrix1, float* matrix2)
	{
		result[0] = (matrix1[0] * matrix2[0]) + (matrix1[1] * matrix2[4]) + (matrix1[2] * matrix2[8]) + (matrix1[3] * matrix2[12]);
		result[1] = (matrix1[0] * matrix2[1]) + (matrix1[1] * matrix2[5]) + (matrix1[2] * matrix2[9]) + (matrix1[3] * matrix2[13]);
		result[2] = (matrix1[0] * matrix2[2]) + (matrix1[1] * matrix2[6]) + (matrix1[2] * matrix2[10]) + (matrix1[3] * matrix2[14]);
		result[3] = (matrix1[0] * matrix2[3]) + (matrix1[1] * matrix2[7]) + (matrix1[2] * matrix2[11]) + (matrix1[3] * matrix2[15]);

		result[4] = (matrix1[4] * matrix2[0]) + (matrix1[5] * matrix2[4]) + (matrix1[6] * matrix2[8]) + (matrix1[7] * matrix2[12]);
		result[5] = (matrix1[4] * matrix2[1]) + (matrix1[5] * matrix2[5]) + (matrix1[6] * matrix2[9]) + (matrix1[7] * matrix2[13]);
		result[6] = (matrix1[4] * matrix2[2]) + (matrix1[5] * matrix2[6]) + (matrix1[6] * matrix2[10]) + (matrix1[7] * matrix2[14]);
		result[7] = (matrix1[4] * matrix2[3]) + (matrix1[5] * matrix2[7]) + (matrix1[6] * matrix2[11]) + (matrix1[7] * matrix2[15]);

		result[8] = (matrix1[8] * matrix2[0]) + (matrix1[9] * matrix2[4]) + (matrix1[10] * matrix2[8]) + (matrix1[11] * matrix2[12]);
		result[9] = (matrix1[8] * matrix2[1]) + (matrix1[9] * matrix2[5]) + (matrix1[10] * matrix2[9]) + (matrix1[11] * matrix2[13]);
		result[10] = (matrix1[8] * matrix2[2]) + (matrix1[9] * matrix2[6]) + (matrix1[10] * matrix2[10]) + (matrix1[11] * matrix2[14]);
		result[11] = (matrix1[8] * matrix2[3]) + (matrix1[9] * matrix2[7]) + (matrix1[10] * matrix2[11]) + (matrix1[11] * matrix2[15]);

		result[12] = (matrix1[12] * matrix2[0]) + (matrix1[13] * matrix2[4]) + (matrix1[14] * matrix2[8]) + (matrix1[15] * matrix2[12]);
		result[13] = (matrix1[12] * matrix2[1]) + (matrix1[13] * matrix2[5]) + (matrix1[14] * matrix2[9]) + (matrix1[15] * matrix2[13]);
		result[14] = (matrix1[12] * matrix2[2]) + (matrix1[13] * matrix2[6]) + (matrix1[14] * matrix2[10]) + (matrix1[15] * matrix2[14]);
		result[15] = (matrix1[12] * matrix2[3]) + (matrix1[13] * matrix2[7]) + (matrix1[14] * matrix2[11]) + (matrix1[15] * matrix2[15]);

		return;
	}

	void Renderer_Windows_OpenGL::CheckOpenGLError()
	{
		// check OpenGL error
		GLenum err = glGetError();

		if (err != GL_NO_ERROR)
		{
			switch (err)
			{
			case GL_INVALID_ENUM:
				printf("GL Error: Invalid Enum\n");
				break;
			case GL_INVALID_VALUE:
				printf("GL Error: Invalid Value\n");
				break;
			case GL_INVALID_OPERATION:
				printf("GL Error: Invalid Operation\n");
				break;
			case GL_STACK_OVERFLOW:
				printf("GL Error: Stack Overflow\n");
				break;
			case GL_STACK_UNDERFLOW:
				printf("GL Error: Stack Underflow\n");
				break;
			case GL_OUT_OF_MEMORY:
				printf("GL Error: Out of Memory\n");
				break;
			}
		}
	}
}