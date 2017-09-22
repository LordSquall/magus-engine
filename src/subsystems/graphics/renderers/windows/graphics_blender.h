#ifndef _GRAPHICS_BLENDER_H_
#define _GRAPHICS_BLENDER_H_

/* System Includes */

/* Local Project Includes */
#include "../software/renderer_software.h"
#include "../software/sr_bitmap.h"
#include "../windows/renderer_windows_opengl.h"
#include "../../../resources/resources.h"

namespace MagusEngine
{
	class Graphics_Blender
	{
	public:
		Graphics_Blender();

		bool Initialise(Renderer_Interface* hardwareRenderer, Renderer_Interface* softwareRenderer, int screenWidth, int screenHeight);

		bool Render(Matrix4f projection, Matrix4f viewMatrix);

	private:
		Renderer_Windows_OpenGL*	_hardwareRenderer;
		Renderer_Software*			_softwareRenderer;
		
		Texture						_texture;
		VBO_Structure				_vbo;

		SR_Bitmap					_bitmap;
	};
}

#endif