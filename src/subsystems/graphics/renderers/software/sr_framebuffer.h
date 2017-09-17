#ifndef _SR_FRAMEBUFFER_H_
#define _SR_FRAMEBUFFER_H_

/* Local Project Includes */
#include "../../../resources/texture.h"

typedef char Byte;

namespace MagusEngine
{
	class SR_Framebuffer
	{
	public:
		SR_Framebuffer();

		bool Initialise(int width, int height, float depth);


		void Clear(float red, float green, float blue, float alpha);

		void DrawPixel(int x, int y, float red, float green, float blue, float alpha);

		void CopyPixel(int destx, int desty, float srcx, float srcy, Texture* texture);

		int GetWidth();
		int GetHeight();
		Byte* GetData();
		
	private:
		int _width;
		int _height;

		Byte* _data;
	};
}

#endif