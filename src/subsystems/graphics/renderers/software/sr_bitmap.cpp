#include "sr_bitmap.h"

namespace MagusEngine
{
	
	SR_Bitmap::SR_Bitmap()
	{

	}

	void SR_Bitmap::Initialise(unsigned int width, unsigned int height)
	{
		_Width = width;
		_Height = height;
	}

	void SR_Bitmap::SetData()
	{

	}


	// Save the bitmap to a bmp file  
	void SR_Bitmap::Save(Byte* pBitmapBits,
		WORD wBitsPerPixel,
		const unsigned long& padding_size,
		LPCTSTR lpszFileName)
	{
		// Some basic bitmap parameters  
		unsigned long headers_size = sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER);

		unsigned long pixel_data_size = _Height * _Width * 32;

		BITMAPINFOHEADER bmpInfoHeader = { 0 };

		// Set the size  
		bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);

		// Bit count  
		bmpInfoHeader.biBitCount = wBitsPerPixel;

		// Use all colors  
		bmpInfoHeader.biClrImportant = 0;

		// Use as many colors according to bits per pixel  
		bmpInfoHeader.biClrUsed = 0;

		// Store as un Compressed  
		bmpInfoHeader.biCompression = 0;

		// Set the height in pixels  
		bmpInfoHeader.biHeight = _Height;

		// Width of the Image in pixels  
		bmpInfoHeader.biWidth = _Width;

		// Default number of planes  
		bmpInfoHeader.biPlanes = 1;

		// Calculate the image size in bytes  
		bmpInfoHeader.biSizeImage = pixel_data_size / 8;

		BITMAPFILEHEADER bfh = { 0 };

		// This value should be values of BM letters i.e 0x4D42  
		// 0x4D = M 0�42 = B storing in reverse order to match with endian  
		bfh.bfType = 0x4D42;
		//bfh.bfType = 'B'+('M' << 8); 

		// <<8 used to shift �M� to end  */  

		// Offset to the RGBQUAD  
		bfh.bfOffBits = headers_size;

		// Total size of image including size of headers  
		bfh.bfSize = headers_size + (pixel_data_size / 8);

		// Create the file in disk to write  
		HANDLE hFile = CreateFile(lpszFileName,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		// Return if error opening file  
		if (!hFile) return;

		DWORD dwWritten = 0;

		// Write the File header  
		WriteFile(hFile,
			&bfh,
			sizeof(bfh),
			&dwWritten,
			NULL);

		// Write the bitmap info header  
		WriteFile(hFile,
			&bmpInfoHeader,
			sizeof(bmpInfoHeader),
			&dwWritten,
			NULL);

		// Write the RGB Data  
		WriteFile(hFile,
			pBitmapBits,
			bmpInfoHeader.biSizeImage,
			&dwWritten,
			NULL);

		// Close the file handle  
		CloseHandle(hFile);
	}
}