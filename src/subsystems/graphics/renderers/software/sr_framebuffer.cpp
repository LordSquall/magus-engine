#include "sr_framebuffer.h"

namespace MagusEngine
{
	SR_Framebuffer::SR_Framebuffer()
	{

	}

	bool SR_Framebuffer::Initialise(unsigned int width, unsigned int height, unsigned int depth)
	{
		_width = width;
		_height = height;

		_data = new Byte[width * height * 4];

		return true;
	}

	void SR_Framebuffer::Clear(float red, float green, float blue, float alpha)
	{
		unsigned int r = 0;
		unsigned int c = 0;

		Byte* bytePtr = &_data[0];

		/* Set the color of each pixel in the framebuffer */
		for (r = 0; r < _width; r++)
		{
			for (c = 0; c < _height; c++)
			{
				// BGRA format
				bytePtr[0]	= 255 * blue;
				bytePtr[1]	= 255 * green;
				bytePtr[2]	= 255 * red;
				bytePtr[3]	= 255 * alpha;

				bytePtr += 4;
			}
		}
	}

	void SR_Framebuffer::DrawPixel(int x, int y, float red, float green, float blue, float alpha)
	{
		unsigned int index = (x + y * _width) * 4;
		_data[index	   ] = 255 * blue;
		_data[index + 1] = 255 * green;
		_data[index + 2] = 255 * red;
		_data[index + 3] = 255 * alpha;
	}

	Byte* SR_Framebuffer::GetData()
	{
		return _data;
	}
}