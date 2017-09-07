#ifndef _SR_FRAMEBUFFER_H_
#define _SR_FRAMEBUFFER_H_

typedef char Byte;

namespace MagusEngine
{
	class SR_Framebuffer
	{
	public:
		SR_Framebuffer();

		bool Initialise(unsigned int width, unsigned int height, unsigned int depth);


		void Clear(float red, float green, float blue, float alpha);

		void DrawPixel(int x, int y, float red, float green, float blue, float alpha);

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