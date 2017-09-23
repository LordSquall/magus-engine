#ifndef _SR_STRUCTURES_H_
#define _SR_STRUCTURES_H_


/* System Includes */
#include <algorithm>
#include <memory>

#ifdef _WIN32
#include <Windows.h>
#endif

typedef char Byte;

namespace MagusEngine
{
	struct BITMAPFILEHEADERs
	{
		Byte bfType[2];
		Byte bfSize[4];
		Byte bfReserved1[2];
		Byte bfReserved2[2];
		Byte bfOffBits[2];
	};

	struct BITMAPINFOHEADERs
	{
		Byte biSize[4];
		Byte biWidth[4];
		Byte biHeight[4];
		Byte biPlanes[2];
		Byte biBitCount[2];
		Byte biCompression[4];
		Byte biSizeImage[4];
		Byte biXPelsPerMeter[4];
		Byte biYPelsPerMeter[4];
		Byte biClrUsed[4];
		Byte biClrImportant[4];
	};

	struct RGBQUADs
	{
		Byte rgbBlue[1];
		Byte rgbGreen[1];
		Byte rgbRed[1];
		Byte rgbReserved[1];
	};

	class SR_Bitmap
	{
	public:
		SR_Bitmap();

		void Initialise(unsigned int width, unsigned int height);

		void SetData();

#ifdef _WIN32
		void Save(Byte* pBitmapBits,
			WORD wBitsPerPixel,
			const unsigned long& padding_size,
			LPCTSTR lpszFileName);
#endif
		
	private:
		BITMAPFILEHEADERs	_FileHeader;
		BITMAPINFOHEADERs	_InfoHeader;
		RGBQUADs			_Colors;
		Byte*				_Data;

		unsigned int _Width;
		unsigned int _Height;
	};
}

#endif